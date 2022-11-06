#pragma once

#if defined(CDR_DEBUG)

#include <assert.h>

#include <vulkan/vulkan.h>

#define VK_VERIFY(x) assert(x == VK_SUCCESS)

#else

#define VK_VERIFY(x) x

#endif