#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

int main() {
    // 1. Configurar la información de la aplicación
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Test 42";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // 2. Configurar la creación de la instancia
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // 3. Crear la instancia de Vulkan
    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        std::cerr << "❌ Error: ¡No se pudo crear la instancia de Vulkan!" << std::endl;
        return 1;
    }
    std::cout << "✅ ¡Instancia de Vulkan creada correctamente!" << std::endl;

    // 4. Detectar tarjetas gráficas (Physical Devices) disponibles en el PC
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        std::cerr << "❌ Error: No se encontraron tarjetas gráficas compatibles con Vulkan." << std::endl;
        vkDestroyInstance(instance, nullptr);
        return 1;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    std::cout << "Conteo de GPUs detectadas: " << deviceCount << std::endl;
    for (const auto& device : devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        std::cout << " - GPU encontrada: " << deviceProperties.deviceName << std::endl;
    }

    // 5. Limpieza y destrucción
    vkDestroyInstance(instance, nullptr);
    std::cout << "✅ Instancia destruida limpiamente. ¡Entorno listo!" << std::endl;

    return 0;
}
