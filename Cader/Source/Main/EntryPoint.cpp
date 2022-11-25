#include "Cader/Core/PlatformDetection.h"

#if defined(CDR_PLATFORM_WINDOWS)

#include "Platform/Win/Entry.h"

#else // defined(CDR_PLATFORM_WINDOWS)

#error "Main not implemented for the current platform"

#endif // defined(CDR_PLATFORM_WINDOWS)