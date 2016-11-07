
#ifndef __MODULE_BL_MYNN_MYM_LEVEL2_IMPL_H__
#define __MODULE_BL_MYNN_MYM_LEVEL2_IMPL_H__

// File version granularity.
#ifndef MODULE_BL_MYNN_MYM_LEVEL2_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_MYM_LEVEL2_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_MYM_LEVEL2_IMPL_VERSION_MINOR
#define MODULE_BL_MYNN_MYM_LEVEL2_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_MYM_LEVEL2_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_MYM_LEVEL2_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_MYM_LEVEL2_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_MYM_LEVEL2_IMPL_CREATE_DATE "Date: 07-11-2016 , Time: 12:37 PM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_MYM_LEVEL2_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_MYM_LEVEL2_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_MYM_LEVEL2_IMPL_AUTHOR
#define MODULE_BL_MYNN_MYM_LEVEL2_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

namespace wrf_phys_wrappers {
	namespace module_bl_mynn {


		template<typename R32 = float,
				 typename I32 = int  >  struct   Wrap_Mym_Level2 {



					 /******************************************
						     Constructors and Destructor.
					 *******************************************/

					 /*
						@Purpose:
									Default Constructor - explicitly default.
					 */
					 Wrap_Mym_Level2() = default;

					 /*
						@Purpose:
								    1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Mym_Level2(_In_ const I32 KTS,
						             _In_ const I32 KTE)
						           :
						        m_KTS{ KTS },
						        m_KTE{ KTE },
						        m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_u{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_v{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_ql{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_dtl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_dqw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_dtv{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_gm{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_gh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						        m_sm{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
								m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) } {

						 // Checking for memory allocation errors i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Mym_Level2'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Zero-initialize arrays.
						 // Using OpenMP and vectorization for
						 // innermost stride.
						 // Zero-initialization of Arrays 1D.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_KTE >= (1 << 20))
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = 0.F;
							 this->m_u[i] = 0.F;
							 this->m_v[i] = 0.F;
							 this->m_thl[i] = 0.F;
							 this->m_qw[i] = 0.F;
							 this->m_ql[i] = 0.F;
							 this->m_vt[i] = 0.F;
							 this->m_vq[i] = 0.F;
							 this->m_dtl[i] = 0.F;
							 this->m_dqw[i] = 0.F;
							 this->m_dtv[i] = 0.F;
							 this->m_gm[i] = 0.F;
							 this->m_gh[i] = 0.F;
							 this->m_sm[i] = 0.F;
							 this->m_sh[i] = 0.F;
						 }



#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = 0.F;
							 this->m_u[i] = 0.F;
							 this->m_v[i] = 0.F;
							 this->m_thl[i] = 0.F;
							 this->m_qw[i] = 0.F;
							 this->m_ql[i] = 0.F;
							 this->m_vt[i] = 0.F;
							 this->m_vq[i] = 0.F;
							 this->m_dtl[i] = 0.F;
							 this->m_dqw[i] = 0.F;
							 this->m_dtv[i] = 0.F;
							 this->m_gm[i] = 0.F;
							 this->m_gh[i] = 0.F;
							 this->m_sm[i] = 0.F;
							 this->m_sh[i] = 0.F;
						 }



#endif


			}

					 /*
						@Purpose:
								  2nd 'main' Constructor which purpose
								  is to allocate and initialize scalar
								  and array members. Array output members are
								  zero-filled. Caller must pass initialized
								  input arrays to correct physical state.
					 */
			         Wrap_Mym_Level2(_In_ const I32 KTS,
				                     _In_ const I32 KTE,
				                     _In_ R32* __restrict const dz,
				                     _In_ R32* __restrict const u,
				                     _In_ R32* __restrict const v,
				                     _In_ R32* __restrict const thl,
				                     _In_ R32* __restrict const qw,
				                     _In_ R32* __restrict const ql,
				                     _In_ R32* __restrict const vt,
				                     _In_ R32* __restrict const vq)
				                            :
				                      m_KTS{ KTS },
				                      m_KTE{ KTE },
				                      m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_u{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_v{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_ql{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_dtl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_dqw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_dtv{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_gm{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_gh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                      m_sm{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
									  m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) } {

						 // Check for memory alloction errors i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Level2'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Check for null pointer occurrence.
						 if (dz  == NULL ||
							 u   == NULL ||
							 v   == NULL ||
							 thl == NULL ||
							 qw  == NULL ||
							 ql  == NULL ||
							 vt  == NULL ||
							 vq  == NULL || ) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Level2'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "One or more caller's arrays contains invalid pointer!!\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }
						 // Using OpenMP and vectorization for
						 // innermost stride.
						 // Copying input Arrays 1D.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40 
#pragma omp parallel for if(m_KTE >= (1 << 20))
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = dz[i];
							 this->m_u[i] = u[i];
							 this->m_v[i] = v[i];
							 this->m_thl[i] = thl[i];
							 this->m_qw[i] = qw[i];
							 this->m_ql[i] = ql[i];
							 this->m_vt[i] = vt[i];
							 this->m_vq[i] = vq[i];
							 this->m_dtl[i] = 0.F;
							 this->m_dqw[i] = 0.F;
							 this->m_dtv[i] = 0.F;
							 this->m_gm[i] = 0.F;
							 this->m_gh[i] = 0.F;
							 this->m_sm[i] = 0.F;
							 this->m_sh[i] = 0.F;
						 }

#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = dz[i];
							 this->m_u[i] = u[i];
							 this->m_v[i] = v[i];
							 this->m_thl[i] = thl[i];
							 this->m_qw[i] = qw[i];
							 this->m_ql[i] = ql[i];
							 this->m_vt[i] = vt[i];
							 this->m_vq[i] = vq[i];
							 this->m_dtl[i] = 0.F;
							 this->m_dqw[i] = 0.F;
							 this->m_dtv[i] = 0.F;
							 this->m_gm[i] = 0.F;
							 this->m_gh[i] = 0.F;
							 this->m_sm[i] = 0.F;
							 this->m_sh[i] = 0.F;
						 }


#endif
			}

					 /*
						@Purpose: 
									Copy Constructor implements deep copy semantics.
					  */
			         Wrap_Mym_Level2(_In_ const Wrap_Mym_Level2 &x)
				                      :
				                 m_KTS{ x.m_KTS },
				                 m_KTE{ x.m_KTE },
				                 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_u{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_v{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_ql{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_dtl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_dqw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_dtv{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_gm{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_gh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                 m_sm{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
								 m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) } {

						 // Check for memory allocation error i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor: 'Wrap_Mym_Level2'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_KTE >= (1 << 20))
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif						
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = x.m_dz[i];
							 this->m_u[i] = x.m_u[i];
							 this->m_v[i] = x.m_v[i];
							 this->m_thl[i] = x.m_thl[i];
							 this->m_qw[i] = x.m_qw[i];
							 this->m_ql[i] = x.m_ql[i];
							 this->m_vt[i] = x.m_vt[i];
							 this->m_vq[i] = x.m_vq[i];
							 this->m_dtl[i] = x.m_dtl[i];
							 this->m_dqw[i] = x.m_dqw[i];
							 this->m_dtv[i] = x.m_dtv[i];
							 this->m_gm[i] = x.m_gm[i];
							 this->m_gh[i] = x.m_gh[i];
							 this->m_sm[i] = x.m_sm[i];
							 this->m_sh[i] = x.m_sh[i];
						 }

#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif						
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = x.m_dz[i];
							 this->m_u[i] = x.m_u[i];
							 this->m_v[i] = x.m_v[i];
							 this->m_thl[i] = x.m_thl[i];
							 this->m_qw[i] = x.m_qw[i];
							 this->m_ql[i] = x.m_ql[i];
							 this->m_vt[i] = x.m_vt[i];
							 this->m_vq[i] = x.m_vq[i];
							 this->m_dtl[i] = x.m_dtl[i];
							 this->m_dqw[i] = x.m_dqw[i];
							 this->m_dtv[i] = x.m_dtv[i];
							 this->m_gm[i] = x.m_gm[i];
							 this->m_gh[i] = x.m_gh[i];
							 this->m_sm[i] = x.m_sm[i];
							 this->m_sh[i] = x.m_sh[i];
						 }


#endif

			}

					 /*
						@Purpose:
								  Move Constructor implements shallow copy semantics.
					 */
					 Wrap_Mym_Level2(_In_ Wrap_Mym_Level2 &&x)
						       :
						 m_KTS{ x.m_KTS },
						 m_KTE{ x.m_KTE } {

						 // Reassign x's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != x.m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 x.m_KTS = x.m_KTE = 0;
			}

					 /*
						@Purpose:
									Class Destructor.
					 */
					 ~Wrap_Mym_Level2() {
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i]) {
								 _mm_free((&this->m_dz)[i]);
							 }
						 }
						 this->m_KTS = this->m_KTE = 0;
			}

					 /*
						@Purpose:
							      Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Mym_Level2 & operator=(_In_ const Wrap_Mym_Level2 &x) {
						 if (this == &x) return (*this);

						 this->m_KTS = x.m_KTS;
						 this->m_KTE = x.m_KTE;
						 constexpr int ntPtrs1D{15};
						 R32  *tPtrs1D[ntPtrs1D] = {};
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if (tPtrs1D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mym_Level2'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs1D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_KTE >= (1 << 20))
						 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int i = m_KTS; i != m_KTE; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }
						 
						 // Deallocate current context of *this.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
						 // Copy temp pointers to *this.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = tPtrs1D[i];
						 }

						 return (*this);
#else

						 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int i = m_KTS; i != m_KTE; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }
						 
						 // Deallocate current context of *this.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
						 // Copy temp pointers to *this.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = tPtrs1D[i];
						 }

						 return (*this);


#endif

			}

					 /*
						@Purpose:
								 Move-assign Operator implements shallow copy semantics.
					 */
					 Wrap_Mym_Level2 & operator=(_In_ Wrap_Mym_Level2 &&x) {
						 if (this == &x) return (*this);

						 this->m_KTS = x.m_KTS;
						 this->m_KTE = x.m_KTE;
						 // Deallocate current state.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
						 // Reassign x's pointers to *this's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 x.m_KTS = 0;
						 x.m_KTE = 0;

						 return (*this);
			}

					 /*
						@Purpose:
						          Call Fortran 90 'MYM_LEVEL2' subroutine.
					 */
					 void  Call_Mym_Level2() {

						 MODULE_BL_MYNN_mp_MYM_LEVEL2(&this->m_KTS, &this->m_KTE,
										&this->m_dz[0], &this->m_u[0], &this->m_v[0],
										&this->m_thl[0], &this->m_qw[0], &this->m_ql[0],
										&this->m_vt[0], &this->m_vq[0],
										&this->m_dtl[0], &this->m_dqw[0], &this->m_dtv[0], &this->m_gm[0],
										&this->m_gh[0], &this->m_sm[0], &this->m_sh[0] );
					 }
					 /*
						@Purpose:
								  Member variables.
					 */

					 I32 m_KTS;

					 I32 m_KTE;

	 // Input arrays.
_Field_size_(m_KTE) R32* __restrict m_dz;

_Field_size_(m_KTE) R32* __restrict m_u;

_Field_size_(m_KTE) R32* __restrict m_v;

_Field_size_(m_KTE) R32* __restrict m_thl;

_Field_size_(m_KTE) R32* __restrict m_qw;

_Field_size_(m_KTE) R32* __restrict m_ql;

_Field_size_(m_KTE) R32* __restrict m_vt;

_Field_size_(m_KTE) R32* __restrict m_vq;

    // Output arrays.
_Field_size_(m_KTE) R32* __restrict m_dtl; // Vertical gradient of Theta_l             (K/m)

_Field_size_(m_KTE) R32* __restrict m_dqw; // Vertical gradient of Q_w

_Field_size_(m_KTE) R32* __restrict m_dtv; // Vertical gradient of Theta_V        (K/m)

_Field_size_(m_KTE) R32* __restrict m_gm; // G_M divided by L^2/q^2                (s^(-2))

_Field_size_(m_KTE) R32* __restrict m_gh; // G_H divided by L^2/q^2                (s^(-2))

_Field_size_(m_KTE) R32* __restrict m_sm; // Stability function for momentum, at Level 2

_Field_size_(m_KTE) R32* __restrict m_sh; // Stability function for heat, at Level 2

				const static int m_totArrays = 15;


			};










	}
}










#endif /*__MODULE_BL_MYNN_MYM_LEVEL2_IMPL_H__*/