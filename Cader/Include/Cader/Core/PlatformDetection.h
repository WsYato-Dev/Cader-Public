#pragma once

#if defined(_WIN32)

#if defined(_WIN64)

#define CDR_PLATFORM_WINDOWS

#else // defined(_WIN64)

#error "x86 is not supported"

#endif // defined(_WIN64)

#else // defined(_WIN32)

#error "Platform not supported"

#endif // defined(_WIN32)