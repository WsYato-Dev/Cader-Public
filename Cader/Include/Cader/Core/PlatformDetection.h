#pragma once

#if defined(_WIN32)

#if defined(_WIN64)

#define CDR_PLATFORM_WINDOWS

#else

#error "x86 is not supported"

#endif

#else

#error "Platform not supported"

#endif