use ash::vk::*; //for short calls of defines and enums
use sdl2::video::Window;

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
	vulkan_instance:			Option<Instance>,
	physical_device:			Option<PhysicalDevice>,
	device:						Option<Device>,
	surface:					Option<SurfaceKHR>,
	vma_allocator:				Option<vk_mem::Allocator>,

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
		true
	}

}


/* bool initialize();
void shutdown();
void run();
 */
