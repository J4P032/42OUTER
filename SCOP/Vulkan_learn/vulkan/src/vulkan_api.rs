use ash::vk::*; //for short calls of defines and enums
use ash::khr::*;
use sdl2::video::Window;
use ash::Entry; //parte del volk

pub const VULKAN_VERSION: u32 = API_VERSION_1_3;
pub const MAX_FRAMES_IN_FLIGHT: usize = 2;
pub const SWAP_CHAIN_IN_FORMAT: Format = Format::B8G8R8A8_SRGB;
pub const DEPTH_FORMAT: Format = Format::D32_SFLOAT;

pub struct FrameResources{
	pub command_pool: 				Option<CommandPool>,
	pub command_buffer:				Option<CommandBuffer>,
	pub image_adquired_semaphore:	Option<Semaphore>,
}
pub struct VulkanApi{
	window:						Option<Window>,
	width:						u32,
	height:						u32,
	running:					bool,
	frame_index:				u32,
	next_signal_value:			u32,
	
	//vulkan core
	vulkan_instance:			Option<ash::Instance>,
	physical_device:			Option<PhysicalDevice>,
	device:						Option<ash::Device>,
	surface:					Option<SurfaceKHR>,
	vma_allocator:				Option<vk_mem::Allocator>,
	vulkan_entry:				Option<ash::Entry>,

	//queue related
	gfx_queue_fam_idx:			u32,
	gfx_queue:					Option<Queue>,

	//swapchain related
	swapchain:					Option<SwapchainKHR>,
	swapchain_images:			Vec<Image>,
	swapchain_image_views:		Vec<ImageView>,
	render_complete_semaphores:	Vec<Semaphore>,
	require_swapchain_recreate:	bool,
	swapchain_width:			u32,
	swapchain_height:			u32,
	
	depth_image:				Option<Image>,
	depth_image_view:			Option<ImageView>,
	depth_image_allocation:		Option<vk_mem::Allocation>,
	
	//graphics pipeline related
	pipeline_layout:			Option<PipelineLayout>,
	pipeline:					Option<Pipeline>,

	//shader resources
	vert_shader:				Option<ShaderModule>,
	frag_shader:				Option<ShaderModule>,
	
	//frame and synchronization resources
	timeline_semaphore:			Option<Semaphore>,
	frame_resources:			[FrameResources; MAX_FRAMES_IN_FLIGHT],		
}

impl FrameResources {
	fn new() -> Self {
		Self {
			command_pool: 				None,
			command_buffer:				None,
			image_adquired_semaphore:	None,
		}
	}
}

impl VulkanApi{
	pub fn new() -> Self{
		Self {
			window:						None,
			width: 						1280,
			height:						720,
			running:					false,
			frame_index:				0,
			next_signal_value:			(MAX_FRAMES_IN_FLIGHT + 1) as u32,
			vulkan_instance:			None,
			physical_device:			None,
			device:						None,
			surface:					None,
			vma_allocator:				None,
			vulkan_entry:				None,
			gfx_queue_fam_idx:			u32::MAX,
			gfx_queue:					None,
			swapchain:					None,
			swapchain_images:			Vec::<Image>::new(),
			swapchain_image_views:		Vec::<ImageView>::new(),
			render_complete_semaphores:	Vec::<Semaphore>::new(),
			require_swapchain_recreate:	false,
			swapchain_width:			0,
			swapchain_height:			0,
			depth_image:				None,
			depth_image_view:			None,
			depth_image_allocation:		None,
			pipeline_layout:			None,
			pipeline:					None,
			vert_shader:				None,
			frag_shader:				None,
			timeline_semaphore:			None,
			frame_resources:			std::array::from_fn(|_| FrameResources::new()), //from_fn obtain size of array and closure fills it with despate instances		
		}
	}
}

/*	######################################################### 
 	#################### INITIALIZATION #####################
	#########################################################	
 */
impl VulkanApi {
	fn show_error(&self, error_message: &str ) {
		sdl2::messagebox::show_simple_message_box(
			sdl2::messagebox::MessageBoxFlag::ERROR,
			"Error",
			error_message,
			&self.window);
	}

	pub fn initialize(&mut self) -> bool {
		if let Ok(sdl_init) = sdl2::init() {
			if let Ok(video_subsystem) = sdl_init.video() {
				match video_subsystem.window("Scop", self.width, self.height).position_centered().vulkan().build() {
					Ok(sdl_window) => { 
						self.window = Some(sdl_window);
					}
					Err(_) => {
						self.show_error("Error creating window");
						return false;
					} 
				}
			} else {
				self.show_error("Error creating window. No video");
				return false;
			}
		} else {
			self.show_error("Error creating window. No SDL2 init");
			return false;
		}

		if !self.initialize_vulkan() {
			return false;
		}
		true
	}
}

impl VulkanApi {
	fn initialize_vulkan(&mut self) -> bool {
		if !self.create_vulkan_instance() {
			self.show_error("Couldn't create a vulkan instance");
			return false;
		}

		if !self.create_surface() {
			self.show_error("Couldn't create window surface");
			return false;
		}
		
		let Some(device) = self.find_physical_device() else {
			self.show_error("Unable to find an appropriate physical device");
			return false;
		};
		self.physical_device = Some(device);

		if !self.find_graphics_queue(){
			self.show_error("Unable to find a compatible graphics queue");
			return false;
		}

		if !self.create_device(self.physical_device){
			self.show_error("Couldn't create the logical GPU device");
			return false;
		}
	

		true
	}

	fn create_vulkan_instance(&mut self) -> bool {
		let app_info;
		let inst_create_info;
		let vulkan_functions_table;
		let mut sdl_extensions_cstring = Vec::new();
		let mut sdl_extensions_pointers = Vec::new();
		
		/*volk is not necesary in Rust as it implements Entry, Instance and Device from 'ash'
		 The info is filled with .default() because sType can be unsafe so it fills for you */
		if let Ok(aux) = unsafe { Entry::load() } {
			let application_name = std::ffi::CStr::from_bytes_with_nul(b"Scop\0").unwrap(); //en Rust 1.75
			app_info = ApplicationInfo::default()
				.application_name(application_name) //in Rust 1.77 it would be .application_name(c"Scop") to end with \0
				.api_version(VULKAN_VERSION);
			vulkan_functions_table = aux;
		} else {
			return false;
		}

		/*vulkan_instance_extensions -> Result<Vec<&'static str>, String>
			enabled_extension_names(vector) needs Cstrings (ended with \0) BUT the
			vulkan struct because it is in C, needs pointers, so:
			1. we convert all the Vec<&'static str> that is a fat pointer into CStrings
				that adds the \0.
			2. Then we convert all of the elements into pointers.

			Rest of data is filled from the .default() method.	*/
		if let Some(window) = &self.window{
			match window.vulkan_instance_extensions(){
				Ok(sdl_extensions) => {
					for i in sdl_extensions {
						if let Ok(c_str) = std::ffi::CString::new(i) {
							sdl_extensions_cstring.push(c_str);	
						} else { 
							return false;
						}
					}
					for i in &sdl_extensions_cstring {
						sdl_extensions_pointers.push(i.as_ptr())
					}
					
					inst_create_info = InstanceCreateInfo::default()
					.application_info(&app_info)
					.enabled_extension_names(&sdl_extensions_pointers);
				}
				Err(_) => {
					return false;
				}
			}
		} else {
			return false;
		}

		
		if let Ok(aux) = unsafe { vulkan_functions_table.create_instance(&inst_create_info, None) } {
			self.vulkan_instance = Some(aux);
			self.vulkan_entry = Some(vulkan_functions_table);
		} else {
				return false;
		}
		true
	}

    /* vulkan_create_surface(&self, instance: VkInstance) -> Result<VkSurfaceKHR, String>
        problem is that it communicates with sdl2 that is internally a handle of usize. So have to 
        convert the window to usize with handle().as_raw(), and then go back to compose again from 
        that handle to the SurfaceKHR object 
        blocks let-else works as if let Some(...) but not make piramid of doom*/
    fn create_surface(&mut self) -> bool {
		let Some(v_instance) = &self.vulkan_instance else { return false; };
        let Some(win) = &self.window else { return false; };
        let Ok(aux) = win.vulkan_create_surface(v_instance.handle().as_raw() as usize) else { return false; };
		
        self.surface = Some(SurfaceKHR::from_raw(aux));
		true
	}

	
	/*enumerate_physical_devices(&self) -> VkResult<Vec<PhysicalDevice>> */
	fn find_physical_device(&mut self) -> Option<PhysicalDevice> {
		let mut device: PhysicalDevice = PhysicalDevice::null();
		
		//vulkan_instance:			Option<ash::Instance>,
		let Some(instance) = &self.vulkan_instance else { return None; };
		//let mut physical_devices = Vec::<PhysicalDevice>::new();
		let Ok(physical_devices) = (unsafe {instance.enumerate_physical_devices()}) else { return None;};
		if physical_devices.len() > 0 {
			device = physical_devices[0]; 
			for idevice in physical_devices {
				let props = unsafe { instance.get_physical_device_properties(idevice) }; //props = PhysicalDeviceProperties
				if props.device_type == PhysicalDeviceType::DISCRETE_GPU {
					device = idevice;
					break;
				}
			}
			return Some(device);
		}
		None
	}

	
	/*pub unsafe fn get_physical_device_queue_family_properties2(
    &self,
    physical_device: PhysicalDevice,
    out: &mut [QueueFamilyProperties2<'_>],) 
		in C++ all Vulkan Functions all load globally. In Rust no. So when we need KHR ones
		those are surface ones, so we need to create a loader from surface to access them.*/
	fn find_graphics_queue(&mut self) -> bool {
		let Some(instance) = &self.vulkan_instance else { return false; };
		let Some(device) = &self.physical_device else { return false;};
		let num_queue_families: usize;
		
		//need a portion of vector with number of queue_families that exist for function vector pusher.
		unsafe {num_queue_families = instance.get_physical_device_queue_family_properties2_len(*device) }; 
		let mut queue_props = vec![QueueFamilyProperties2::default(); num_queue_families];
		unsafe { instance.get_physical_device_queue_family_properties2(*device, &mut queue_props) };

		//no use of SurfaceKHR because is the data. We need the function, that is the Entry.
		let Some(khr_functions) = &self.vulkan_entry else { return false; };
		let Some(surface) = &self.surface else { return false; };
		let surface_loader = surface::Instance::new(khr_functions, instance);

		//get_physical_device_surface_support(&self, physical_device: PhysicalDevice, queue_family_index: u32, surface: SurfaceKHR,) -> VkResult<bool>
		for family_idx in 0..num_queue_families{
			let Ok(push_to_screen_flag) = (unsafe {surface_loader.get_physical_device_surface_support(*device, family_idx as u32, *surface)}) else { continue; }; 
			
			//dont do bitwise operations here in rust. Use contains(GRAPHICS)
			let props = &queue_props[family_idx];
			let draw_flag = props.queue_family_properties.queue_flags.contains(QueueFlags::GRAPHICS);

			if push_to_screen_flag && draw_flag == true {
				self.gfx_queue_fam_idx = family_idx as u32;
				return true;
			}
		}

		false
	}

	fn create_device(&mut self, physical_device: Option::<PhysicalDevice>) -> bool {
		if physical_device == None {
			return false;
		}
		let dev = physical_device.unwrap();
		let mut queue_priority: f32 = 1.0;
        let binding = [queue_priority]; //need to extend lifetime
		let gfx_queue_info = DeviceQueueCreateInfo::default()
			.queue_family_index(self.gfx_queue_fam_idx)
			.queue_priorities(&binding); //queueCount picks from this.

		// query suppoted features.
        //NOTA: INCLUIR 14 SI SE INSTALA
        let mut supported_features13 = PhysicalDeviceVulkan13Features::default();
		let mut supported_features12 = PhysicalDeviceVulkan12Features::default();
		let mut supported_features = PhysicalDeviceFeatures2::default()
			.push_next(&mut supported_features13)
			.push_next(&mut supported_features12); //order: features-12-13.
        let Some(instance) = &self.vulkan_instance else { return false;};
        unsafe { instance.get_physical_device_features2(dev, &mut supported_features) };

        // check if what we need is supported
        if supported_features13.dynamic_rendering == 0 || supported_features13.synchronization2 == 0 ||
            supported_features12.timeline_semaphore == 0{
                self.show_error("Physical device doesn't meet the feature requirements");
                return false;
        }

        // produce a separate features struct chain for device creation
        let mut features13 = PhysicalDeviceVulkan13Features::default()
            .synchronization2(true).dynamic_rendering(true);
        let mut features12 = PhysicalDeviceVulkan12Features::default()
            .timeline_semaphore(true);
        let mut features = PhysicalDeviceFeatures2::default()
            .push_next(&mut features13)
            .push_next(&mut features12);

        let gfxqueueinfo = [gfx_queue_info]; //lifetime
        let extensions = [swapchain::NAME.as_ptr()];
        let dev_create_info = DeviceCreateInfo::default()
            .push_next(&mut features)
            .queue_create_infos(&gfxqueueinfo)
            .enabled_extension_names(&extensions);

        let Ok(logical_device) = (unsafe { instance.create_device(dev, &dev_create_info, None)} ) else {
            return false;
        };
        self.device = Some(logical_device.clone());

        // grab the VkQueue object finally
        //gfx_queue:					Option<Queue>,
        let gfxqueue = unsafe { logical_device.get_device_queue(self.gfx_queue_fam_idx, 0)};
        if gfxqueue == Queue::null(){
            self.show_error("Couldn't get the graphics queue");
            return false;
        }
        
        self.gfx_queue = Some(gfxqueue);
		true
	}

}


/* // grab the VkQueue object finally
	vkGetDeviceQueue(device, gfxQueueFamIdx, 0, &gfxQueue);
	if (!gfxQueue)
	{
		showError("Couldn't get the graphics queue");
		return false;
	}
	return true; */