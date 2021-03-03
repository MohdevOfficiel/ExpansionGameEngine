#pragma once

#ifdef _WIN32
	#ifdef RAINDROPRENDERER_EXPORTS
		#define RD_API __declspec(dllexport)
	#else
		#define RD_API __declspec(dllimport)
	#endif
#else
	#define RD_API
#endif //_WIN32

#include "RD_RenderingAPI.h"

#ifdef BUILD_VULKAN

#ifdef _DEBUG
constexpr bool enblValLayers = true;
#else
constexpr bool enblValLayers = false;
#endif //DEBUG

#define VK_SHADER_FOLDER "spv"

#undef max
#undef min

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <cstring>
#include <optional>
#include <set>
#include <algorithm>

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> dev_extension = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;
};

struct SwapChainDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentMode;
};

class RD_API RD_RenderingAPI_VertexElemBuffer_Vk : public RD_RenderingAPI_VertexElemBuffer {
public:
	RD_RenderingAPI_VertexElemBuffer_Vk();
	~RD_RenderingAPI_VertexElemBuffer_Vk();

	virtual void CreateBuffer();
	virtual void FillBufferData(float* data, int count, unsigned int* elemsData, int elemCount);
	virtual void DeleteBuffer();

	virtual void BindBuffer();
	virtual void UnbindBuffer();

	virtual unsigned int GetElementCount();
};

class RD_API RD_RenderingAPI_VertexBuffer_Vk : public RD_RenderingAPI_VertexBuffer {
public:
	RD_RenderingAPI_VertexBuffer_Vk();
	~RD_RenderingAPI_VertexBuffer_Vk();

	virtual void CreateBuffer();
	virtual void FillBufferData(float* data, int count);
	virtual void DeleteBuffer();

	virtual void BindBuffer();
	virtual void UnbindBuffer();

	virtual unsigned int GetFloatCount();
};

class RD_API RD_WindowingSystem_GLFW_Vk : public RD_WindowingSystem {
public:
	RD_WindowingSystem_GLFW_Vk(RaindropRenderer* rndr);
	~RD_WindowingSystem_GLFW_Vk();

	virtual bool OpenWindow(std::string name, int w, int h);
	virtual void SetFullscreenMode(bool mode);

	virtual bool GetKeyPress(int key);
	virtual bool GetMouseButton(int button);

	virtual double GetCursorPosX();
	virtual double GetCursorPosY();
	virtual void SetCursorPos(double x, double y);

	virtual void CaptureCursor(bool mode);

	virtual int GetHeight();
	virtual int GetWidth();

	virtual void SwapWindow();
	virtual void SetVSync(const bool vsync);

	virtual bool WantToClose();
	virtual void PollEvents();

	void CreateWindowSurface(VkInstance inst);
	VkSurfaceKHR GetWindowSurface();

	void CreateViewportAndScissors(VkExtent2D extent);
	VkViewport GetViewport() { return m_viewport; }
	VkRect2D GetScissors() { return m_scissors; }
private:
	RaindropRenderer* m_rndr;
	GLFWwindow* m_win;
	
	VkSurfaceKHR m_surface;
	VkViewport m_viewport;
	VkRect2D m_scissors;
};

class RD_API RD_RenderingAPI_Vk : public RD_RenderingAPI {
public:
	RD_RenderingAPI_Vk(RaindropRenderer* rndr);
	~RD_RenderingAPI_Vk();

	virtual bool InitializeAPI(const int w, const int h, const std::string wname);
	void EndInit();
	virtual RD_WindowingSystem* GetWindowingSystem();

	virtual RD_RenderingAPI_VertexElemBuffer* CreateVertexElemBuffer();
	virtual RD_RenderingAPI_VertexBuffer* CreateVertexBuffer();
	virtual RD_Texture* CreateTexture();
	virtual RD_FrameBuffer* CreateFrameBuffer(int w, int h, bool nodepth);
	virtual RD_ShaderLoader* CreateShader();
	virtual RD_Cubemap* CreateCubemap();
	virtual RD_UniformBuffer* CreateUniformBuffer(const size_t size, const int binding);

	virtual void SetViewportSize(int w, int h, int x, int y);

	virtual void Clear(int masks);
	virtual void SetClearColor(const vec3f& color = vec3f());
	virtual void Draw(RD_RenderingAPI_VertexElemBuffer* vbuff);
	virtual void DrawVB(RD_RenderingAPI_VertexBuffer* vbuff, DrawMode dm);
	virtual void SetFilledMode(FillingMode fmode);

	virtual int GetMaxTextureCount();

	VkShaderModule CreateShaderModule(const std::vector<char>& code_char);
	void DestroyShaderModule(VkShaderModule shader);

	VkPipeline CreateGraphicPipeline(const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages);
	void BeginRenderPass();

private:
	static VKAPI_ATTR VkBool32 VKAPI_CALL dbgCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT msgSeverity,
		VkDebugUtilsMessageTypeFlagsEXT msgType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {

		if (msgSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
			std::cerr << "VALIDATION LAYER MESSAGE : " << pCallbackData->pMessage << std::endl;
		}

		return VK_FALSE;
	}

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	bool IsDeviceSuitable(VkPhysicalDevice dev) {
		QueueFamilyIndices ind = FindQueueFamilies(dev);

		bool sChainAdequate = false;
		if (CheckDeviceExtension(dev)) {
			SwapChainDetails schainDetails = QuerySwapChainSupport(dev);
			sChainAdequate = !schainDetails.formats.empty() && !schainDetails.presentMode.empty();
		}

		return (ind.graphicsFamily.has_value() && ind.presentFamily.has_value()) && sChainAdequate;
	}

	bool CheckDeviceExtension(VkPhysicalDevice dev) {
		uint32_t extCount;
		vkEnumerateDeviceExtensionProperties(dev, nullptr, &extCount, nullptr);
		std::cout << "Number of Device Extension available : " << extCount << std::endl;

		std::vector<VkExtensionProperties> availableExt(extCount);
		vkEnumerateDeviceExtensionProperties(dev, nullptr, &extCount, availableExt.data());

		std::set<std::string> reqExt(dev_extension.begin(), dev_extension.end());
		for (const auto& ext : availableExt) {
			reqExt.erase(ext.extensionName);
		}

		return reqExt.empty();
	}

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availFormats) {
		for (const auto& aFormat : availFormats) {
			if (aFormat.format == VK_FORMAT_B8G8R8A8_SRGB && aFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return aFormat;
			}
		}

		return availFormats[0];
	}

	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availPresMde) {
		for (const auto& aPresMode : availPresMde) {
			if (aPresMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return aPresMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& cap) {
		const int h = m_winsys->GetHeight();
		const int w = m_winsys->GetWidth();

		if (cap.currentExtent.width != UINT32_MAX) {
			return cap.currentExtent;
		}
		else {
			VkExtent2D actualExtent = {
				static_cast<uint32_t>(w),
				static_cast<uint32_t>(h)
			};

			actualExtent.width = std::max(cap.minImageExtent.width, std::min(cap.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(cap.minImageExtent.height, std::min(cap.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

	bool CreateInstance();
	void FetchPhysicalDevice();
	void SetupDebugMessenger();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void CreateImageViews();
	void CreateMainRenderPass();
	void CreatePipelineLayout();
	void CreateFramebuffers();
	void CreateCommandPool();
	void CreateCommandBuffers();

	std::vector<const char*> GetRequiredExtensions();

	bool CheckValidationLayerSupport();
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice dev);
	SwapChainDetails QuerySwapChainSupport(VkPhysicalDevice dev);
	
	RD_WindowingSystem_GLFW_Vk* m_winsys;

	VkInstance m_inst;
	VkSwapchainKHR m_swapchain;
	VkRenderPass m_mainsRenderPass;
	VkPipelineLayout m_layout;

	VkCommandPool m_command_pool;
	std::vector<VkCommandBuffer> m_command_buffers;

	VkDebugUtilsMessengerEXT m_dbg_msg;

	VkPhysicalDevice m_pdevice;
	VkDevice m_device;

	VkQueue m_gfx_queue;
	VkQueue m_presentation_queue;

	VkFormat m_format;
	VkExtent2D m_sc_extent;

	std::vector<VkImage> m_sc_images;
	std::vector<VkImageView> m_sc_img_view;

	std::vector<VkFramebuffer> m_sc_fbo;

	VkClearValue m_clr;
};

#endif //BUILD_VULKAN