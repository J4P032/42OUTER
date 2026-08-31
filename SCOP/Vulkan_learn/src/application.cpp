#include "application.h"
#include "utils.h"

#ifdef USING_SDL2
	#include <SDL2/SDL.h> //para SDL2 instalado en 42.
#else
	#include <SDL3/SDL.h>
#endif

#define VOLK_IMPLEMENTATION
#include <volk.h>
#define VMA_IMPLEMENTATION
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#include <vma/vk_mem_alloc.h>




#include <iostream>

void Application::showError(const std::string &errorMessasge) const
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", errorMessasge.c_str(), window);
}

/*SDL es independiente de Vulkan.
Es una libreria que proporciona cosas que el SO hace (ventanas, Teclado/raton, eventos, entrada...)
La secuencia es: Programa -> SDL -> Vulkan -> dibuja en la ventana.
Se podria usar en OpenGl tambien.
SDL -> crea y gestiona la ventana
Vulkan -> se comunica con la GPU para dibujar en la ventana.
*/
bool Application::initialize()
{
	//con -DUSING_SDL2 en el compilador podemos definir si usamos SDL2 o SDL3
	//hay que cambiar las macros o llamada a funciones por que son diferentes.	
	#ifdef USING_SDL2
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow(
			"Vulkan SDL2",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE );
	#else
			//dice a SDL -> quiero activar el subsistema de video
			SDL_InitSubSystem(SDL_INIT_VIDEO);
			//SDL_WINDOW_VULKAN = la ventana sera usada con vulkan
			window = SDL_CreateWindow("Vulkan SDL3", width, height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE); 
	#endif
	
	if (!window)
	{
		showError("Error creating window");
		return false;
	}

	if (!initializeVulkan())
	{
		return false;
	}

	return true;
}

void Application::shutdown()
{
	// wait in case resources are in use
	vkDeviceWaitIdle(device);

	// frame / sync object cleanup
	if (timelineSemaphore)
	{
		vkDestroySemaphore(device, timelineSemaphore, nullptr);
	}
	for (auto &res : frameResources)
	{
		vkDestroySemaphore(device, res.imageAcquiredSemaphore, nullptr);
		vkDestroyCommandPool(device, res.commandPool, nullptr); // destroys buffers implicitly
	}

	// pipeline cleanup
	if (pipelineLayout)
	{
		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
	}
	if (pipeline)
	{
		vkDestroyPipeline(device, pipeline, nullptr);
	}

	// cleanup shaders
	if (vertShader)
	{
		vkDestroyShaderModule(device, vertShader, nullptr);
	}
	if (fragShader)
	{
		vkDestroyShaderModule(device, fragShader, nullptr);
	}

	// cleanup swapchain
	destroySwapchain();

	// VMA
	if (vmaAllocator)
	{
		vmaDestroyAllocator(vmaAllocator);
	}

	// cleanup Vulkan
	if (surface)
	{
		vkDestroySurfaceKHR(vulkanInstance, surface, nullptr);
	}
	if (device)
	{
		vkDestroyDevice(device, nullptr);
	}
	if (vulkanInstance)
	{
		vkDestroyInstance(vulkanInstance, nullptr);
	}
	volkFinalize();

	// cleanup SDL
	if (window)
	{
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

void Application::run()
{
	running = true;
	while (running)
	{
		SDL_Event event{ 0 };
		while (SDL_PollEvent(&event))
		{
			#ifdef USING_SDL2
				if (event.type == SDL_QUIT){
					running = false;
					break;
				}
				else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED){
					width = event.window.data1;
					height = event.window.data2;
					break;
				}
			#else
				if (event.type == SDL_EVENT_QUIT)
				{
					running = false;
					break;
				}
				else if (event.type == SDL_EVENT_WINDOW_RESIZED)
				{
					width = event.window.data1;
					height = event.window.data2;
					break;
				}
			#endif
		}
		render();
	}
}

bool Application::initializeVulkan()
{
	
	//saca el "VkInstance vulkanInstance" de Application
	//Datos de info e instancia para comunicarnos con Vulkan
	if (!createVulkanInstance())
	{
		showError("Couldn't create a vulkan instance");
		return false;
	}

	//saca el "VkSurfaceKHR surface" de Application
	//Surface = canvas para dibujar lo que le pidamos
	if (!createSurface())
	{
		showError("Couldn't create window surface");
		return false;
	}

	//saca el "VkPhysicalDevice physicalDevice" de Application
	//Encuentra GPU compatible con el formato de color que queramos.
	if (physicalDevice = findPhysicalDevice(); !physicalDevice)
	{
		showError("Unable to find an appropriate physical device");
		return false;
	}

	//saca el "gfxQueueFamIdx" de Application
	//es el índice de las queue (proceso que se puede hacer en la GPU) que Dibuje y Se muestre en pantalla
	//solo nos da información.
	if (!findGraphicsQueue())
	{
		showError("Unable to find a compatible graphics queue");
		return false;
	}

	//sacamos el device que almacenaremos en device de Application y el queue que almacenamos en gfxQueue de Application
	//Tenemos el índice del queue. Ahora buscamos las herramientas de updates de Vulkan para hacerlo
	//y abrimos la gpu para que nos de el handler para hacer peticiones a ese queue
	if (!createDevice(physicalDevice))
	{
		showError("Couldn't create the logical GPU device");
		return false;
	}

	//saca el vmaAllocator de Application
	//prepara la memoria de la GPU para ser reservada. NO LA RESERVA. Eso lo hará vmaCreateBuffer.
	if (!initializeVMA())
	{
		showError("Unable to create Vulkan Memory Allocator");
		return false;
	}

	//Configurará y creará el swapchain(formato de color y num de imagenes a volcar) de Vulkan más los
	//semáforos para controlar los procesos de creación de la imágenes.
	//estos semáforos controlan el FINAL del dibujo. La GPU termina de pintar el triángulo entonces activa este semáforo.
	//..Avisan a la pantalla que ya pueden mostrar la imagen 
	if (!createSwapchain(width, height))
	{
		showError("Unable to create swapchain");
		return false;
	}

	//carga los dos shaders VkShaderModule en Application
	if (!createShaders())
	{
		showError("Error creating shader modules");
		return false;
	}

	//Prepara el contrato de trabajo de lo que hacer el queue.
	if (pipeline = createGraphicsPipeline(); !pipeline)
	{
		showError("Unable to initialize the graphics pipeline");
		return false;
	}

	//configura la CPU y GPU para sincronizarse juntos y no haya 'atropellos'
	//Se usan semáforos pero estos controlan el INICIO del dibujo. El código pide una imagen...
	//...el swapchain tarda unos milisegundos en darla y activa este semáforo. La GPU ve verde y empieza a dibujar.
	if (!createSyncResources())
	{
		showError("Couldn't create the sync related resources");
		return false;
	}

	//Los trabajos no se hacen uno a uno, sino por un set de commandos.
	//Estos han de crearse en un buffer para soltarlo todo. Aquí se realiza el trabajo...
	//...de construcción de dicho buffer.
	if (!createCommandBuffers())
	{
		showError("Couldn't create command buffer objects");
		return false;
	}

	return true;
}

/*Vulkan está escrito en C. No es una instancia de una clase, sino un conjunto
de datos que hace que me pueda comunicar con la GPU. Cuando creo la instancia
se genera un HANDLE (manejador), que es una dirección de memoria a todos esos datos
(supongo que un struct masivo). Se nos da "el carnet de socio" de dicha GPU
Este HANDLE se meterá dentro de la variable que forma parte de la clase application
si se busca en los datos privados, ahí está*/
bool Application::createVulkanInstance()
{
	// Initialize Volk and load Vk function pointers
	/*por que no esta instalado el SDK, el llamar a una funcion de vulkan
	directamente como vkCreateInstance crasearia. Es por ello que tenemos
	que usar volk, que crea una tabla gigante de punteros a funciones y
	cada vez que hagamos la llamada a la funcion, volk por debajo interceptara
	esa llamada y localizara el puntero donde esta la direccion de memoria
	de la GPU donde se guarda dicha instruccion*/
	if (volkInitialize() != VK_SUCCESS)
	{
		showError("Error initializing Volk");
		return false;
	}

	/* Create the vulkan application instance. appInfo se meterá en
	VkInstanceCreateInfo. Esta primera más básica es para inicializar
	la segunda tiene todos los datos (2).
	*/
	VkApplicationInfo appInfo
	{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "My First Triangle",
		.apiVersion = VulkanVersion,
	};

	uint32_t instExtCount = 0;
	const char *const *extensions = nullptr; //puntero a array de punteros a cadenas de texto de solo lectura. Son nombres de extensiones ("VK_KHR_surface", "blabla")

	/*extensiones: caracteristica o funcionabilidad necesaria, que no forma parte del
	nucleo de Vulkan pero que son necesarias para que Vulkan pueda comunicarse
	con el gestor de ventanas y asi dibujar en pantalla. Sin ellas solo haria calculos
	*/ 
	#ifdef USING_SDL2
		// Código para SDL2: Pedimos primero cuántas hay, y luego rellenamos un vector
    	SDL_Vulkan_GetInstanceExtensions(window, &instExtCount, nullptr);
    	std::vector<const char*> sdlExtensions(instExtCount);
    	SDL_Vulkan_GetInstanceExtensions(window, &instExtCount, sdlExtensions.data());
    	extensions = sdlExtensions.data();
	#else
    	// Código original para SDL3
    	extensions = SDL_Vulkan_GetInstanceExtensions(&instExtCount);	
	#endif

	//evitamos el layer de comprobacion por que no tengo instalado el sdk de vulkan. cuando este se puede dejar.
	/* std::vector<const char *> requestedLayers
	{
		"VK_LAYER_KHRONOS_validation"
	}; */

	/*las capas de validación que desconectamos aqui, son capas extra para
	distinguir posibles errores, o pérdidas de memoria. Como no esta instalado el
	SDK, no sabe al compilar donde buscar el compilador*/
	std::vector<const char *> requestedLayers{};

	//(2) Esta es la segunda info con todos los datos.
	VkInstanceCreateInfo instCreateInfo
	{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appInfo,
		.enabledLayerCount = static_cast<uint32_t>(requestedLayers.size()),
		.ppEnabledLayerNames = requestedLayers.data(),
		.enabledExtensionCount = instExtCount,
		.ppEnabledExtensionNames = extensions
	};

	/*este es el que realmente crea la instancia. Al llamarse la función, como no
	teniamos instalado el SDK, volk se encargará de decir donde está dicha función y funcionará.
	metemos el primer info que era necesario y nullptr es el gestor de memoria(vkAllocationCallbacks).
	Al dejarlo con nullptr, dejamos que sea por defecto
	vulkanInstance es un puntero tipo VkInstance que es lo que me permitirá comunicarme
	con Vulkan */
	if (vkCreateInstance(&instCreateInfo, nullptr, &vulkanInstance) != VK_SUCCESS)
	{
		return false;
	}
	//volkLoadInstance. Una vez creada la instancia, llama a la GPU y pide
	//el resto de direcciones de memoria de las funciones restantes de Vulkan (buffers, texturas, shaders...)
	volkLoadInstance(vulkanInstance);
	return true;
}

/*La superficie es la parte de la ventana que se puede escribir. En lienzo. 
el window es el marco, que se puede arrastrar, agrandar, etc...
cada sistema operativo tiene su forma de hacer ventanas, y la función de Vulkan
para llamar a dichas ventanas es diferente en cada OS.
La Función SDL_Vulkan_CreateSurface dentro de SDL_vulkan.h se encarga de hacer
ese trabajo sucio y saca la función apropiada y la información del surface a 
escribir, almancenándolo en "surface" que es un puntero VkSurfaceKHR que está
dentro de la clase Application*/
bool Application::createSurface()
{
	#ifdef USING_SDL2
    	if (!SDL_Vulkan_CreateSurface(window, vulkanInstance, &surface))
	#else
    	if (!SDL_Vulkan_CreateSurface(window, vulkanInstance, nullptr, &surface))
	#endif
	{
		showError("Failed to create Vulkan surface from window");
		return false;
	}
	return true;
}

/*Encuentra las GPUs que haya instalada en el equipo compatible con Vulkan y elige la mejor.*/
VkPhysicalDevice Application::findPhysicalDevice()
{
	// 1. Cuantas GPUs hay. Al pasarle nullptr le decimos que no me metas los datos en ningun sitio.
	uint32_t physDeviceCount = 0;
	vkEnumeratePhysicalDevices(vulkanInstance, &physDeviceCount, nullptr);
	// 2. Crea un vector dinamico con ese tamaño y lo rellena de los HANDLES de las tarjetas
	std::vector<VkPhysicalDevice> physicalDevices(physDeviceCount);
	vkEnumeratePhysicalDevices(vulkanInstance, &physDeviceCount, physicalDevices.data());

	VkPhysicalDevice physicalDevice = nullptr;
	if (physDeviceCount)
	{
		// if you have issues, you can always just hardcode a GPU index while learning
		physicalDevice = physicalDevices[0]; // default to first GPU
		// look through list and see if a dGPU exists
		for (auto &pDev : physicalDevices)
		{
			VkPhysicalDeviceProperties props{};
			vkGetPhysicalDeviceProperties(pDev, &props);
			//DISCRETE es una GPU separada con su propia memoria VRAM
			if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				physicalDevice = pDev;
				break;
			}
		}
		//aqui está con una GPU dedicada o la primera que tuviera.
	}

	// ensure the desired swapchain format is supported
	/*La GPU tiene unos formatos de imagen de como se almacenan los colores RGBA
	El format, va a devolverle cuantos formatos es capaz de reconocer y cuantos bytes asigna
	a cada uno de los colores. Puede ser por ejemplo:
	VK_FORMAT_R8G8B8A8_UNORM (8bytes para RGBA), o VK_FORMAT_B8G8R8A8_SRGB (formato invertido BGRA)
	No todas las GPU ni monitores leen los colores en el mismo orden.
	La tarjeta devolverá todos los formatos que los metemos en un Vector dinámico.
	swapchain = Es el formato de color + evitar el buster (parpadeo) que contine
	2 ó 3 imágenes para intercambiarlas rápido.
	*/
	uint32_t formatCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);
	std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, surfaceFormats.data());

	bool formatSupported = false;
	for (const VkSurfaceFormatKHR &surfFormat : surfaceFormats)
	{
		/*swapchainFormat viene de Application y se ha elegido el formato: VK_FORMAT_B8G8R8A8_SRGB
		que es compatible con la mayoría de las tarjetas y monitores.*/
		if (surfFormat.format == swapchainFormat)
		{
			formatSupported = true;
			break;
		}
	}
	if (!formatSupported) //se sale si no es soportado.
	{
		showError("Requested swapchain format is not supported by the surface");
		return nullptr;
	}

	return physicalDevice;
}

/*La GPU es como una fábrica enorme con diferentes cintas transportadoras de trabajo
 (Cálculos matemáticos, Copia de datos de la RAM a la VRAM, Dibujar Triángulos, Enviar
 el dibujo final al monitor)
Esto es el canal de comunicación que se conoce como QUEUEs (cada una de esas "cintas" es un
queue).*/
bool Application::findGraphicsQueue()
{
	// eventually we'll have more complex queue lookup for presentation, etc
	// 1. Pillamos toda la familia de Queues que exiten en la Tarjeta elegida (physicalDevice). Cuantos Queues tienes?
	uint32_t queueFamCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, &queueFamCount, nullptr);
	// 2. Lo metenemos en un vector
	std::vector<VkQueueFamilyProperties2> queueFamProps(queueFamCount, { VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2, nullptr });
	vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, &queueFamCount, queueFamProps.data());

	/*Buscamos una queue que sepa dibujar y también sepa mostrarlo en pantalla, y guardamos ese
	índice para usarlo después en el Logical Device*/
	for (size_t currentFamIdx = 0; currentFamIdx < queueFamProps.size(); currentFamIdx++)
	{
		// ensure it has presentation support
		//Tiene conexión física con la ventana de SDL (surface)		
		VkBool32 hasPresentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, currentFamIdx, surface, &hasPresentSupport);

		//Sabe dibujar?
		const auto &props = queueFamProps[currentFamIdx];
		// ensure this is a GRAPHICS queue with presentation support
		/*queueFlags es un entero de 32bits en binario que cada 1 es un "lo hago" y un 0 "NO lo hago"
		Para no hacer flags booleanas de lo que puede hacer o no cada "ventana" (queue), hacemos este sistema
		y metemos todo en ese número.
		Bit1: Graficos VK_QUEUE_GRAPHICS_BIT = 0x00000001
		Bit2: Cálculo VK_QUEUE_COMPUTE_BIT = 0x00000002
		Bit3: Copia datos VK_QUEUE_TRANSFER_BIT = 0x00000004
		Si nos devuelve un Queue que tiene por ejemplo 00000010 es decir solo sabe computar, no me vale
		ya que buscamos dibujar, pero si es 00000111 este si que sabe dibujar aunque haga otras cosas
		asi que perfecto me sirve!
		*/
		if (props.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT && hasPresentSupport)
		{
			gfxQueueFamIdx = currentFamIdx;
			return true;
		}
	}
	return false;
}

/*Antes obtuvimos el índice de una queue (cinta transportadora de nuestra fábrica GPU)
que podía dibujar y mandar el dibujo a la pantalla. Ahora con esto vamos a tomar
el control de ella:
1. La Queue sabe hacer el trabajo. Es como un blueprint. PERO tiene herramientas base antiguas
   Para ser más eficientes, buscamos las herramientas modernas (features) en la GPU.
2. "abremos la fábrica", con vkCreateDevice y avisamos que vamos a usar ese queue
3. con vkGetDeviceQueue nos darán el handler (direccion de memoria) de dicho queue
4. (fuera de la función) con gfxQueue podré usar dicho handle para dibujar lo que quiera*/
bool Application::createDevice(VkPhysicalDevice physicalDevice)
{
	float queuePriority = 1.0f; //Le damos la prioridad máxima para procesar comandos a ese queue
	
	/*No se utiliza (estaba en el tutorial), pero se puede usar para 
	crear varias colas distintas como para gráficos, otra texturas, etc
	en paralelo. PERO NO AQUI. Debería estar en la clase xejemplo: 
	vector uint32_t gfxQueueFamIdx y vector uint32_t transferQueueFamInx*/
	std::vector<uint32_t> queueFamiles{ gfxQueueFamIdx };

	//vkCreateDevice lo necesita esta variable.
	VkDeviceQueueCreateInfo gfxQueueInfo
	{
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, //qué tipo de estructura es
		.queueFamilyIndex = gfxQueueFamIdx,//el índice del queue encontrado antes
		.queueCount = 1,//cuantos QUEUEs voy a abrir de el tipo que busco
		//la prioridad. Se pasa *float por .queueCount ya que asi se leeria mas rapido al pasarse por array. 
		//En caso de queueCount = 3, priorities[3] = {1.0f, 0.5f, 0.2f} se pasa el puntero a la primera y tienes todos.
		.pQueuePriorities = &queuePriority 
	};

	// query suppoted features
	/*Aqui buscamos las herramientas modernas. Primero se llama a Features2, que es Vulkan 1.1
	Como cada versión incluyó mas features (herramientas), para no perder la retrocompatibilidad
	se creó una lista enlazada (cadena de structuras pNext chain) con los datos de las nuevas
	herramientas.
	Al final le pasamos esas features a vkGetPhysicalDeviceFeatures2 que modificará los
	objetos en memoria y los rellenará con VK_TRUE o VK_FALSE al pasarle la & de esa primera
	estructura podrá seguir hasta la última 1.3 o 1.4.
	Comento la linea de 14 por que no está instalada en 42, pero aunque estuviera, no aporta
	grandes cambios y compilaría.*/
	//VkPhysicalDeviceVulkan14Features supportedFeatures14{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES, .pNext = nullptr };
	VkPhysicalDeviceVulkan13Features supportedFeatures13{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES, .pNext = nullptr };
	VkPhysicalDeviceVulkan12Features supportedFeatures12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, .pNext = &supportedFeatures13 };
	VkPhysicalDeviceFeatures2 supportedFeatures{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, .pNext = &supportedFeatures12 };
	vkGetPhysicalDeviceFeatures2(physicalDevice, &supportedFeatures);

	// check if what we need is supported
	if (!supportedFeatures13.dynamicRendering || !supportedFeatures13.synchronization2 ||
		!supportedFeatures12.timelineSemaphore)
	{
		showError("Physical device doesn't meet the feature requirements");
		return false;
	}

	// PASO 1. Buscamos las herramientas
	// produce a separate features struct chain for device creation
	/*La primera lista, era para preguntar las features existentes y las devolvia como una
	lista. Y esta segunda que creamos es la petición de lo que necesitamos de cada modulo de Vulkan
	*/
/* 	VkPhysicalDeviceVulkan14Features features14
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES,
		.pNext = nullptr,
	}; */
	VkPhysicalDeviceVulkan13Features features13
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
		.pNext = nullptr,
		.synchronization2 = VK_TRUE,
		.dynamicRendering = VK_TRUE,
	};
	VkPhysicalDeviceVulkan12Features features12
	{
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
		.pNext = &features13,
		.timelineSemaphore = VK_TRUE
	};
	VkPhysicalDeviceFeatures2 features{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, .pNext = &features12 };

	//VK_KHR_SWAPCHAIN_EXTENSION_NAME = le damos permiso a la GPU para que en el futuro use un swapchain
	/*la Estructura devCreateInfo es necesaria para la creación de vkCreateDevice*/
	const std::vector<const char *> deviceExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	VkDeviceCreateInfo devCreateInfo
	{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = &features,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &gfxQueueInfo,
		.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()),
		.ppEnabledExtensionNames = deviceExtensions.data(),
		.pEnabledFeatures = nullptr // features struct chain is set in pNext
	};

	//PASO 2. abrimos la fábrica.
	if (vkCreateDevice(physicalDevice, &devCreateInfo, nullptr, &device) != VK_SUCCESS)
	{
		return false;
	}

	// 3. PASO. Nos dan el handler de dicho queue y lo metemos en gfxQueue
	// grab the VkQueue object finally
	vkGetDeviceQueue(device, gfxQueueFamIdx, 0, &gfxQueue);
	if (!gfxQueue)
	{
		showError("Couldn't get the graphics queue");
		return false;
	}
	return true;
}

/*Esto es como un malloc. Reserva la memoria dentro de la GPU para almacenar
las posiciones de los vértices. PERO AQUI NO RESERVAMOS.. sino que le pedimos al sistema
que vamos a reservar. Es una INICIALIZACIÓN
Como todo en Vulkan necesita componer un info, para mandarle dicha estructura
a la funcion que aloca la memoria
los datos se obtienen mediante funcionesde Vulkan vkGetInstanceProcAddr, vkGetDeviceProcAddr
que como usamos Volk en el principio, este se encarga de enlazar y ejecutar */
bool Application::initializeVMA()
{
	VmaVulkanFunctions vmaFuncInfo{};
	
	// Mapeamos manualmente las funciones de carga dinámica desde Volk hacia VMA
	vmaFuncInfo.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
	vmaFuncInfo.vkGetDeviceProcAddr   = vkGetDeviceProcAddr;

	VmaAllocatorCreateInfo vmaAllocInfo
	{
		.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT,
		.physicalDevice = physicalDevice,
		.device = device,
		.pVulkanFunctions = &vmaFuncInfo,
		.instance = vulkanInstance,
		.vulkanApiVersion = VulkanVersion
	};

	// Borrada la llamada a vmaImportVulkanFunctionsFromVolk que daba error

	if (vmaCreateAllocator(&vmaAllocInfo, &vmaAllocator) != VK_SUCCESS)
	{
		return false;
	}
	return true;
}


/*Aquí se construye el almacén de imágenes para la pantalla. Pero todavia no se componen
solo SE PREPARAN para que estén disponibles.
1. Preguntamos a la pantalla de SDL (surface) qué limites tiene
2. Configuramos y creamos el Swapchain
3. Extraer las imágenes y crear las vistas con vkImageView
4. Semáforos de sincronización renderCompleteSemaphores
5. ZBuffering para profundidad 3D (no necesario para el triángulo) depthImageView
*/
bool Application::createSwapchain(uint32_t width, uint32_t height)
{
	swapchainWidth = width;
	swapchainHeight = height;

	/*1. NO es el tamaño del escritorio. Los límites son las capacidades del driver
	de la GPU y de la ventana que creó SDL. Son para el número de imágenes min y max acepta el sistema
	operativo para hacer intercambio de buffers. O transformaciones, por ejemplo
	rotaciones en móviles (girar pantalla) o no.*/
	VkSurfaceCapabilitiesKHR surfaceCaps{};
	if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCaps) != VK_SUCCESS)
	{
		showError("Couldn't get the surface capabilities");
		return false;
	}

	//2. Creamos el Swapchain.
	//rellenamos el info para meterlo en la funcion
	VkSwapchainCreateInfoKHR swapchainCreateInfo
	{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = surface,
		.minImageCount = surfaceCaps.minImageCount, //el num minimo de imagenes superpuestas para evitar el flick. Normalmente 2 o 3
		.imageFormat = swapchainFormat, //el formato del color. RGBa, BGRa, etc..
		.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR,
		.imageExtent{.width = swapchainWidth, .height = swapchainHeight },//tamaño de la ventana en píxeles
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = VK_PRESENT_MODE_FIFO_KHR //activa el V-Sync para evitar el tearing
	};

	if (vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &swapchain) != VK_SUCCESS)
	{
		showError("Error creating swapchain");
		return false;
	}

	//3. PREPARO las imagenes.
	/*como en minilibx teniamos que componer la imagen para luego pushearla
	a la pantalla y asi no generar parpadeos componiendo por píxeles.
	Pues esto es lo mismo, pero en vez de una imagen de minilibx son 2 o 3 (las
	que se hayan puesto en minImageCount), asi mientras se vuelca una
	la gpu está haciendo otra por detrás.*/
	// grab the swapchain images
	/*3a. Podriamos pensar que ya teniamos el número de imágenes a componer en
		.minImageCount.. pero ese es el MINIMO. El driver de la GPU y el SO puede darte más
		entonces sacamos el número que tiene, llamando con nullptr, y luego lo metemos en el vector*/
	uint32_t imageCount = 0;
	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, swapchainImages.data());
	swapchainImageViews.resize(imageCount);

	// create the swapchain image views
	for (size_t i = 0; i < swapchainImages.size(); ++i)
	{
		VkImageViewCreateInfo imgViewInfo
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = swapchainImages[i],
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = swapchainFormat,
			.subresourceRange
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.levelCount = 1,
				.layerCount = 1
			}
		};

		//aquí creo cada imagen
		if (vkCreateImageView(device, &imgViewInfo, nullptr, &swapchainImageViews[i]) != VK_SUCCESS)
		{
			showError("Error creating swapchain image view");
			return false;
		}
	}

	// semaphores used to signal render completion
	/* pillo el numero de imagenes que hay y creo un semáforo por cada uno de
	ellos metiéndolo en el vector renderCompleteSemaphores
	Solo crea los semáforos, pero no gestiona. Lo haremos después*/
	renderCompleteSemaphores.resize(swapchainImages.size());
	for (VkSemaphore &semaphore : renderCompleteSemaphores)
	{
		VkSemaphoreCreateInfo semaphoreInfo{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
		if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &semaphore) != VK_SUCCESS)
		{
			showError("Error creating the render-complete semaphore");
			return false;
		}
	}

	// create depth image
	/*Como se puede ver tiene otro vkCreateImageView. Esto es por que el 
	zbuffer es otra imagen igual pero en escala de grises (negro cercano, blanco lejano)
	*/
	VkImageCreateInfo depthCreateInfo
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = depthFormat,
		.extent{.width = swapchainWidth, .height = swapchainHeight, .depth = 1 },
		.mipLevels = 1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
	};

	VmaAllocationCreateInfo allocInfo
	{
		.flags = VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT,
		.usage = VMA_MEMORY_USAGE_AUTO
	};
	if (vmaCreateImage(vmaAllocator, &depthCreateInfo, &allocInfo, &depthImage, &depthImageAllocation, nullptr) != VK_SUCCESS)
	{
		showError("Error allocating depth image");
		return false;
	}

	VkImageViewCreateInfo depthImgViewInfo
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.image = depthImage,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = depthFormat,
		.subresourceRange{.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT, .levelCount = 1, .layerCount = 1}
	};
	//segundo create image view para el zbuffer
	if (vkCreateImageView(device, &depthImgViewInfo, nullptr, &depthImageView) != VK_SUCCESS)
	{
		showError("Error creating depth image view");
		return false;
	}

	return true;
}

void Application::destroySwapchain()
{
	//recorremos el vector y vamos eliminando cada dato.
	for (VkImageView swapchainImgView : swapchainImageViews)
	{
		vkDestroyImageView(device, swapchainImgView, nullptr);
	}
	swapchainImageViews.clear();

	// destroy render-complete ssemaphores
	for (VkSemaphore &semaphore : renderCompleteSemaphores)
	{
		vkDestroySemaphore(device, semaphore, nullptr);
	}
	renderCompleteSemaphores.clear();

	if (swapchain)
	{
		vkDestroySwapchainKHR(device, swapchain, nullptr);
		swapchain = nullptr;
	}

	// destroy the depth buffer along with the swapchain
	if (depthImageView)
	{
		vkDestroyImageView(device, depthImageView, nullptr);
		vmaDestroyImage(vmaAllocator, depthImage, depthImageAllocation);
		depthImageView = nullptr;
	}
}

VkShaderModule Application::createShaderModule(const std::string &fileName, shaderc_shader_kind kind) const
{
	// read shader file from disk
	const std::string shaderPath = "src/shaders/" + fileName;
	const std::string src = readTextFile(shaderPath); //todo el código con '\n' incluido en 'src'
	if (src.empty())
	{
		showError("Specified shader file doesn't exist: " + shaderPath);
		return nullptr;
	}

	// compile the shader to SPIR-V
	/* Los shaders son código que representa 3D en la pantalla. Pueden calcular reflejos,
	bump, etc...
	SPIR-V es código binario que entiende Vulkan. Los Shaders están en código, lenguaje
	GLSL, que viene de OpenGL y utiliza Vulkan.
	La librería incluida en shaderc/shaderc.hpp es la que se encarga de convertirlo a
	SPIR-V*/
	std::cout << "Compiling shader: " << shaderPath << std::endl;
	shaderc::Compiler compiler;
	shaderc::CompileOptions opts;
	opts.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
	opts.SetTargetSpirv(shaderc_spirv_version_1_6);
	opts.SetOptimizationLevel(shaderc_optimization_level_performance);
	shaderc::CompilationResult result = compiler.CompileGlslToSpv(src, kind, fileName.c_str(), opts);

	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
	{
		std::cerr << "Shader Compilation Error: " << result.GetErrorMessage() << std::endl;
		return nullptr;
	}
	//copiamos ese result que son en binario enorme, entero al vector spv.
	std::vector<uint32_t> spv = { result.cbegin(), result.cend() };

	// pass spir-v to vulkan and create shader-module
	VkShaderModuleCreateInfo moduleCreateInfo
	{
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.codeSize = spv.size() * sizeof(uint32_t),
		.pCode = spv.data() //vulkan esta en C y no entiende vector de c++ por ello con .data() le pasamos el puntero al primer elemento.
	};
	VkShaderModule shaderModule = nullptr;
	if (vkCreateShaderModule(device, &moduleCreateInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		showError("Error creating shader module");
		return nullptr;
	}
	return shaderModule;
}

//Carga los shaders que están en /shaders/ para ser luego usados.
//Transforma el código GLSL(openGL shading Language) en codigo binario para ser leido por Vulkan.
bool Application::createShaders()
{
	// create the shader modules that we'll need for the graphics pipeline
	if (vertShader = createShaderModule("shader.vert", shaderc_vertex_shader); !vertShader)
	{
		return false;
	}
	if (fragShader = createShaderModule("shader.frag", shaderc_fragment_shader); !fragShader)
	{
		return false;
	}
	return true;
}

/*Es la cadena de montaje de la GPU
1. vkCreatePipelineLayout -> Configura el Layout, que es el espacio reservado
	para saber si al shader le vamos a pasar variables globales cambiantes (como matrices
	de rotación para SCOP).
	//setLayoutCount = 0, por que no tiene ninguna variable exterior.
	El triángulo no variará por interacción del usuario 
2.	VkPipelineShaderStageCreateInfo -> Carga Shaders
3.	VkPipelineVertexInputStateCreateInfo -> Define como leer los vértices de la memoria
4.	VkPipelineInputAssemblyStateCreateInfo -> Dice a la GPU como interpretar los puntos
5.	VkPipelineDepthStencilStateCreateInfo -> Activa el ZBuffer
6.	VkPipelineViewportStateCreateInfo -> Define el tamaño del lienzo
7.	VkPipelineRasterizationStateCreateInfo -> Convierte las lineas matemáticas en pixeles. Como se pinta la geometría
8.	VkPipelineColorBlendStateCreateInfo -> Mezcla de los colores
9. 	VkPipelineRenderingCreateInfo -> Gracias a Vulkan1.3 se puede usar dynamic rendering
10. VkGraphicsPipelineCreateInfo -> El contrato final.
*/
VkPipeline Application::createGraphicsPipeline()
{
	
	//1. need to define a pipeline layout. 0 no matriz de rotación.
	//el cambio de forma por reajuste de ventana viene en el paso 6.
	VkPipelineLayoutCreateInfo pipelineLayoutInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.setLayoutCount = 0, 
		.pushConstantRangeCount = 0
	};
	if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
	{
		showError("Unable to create the pipeline layout");
		return nullptr;
	}

	//2.  configure the shader stages struct. Carga los dos shaders.
	const char *entryPoint = "main"; //le dice a la GPU que la función para empezar a trabajar se llama 'main' (la del shader en codigo GLSL)
	std::vector<VkPipelineShaderStageCreateInfo> shaderStages
	{
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage = VK_SHADER_STAGE_VERTEX_BIT,
			.module = vertShader,
			.pName = entryPoint
		},
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
			.module = fragShader,
			.pName = entryPoint
		}
	};

	//3. vertex pulling, don't define vertex input details
	//Está vacia por que los vértices están metidos en el shader.
	/*COMENTADO ESTA LA INFO DEL SCOP. Es el mapa de carreteras para que la GPU sepa interpretar los bytes del OBJ. Los puntos no están todavía.
	1. VkVertexInputBindingDescription -> el cable. Velocidad a avanzar por la memoria. Vas a leer del slot 0 y cada vértice ocupa sizeof(Vect3) bytes
	2.	VkVertexInputAttributeDescription -> el formato. qué es cada campo dentro de los bytes. 
		"En el canal 0 hay datos de tipo VK_FORMAT_R32G32B32_SFLOAT (es decir, 3 floats de 32 bits, tu X, Y, Z) y empiezan en el byte 0" "
		Con esto, la tubería queda programada para saber que cuando le envíes el buffer del OBJ, debe trocear los bytes de 3 en 3 floats para alimentar al Vertex Shader.
		*/
	VkPipelineVertexInputStateCreateInfo vertInputInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO
		/* para SCOP:
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    		.vertexBindingDescriptionCount = 1,
    		.pVertexBindingDescriptions = &miBindingDescription,   // El cable
    		.vertexAttributeDescriptionCount = 1,
    		.pVertexAttributeDescriptions = &miAttributeDescription // El formato
		*/
	};

	//4. input assembly, we'll be drawing triangle lists
	//al poner VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST le dice que espere 3 puntos y dibuje el triángulo
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST
	};

	//5. depth/stencil configuration
	// al poner: VK_COMPARE_OP_LESS = si el nuevo pixel está más cerca, que el que ya estaba pintado, lo dibujará encima.
	/* para optimizar por que aqui dibuja 2 pixeles, podemos transformar en la CPU
	los objetos por boundyBox y calculamos la distancia a la camara, luego los ordenamos por distancia
	y ya hacemos el calculo con VK_COMPARE_OP_LESS*/
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.depthTestEnable = VK_TRUE,
		.depthWriteEnable = VK_TRUE,
		.depthCompareOp = VK_COMPARE_OP_LESS,
		.stencilTestEnable = VK_FALSE
	};

	//6. dynamic rendering allows to set this up...dynamically
	// we still need this struct though
	// al ponerle 
	VkPipelineViewportStateCreateInfo viewportInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.pViewports = nullptr,
		.scissorCount = 1,
		.pScissors = nullptr
	};

	//7. rasterizer settings
	//El formato de como se pinta dicha geometría
	VkPipelineRasterizationStateCreateInfo rasterInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.polygonMode = VK_POLYGON_MODE_FILL, //Triángulo relleno, no solo lineas
		.cullMode = VK_CULL_MODE_BACK_BIT, //Backcull. No pinta la geometria de atrás.
		.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
		.lineWidth = 1.0f,
	};

	// No multisampling
	VkPipelineMultisampleStateCreateInfo multiSampleInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
	};

	// 8.Alpha-blending (disabled for now), still need
	// attachment info and write mask
	// Configura las transparencias (alpha blending)
	VkPipelineColorBlendAttachmentState attachState
	{
		.blendEnable = VK_FALSE, //alphablend en falso. Color 100% opaco
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
	};
	VkPipelineColorBlendStateCreateInfo blendInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.attachmentCount = 1,
		.pAttachments = &attachState
	};

	// 6b. enable dynamic state
	// No importa el tamaño del lienzo por ahora, ya lo dirá en tiempo real.
	// eso último lo marca: VK_DYNAMIC_STATE_VIEWPORT
	// Con esto y VK_DYNAMIC_STATE_SCISSOR el dibujo se adapta al resize de la pantalla
	std::vector<VkDynamicState> dynamicState
	{
		VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR
	};
	VkPipelineDynamicStateCreateInfo dynamicStateInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = static_cast<uint32_t>(dynamicState.size()),
		.pDynamicStates = dynamicState.data()
	};

	//9. structure required for dynamic rendering
	//Se avisa a la pipe el formato de color a pasar swapchainFormat
	VkPipelineRenderingCreateInfo renderInfo
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
		.colorAttachmentCount = 1,
		.pColorAttachmentFormats = &swapchainFormat,
		.depthAttachmentFormat = depthFormat
	};

	//10. Create the graphics pipeline
	VkGraphicsPipelineCreateInfo pipelineInfo
	{
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.pNext = &renderInfo,
		.stageCount = static_cast<uint32_t>(shaderStages.size()),
		.pStages = shaderStages.data(),
		.pVertexInputState = &vertInputInfo,
		.pInputAssemblyState = &inputAssemblyInfo,
		.pViewportState = &viewportInfo,
		.pRasterizationState = &rasterInfo,
		.pMultisampleState = &multiSampleInfo,
		.pDepthStencilState = &depthStencilInfo,
		.pColorBlendState = &blendInfo,
		.pDynamicState = &dynamicStateInfo,
		.layout = pipelineLayout,
		.renderPass = VK_NULL_HANDLE,
	};
	if (vkCreateGraphicsPipelines(device, nullptr, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS)
	{
		showError("Error creating the pipeline");
		return nullptr;
	}
	return pipeline;
}

/*VK_SEMAPHORE_TYPE_TIMELINE es un semáforo que no es binario, sino un contador numérico (un marcador de turnos)
Cuenta el fotograma en el que está trabajando la GPU para no mandar la CPU que trabaje en otra
más avanzada.
imageAcquiredSemaphore es un semáforo binario por cada fotograma en vuelo que permitimos en la struct frameResource
Este semáforo binario controla el momento exacto en que el Swapchain entrega una imagen:
"toma este semáforo. Cuando me des la imagen de la ventana, ponlo en verde (signal)". La GPU
esperará a que este semáforo cambie a verde antes de ejecutar el vertex shader del triángulo.
*/
bool Application::createSyncResources()
{
	VkSemaphoreTypeCreateInfo semaphoreTypeInfo
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
		.semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
		.initialValue = MaxFramesInFlight
	};
	VkSemaphoreCreateInfo semaphoreInfo
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = &semaphoreTypeInfo
	};
	if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &timelineSemaphore) != VK_SUCCESS)
	{
		showError("Unable to create the timeline semaphore");
		return false;
	}

	// per-frame image-acquire semaphores
	for (FrameResources &res : frameResources)
	{
		// create the binary semaphores
		VkSemaphoreCreateInfo semaphoreInfo{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
		if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &res.imageAcquiredSemaphore) != VK_SUCCESS)
		{
			showError("Error creating the per-frame image-acquire semaphore");
			return false;
		}
	}

	return true;
}

/*Es el Block de notas donde apuntar las órdenes de dibujo en cada fotograma
No se le dice "dibuja esto ahora" sino que se graban todas las órdenes en un command buffer
y luego se lanza el buffer entero a la gfxQueue.
Se crean dos herramientas por cada fotograma (frameResources)
1.	VkCommandPool -> La fábrica de hojas. Porción de memoria asignada de donde se sacan los blocs de notas
	se borra de memoria por entero en cada fotograma cuando termina la GPU de dibujar cada frame. Mejor rendimiento
	se le pasa por el queue que sabe hacer el trabajo gfxQueueFamIdx
2.	vkCommandBuffer -> el block de notas en si. Con vkAllocateCommandBuffers se saca una "hoja" del pool anterior
*/

bool Application::createCommandBuffers()
{
	for (FrameResources &res : frameResources)
	{
		// we'll give each frame its own pool, faster cmd buffer resets this way
		VkCommandPoolCreateInfo poolInfo
		{
			.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			.queueFamilyIndex = gfxQueueFamIdx
		};
		if (vkCreateCommandPool(device, &poolInfo, nullptr, &res.commandPool) != VK_SUCCESS)
		{
			showError("Unable to create command buffer pool");
			return false;
		}

		// create the command buffer for this frame
		VkCommandBufferAllocateInfo cmdAllocInfo
		{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.commandPool = res.commandPool,
			.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY, //block de notas principal que se puede mandar directo al queue de la GPU
			.commandBufferCount = 1, //Solo un block por frame para ver el triángulo.
		};

		if (vkAllocateCommandBuffers(device, &cmdAllocInfo, &res.commandBuffer) != VK_SUCCESS)
		{
			showError("Unable to allocate command buffer");
			return false;
		}
	}
	return true;
}


/*	1. Control de Redimensión
	2. Sincronización Timeline
	3. Captura de Imagen
	4. Barreras de Memoria
	5. Dibujo dinámico
	6. Envio y Presentación	*/
void Application::render()
{
	// first check if our swapchain is still valid
	/*1. Si cambiamos el tamaño de la ventana, el viejo lienzo no sirve
		Destruimos el Swapchain anterior y creamos uno nuevo*/
	if (requireSwapchainRecreate) //primera vez es false
	{
		vkDeviceWaitIdle(device); //Pausa la CPU
		destroySwapchain();
		createSwapchain(width, height);
		requireSwapchainRecreate = false;
	}

	/*2.CREAMOS DOS CAJONES para hacer el trabajo.
		frameResIndex es el indice de esos dos cajones que será 0 ó 1.
		En ellos metemos las herramientas que la CPU necesita para preparar un frame. 
		Son 2 por que si fuera 1, se pararía la CPU ya que tiene que esperar a la GPU para
		que procese el pedido. La CPU es más rápida que la GPU y se sigue parando
		cuando vuelve al cajón 0, pero se obtiene mejor rendimiento. Es un trade off
		Con 1 solo cajón habría cero input lag, pero el rendimiento sería la mitad.
		No añadir más "cajones" haría el cuadruple de rendimiento, ya que la GPU ya estaría
		trabajando al 100% de su rendimiento.
			MaxFramesInFlight son los frames que va a procesar la CPU y que están 
		POR DELANTE de petición sobre la GPU. Normalmente son 2, como está inicializado
		y no se ponen más para que no haya input lag en la imagen. No tiene que ver
		con el número de imágenes que puede procesar la GPU en el Swapchain (normalmente 3 ó 4)
		frameIndex es uint64_t y es un contador de frames, pero necesita ser 64bits por que 
		se utiliza Timeline Semaphores, que no son 0-1 sino avanzan hacia adelante como un 
		contador de km de un coche. NO hace overflow por que a 60fps tardaría 10.000 millones de años
		en desbordarse.
		
		Las signals en Vulkan es dar luz verde. El timelineSemaphore empieza en 0. Cuando la GPU
		termina de pintar un frame, señaliza subiendo su valor y SIEMPRE tiene que ser un valor
		mayor. Por eso se usa uint64_t.
		nextSignalValue, empieza en 3 por que la CPU necesita que los valores de sincronización
		vayan por delante 
		
		vkWaitSemaphores mira el valor actual del semáforo en la GPU y lo compara
		con el waitValue.
			Valor_GPU >= waitvalue -> la CPU se para 0ms. No se para
			Valor_GPU < waitValue -> la CPU se para hasta que alcance el waitValue
		El valor inicial de dicho semáforo era creado en la inicialización de VkSemaphoreTypeCreateInfo:
		.initialValue = MaxFramesInFlight, que en este caso es 2.
		Ese 2 no se actualizará hasta que se dibuje cada fotograma en la GPU. Por eso
		para cada dos si la GPU no ha actualizado.
		
		Una vez que el semáforo da luz verde a la CPU,
		FrameResources &res = frameResources[frameResIndex]; guarda la direccion de memoria
		del cajón que toca usar (0 ó 1). 
		vkResetCommandPool vacía el cajón de datos. Lo resetea. 
		*/
		

	
	const uint32_t frameResIndex = frameIndex++ % MaxFramesInFlight;
	const uint64_t signalValue = nextSignalValue++;
	const uint64_t waitValue = signalValue - MaxFramesInFlight;

	VkSemaphoreWaitInfo waitInfo
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
		.semaphoreCount = 1,
		.pSemaphores = &timelineSemaphore,
		.pValues = &waitValue
	};
	vkWaitSemaphores(device, &waitInfo, UINT64_MAX);

	// now its safe to start recording commands
	FrameResources &res = frameResources[frameResIndex];
	vkResetCommandPool(device, res.commandPool, 0);


	/*3. vkAcquireNextImageKHR le pide al monitor una imagen vacia para empezar a pintar
		en ella.
		Si el monitor dice que se quedó obsoleta (VK_ERROR_OUT_OF_DATE_KHR), activamos la 
		redimensión*/
	// get the resources for this frame
	VkSemaphore imageAcquireSemaphore = frameResources[frameResIndex].imageAcquiredSemaphore;

	uint32_t imageIndex = 0;
	VkResult acquireResult = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAcquireSemaphore, VK_NULL_HANDLE, &imageIndex);

	// handle resize and out-of-date images, may need swapchain recreate
	/* requireSwapchainRecreate es la que permite arriba en el paso 1, que se haga
		un nuevo Swapchain. Este primer evento VK_ERROR_OUT_OF_DATA_KHR no parece que 
		haga mención al resize, que también tiene que cambiar el Swapchain, pero es que
		este VK_ERROR_OUT_OF_DATA_KHR salta, cuando se ha hecho un resize. Por eso no usamos
		el evento SDL_EVENT_WINDOW_RESIZED que está en el if de Application::run()
		Por ello no hace falta añadir un requireSwapchainRecreate = true; en ese if. Este cubre
		los dos.*/
	if (acquireResult == VK_ERROR_OUT_OF_DATE_KHR)
	{
		requireSwapchainRecreate = true;
		return;
	}
	else if (acquireResult == VK_SUBOPTIMAL_KHR)
	{
		// can render this frame, recreate next time around
		requireSwapchainRecreate = true;
	}

	// begin recording commands
	VkCommandBufferBeginInfo cmdBeginInfo
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
	};
	vkBeginCommandBuffer(res.commandBuffer, &cmdBeginInfo);

	/*4.	vkCmdPipelineBarrier2 -> Las imágenes en Vulkan necesitan cambiar de
		estado para que los chips de la GPU sepan que hacer con ellas.
		Imagen de Color: Cambia de estado "desconocido" a "optimizado para recibir color"
		depthImage: Cambai a "Optimizado para pruebas de profundidad"*/
	// transition the color and depth images
	std::vector<VkImageMemoryBarrier2> layoutBarriers
	{
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
			.srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
			.srcAccessMask = 0,
			.dstStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
			.dstAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
			.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			.image = swapchainImages[imageIndex],
			.subresourceRange
			{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1,
			}
		},
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
			.srcStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT,
			.srcAccessMask = 0,
			.dstStageMask = VK_PIPELINE_STAGE_2_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_2_LATE_FRAGMENT_TESTS_BIT, // both specified to control memory access at both stages (write)
			.dstAccessMask = VK_ACCESS_2_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
			.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.newLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
			.image = depthImage,
			.subresourceRange
			{
				.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1,
			}
		}
	};
	VkDependencyInfo depInfo
	{
		.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
		.imageMemoryBarrierCount = static_cast<uint32_t>(layoutBarriers.size()),
		.pImageMemoryBarriers = layoutBarriers.data()
	};
	vkCmdPipelineBarrier2(res.commandBuffer, &depInfo);

	
	/*5.	vkCmdBeginRendering activa el lienzo usando las configuracionde de color
		y profundidad directamente.
			vkCmdSetViewport y vkCmdSetScissor: Definen la región exacta de la pantalla 
		donde se va a pintar.
		vkCmdBindPipeline: Carga el shader de vértices y fragmentos	
		vkCmdDraw(..., 3, ...) dibuja los 3 vértices del triángulo
		vkCmdPipelineBarrier2 (el segundo): Devuelve la imagen de color al estado "Listo
		para mostrar en pantalla */
	// setup the attachments (color and depth) and begin rendering (dynamic)
	VkRenderingAttachmentInfo colorAttachInfo
	{
		.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
		.imageView = swapchainImageViews[imageIndex],
		.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR, // clear the image
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE, // keep data for presentation
		.clearValue{.color{0.01f, 0.01f, 0.01f, 1.0f}}
	};
	VkRenderingAttachmentInfo depthAttachInfo
	{
		.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
		.imageView = depthImageView,
		.imageLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR, // clear the depth data
		.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, // don't care after rendering
		.clearValue{.depthStencil{1.0f, 0}}
	};
	VkRenderingInfo renderingInfo
	{
		.sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
		.renderArea
		{
			.offset{.x = 0, .y = 0},
			.extent{.width = swapchainWidth, .height = swapchainHeight}
		},
		.layerCount = 1,
		.colorAttachmentCount = 1,
		.pColorAttachments = &colorAttachInfo,
		.pDepthAttachment = &depthAttachInfo
	};

	// begin dynamic rendering
	vkCmdBeginRendering(res.commandBuffer, &renderingInfo);
	{
		// set the viewpot and scissor state
		VkViewport viewport
		{
			.x = 0, .y = 0,
			.width = static_cast<float>(swapchainWidth),
			.height = static_cast<float>(swapchainHeight)
		};
		vkCmdSetViewport(res.commandBuffer, 0, 1, &viewport);

		VkRect2D scissor
		{
			.offset{.x = 0, .y = 0 },
			.extent{.width = swapchainWidth, .height = swapchainHeight}
		};
		vkCmdSetScissor(res.commandBuffer, 0, 1, &scissor);

		// draw our triangle
		vkCmdBindPipeline(res.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
		vkCmdDraw(res.commandBuffer, 3, 1, 0, 0);
	}
	// end dynamic rendering
	vkCmdEndRendering(res.commandBuffer);


	/*6.	vkQueueSubmit2: Envía todo este paquete de órdenes grabado a la cola de la GPU
		(gfxQueue) para que empiece a trabajar
		vkQueuePresentKHR: Le dice al monitor: "Oye, la GPU ya ha terminado, pon esta imagen
		terminada (imageIndex) en la pantalla del usuario"*/
	// transition the image from color attachment to presentation so we can show it
	VkImageMemoryBarrier2 presentLayoutBarrier
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
		.srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask = VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT,
		.dstStageMask = VK_PIPELINE_STAGE_2_NONE, // nothing is waiting, but the cache is flushed and layout is transition
		.dstAccessMask = 0,
		.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		.image = swapchainImages[imageIndex],
		.subresourceRange
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1,
		}
	};
	VkDependencyInfo presentDepInfo
	{
		.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
		.imageMemoryBarrierCount = 1,
		.pImageMemoryBarriers = &presentLayoutBarrier
	};
	vkCmdPipelineBarrier2(res.commandBuffer, &presentDepInfo);

	vkEndCommandBuffer(res.commandBuffer);

	// ensure swapchain image is actually vailable to start color output
	VkSemaphoreSubmitInfo imageAcquireWaitInfo
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
		.semaphore = imageAcquireSemaphore,
		.stageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT // wait before drawing to image
	};
	// signal that the image can be presented
	std::vector<VkSemaphoreSubmitInfo> semaphoreSignals
	{
		{ // render work completion signal
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
			.semaphore = renderCompleteSemaphores[imageIndex],
			.stageMask = VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT
		},
		{ // entire frame is completed (timeline)
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
			.semaphore = timelineSemaphore,
			.value = signalValue,
			.stageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT
		}
	};
	VkCommandBufferSubmitInfo cmdSubmitInfo
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
		.commandBuffer = res.commandBuffer,
	};
	VkSubmitInfo2 submitInfo
	{
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
		.waitSemaphoreInfoCount = 1,
		.pWaitSemaphoreInfos = &imageAcquireWaitInfo, // ensure the image is ready
		.commandBufferInfoCount = 1,
		.pCommandBufferInfos = &cmdSubmitInfo,
		.signalSemaphoreInfoCount = static_cast<uint32_t>(semaphoreSignals.size()),
		.pSignalSemaphoreInfos = semaphoreSignals.data()
	};
	vkQueueSubmit2(gfxQueue, 1, &submitInfo, VK_NULL_HANDLE);

	// present the image
	VkPresentInfoKHR presentInfo{
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &renderCompleteSemaphores[imageIndex], // render work completed semaphore
		.swapchainCount = 1,
		.pSwapchains = &swapchain,
		.pImageIndices = &imageIndex,
		.pResults = nullptr
	};

	vkQueuePresentKHR(gfxQueue, &presentInfo);
}

