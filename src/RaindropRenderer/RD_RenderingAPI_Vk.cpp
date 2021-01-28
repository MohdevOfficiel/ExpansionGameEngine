#include "pch.h"
#include "RD_RenderingAPI_Vk.h"

#ifdef BUILD_VULKAN

//RD_RenderingAPi_VertexElemBuffer_Vk

RD_RenderingAPI_VertexElemBuffer_Vk::RD_RenderingAPI_VertexElemBuffer_Vk() : RD_RenderingAPI_VertexElemBuffer() {
	
}

RD_RenderingAPI_VertexElemBuffer_Vk::~RD_RenderingAPI_VertexElemBuffer_Vk() {
	
}

void RD_RenderingAPI_VertexElemBuffer_Vk::CreateBuffer() {
	
}

void RD_RenderingAPI_VertexElemBuffer_Vk::FillBufferData(float* data, int count, unsigned int* elemsData, int elemCount) {
	
}

void RD_RenderingAPI_VertexElemBuffer_Vk::DeleteBuffer() {
	
}

void RD_RenderingAPI_VertexElemBuffer_Vk::BindBuffer() {
	
}

void RD_RenderingAPI_VertexElemBuffer_Vk::UnbindBuffer() {
	
}

unsigned int RD_RenderingAPI_VertexElemBuffer_Vk::GetElementCount() {
	return 0;
}

//RD_RenderingAPI_VertexBuffer_Vk

RD_RenderingAPI_VertexBuffer_Vk::RD_RenderingAPI_VertexBuffer_Vk() : RD_RenderingAPI_VertexBuffer() {
	
}

RD_RenderingAPI_VertexBuffer_Vk::~RD_RenderingAPI_VertexBuffer_Vk() {
	
}

void RD_RenderingAPI_VertexBuffer_Vk::CreateBuffer() {
	
}

void RD_RenderingAPI_VertexBuffer_Vk::FillBufferData(float* data, int count) {
	
}

void RD_RenderingAPI_VertexBuffer_Vk::DeleteBuffer() {
	
}

void RD_RenderingAPI_VertexBuffer_Vk::BindBuffer() {
	
}

void RD_RenderingAPI_VertexBuffer_Vk::UnbindBuffer() {
	
}

unsigned RD_RenderingAPI_VertexBuffer_Vk::GetFloatCount() {
	return 0;
}

//RD_WindowingSystem_GLFW_Vk

RD_WindowingSystem_GLFW_Vk::RD_WindowingSystem_GLFW_Vk(RaindropRenderer* rndr) : RD_WindowingSystem() {
	m_rndr = rndr;
}

RD_WindowingSystem_GLFW_Vk::~RD_WindowingSystem_GLFW_Vk() {
	glfwDestroyWindow(m_win);
	glfwTerminate();
}

VkSurfaceKHR RD_WindowingSystem_GLFW_Vk::GetWindowSurface() {
	return m_surface;
}

bool RD_WindowingSystem_GLFW_Vk::OpenWindow(std::string name, int w, int h) {
	if(!glfwInit()) {
		const char* error;
		glfwGetError(&error);
		
		std::cerr << "Cannot initialize GLFW. " << error << std::endl;
		dispErrorMessageBox(StrToWStr("Cannot initialize GLFW." + std::string(error)));
		glfwTerminate();
		return false;
	}

	if (!glfwVulkanSupported()) {
		std::cerr << "Vulkan is not supported." << std::endl;
		dispErrorMessageBox(StrToWStr("Vulkan is not supported."));
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_win = glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr);
	if(!m_win) {
		const char* error;
		glfwGetError(&error);

		std::cerr << "GLFW ERROR : " << error << std::endl;
		dispErrorMessageBox(StrToWStr("Cannot initialize GLFW. " + std::string(error)));
		glfwTerminate();
		return false;
	}

	glfwSetWindowUserPointer(m_win, m_rndr);
	
	return true;
}

void RD_WindowingSystem_GLFW_Vk::SetFullscreenMode(bool mode) {
	if (mode) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (!monitor) {
			std::cerr << "Cannot turn on fullscreen mode" << std::endl;
		}

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwSetWindowMonitor(m_win, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else {
		glfwSetWindowMonitor(m_win, nullptr, 0, 0, m_w, m_h, 60);
	}
}

bool RD_WindowingSystem_GLFW_Vk::GetKeyPress(int key) {
	return glfwGetKey(m_win, key) == GLFW_PRESS;
}

bool RD_WindowingSystem_GLFW_Vk::GetMouseButton(int button) {
	return glfwGetMouseButton(m_win, button) == GLFW_PRESS;
}

double RD_WindowingSystem_GLFW_Vk::GetCursorPosX() {
	return 0;
}

double RD_WindowingSystem_GLFW_Vk::GetCursorPosY() {
	return 0;
}


void RD_WindowingSystem_GLFW_Vk::SetCursorPos(double x, double y) {
	
}

void RD_WindowingSystem_GLFW_Vk::CaptureCursor(bool mode) {
	if (mode) {
		glfwSetInputMode(m_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		glfwSetInputMode(m_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

int RD_WindowingSystem_GLFW_Vk::GetHeight() {
	return 0;
}

int RD_WindowingSystem_GLFW_Vk::GetWidth() {
	return 0;
}

void RD_WindowingSystem_GLFW_Vk::SwapWindow() {
	
}

void RD_WindowingSystem_GLFW_Vk::SetVSync(const bool vsync) {
	
}

bool RD_WindowingSystem_GLFW_Vk::WantToClose() {
	return glfwWindowShouldClose(m_win);
}

void RD_WindowingSystem_GLFW_Vk::PollEvents() {
	glfwPollEvents();
}

void RD_WindowingSystem_GLFW_Vk::CreateWindowSurface(VkInstance inst) {
	if (glfwCreateWindowSurface(inst, m_win, nullptr, &m_surface) != VK_SUCCESS) {
		std::cerr << "ERROR: Cannot create window surface." << std::endl;
		dispErrorMessageBox(StrToWStr("Cannot create window surface."));
	}
	else {
		std::cout << "Created window surface !" << std::endl;
	}
}

//RD_RenderingAPI_Vk

RD_RenderingAPI_Vk::RD_RenderingAPI_Vk(RaindropRenderer* rndr) : RD_RenderingAPI() {
	m_winsys = new RD_WindowingSystem_GLFW_Vk(rndr);
	m_inst = nullptr;
}

RD_RenderingAPI_Vk::~RD_RenderingAPI_Vk() {
	if (enblValLayers) {
		DestroyDebugUtilsMessengerEXT(m_inst, m_dbg_msg, nullptr);
	}

	for (auto imgv : m_sc_img_view) {
		vkDestroyImageView(m_device, imgv, nullptr);
	}

	vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
	vkDestroySurfaceKHR(m_inst, m_winsys->GetWindowSurface(), nullptr);

	vkDestroyDevice(m_device, nullptr);
	vkDestroyInstance(m_inst, nullptr);

	delete m_winsys;
}

bool RD_RenderingAPI_Vk::InitializeAPI(const int w, const int h, const std::string wname) {
	m_winsys->OpenWindow(wname, w, h);

	if(!CreateInstance()) {
		return false;
	}

	SetupDebugMessenger();

	m_winsys->CreateWindowSurface(m_inst);

	FetchPhysicalDevice();
	CreateLogicalDevice();
	CreateSwapChain();
	CreateGraphicPipeline();

	return true;
}

void RD_RenderingAPI_Vk::CreateGraphicPipeline() {

}

bool RD_RenderingAPI_Vk::CreateInstance() {
	if (enblValLayers && !CheckValidationLayerSupport()) {
		std::cerr << "ERROR: Validation layers are enabled but not available." << std::endl;
	}

	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "ExpansionGame";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Expansion Game Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.pNext = nullptr;

	VkInstanceCreateInfo cInfo;
	cInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	cInfo.pApplicationInfo = &appInfo;

	std::vector<const char*> ext = GetRequiredExtensions();

	cInfo.enabledExtensionCount = static_cast<uint32_t>(ext.size());
	cInfo.ppEnabledExtensionNames = ext.data();
	cInfo.flags = 0;
	cInfo.pNext = nullptr;

	if (enblValLayers) {
		cInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		cInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		cInfo.enabledLayerCount = 0;
		cInfo.ppEnabledLayerNames = nullptr;
	}

	if(vkCreateInstance(&cInfo, nullptr, &m_inst) != VK_SUCCESS) {
		std::cerr << "ERROR: Cannot initialize Vulkan. Failed to create instance." << std::endl;
		dispErrorMessageBox(StrToWStr("Cannot initialize Vulkan. Failed to create instance."));
		return false;
	} else {
		std::cout << "Created VkInstance !" << std::endl;
	}

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensionDetails(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionDetails.data());

	std::cout << "Available Extensions : " << std::endl;
	for (auto& extensionDetail : extensionDetails) {
		std::cout << "\t" << extensionDetail.extensionName << std::endl;
	}

	return true;
}

void RD_RenderingAPI_Vk::FetchPhysicalDevice() {
	m_pdevice = VK_NULL_HANDLE;

	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_inst, &deviceCount, nullptr);

	if (deviceCount == 0) {
		std::cerr << "ERROR: No GPU(s) supporting Vulkan found." << std::endl;
		dispErrorMessageBox(StrToWStr("No GPU(s) supporting Vulkan found."));
		return;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_inst, &deviceCount, devices.data());

	for (const auto& dev : devices) {
		if (IsDeviceSuitable(dev)) {
			m_pdevice = dev;

			VkPhysicalDeviceProperties devProp;
			vkGetPhysicalDeviceProperties(dev, &devProp);
			std::cout << "Using Device : " << devProp.deviceName << std::endl;

			break;
		}
	}

	if (m_pdevice == VK_NULL_HANDLE) {
		std::cerr << "ERROR: No GPU(s) supporting all needed features found." << std::endl;
		dispErrorMessageBox(StrToWStr("No GPU(s) supporting all needed features found."));
		return;
	}
}

void RD_RenderingAPI_Vk::CreateLogicalDevice() {
	QueueFamilyIndices ind = FindQueueFamilies(m_pdevice);

	std::vector<VkDeviceQueueCreateInfo> qCrInfo;
	std::set<uint32_t> uniqueQfam = {ind.graphicsFamily.value(), ind.presentFamily.value()};

	float qPrio = 1.0f;
	for (uint32_t qFam : uniqueQfam) {
		VkDeviceQueueCreateInfo cInfo{};
		cInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		cInfo.queueFamilyIndex = qFam;
		cInfo.queueCount = 1;
		cInfo.pQueuePriorities = &qPrio;

		qCrInfo.push_back(cInfo);
	}

	VkPhysicalDeviceFeatures devFeatures{};
	
	VkDeviceCreateInfo cDevInfo{};
	cDevInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	cDevInfo.pQueueCreateInfos = qCrInfo.data();
	cDevInfo.queueCreateInfoCount = static_cast<uint32_t>(qCrInfo.size());
	cDevInfo.pEnabledFeatures = &devFeatures;
	cDevInfo.enabledExtensionCount = static_cast<uint32_t>(dev_extension.size());
	cDevInfo.ppEnabledExtensionNames = dev_extension.data();
	cDevInfo.enabledLayerCount = 0;
	cDevInfo.pNext = 0;
	cDevInfo.ppEnabledLayerNames = nullptr;

	if (vkCreateDevice(m_pdevice, &cDevInfo, nullptr, &m_device) != VK_SUCCESS) {
		std::cerr << "ERROR: Failed to create logical device." << std::endl;
		dispErrorMessageBox(StrToWStr("Failed to create logical device."));
		return;
	}

	vkGetDeviceQueue(m_device, ind.graphicsFamily.value(), 0, &m_gfx_queue);
	vkGetDeviceQueue(m_device, ind.presentFamily.value(), 0, &m_presentation_queue);
}

void RD_RenderingAPI_Vk::CreateSwapChain() {
	SwapChainDetails scDetails = QuerySwapChainSupport(m_pdevice);

	VkSurfaceFormatKHR sFormat = ChooseSwapSurfaceFormat(scDetails.formats);
	VkPresentModeKHR pMode = ChooseSwapPresentMode(scDetails.presentMode);
	VkExtent2D extent = ChooseSwapExtent(scDetails.capabilities);

	uint32_t imgCount = scDetails.capabilities.minImageCount + 1;
	if (scDetails.capabilities.maxImageCount > 0 && imgCount > scDetails.capabilities.maxImageCount) {
		imgCount = scDetails.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR cInfo{};
	cInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	cInfo.surface = m_winsys->GetWindowSurface();
	cInfo.minImageCount = imgCount;
	cInfo.imageFormat = sFormat.format;
	cInfo.imageColorSpace = sFormat.colorSpace;
	cInfo.imageExtent = extent;
	cInfo.imageArrayLayers = 1;
	cInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices ind = FindQueueFamilies(m_pdevice);
	uint32_t qFam[] = { ind.graphicsFamily.value(), ind.presentFamily.value() };

	if (ind.graphicsFamily != ind.presentFamily) {
		cInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		cInfo.queueFamilyIndexCount = 2;
		cInfo.pQueueFamilyIndices = qFam;
	}
	else {
		cInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		cInfo.queueFamilyIndexCount = 0;
		cInfo.pQueueFamilyIndices = nullptr;
	}

	cInfo.preTransform = scDetails.capabilities.currentTransform;
	cInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	cInfo.presentMode = pMode;
	cInfo.clipped = VK_TRUE;
	cInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(m_device, &cInfo, nullptr, &m_swapchain) != VK_SUCCESS) {
		std::cerr << "ERROR: Cannot create swapchain." << std::endl;
		dispErrorMessageBox(StrToWStr("Cannot create swapchain."));
	}
	else {
		std::cout << "Created swapchain !" << std::endl;
	}

	vkGetSwapchainImagesKHR(m_device, m_swapchain, &imgCount, nullptr);
	m_sc_images.resize(imgCount);
	vkGetSwapchainImagesKHR(m_device, m_swapchain, &imgCount, m_sc_images.data());

	m_format = sFormat.format;
	m_sc_extent = extent;
}

void RD_RenderingAPI_Vk::CreateImageViews() {
	m_sc_img_view.resize(m_sc_images.size());

	for (int i = 0; i < m_sc_images.size(); i++) {
		VkImageViewCreateInfo cInfo;
		cInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		cInfo.image = m_sc_images[i];
		cInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		cInfo.format = m_format;

		cInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		cInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		cInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		cInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		cInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		cInfo.subresourceRange.baseMipLevel = 0;
		cInfo.subresourceRange.levelCount = 1;
		cInfo.subresourceRange.baseArrayLayer = 0;
		cInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(m_device, &cInfo, nullptr, &m_sc_img_view[i]) != VK_SUCCESS) {
			std::cerr << "ERROR: Failed to create image view." << std::endl;
			dispErrorMessageBox(StrToWStr("Failed to create image view."));
		}
	}
}

QueueFamilyIndices RD_RenderingAPI_Vk::FindQueueFamilies(VkPhysicalDevice dev) {
	QueueFamilyIndices ind;

	uint32_t qFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &qFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> qFamilies(qFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(dev, &qFamilyCount, qFamilies.data());

	int i = 0;
	for (const auto& qFam : qFamilies) {
		if (qFam.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			ind.graphicsFamily = i;
		}

		VkBool32 presentSupport;
		vkGetPhysicalDeviceSurfaceSupportKHR(dev, i, m_winsys->GetWindowSurface(), &presentSupport);
		if (presentSupport) {
			ind.presentFamily = i;
		}

		i++;
	}

	return ind;
}

std::vector<const char*> RD_RenderingAPI_Vk::GetRequiredExtensions() {
	uint32_t extCount = 0;
	const char** ext;
	ext = glfwGetRequiredInstanceExtensions(&extCount);

	if (extCount == 0) {
		const char* err;
		glfwGetError(&err);

		std::cerr << "GLFW ERROR : Cannot get all required vulkan extensions. " << err << std::endl;
		dispErrorMessageBox(StrToWStr("GLFW ERROR : Cannot get all required vulkan extensions. " + std::string(err)));
		return {};
	}

	std::vector<const char*> extensions(ext, ext + extCount);

	if (enblValLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

bool RD_RenderingAPI_Vk::CheckValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> avlblLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, avlblLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : avlblLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

SwapChainDetails RD_RenderingAPI_Vk::QuerySwapChainSupport(VkPhysicalDevice dev) {
	SwapChainDetails details;
	VkSurfaceKHR surf = m_winsys->GetWindowSurface();

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surf, &details.capabilities);

	uint32_t fCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surf, &fCount, nullptr);

	if (fCount != 0) {
		details.formats.resize(fCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surf, &fCount, details.formats.data());
	}

	uint32_t pModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surf, &pModeCount, nullptr);

	if (pModeCount != 0) {
		details.presentMode.resize(pModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surf, &pModeCount, details.presentMode.data());
	}

	return details;
}

void RD_RenderingAPI_Vk::SetupDebugMessenger() {
	VkDebugUtilsMessengerCreateInfoEXT cInfo;
	cInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	cInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	cInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	cInfo.pfnUserCallback = dbgCallback;
	cInfo.pUserData = nullptr;
	cInfo.pNext = nullptr;
	cInfo.flags = 0;

	if (CreateDebugUtilsMessengerEXT(m_inst, &cInfo, nullptr, &m_dbg_msg) != VK_SUCCESS) {
		std::cerr << "ERROR: Cannot create debug messenger." << std::endl;
	}
}

RD_WindowingSystem* RD_RenderingAPI_Vk::GetWindowingSystem() {
	return m_winsys;
}

RD_RenderingAPI_VertexElemBuffer* RD_RenderingAPI_Vk::CreateVertexElemBuffer() {
	return new RD_RenderingAPI_VertexElemBuffer_Vk();
}

RD_RenderingAPI_VertexBuffer* RD_RenderingAPI_Vk::CreateVertexBuffer() {
	return new RD_RenderingAPI_VertexBuffer_Vk();
}

RD_Texture* RD_RenderingAPI_Vk::CreateTexture() {
	return nullptr;
}

RD_ShaderLoader* RD_RenderingAPI_Vk::CreateShader() {
	return nullptr;
}

RD_FrameBuffer* RD_RenderingAPI_Vk::CreateFrameBuffer(int w, int h, bool nodepth) {
	return nullptr;
}

RD_Cubemap* RD_RenderingAPI_Vk::CreateCubemap() {
	return nullptr;
}

void RD_RenderingAPI_Vk::SetViewportSize(int w, int h, int x, int y) {
	
}

void RD_RenderingAPI_Vk::Clear(int masks) {
	
}

void RD_RenderingAPI_Vk::SetClearColor(const vec3f& color) {
	
}

void RD_RenderingAPI_Vk::Draw(RD_RenderingAPI_VertexElemBuffer* vbuff) {
	
}

void RD_RenderingAPI_Vk::DrawVB(RD_RenderingAPI_VertexBuffer* vbuff, DrawMode dm) {
	
}

void RD_RenderingAPI_Vk::SetFilledMode(FillingMode fmode) {
	
}

int RD_RenderingAPI_Vk::GetMaxTextureCount() {
	return 0;
}


#endif //BUILD_VULKAN
