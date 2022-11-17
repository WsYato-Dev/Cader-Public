#pragma once

#if defined(CDR_DEBUG)

#define CDR_ASSERT(expr) do { if(!(expr)) throw "Assertion Failed"; } while(false)

#else

#define CDR_ASSERT(expr)

#endif