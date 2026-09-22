/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan_api.rs                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 20:36:28 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/22 17:15:57 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*To communicate with Vulkan SDK in C, we use ash crate. All information:
	https://docs.rs/ash/latest/ash/
	All depending on Instances, Entry (way of volk in Rust) and Device
	can be found at:
		https://docs.rs/ash/latest/ash/struct.Instance.html
		https://docs.rs/ash/latest/ash/struct.Entry.html
		https://docs.rs/ash/latest/ash/struct.Device.html

	As a norm. All funcions of KHR are separated from ash here (ash::khr):
		https://docs.rs/ash/latest/ash/khr/index.html
	BUT all structures or objects of KHR are separated here (ash:vk):
		https://docs.rs/ash/latest/ash/vk/index.html

	vma is present in Crate vk_mem:
		https://docs.rs/vk-mem/latest/vk_mem/
*/


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
	event_pump:					Option<sdl2::EventPump>,
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
	surface_loader:				Option<ash::khr::surface::Instance>,
	vma_allocator:				Option<vk_mem::Allocator>,
	vulkan_entry:				Option<ash::Entry>,

	//queue related
	gfx_queue_fam_idx:			u32,
	gfx_queue:					Option<Queue>,

	//swapchain related
	swapchain:					Option<SwapchainKHR>,
	swapchain_loader:			Option<ash::khr::swapchain::Device>,
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
			event_pump:					None,
			width: 						1280,
			height:						720,
			running:					false,
			frame_index:				0,
			next_signal_value:			(MAX_FRAMES_IN_FLIGHT + 1) as u32,
			vulkan_instance:			None,
			physical_device:			None,
			device:						None,
			surface:					None,
			surface_loader:				None,
			vma_allocator:				None,
			vulkan_entry:				None,
			gfx_queue_fam_idx:			u32::MAX,
			gfx_queue:					None,
			swapchain:					None,
			swapchain_loader:			None,
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

			let Ok(event_pump) = sdl_init.event_pump() else { 
				self.show_error("Error creating event pump");
				return false;
			};
			self.event_pump = Some(event_pump); //for run() check events.

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
	
		if !self.initialize_vma(){
			self.show_error("Unable to create Vulkan Memory Allocator");
			return false;
		}

		if !self.create_swapchain(self.width, self.height){
			self.show_error("Unable to create swapchain");
			return false;
		}

		if !self.create_shaders(){
			self.show_error("Error creating shader modules");
			return false;
		}

		let Some(pipeline) = self.create_graphics_pipeline() else {
			self.show_error("Unable to initialize the graphics pipeline");
			return false;
		};
		self.pipeline = Some(pipeline);

		if !self.create_sync_resources() {
			self.show_error("Couldn't create the sync related resources");
			return false;
		}

		if !self.create_command_buffers() {
			self.show_error("Couldn't create command buffer objects");
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

		self.surface_loader = Some(surface_loader);
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

	/*Not use ash crate, but instead, vk_mem one */
	fn initialize_vma(&mut self) -> bool{
		let Some(instance) = &self.vulkan_instance else { return false;};
		let Some(pdevice) = &self.physical_device else { return false;};
		let Some(device) = &self.device else { return false;};
		let mut vma_alloc_info = vk_mem::AllocatorCreateInfo::new(instance, device, *pdevice);
		vma_alloc_info.flags = vk_mem::AllocatorCreateFlags::BUFFER_DEVICE_ADDRESS;

		let Ok(allocator) = (unsafe{vk_mem::Allocator::new(vma_alloc_info)}) else { return false;}; 
		self.vma_allocator = Some(allocator);
		true
	}

	/*in C++ to find functions from KHR_Surface, que used Volk, but here we need
		to separate it. So we need a surface_loader variable that loads all those functions
		because they are not in basic ash instance. Same for swapchain creation*/
	fn create_swapchain(&mut self, width: u32, height: u32) -> bool{
		self.swapchain_width = width;
		self.swapchain_height = height;
		
		let Some(entry) = &self.vulkan_entry else { return false;};
		let Some(instance) = &self.vulkan_instance else { return false;};
		let Some(pdevice) = &self.physical_device else { return false;};
		let Some(device) = &self.device else { return false;};
		let Some(surface) = &self.surface else { return false;};
		
		//1.see if surface es good enough
		let surface_loader = ash::khr::surface::Instance::new(entry, instance);
		let Ok(surface_caps) = (unsafe {surface_loader.get_physical_device_surface_capabilities(*pdevice, *surface)}) else {
			self.show_error("Couldn't get the surface capabilities");
			return false;
		};
		
		//2. create swapchain
		let swapchain_create_info = ash::vk::SwapchainCreateInfoKHR::default()
			.surface(*surface)
			.min_image_count(surface_caps.min_image_count.max(3))
			.image_format(ash::vk::Format::B8G8R8A8_SRGB)
			.image_color_space(ash::vk::ColorSpaceKHR::SRGB_NONLINEAR)
			.image_extent(ash::vk::Extent2D {width: self.swapchain_width, height: self.swapchain_height })
			.image_array_layers(1)
			.image_usage(ash::vk::ImageUsageFlags::COLOR_ATTACHMENT)
			.pre_transform(ash::vk::SurfaceTransformFlagsKHR::IDENTITY)
			.composite_alpha(ash::vk::CompositeAlphaFlagsKHR::OPAQUE)
			.present_mode(ash::vk::PresentModeKHR::FIFO);
		
		
		let swapchain_loader = ash::khr::swapchain::Device::new(instance, device);
		let Ok(swapchain) = (unsafe {swapchain_loader.create_swapchain(&swapchain_create_info, None)}) else {
			self.show_error("Error creating swapchain");
			return false;
		};
		self.swapchain = Some(swapchain);
		self.swapchain_loader = Some(swapchain_loader.clone());
	
		//3.Prepare Images
		let Ok(swapchain_images) = (unsafe {swapchain_loader.get_swapchain_images(swapchain)}) else {
			return false;
		};
		self.swapchain_images = swapchain_images.clone();

		for image in swapchain_images {
			let img_view_info = ash::vk::ImageViewCreateInfo::default()
			.image(image)
			.view_type(ash::vk::ImageViewType::TYPE_2D)
			.format(ash::vk::Format::B8G8R8_SRGB)
			.subresource_range(ash::vk::ImageSubresourceRange {
				aspect_mask : ash::vk::ImageAspectFlags::COLOR,
				level_count : 1,
				layer_count : 1,
				..Default::default() //set base_mip_level and base_array_layer to 0
			});
			
			//swapchain_image_views:		Vec<ImageView>,
			let Ok(image_view) = (unsafe {device.create_image_view(&img_view_info, None)}) else {
				self.show_error("Error creating swapchain image view");
				return false;
			};
			self.swapchain_image_views.push(image_view);
		}
		
		//4.Semaphores.
		let num_images = self.swapchain_images.len();
		self.render_complete_semaphores.reserve(num_images);
		let mut semaphore_info = ash::vk::SemaphoreCreateInfo::default(); //MIRAR SI METERLO DENTRO DEL FOR
		for _ in 0..num_images{
			let Ok(semaphore) = (unsafe{device.create_semaphore(&semaphore_info, None)}) else {
				self.show_error("Error creating the render-complete semaphore");
				return false;
			}; 
			self.render_complete_semaphores.push(semaphore);	
		}

		//5.Create depth image
		let depth_create_info = ash::vk::ImageCreateInfo::default()
			.image_type(ash::vk::ImageType::TYPE_2D)
			.format(ash::vk::Format::D32_SFLOAT)
			.extent(ash::vk::Extent3D {
				width: self.swapchain_width,
				height: self.swapchain_height,
				depth: 1
			})
			.mip_levels(1)
			.array_layers(1)
			.samples(ash::vk::SampleCountFlags::TYPE_1)
			.tiling(ash::vk::ImageTiling::OPTIMAL)
			.usage(ash::vk::ImageUsageFlags::DEPTH_STENCIL_ATTACHMENT)
			.initial_layout(ash::vk::ImageLayout::UNDEFINED);

		let mut alloc_info = vk_mem::AllocationCreateInfo::default();
		alloc_info.flags = vk_mem::AllocationCreateFlags::DEDICATED_MEMORY;
		alloc_info.usage = vk_mem::MemoryUsage::Auto;

		
		let Some(allocator) = &self.vma_allocator else { return false; };
		let Ok((depth_image, depth_allocation)) = (unsafe {
			vk_mem::Alloc::create_image(allocator, &depth_create_info, &alloc_info)}) else {
			self.show_error("Error allocating depth image");
			return false;
		};

		let depth_img_view_info = ash::vk::ImageViewCreateInfo::default()
			.image(depth_image)
			.view_type(ash::vk::ImageViewType::TYPE_2D)
			.format(ash::vk::Format::D32_SFLOAT)
			.subresource_range(ash::vk::ImageSubresourceRange {
				aspect_mask: ash::vk::ImageAspectFlags::DEPTH,
				level_count: 1,
				layer_count: 1,
				..Default::default()
			});
		
		let Ok(image_depth_view) = (unsafe {device.create_image_view(&depth_img_view_info, None)}) else {
			self.show_error("Error creating depth image view");
			return false;
		};

		self.depth_image = Some(depth_image);
		self.depth_image_view = Some(image_depth_view);
		self.depth_image_allocation = Some(depth_allocation);
		true
	}

	/* Because I don't have SUDO in 42, we cannot compile in run time shaderc crate
		so I am made both shaders binary files with:

		/goinfre/jrollon-/scop_vulkan/1.3.296.0/x86_64/bin/glslc shader.vert -o vert.spv

		/goinfre/jrollon-/scop_vulkan/1.3.296.0/x86_64/bin/glslc shader.frag -o frag.spv
	
		we need to use read_spv because create_shader_module don't expect normal bytes
		&[u32] but 32bits 'words' because SPIR-V format is lined to 4 bytes. That function
		gives me the vec<u32> for me.
	*/
	fn create_shaders(&mut self) -> bool {
		//let shader_vert = "/shaders/vert.spv".to_string();
		//let shader_frag = "/shaders/frag.spv".to_string();
		let Ok(mut shader_vert) = std::fs::File::open("src/shaders/vert.spv") else {
			println!{"Cannot open vert shader file"};
			return false;
		};
		let Ok(shader_vert_vec) = ash::util::read_spv(&mut shader_vert) else {
			return false;
		};
		
		let Ok(mut shader_frag) = std::fs::File::open("src/shaders/frag.spv") else {
			println!{"Cannot open frag shader file"};
			return false;
		};
		let Ok(shader_frag_vec) = ash::util::read_spv(&mut shader_frag) else {
			return false;
		};
		
		let Some(device) = &self.device else { return false;};
		let mut vert_module_create_info = ash::vk::ShaderModuleCreateInfo::default();
		vert_module_create_info.code_size = shader_vert_vec.len() * std::mem::size_of::<u32>(); //size in bytes
		vert_module_create_info.p_code = &shader_vert_vec[0];
		
		let mut frag_module_create_info = ash::vk::ShaderModuleCreateInfo::default();
		frag_module_create_info.code_size = shader_frag_vec.len() * std::mem::size_of::<u32>();
		frag_module_create_info.p_code = &shader_frag_vec[0];
		
		let Ok(v_shader) = (unsafe {device.create_shader_module(&vert_module_create_info, None)}) else {return false;};
		let Ok(f_shader) = (unsafe {device.create_shader_module(&frag_module_create_info, None)}) else {return false;};
		
		self.vert_shader = Some(v_shader);
		self.frag_shader = Some(f_shader);

		true
	}

	fn create_graphics_pipeline(&mut self) -> Option<ash::vk::Pipeline> {
		//1. need to define a pipeline layout.
		let Some(device) = &self.device else { return None;};
		let pipeline_layout_info = ash::vk::PipelineLayoutCreateInfo{
			set_layout_count: 0,
			push_constant_range_count: 0,
			..Default::default()	
		};
		let Ok(pipeline_layout) = (unsafe {device.create_pipeline_layout(&pipeline_layout_info, None)}) else { 
			self.show_error("Unable to create the pipeline layout");
			return None;};
		self.pipeline_layout = Some(pipeline_layout);
		

		//2.  configure the shader stages struct.
		/* entry_point has to be ended by /0 but when we create a &str that don't end in \0
			so we can do aslo as put here in code:
			let entry_point: &str = "main\0"
			p_name: entry_point.as_ptr() as *const i8
			why i8? because it ask in vulkan i8, but &str is u8*/
		let Some(vert_shader) = &self.vert_shader else { return None;};
		let Some(frag_shader) = &self.frag_shader else { return None;};
		let entry_point = b"main\0"; //b".." is static memory. No heap like CString::new("main")
		
		let mut shader_stages: Vec::<ash::vk::PipelineShaderStageCreateInfo> = vec![
			ash::vk::PipelineShaderStageCreateInfo{
				stage:	ash::vk::ShaderStageFlags::VERTEX,
				module: *vert_shader,
				p_name: entry_point.as_ptr() as *const std::os::raw::c_char,
				..Default::default()
			},
			ash::vk::PipelineShaderStageCreateInfo{
				stage:	ash::vk::ShaderStageFlags::FRAGMENT,
				module: *frag_shader,
				p_name: entry_point.as_ptr() as *const std::os::raw::c_char,
				..Default::default()
			},
		];
		
		//3. vertex pulling, don't define vertex input details
		/* for Tutorial we comment the channel lines, but are necesary:
			GPU needs to know how many bytes ignore or advance to find next vertex in memory
			Channel -> we can send different data arrays from CPU. The number says which "plug"
						we are connected to. in Scop 0 is enough. Then link in Vertex Buffer to
						same channel.
			stride ->	size of vertex3
			input_rate -> freq GPU advance to next element. Scop: we are going to draw vertices
						ones by one so it should advance by each vertex VertexInputRate::VERTEX	 

			BE CAREFULL WITH LIFETIME AS binding_descriptions will last only here and 			
			*/
		let mut vert_input_info = ash::vk::PipelineVertexInputStateCreateInfo::default();
		/* 
		PARA SCOP!!!!!
		
		vert_input_info.vertex_binding_description_count = 1;
		let binding_descriptions = ash::vk::VertexInputBindingDescription::default()
			.binding(0)
			.stride(std::mem::size_of::<u32>() as u32)
			.input_rate(ash::vk::VertexInputRate::VERTEX);
		let attribute_descriptions = ash::vk::VertexInputAttributeDescription::default()
			.location(0) //shader.vert line: layout(location = 0) in vec3 inPosition; 
			.binding(0) //same as binding_descritions.binding
			.format(ash::vk::Format::R32G32B32_SFLOAT)
			.offset(0);
		vert_input_info.p_vertex_binding_descriptions = &binding_descriptions;
		vert_input_info.vertex_attribute_description_count = 1;
		vert_input_info.p_vertex_attribute_descriptions = &attribute_descriptions; 
		*/
		
		//4. input assembly, we'll be drawing triangle lists
		let input_assembly_info = ash::vk::PipelineInputAssemblyStateCreateInfo::default()
			.topology(ash::vk::PrimitiveTopology::TRIANGLE_LIST);
		
		//5. depth/stencil configuration
		let depth_stencil_info = ash::vk::PipelineDepthStencilStateCreateInfo::default()
			.depth_test_enable(true)
			.depth_write_enable(true)
			.depth_compare_op(ash::vk::CompareOp::LESS)
			.stencil_test_enable(false);
		
		//6. dynamic rendering allows to set this up...dynamically
		let viewport_info = ash::vk::PipelineViewportStateCreateInfo::default()
		.viewport_count(1)
		.scissor_count(1);
	
	// 6b. enable dynamic state
		//let dynamic_state = Vec::<ash::vk::DynamicState>::new();
		let dynamic_state = vec![ash::vk::DynamicState::VIEWPORT, ash::vk::DynamicState::SCISSOR];
		let dynamic_state_info = ash::vk::PipelineDynamicStateCreateInfo{
			dynamic_state_count: dynamic_state.len() as u32,
			p_dynamic_states: dynamic_state.as_ptr(),
			..Default::default()
		};

		//7. rasterizer settings
		let raster_info = ash::vk::PipelineRasterizationStateCreateInfo::default()
			.polygon_mode(ash::vk::PolygonMode::FILL) //fill triangle
			.cull_mode(ash::vk::CullModeFlags::BACK) //no draw backface
			.front_face(ash::vk::FrontFace::COUNTER_CLOCKWISE)
			.line_width(1.0);
		// No multisampling
		let multisample_info = ash::vk::PipelineMultisampleStateCreateInfo::default()
			.rasterization_samples(ash::vk::SampleCountFlags::TYPE_1);

		// 8.Alpha-blending (disabled for now), still need attachment info and write mask
		let attach_state = ash::vk::PipelineColorBlendAttachmentState::default()
			.blend_enable(false)
			.color_write_mask(ash::vk::ColorComponentFlags::RGBA);
		let blend_info = ash::vk::PipelineColorBlendStateCreateInfo{
			attachment_count: 1,
			p_attachments: &attach_state,
			..Default::default()
		};

		//9. structure required for dynamic rendering
		let mut render_info = ash::vk::PipelineRenderingCreateInfo{
			color_attachment_count: 1,
			p_color_attachment_formats: &SWAP_CHAIN_IN_FORMAT,
			depth_attachment_format: DEPTH_FORMAT,
			..Default::default()	
		};

		//10. Create the graphics pipeline
		/*Here we can see several & pointers. It is NOT a problem about removing the LOCAL
			vectors and structs to build this info, BECAUSE vulkan function device.create_graphics_pipelines
			will make a full NEW object inside the GPU with VRam so later all can be destroyed in
			CPU (this local funcion) */
		let mut pipeline_info = ash::vk::GraphicsPipelineCreateInfo{
			stage_count: shader_stages.len() as u32, 
			p_stages: shader_stages.as_ptr(),
			p_vertex_input_state: &vert_input_info,
			p_input_assembly_state: &input_assembly_info,
			p_viewport_state: &viewport_info,
			p_rasterization_state: &raster_info,
			p_multisample_state: &multisample_info,
			p_depth_stencil_state: &depth_stencil_info,
			p_color_blend_state: &blend_info,
			p_dynamic_state: &dynamic_state_info,
			layout: pipeline_layout,
			render_pass: ash::vk::RenderPass::null(),
			
			..Default::default()	
		};

		pipeline_info.push_next(&mut render_info);

		let Ok(pipes) = (unsafe {device.create_graphics_pipelines(ash::vk::PipelineCache::null(), &[pipeline_info], None)}) else {
			self.show_error("Error creating the pipeline");
			return None;
		};

		/*garantee vectors not destroyed until here to be assigned propertly.
			When we make internally the .as_ptr() in any vector, Rust compiler looks for 
			more use of those vectors lines below. If not find it it can trash the vectors
			so we would have bad pointer data even compiler let you compile. That way, putting
			drop, they are preserved until the end.. even they were going to be destroyed.*/
		drop(shader_stages);
		drop(dynamic_state);

		let Some(pipe) = pipes.into_iter().next() else { return None;};
		Some(pipe)
	}

	fn create_sync_resources(&mut self) -> bool {
		let Some(device) = &self.device else { return false;};
		
		let mut semaphore_type_info = ash::vk::SemaphoreTypeCreateInfo::default()
			.semaphore_type(ash::vk::SemaphoreType::TIMELINE)
			.initial_value(MAX_FRAMES_IN_FLIGHT as u64);
		
		let semaphore_info = ash::vk::SemaphoreCreateInfo::default();
		semaphore_info.push_next(&mut semaphore_type_info);

		let Ok(semaphore) = (unsafe {device.create_semaphore(&semaphore_info, None)}) else {
			self.show_error("Unable to create the timeline semaphore");
			return false;
		};
		self.timeline_semaphore = Some(semaphore);

		for frame in &mut self.frame_resources {
			let semaphore_info2 = ash::vk::SemaphoreCreateInfo::default();
			let Ok(semaphore2) = (unsafe {device.create_semaphore(&semaphore_info2, None)}) else {
				self.show_error("Error creating the per-frame image-acquire semaphore");
				return false;
			};
			frame.image_adquired_semaphore = Some(semaphore2);
		}
		true
	}

	fn create_command_buffers(&mut self) -> bool {
		let Some(device) = &self.device else { return false;};
				
		for frame in &mut self.frame_resources {
			let pool_info = ash::vk::CommandPoolCreateInfo::default()
				.queue_family_index(self.gfx_queue_fam_idx);
			
			let Ok(command_pool) = (unsafe{device.create_command_pool(&pool_info, None)}) else {
				self.show_error("Unable to create command buffer pool");
				return false;
			};
			frame.command_pool = Some(command_pool);

			let cmd_alloc_info = ash::vk::CommandBufferAllocateInfo{

				command_pool: command_pool,
				level: ash::vk::CommandBufferLevel::PRIMARY,
				command_buffer_count: 1,
				..Default::default()
			};
			let Ok(command_buffer) = (unsafe{device.allocate_command_buffers(&cmd_alloc_info)}) else {
				self.show_error("Unable to allocate command buffer");
				return false;
			};
			let Some(command_buffer_first) = command_buffer.first().copied() else { return false;};
			frame.command_buffer = Some(command_buffer_first);
		}
		true
	}

	
}



/*	######################################################### 
 	####################### RUNNING #########################
	#########################################################	
*/


/*	When we save event_pump in structure, that gives us right to ask about
	events changes. .poll_iter() search in operating system, change in the 
	hardware (move mouse, change window size...), so that changes state of 
	connection with system. That is the reason it needs to be &mut.
	doc about resized event: 
	https://docs.rs/sdl2/latest/sdl2/event/enum.WindowEvent.html
	*/
impl VulkanApi {
	fn run(&mut self) {
		let mut running = true;
		
		while running {
			let Some(event_pump) = &mut self.event_pump else { return; };
			for event in event_pump.poll_iter(){
				match event {
					sdl2::event::Event::Quit { .. } => { //{..} = ignore internal values
						running = false;
					}
					
					sdl2::event::Event::Window { win_event: sdl2::event::WindowEvent::Resized(w, h), .. } => { 
						self.width = w as u32;
						self.height = h as u32;
						break;	
					}

					_ => {}
				}
			}
			self.render();
		}
	}

	fn render(&mut self) {
		// first check if our swapchain is still valid
		let Some(device) = self.device.clone() else { return; };
		
		if self.require_swapchain_recreate {
			let Ok(()) = (unsafe{device.device_wait_idle()}) else { return; };
			self.destroy_swapchain();
			self.create_swapchain(self.width, self.height);
			self.require_swapchain_recreate = false;
		}
		
		//create 2 'drawers' to do the job
		let mut wait_value: u64;
		let frame_res_index: u32 = self.frame_index % MAX_FRAMES_IN_FLIGHT as u32;
		self.frame_index += 1;
		let signal_value: u64 = self.next_signal_value as u64;
		self.next_signal_value += 1;
		if signal_value >= MAX_FRAMES_IN_FLIGHT as u64 {
			wait_value = signal_value - MAX_FRAMES_IN_FLIGHT as u64;
		} else {
			wait_value = 0;
		}
		
		
		//timeline_semaphore:			Option<Semaphore>,
		let Some(timeline_semaphore) = &self.timeline_semaphore else { return; };
		let wait_info = ash::vk::SemaphoreWaitInfo {
			semaphore_count: 1,
			p_semaphores: timeline_semaphore,
			p_values: &wait_value,
			..Default::default()	
		};
		let Ok(wait_semaphores) = ( unsafe {device.wait_semaphores(&wait_info, u64::MAX)}) else { return;};
		
		// now its safe to start recording commands
		
		

	}

	fn destroy_swapchain(&mut self) {
		let Some(device) = &self.device else { return; };
		
		//destroy all imageviews
		for siv in &self.swapchain_image_views {
			unsafe {device.destroy_image_view(*siv, None);};
		}
		self.swapchain_image_views.clear();
		
		//destroy all render semaphores
		for rcs in &self.render_complete_semaphores {
			unsafe { device.destroy_semaphore(*rcs, None);};
		}
		self.render_complete_semaphores.clear();

		if let (Some(swapchain), Some(sloader)) = (&self.swapchain, &self.swapchain_loader) {
			unsafe { sloader.destroy_swapchain(*swapchain, None); };
			self.swapchain = None;
		}

		// destroy the depth buffer along with the swapchain
		if let (Some(div), Some(vmaa), Some(dia), Some(di)) = (
			&self.depth_image_view,
			&self.vma_allocator,
			&mut self.depth_image_allocation,
			&self.depth_image,)
		{		
			unsafe { device.destroy_image_view(*div, None);};
			unsafe { vmaa.destroy_image(*di, dia)}
			self.depth_image_view = None;
			self.depth_image = None;
		}
	}



}
