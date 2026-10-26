/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vulkan_init.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:03:06 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/21 14:03:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#define VK_NO_PROTOTYPES

#ifdef USING_SDL2
	#include <SDL2/SDL_vulkan.h> //para SDL2 42
#else
	#include <SDL3/SDL_vulkan.h>
#endif

#include "Obj.hpp"
#include <string>
#include <vulkan/vulkan.h>
#include <vector>
#include <array>
#include <string>
#include <shaderc/shaderc.hpp>

struct SDL_Window;
struct VmaAllocator_T;
typedef struct VmaAllocator_T* VmaAllocator;
struct VmaAllocation_T;
typedef struct VmaAllocation_T* VmaAllocation;

struct FrameResources
{
	VkCommandPool commandPool = nullptr;
	VkCommandBuffer commandBuffer = nullptr;
	VkSemaphore imageAcquiredSemaphore = nullptr;
};

class VulkanInit
{
	constexpr static uint32_t VulkanVersion{ VK_API_VERSION_1_3 };
	constexpr static uint32_t MaxFramesInFlight{ 2 };
	constexpr static VkFormat swapchainFormat{ VK_FORMAT_B8G8R8A8_SRGB };
	constexpr static VkFormat depthFormat{ VK_FORMAT_D32_SFLOAT };

	SDL_Window* window = nullptr;
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t vertexCount = 0;
	bool running = false;
    uint64_t frameIndex = 0;
    uint64_t nextSignalValue = MaxFramesInFlight + 1;

	// vulkan core
	VkInstance 			vulkanInstance = VK_NULL_HANDLE;
	VkPhysicalDevice	physicalDevice = VK_NULL_HANDLE;
	VkDevice 			device = VK_NULL_HANDLE;
	VkSurfaceKHR 		surface = VK_NULL_HANDLE;
	VmaAllocator 		vmaAllocator = VK_NULL_HANDLE;
	VkBuffer			vertexBuffer = VK_NULL_HANDLE;
	VmaAllocation		vertexAllocation = VK_NULL_HANDLE;


	// queue related
	uint32_t gfxQueueFamIdx = UINT32_MAX;
	VkQueue gfxQueue = VK_NULL_HANDLE;

	// swapchain related
	VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	std::vector<VkImage> swapchainImages;
	std::vector<VkImageView> swapchainImageViews;
	std::vector<VkSemaphore> renderCompleteSemaphores;
	bool requireSwapchainRecreate = false;
	uint32_t swapchainWidth = 0;
	uint32_t swapchainHeight = 0;

	VkImage depthImage = VK_NULL_HANDLE;
	VkImageView depthImageView = VK_NULL_HANDLE;
	VmaAllocation depthImageAllocation = VK_NULL_HANDLE;

	// graphics pipeline related
	VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
	VkPipeline pipeline = VK_NULL_HANDLE;

	// shader resources
	VkShaderModule vertShader = VK_NULL_HANDLE;
	VkShaderModule fragShader = VK_NULL_HANDLE;

	// frame and synchronization resources
	VkSemaphore timelineSemaphore = VK_NULL_HANDLE;
	std::array<FrameResources, MaxFramesInFlight> frameResources;

	void showError(const std::string &errorMessasge) const;

	bool initializeVulkan(Obj& obj3D);
	bool createVulkanInstance();
	bool createSurface();
	VkPhysicalDevice findPhysicalDevice();
	bool findGraphicsQueue();
	bool createDevice(VkPhysicalDevice physicalDevice);
	bool initializeVMA();
	bool createVertexBuffer(Obj& obj3D);
	bool createSwapchain(uint32_t width, uint32_t height);
	void destroySwapchain();
	VkShaderModule createShaderModule(const std::string &fileName, shaderc_shader_kind kind) const;
	bool createShaders();
	VkPipeline createGraphicsPipeline();
	bool createSyncResources();
	bool createCommandBuffers();
	void render();

public:
	bool initialize(Obj& obj3D);
	void shutdown();
	void run();
};
