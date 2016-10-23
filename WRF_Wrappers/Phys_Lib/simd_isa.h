
#ifndef __SIMD_ISA_H__
#define __SIMD_ISA_H__

// File granularity version.
#ifndef SIMD_ISA_VERSION_MAJOR
#define SIMD_ISA_VERSION_MAJOR 1
#endif

#ifndef SIMD_ISA_VERSION_MINOR 
#define SIMD_ISA_VERSION_MINOR 0
#endif

#ifndef SIMD_ISA_PATCH_VERSION
#define SIMD_ISA_PATCH_VERSION 0
#endif

#ifndef SIMD_ISA_CREATE_DATE
#define SIMD_ISA_CREATE_DATE "Date: 13-10-2016 , Time: 12:09 PM GMT+2"
#endif

// Set this to successfull build date/time.
#ifndef SIMD_ISA_BUILD_DATE
#define SIMD_ISA_BUILD_DATE ""
#endif

#ifndef SIMD_ISA_AUTHOR
#define SIMD_ISA_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif

/* Determine SIMD architecture ISA set
and its corresponding intrinsic sets.
*/

#if !defined SIMDISA
#if defined (__AVX512__) || defined (__AVX512CD__) || defined (__AVX512DQ__) \
	|| defined (__AVX512ER__) || defined (__AVX512F__) || defined (__AVXPF__)
#defined SIMDISA 9
#elif defined (__AVX2__)
#define SIMDISA 8
#elif defined (__AVX__)
#define SIMDISA 7
#elif defined (__SSE4_2__)
#define SIMDISA 6
#elif defined (__SSE4__)
#define SIMDISA 5
#elif defined (__SSSE3__)
#define SIMDISA 4
#elif defined (__SSE3__)
define SIMDISA 3
#elif defined (__SSE2__)
#define SIMDISA 2
#elif defined (__SSE__)
#define SIMDISA 1
#elif defined (_M_IX86_FP)
#define SIMDISA _M_IX86_FP
#else
#define SIMDISA 0
#endif
#endif

#if defined __INTEL_COMPILER
#if SIMDISA > 8
#include <zmmintrin.h>
#elif SIMDISA == 8
#include <immintrin.h>
#elif SIMDISA == 7
#include <immintrin.h>
#elif SIMDISA == 6
#include <nmmintrin.h>
#elif SIMDISA == 5
#include <smmintrin.h>
#elif SIMDISA == 4
#include <tmmintrin.h>
#elif SIMDISA == 3
#include <emmintrin.h>
#elif SIMDISA == 2
#include <xmmintrin.h>
#elif defined _MSC_VER
#include <intrin.h>
#else
#error "Unsuported compiler detected."
#endif
#endif



#endif /*__SIMD_ISA_H__*/