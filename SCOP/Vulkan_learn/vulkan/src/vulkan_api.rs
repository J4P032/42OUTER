use ash::vk::*; //for short calls of defines and enums
use sdl2::video::Window;

pub const VULKAN_VERSION: u32 = API_VERSION_1_3;
pub const MAX_FRAMES_IN_FLIGHT: u32 = 2;
pub const SWAP_CHAIN_IN_FORMAT: Format = Format::B8G8R8A8_SRGB;
pub const DEPTH_FORMAT: Format = Format::D32_SFLOAT;

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

	
}
