#include "Cader/Core/PlatformDetection.h"

#if defined(CDR_PLATFORM_WINDOWS)

#include "Platform/Win/Entry.h"

#else

#error "Main not implemented for the current platform"

#endif