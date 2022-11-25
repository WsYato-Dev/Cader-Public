#pragma once

#if defined(CDR_DEBUG)

#include "Cader/Utility/Assert.h"

#include <vulkan/vulkan.h>

#define VK_VERIFY(expr) CDR_ASSERT(VK_SUCCESS == expr)

#else

#define VK_VERIFY(expr) expr

#endif