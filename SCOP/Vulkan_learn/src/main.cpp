#include "application.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	
	Application app;
	if (app.initialize())
	{
		app.run();
	}
	app.shutdown();

	return 0;
}


/*

initialize -> initializeVulkan -> createVulkanIntance ...

 [ Computador Físico ]
          │
     VkInstance         <── Tu punto de partida (createVulkanInstance)
          │
   VkPhysicalDevice     <── Elige la GPU real (la AMD Radeon de tu máquina de 42)
          │
       VkDevice         <── El "Dispositivo Lógico" (la interfaz para mandarle órdenes)
   ┌──────┴──────┐
VkSwapchain   VkCommandPool
   │             │
[Imágenes]    [Instrucciones de Renderizado]

*/
