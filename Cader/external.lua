VulkanSDK = os.getenv("VULKAN_SDK")

-- This is temporary as it is Windows only. Will change to build glfw to create the library for other systems
Glfw = {}
Glfw["Include"] = "%{prj.location}/External/glfw-3.3.8/include/"
Glfw["Lib"] = "%{prj.location}/External/glfw-3.3.8/lib-vc2022/glfw3.lib"

Vulkan = {}
Vulkan["Include"] = "%{VulkanSDK}/Include/"
Vulkan["Lib"] = "%{VulkanSDK}/Lib/vulkan-1.lib"