
#ifndef __PHYS_LIB_CONFIG_H__
#define __PHYS_LIB_CONFIG_H__

// File granularity version.
#ifndef PHYS_LIB_CONFIG_VERSION_MAJOR
#define PHYS_LIB_CONFIG_VERSION_MAJOR 1
#endif

#ifndef PHYS_LIB_CONFIG_VERSION_MINOR
#define PHYS_LIB_CONFIG_VERSION_MINOR 0
#endif

#ifndef PHYS_LIB_CONFIG_PATCH_VERSION
#define PHYS_LIB_CONFIG_PATCH_VERSION 0
#endif

#ifndef PHYS_LIB_CONFIG_CREATE_DATE
#define PHYS_LIB_CONFIG_CREATE_DATE "Date: 13-10-2016 , Time: 12:01 PM GMT+2"
#endif

// Set this to successfull build date/time.
#ifndef PHYS_LIB_CONFIG_BUILD_DATE
#define PHYS_LIB_CONFIG_BUILD_DATE ""
#endif

#ifndef PHYS_LIB_CONFIG_AUTHOR
#define PHYS_LIB_CONFIG_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


/* Start of Compiler specific declarations. */
#if defined (__cplusplus)
#define PHYS_LIB_WRAPPERS_CXX_98 199711L
#define PHYS_LIB_WRAPPERS_CXX_11 201103L
#define PHYS_LIB_WRAPPERS_CXX_14 201402L
#endif



/* Determine current version supported by ICC.*/
#if defined (__cplusplus) && !defined (__INTEL_CXX11_MODE__)
#if PHYS_LIB_WRAPPERS_CXX_98 < PHYS_LIB_WRAPPERS_CXX_11
#define PHYS_LIB_DEFAULT_CXX_VER 199711L
#else
#define PHYS_LIB_DEFAULT_CXX_VER 201103L
#endif
#endif

/* Is Intel Compiler choosen as project compiler? */
#if defined (__INTEL_COMPILER)
#define PHYS_LIB_WRAPPERS_COMPILED_BY_ICC 0x1
#else
#define PHYS_LIB_WRAPPERS_COMPILED_BY_ICC 0x0
#error "ERROR: Detected non Intel Compiler -- Cannot Compile!!"
#endif

/* Is 64-bit mode current one? */
#if (defined (_M_AMD64) || defined(_M_X64_) || defined (__amd64) ) \
	&& !defined (__x86_64__)
#define __x86_64__ 1
#endif

/* Determine Architectural support for full set of GP registers. */

#if __x86_64__ == 1
#define PHYS_LIB_WRAPPERS_HAS_FULL_GPR_SET 16
#elif __x86_64__ == 0
#define PHYS_LIB_WRAPPERS_HAS_FULL_GPR_SET 8
#else
#error "ERROR: Cannot determine 32-bit or 64-bit mode!!"
#endif

/* Determine Architectiral support for full set of SIMD registers. */
#if __x86_64__ == 1
#define PHYS_LIB_WRAPPERS_HAS_FULL_SIMD_SET 32
#elif __x86_64__ == 0
#define PHYS_LIB_WRAPPERS_HAS_FULL_SIMD_SET 16
#else
#error "ERROR: Cannot detemine suuport for full set(32) SIMD registers!!"
#endif

/* Compiler optimization settings. Should mimick some
settings set from command line or project UI. */

#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) &&  \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define MIMICK_UI_OPTIM_SETTINGS 0x1

#else
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif

#if defined(MIMICK_UI_OPTIM_SETTINGS) && \
	MIMICK_UI_OPTIM_SETTINGS == 1
#define NO_OPTIMIZATION 0x0
#define OPTIM_LEVEL_1  0x1
#define OPTIM_LEVEL_2  0x2
#define OPTIM_LEVEL_3  0x3
#endif


#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) &&  \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define USE_ICL_PERF_LIBS 0x1
#else
#define USE_ICL_PERF_LIBS 0x0
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif


#if defined (USE_ICL_PERF_LIBS) && \
	USE_ICL_PERF_LIBS == 1
#define USE_ICL_MKL 0x1
#define USE_ICL_IPP 0x1
#define USE_ICL_TBB 0x1
#endif


#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) && \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define USE_ICL_OPENMP 0x1
#else 
#define USE_ICL_OPENMP 0x1
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif


#if defined (USE_ICL_OPENMP) && \
	USE_ICL_OPENMP == 1
#include <omp.h>
#endif


#if defined (USE_ICL_OPENMP) && \
	USE_ICL_OPENMP == 1
#define OPENMP_VER_10 10
#define OPENMP_VER_15 15
#define OPENMP_VER_20 20
#define OPENMP_VER_25 25
#define OPENMP_VER_30 30
#define OPENMP_VER_35 35
#define OPENMP_VER_40 40
#define OPENMP_VER_45 45

#endif

#if defined (USE_ICL_OPENMP) && \
 USE_ICL_OPENMP == 1
 #define OPENMP_CURR_VER 40
 #endif


/* Manual unrolling settings */
#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) && \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define USE_MANUAL_UNROLLING 0x1
#else
#define USE_MANUAL_UNROLLING 0x0
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif

#if defined (USE_MANUAL_UNROLLING) && \
	USE_MANUAL_UNROLLING == 1
#define UNROLL_2X  0x2
#define UNROLL_4X  0x4
#define UNROLL_8X  0x8
#if __x86_64__ == 1
#define UNROLL_16X  0x10
#define UNROLL_32X  0x20
#endif
#endif

/* Software Prefetching distances */
#if defined(PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) && \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define USE_SOFT_PREFETCHING 0x1
#else
#define USE_SOFT_PREFETCHING 0x0
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif

#if defined (USE_SOFT_PREFETCHING) && \
	USE_SOFT_PREFETCHING == 1
#define PREFETCH_TO_L1D 0x1
#define PREFETCH_TO_L2  0x2
#define PREFETCH_TO_L3  0x3
/* Prefetching in terms of loop cycles no.*/
#define PREFETCH_L1_NCYCLES 0x1
#define PREFETCH_L2_NCYCLES 0x2
#define PREFETCH_L3_NCYCLES 0x3
#else
#error "ERROR: Cannot proceed , probably invalid Compiler!!"
#endif

// Set this value to accordingly to your machine CPU.
#if defined (PREFETCH_TO_L1D)
constexpr int L1_MAX_SP{ 8000 };
constexpr int L1_MAX_DP{ 4000 };
#endif

// Set this value to accordingly to your machine CPU.
#if defined (PREFETCH_TO_L2)
constexpr int L2_MAX_SP{ 8 * L1_MAX_SP };
constexpr int L2_MAX_DP{ 8 * L1_MAX_DP };
#endif

// Set this value to accordingly to your machine CPU.
#if defined (PREFETCH_TO_L3)
constexpr int L3_MAX_SP{ 1572864 };
constexpr int L3_MAX_DP{ 786432 };
#endif

/* You should test these values on your machine!!*/
#if defined (PREFETCH_L1_NCYCLES)
constexpr int L1_NCYCLES{ 4 };
#endif

/* You should test these values on your machine!!*/
#if defined (PREFETCH_L2_NCYCLES)
constexpr int L2_NCYCLES{ 8 };
#endif

/* You should test these values on your machine!!*/
#if defined (PREFETCH_L3_NCYCLES)
constexpr int L3_NCYCLES{16};
#endif


#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) && \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define USE_AUTO_VECTORIZATION 0x1
#else
#define USE_AUTO_VECTORIZATION 0x0
#error "ERROR: Cannot Detect Intel Compiler"
#endif

#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) && \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#ifndef _MM_MALLOC_ALIGNED_
#define _MM_MALLOC_ALIGNED_
#else
#undef _MM_MALLOC_ALIGNED_
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif
#endif

#if defined (_MM_MALLOC_ALIGNED_)
constexpr int align16B{ 16 };
constexpr int align32B{ 32 };
#endif

#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) && \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define OPTIMIZE_SPEC_CPU 0x1
#else
#define OPTIMIZE_SPEC_CPU 0x0
#error "ERROR: Cannot Detect Intel Compiler!!"
#endif

/* Three level of specific CPU(code path) optimization:
1) SSE.
2) AVX.
3) AVX2.
*/
/* These macros are used in conjugation with compiler
pragmas which mimicks ICL UI settings related to
specific CPU code path.*/
#if defined (OPTIMIZE_SPEC_CPU) && \
	OPTIMIZE_SPEC_CPU == 1
#define SSE_PATH 0x1
#define AVX_PATH 0x2
#define AVX2_PATH 0x3
#endif

/* Loop blocking optimization switch on/off.*/
#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) && \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define USE_LOOP_BLOCKING 0x1
#else
#define USE_LOOP_BLOCKING 0x0
#endif

// Default loop block size.
#if defined (USE_LOOP_BLOCKING)
constexpr int DEFAULT_BLOCK_SIZE{ 8 };
#endif

/* Strip Mining optimization switch on/off.*/
#if defined (PHYS_LIB_WRAPPERS_COMPILED_BY_ICC) && \
	PHYS_LIB_WRAPPERS_COMPILED_BY_ICC == 1
#define USE_STRIP_MINING 0x1
#else
#define USE_STRIP_MINING 0x0
#endif

// Default strip size.
#if defined (USE_STRIP_MINING)
constexpr int DEFAULT_STRIP_SIZE{8};
#endif

/* Debug Mode */
#if defined _DEBUG
#define PHYS_LIB_WRAPPERS_DEBUG_ON 0x
#undef _DEBUG
#endif




#endif /*__PHYS_LIB_CONFIG_H__*/