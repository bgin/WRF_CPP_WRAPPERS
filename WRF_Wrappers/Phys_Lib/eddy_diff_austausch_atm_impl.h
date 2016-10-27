#ifndef __EDDY_DIFF_AUSTAUSCH_ATM_IMPL_H__
#define __EDDY_DIFF_AUSTAUSCH_ATM_IMPL_H__

// File granularity version.
#ifndef EDDY_DIFF_AUSTAUSCH_ATM_IMPL_VERSION_MAJOR
#define EDDY_DIFF_AUSTAUSCH_ATM_IMPL_VERSION_MAJOR 1
#endif

#ifndef EDDY_DIFF_AUSTAUSCH_ATM_IMPL_VERSION_MINOR
#define EDDY_DIFF_AUSTAUSCH_ATM_IMPL_VERSION_MINOR 0
#endif

#ifndef EDDY_DIFF_AUSTAUSCH_ATM_IMPL_PATCH_VERSION
#define EDDY_DIFF_AUSTAUSCH_ATM_IMPL_PATCH_VERSION 0
#endif

#ifndef EDDY_DIFF_AUSTAUSCH_ATM_IMPL_CREATE_DATE
#define EDDY_DIFF_AUSTAUSCH_ATM_IMPL_CREATE_DATE "Date: 26-10-2016 , Time: 15:22 PM GMT+2"
#endif

#ifndef EDDY_DIFF_AUSTAUSCH_ATM_IMPL_BUILD_DATE
#define EDDY_DIFF_AUSTAUSCH_ATM_IMPL_BUILD_DATE ""
#endif

#ifndef EDDY_DIFF_AUSTAUSCH_ATM_IMPL_AUTHOR
#define EDDY_DIFF_AUSTAUSCH_ATM_IMPL_AUTHOR "Name: Bernard Gingold , e-mail:beniekg@gmail.com"
#endif

#include "module_cam_bl_eddy_diff_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

namespace phys_lib_wrappers {
	namespace module_eddy_diff {


		/*
		*   Wrapping structure called 'Wrap_AustauschAtm' its main
		*   purpose is to present herself as high level wrapper interface
		*	to underlying Fortran 90 'AUSTAUSCH_ATM' subroutine.
		*   Notification:
		*                 'EDDY_DIFF_mp_AUSTAUSCH_ATM' subroutine is module
		*                  internal (private) and should not be called
		*                  directly by C++ code side.
		*/

		template<typename R64 = double,
				 typename I32 = int >   struct Wrap_AustauschAtm {




					 /*********************************
					     Constructors and Destructor.
					 **********************************/

					 /*
						@Purpose:
								  Default Constructor - explicitly default.
					 */
					 Wrap_AustauschAtm() = default;

					 /*
						@Purpose:
									1st 'main' Constructor which purpose
								  is to allocate and initialize scalar
								  and array members. Array members are
								  zero-filled. Caller must later initialize
								  input arrays to correct physical state.
					 */
					 Wrap_AustauschAtm(_In_ const I32 pcols,
						               _In_ const I32 pver,
						               _In_ const I32 ncol)
						              :
						        m_pcols{ pcols },
						        m_pver{ pver },
						        m_ncol{ ncol },
						        m_ri{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						        m_s2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						        m_kvf{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)), align32B)) } {

								//Checking for memory allocation errors (malloc failures).
						 if (this->m_ri ==  NULL ||
							 this->m_s2 ==  NULL ||
							 this->m_kvf == NULL ) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor 'Wrap_AustauschAtm'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << " Memory allocation failure in 1st Constructor: 'Wrap_AustauschAtm' \n";
							 m_ri == NULL ? std::cerr << "m_ri is invalid: " << std::hex << "0x" << m_ri << "\n" :
								 std::cerr << "m_ri is valid.\n";
							 m_s2 == NULL ? std::cerr << "m_s2 is invalid: " << std::hex << "0x" << m_s2 << "\n" :
								 std::cerr << " m_s2 is valid.\n";
							 m_kvf == NULL ? std::cerr << "m_kvf is invalid: " << std::hex << "0x" << m_kvf << "\n" :
								 std::cerr << "m_kvf is valid.\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }
						 // Zero-initialize input and output arrays.
						 // Using OpenMP.
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 20))
						 for(int i { 0 }; i != this->m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int j{ 0 }; j != this->m_pver; ++j) {
								 this->m_ri[i + m_pcols * j] = 0.0;
								 this->m_s2[i + m_pcols * j] = 0.0;
								 this->m_kvf[i + m_pcols * j] = 0.0;
							 }
						 }
						 const int top = this->m_pcols + (this->m_pver + 1);
						 this->m_kvf[top] = 0.0;
#else
						 // Use loop blocking.
						 // Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)
						 for(int i{0}; i != this->m_pcols; i += DEFAULT_BLOCK_SIZE) {
							 for(int j{0}; j != this->m_pver; j += DEFAULT_BLOCK_SIZE) {
								 for(int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
									 for(int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
										 this->m_ri[ii + m_pcols * jj] = 0.0;
										 this->m_s2[ii + m_pcols * jj] = 0.0;
										 this->m_kvf[ii + m_pcols * jj] = 0.0;
									 }
								 }
							 }
						 }

#endif
						 const int top = this->m_pcols + (this->m_pver + 1);
						 this->m_kvf[top] = 0.0;
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
					 Wrap_AustauschAtm(_In_ const I32 pcols,
						               _In_ const I32 pver,
						               _In_ const I32 ncol,
						               _In_ R64* __restrict const ri,
						               _In_ R64* __restrict const s2)
						            :
						      m_pcols{ pcols },
						      m_pver{ pver },
						      m_ncol{ ncol },
						      m_ri{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						      m_s2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						      m_kvf{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)), align32B)) } {

							  //Check for memory allocation errors(malloc failures).
						 if (this->m_ri ==  NULL ||
							 this->m_s2 ==  NULL ||
							 this->m_kvf == NULL ||
							          ri == NULL ||
							          s2 == NULL) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor 'Wrap_AustauschAtm'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << " Memory allocation failure in 2nd Constructor: 'Wrap_AustauschAtm' \n";
							 
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }
						 // Copy caller's input arrays and zero initialize
						 // output array. Use OpenMP.
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 20))
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int j{ 0 }; j != this->m_pver; ++j) {
								 this->m_ri[i + m_pcols * j] = ri[i + m_pcols * j];
								 this->m_s2[i + m_pcols * j] = s2[i + m_pcols * j];
								 this->m_kvf[i + m_pcols * j] = 0.0;
							 }
						 }

						 const int top = this->m_pcols + (this->m_pver + 1);
						 this->m_kvf[top] = 0.0;
#else
						 // Use loop blocking.
						 // Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)
						 for (int i{0}; i != this->m_pcols; i += DEFAULT_BLOCK_SIZE) {
							 for (int j{0}; j != this->m_pver; j += DEFAULT_BLOCK_SIZE) {
								 for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
									 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
										 this->m_ri[ii + m_pcols * jj] = ri[ii + m_pcols * jj];
										 this->m_s2[ii + m_pcols * jj] = s2[ii + m_pcols * jj];
										 this->m_kvf[ii + m_pcols * jj] = 0.0;
									 }
								 }
							 }
						 }


#endif
						 const int top = this->m_pcols + (this->m_pver + 1);
						 this->m_kvf[top] = 0.0;
#endif

			}

					 /*
						@Purpose:
								  Copy Constructor implements deep copy semantics.
					 */
					 Wrap_AustauschAtm(_In_ const Wrap_AustauschAtm &x)
						            :
						      m_pcols{ x.m_pcols },
						      m_pver{ x.m_pver },
						      m_ncol{ x.m_ncol },
						      m_ri{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						      m_s2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						      m_kvf{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) }{

						 if (this->m_ri == NULL ||
							 this->m_s2 == NULL ||
							 this->m_kvf == NULL  ) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor 'Wrap_AustauschAtm'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << " Memory allocation failure in 1st Constructor: 'Wrap_AustauschAtm' \n";
							 m_ri == NULL ? std::cerr << "m_ri is invalid: " << std::hex << "0x" << m_ri << "\n" :
								 std::cerr << "m_ri is valid.\n";
							 m_s2 == NULL ? std::cerr << "m_s2 is invalid: " << std::hex << "0x" << m_s2 << "\n" :
								 std::cerr << " m_s2 is valid.\n";
							 m_kvf == NULL ? std::cerr << "m_kvf is invalid: " << std::hex << "0x" << m_kvf << "\n" :
								 std::cerr << "m_kvf is valid.\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

						 // Using OpenMP for copying loop.
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 20))
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int j{ 0 }; j != this->m_pver; ++j) {
								 this->m_ri[i + m_pcols * j] = x.m_ri[i + x.m_pcols * j];
								 this->m_s2[i + m_pcols * j] = x.m_s2[i + x.m_pcols * j];
								 this->m_kvf[i + m_pcols * j] = x.m_kvf[i + x.m_pcols * j];
							 }
						 }
						 const int top = this->m_pcols + (this->m_pver + 1);
						 this->m_kvf[top] = x.m_kvf[top];

#else
						 // Use loop blocking.
						 // Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)
						 for (int i{ 0 }; i != this->m_pcols; i += DEFAULT_BLOCK_SIZE) {
							 for (int j{ 0 }; j != this->m_pver; j += DEFAULT_BLOCK_SIZE) {
								 for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
									 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
										 this->m_ri[ii + m_pcols * jj] = x.m_ri[ii + x.m_pcols * jj];
										 this->m_s2[ii + m_pcols * jj] = x.m_s2[ii + x.m_pcols * jj];
										 this->m_kvf[ii + m_pcols * jj] = x.m_kvf[ii + x.m_pcols * jj];
									 }
								 }
							 }
						 }

#endif
						 const int top = this->m_pcols + (this->m_pver + 1);
						 this->m_kvf[top] = x.m_kvf[top];
#endif
		     }

					     /*
					      @Purpose:
					               Move Constructor implements shallow copy semantics.
					      */
					 Wrap_AustauschAtm(_In_ Wrap_AustauschAtm &&x)
						            :
						        m_pcols{ x.m_pcols },
						        m_pver{ x.m_pver },
						        m_ncol{ x.m_ncol },
						        m_ri{ x.m_ri },
						        m_s2{ x.m_s2 },
						        m_kvf{ x.m_kvf } {

								x.m_ri = NULL;
								x.m_s2 = NULL;
								x.m_kvf = NULL;
								x.m_pcols = 0;
								x.m_pver = 0;
			 }

					       /*
					         @Purpose:
					                  Class Destructor.
					       */
					 ~Wrap_AustauschAtm() {
						 if (this->m_ri) {
							 _mm_free(this->m_ri);
							 this->m_ri = NULL;
							 this->m_pcols = 0;
							 this->m_pver = 0;
						 }
						 if (this->m_s2) {
							 _mm_free(this->m_s2);
							 this->m_s2 = NULL;
						 }
						 if (this->m_kvf) {
							 _mm_free(this->m_kvf);
							 this->m_kvf = NULL
;						 }
			}

					 /*
						@Purpose:
								 Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_AustauschAtm & operator=(_In_ const Wrap_AustauschAtm &x) {
						 if (this == &x) return (*this);

						 this->m_pcols = x.m_pcols;
						 this->m_pver = x.m_pver;
						 this->m_ncol = x.m_ncol;
						 constexpr int nPtrs2D{3};
						 R64 *tPtrs2D[nPtrs2D] = {};
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 tPtrs2D[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if (tPtrs2D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Operator: 'Wrap_AustauschAtm'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << " Memory allocation failure in Copy-Operator: 'Wrap_AustauschAtm' \n";

								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 20))
						 for(int i{0}; i != this->m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int j{ 0 }; j != this->m_pver; ++j) {
								 tPtrs2D[0][i + m_pcols * j] = x.m_ri[i + x.m_pcols * j];
								 tPtrs2D[1][i + m_pcols * j] = x.m_s2[i + x.m_pcols * j];
								 tPtrs2D[2][i + m_pcols * j] = x.m_kvf[i + x.m_pcols * j];
							 }
						 }
						 const int top = this->m_pcols * (this->m_pver + 1);
						 tPtrs2D[2][top] = x.m_kvf[top];
						 _mm_free(this->m_ri);
						 _mm_free(this->m_s2);
						 _mm_free(this->m_kvf);
						 this->m_ri = tPtrs2D[0];
						 this->m_s2 = tPtrs2D[1];
						 this->m_kvf = tPtrs2D[2];

						 return (*this);
#else
						 // Use loop blocking.
						 // Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)
						 for (int i{0}; i != this->m_pcols; i += DEFAULT_BLOCK_SIZE ) {
							 for (int j{0}; j != this->m_pver; j += DEFAULT_BLOCK_SIZE) {
								 for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
									 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
										 tPtrs2D[0][ii + m_pcols * jj] = x.m_ri[ii + x.m_pcols * jj];
										 tPtrs2D[1][ii + m_pcols * jj] = x.m_s2[ii + x.m_pcols * jj];
										 tPtrs2D[2][ii + m_pcols * jj] = x.m_kvf[ii + x.m_pcols * jj];
									 }
								 }
							 }
						 }

#endif
						 const int top = this->m_pcols * (this->m_pver + 1);
						 tPtrs2D[2][top] = x.m_kvf[top];
						 _mm_free(this->m_ri);
						 _mm_free(this->m_s2);
						 _mm_free(this->m_kvf);
						 this->m_ri = tPtrs2D[0];
						 this->m_s2 = tPtrs2D[1];
						 this->m_kvf = tPtrs2D[2];

						 return (*this);
#endif

			}

					 /*
						@Purpose:
								 Move-assign Operator implements shallow copy semantics.
					 */
					 Wrap_AustauschAtm & operator=(_In_ Wrap_AustauschAtm &&x) {
						 if (this == &x) return (*this);

						 this->m_pcols = x.m_pcols;
						 this->m_pver = x.m_pver;
						 this->m_ncol = x.m_ncol;
						 _mm_free(this->m_ri);
						 this->m_ri = x.m_ri;
						 x.m_ri = NULL;
						 x.m_pcols = 0;
						 x.m_pver = 0;
						 _mm_free(this->m_s2);
						 this->m_s2 = x.m_s2;
						 x.m_s2 = NULL;
						 _mm_free(this->m_kvh);
						 this->m_kvf = x.m_kvf;
						 x.m_kvf = NULL;

						 return (*this);
			}

					 /*
						@Purpose:
									Call Fortran 90 AUSTAUSCH_ATM subroutine.
									Warning:
									        'AUSTAUSCH_ATM' probably will not
									         be accessible from outside eddy_diff module.
					 */
					 void  Call_AUSTAUSCH_ATM() {

						 EDDY_DIFF_mp_AUSTAUSCH_ATM(&this->m_pcols, &this->m_pver, &this->m_ncol,
							 &this->m_ri[0], &this->m_s2[0], &this->m_kvf[0]);

					 }
					 /*
						@Purpose:
								  Member variables.
					 */
					 I32 m_pcols;

					 I32 m_pver;

					 I32 m_ncol;

_Field_size_(m_pcols * m_pver) R64* __restrict m_ri;

_Field_size_(m_pcols * m_pver) R64* __restrict m_s2;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_kvf;

					 static const int m_nArrays = 3;
			};


	}
}


#endif /*__EDDY_DIFF_AUSTAUSCH_ATM_IMPL_H__*/