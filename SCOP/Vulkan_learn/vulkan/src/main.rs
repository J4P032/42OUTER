mod vulkan_api;

use ash::Entry;
use crate::vulkan_api::VulkanApi;

fn main() {
    // 1. Prueba de SDL2 (Reemplaza a SDL3 temporalmente)
    let _sdl_context = sdl2::init().expect("Error al inicializar SDL2");
    println!("✅ SDL2 detectado correctamente.");

    // 2. Prueba de Vulkan (Carga dinámica)
    unsafe {
        let entry = Entry::load().expect("No se encontró el SDK de Vulkan");
        if let Ok(Some(version)) = entry.try_enumerate_instance_version() {
            println!(
                "✅ Vulkan SDK detectado. Versión: {}.{}.{}",
                ash::vk::api_version_major(version),
                ash::vk::api_version_minor(version),
                ash::vk::api_version_patch(version)
            );
        }
    }
}
