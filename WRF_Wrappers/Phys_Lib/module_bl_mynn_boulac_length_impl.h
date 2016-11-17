
#ifndef __MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_H__
#define __MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_H__

// File version granularity.
#ifndef MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_VERSION_MINOR
#define MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_CREATE_DATE "Date: 15-11-2016 , Time: 11:54 AM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_AUTHOR
#define MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"


namespace wrf_phys_wrappers {
	namespace module_bl_mynn {



		template<typename R32 = float,
			     typename I32 = int >  struct  Wrap_Boulac_Length {


					 /************************************
						  Constructors and Destructor.
					 *************************************/

					 /*
						@Purpose:
								   Default Constructor - explicitly default.
					 */
					 Wrap_Boulac_Length() = default;

					 /*
						@Purpose:
									1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Boulac_Length(_In_ const I32 kts,
						 _In_ const I32 kte)
						 :
						 m_kts{ kts },
						 m_kte{ kte },
						 m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
						 m_qtke{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
						 m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
						 m_lb1{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
						 m_lb2{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 if (0 >= (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 1st Ctor: 'Wrap_Boulac_Length'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Lower range value m_kts: " << m_kts << "\n";
							 std::cerr << "Upper range value m_kte: " << m_kte << "\n";
							 std::cerr << "Range value difference: " << m_kte - m_kts << "\n";
							 std::cerr << "Cannot recover --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_zw)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Boulac_Length'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_zw)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kte >= (1 << 16))
						 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_zw)[idx][i] = 0.f;
							 }
						 }
						 const int top = m_kte + 1;
						 (&this->m_zw)[0][top] = 0.f;

#else
						// You must not #undef 'USE_AUTO_VECTORIZATION' macro!!
#if defined (USE_AUTO_VECTORIZATION)

						 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_zw)[idx][i] = 0.f;
							 }
						 }
						 const int top = m_kte + 1;
						 (&this->m_zw)[0][top] = 0.f;

#endif


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
					 Wrap_Boulac_Length(_In_ const I32 kts,
						 _In_ const I32 kte,
						 _In_ R32* __restrict const zw,
						 _In_ R32* __restrict const dz,
						 _In_ R32* __restrict const qtke,
						 _In_ R32* __restrict const theta)
						 :
						 m_kts{ kts },
						 m_kte{ kte },
						 m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
						 m_qtke{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
						 m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
						 m_lb1{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
						 m_lb2{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 if (0 >= (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 2nd Ctor: 'Wrap_Boulac_Length'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Lower range value m_kts: " << m_kts << "\n";
							 std::cerr << "Upper range value m_kte: " << m_kte << "\n";
							 std::cerr << "Range value difference: " << m_kte - m_kts << "\n";
							 std::cerr << "Cannot recover --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_zw)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Boulac_Length'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_zw)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }

						 if (zw    == NULL ||
							 dz    == NULL ||
							 qtke  == NULL ||
							 theta == NULL    ) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Boulac_Length'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "One or more caller's arrays contains invalid pointer!!\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kte >= (1 << 16))
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_zw[i] = zw[i];
							 m_dz[i] = dz[i];
							 m_qtke[i] = qtke[i];
							 m_theta[i] = theta[i];
							 m_lb1[i] = 0.f;
							 m_lb2[i] = 0.f;
						 }
						 const int top = m_kte + 1;
						 m_zw[top] = zw[top];


#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_zw[i] = zw[i];
							 m_dz[i] = dz[i];
							 m_qtke[i] = qtke[i];
							 m_theta[i] = theta[i];
							 m_lb1[i] = 0.f;
							 m_lb2[i] = 0.f;
						 }
						 const int top = m_kte + 1;
						 m_zw[top] = zw[top];


#endif


#endif
			}

					 /*
						@Purpose:
									Copy Constructor implements deep copy semantics.
					 */
						 Wrap_Boulac_Length(_In_ const Wrap_Boulac_Length &x)
							 :
							 m_kts{ x.m_kts },
							 m_kte{ x.m_kte },
							 m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
							 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
							 m_qtke{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
							 m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
							 m_lb1{ reinterpret_cast<R32*>(_mm_malloc((m_kte  * sizeof(R32)), align32B)) },
							 m_lb2{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 if ((&this->m_zw)[i] == NULL) {
									 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor: 'Wrap_Boulac_Length'!!\n";
									 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
									 std::cerr << "***** ERROR-DETAILS ***** \n";
									 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_zw)[i] << "\n";
									 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
									 std::exit(-1);
								 }
							 }
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kte >= (1 << 16))
							 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
								 for (int i = m_kts; i != m_kte; ++i) {
									 (&this->m_zw)[idx][i] = (&x.m_zw)[idx][i];
								 }
							 }
							 const int top = m_kte + 1;
							 (&this->m_zw)[0][top] = (&x.m_zw)[0][top];



#else

#if defined (USE_AUTO_VECTORIZATION)
							 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
								 for (int i = m_kts; i != m_kte; ++i) {
									 (&this->m_zw)[idx][i] = (&x.m_zw)[idx][i];
								 }
							 }
							 const int top = m_kte + 1;
							 (&this->m_zw)[0][top] = (&x.m_zw)[0][top];



#endif


#endif
			}

						 /*
							@Purpose:
										Move Constructor implements shallow copy semantics.
						 */
						 Wrap_Boulac_Length(_In_ Wrap_Boulac_Length &&x)
							 :
							 m_kts{ x.m_kts },
							 m_kte{ x.m_kte }{

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 (&this->m_zw)[i] = (&x.m_zw)[i];
							 }

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 (&x.m_zw)[i] = NULL;
							 }
							 x.m_kts = 0;
							 x.m_kte = 0;
			}

						 /*
							@Purpose:
									  Class Destructor.
						 */
						 ~Wrap_Boulac_Length() {

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 if ((&this->m_zw)[i]) {
									 _mm_free((&this->m_zw)[i]);
								 }
							 }

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 (&this->m_zw)[i] = NULL;
							 }
							 m_kts = 0;
							 m_kte = 0;
			}

						 /*
							@Purpose:
										Copy-assign Operator implements deep copy semantics.
						 */
						 Wrap_Boulac_Length & operator=(_In_ const Wrap_Boulac_Length &x) {
							 if (this == &x) return (*this);

							 m_kts = x.m_kts;
							 m_kte = x.m_kte;
							 constexpr int ntPtrs1D{6};
							 R32 *tPtrs1D[ntPtrs1D] = {};
							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 tPtrs1D[i] = reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)),align32B));
							 }

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 if (tPtrs1D[i] == NULL) {
									 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Boulac_Length'!!\n";
									 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
									 std::cerr << "***** ERROR-DETAILS ***** \n";
									 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs1D[i] << "\n";
									 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
									 std::exit(-1);
								 }
							 }
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kte >= (1 << 16))
							 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
								 for (int i = m_kts; i != m_kte; ++i) {
									 tPtrs1D[idx][i] = (&x.m_zw)[idx][i];
								 }
							 }
							 const int top = m_kte + 1;
							 tPtrs1D[0][top] = (&x.m_zw)[0][top];

							 for(int i {0}; i != this->m_totArrays; ++i) {
								 _mm_free((&this->m_zw)[i]);
							 }

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 (&this->m_zw)[i] = tPtrs1D[i];
							 }

							 return (*this);
#else

#if defined (USE_AUTO_VECTORIZATION)

							 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
								 for (int i = m_kts; i != m_kte; ++i) {
									 tPtrs1D[idx][i] = (&x.m_zw)[idx][i];
								 }
							 }
							 const int top = m_kte + 1;
							 tPtrs1D[0][top] = (&x.m_zw)[0][top];

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 _mm_free((&this->m_zw)[i]);
							 }

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 (&this->m_zw)[i] = tPtrs1D[i];
							 }

							 return (*this);


#endif


#endif
			}

						 /*
							@Purpose:
										Move-assign Operator implements shallow copy semantics.
						 */
					 Wrap_Boulac_Length & operator=(_In_ Wrap_Boulac_Length &&x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_zw)[i]);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_zw)[i] = (&x.m_zw)[i];
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_zw)[i] = NULL;
						 }
						 x.m_kts = 0;
						 x.m_kte = 0;

						 return (*this);
			}

					 /*
						@Purpose:
									Call Fortran 90 'BOULAC_LENGTH' subroutine. 
					 */
					 void  Call_Boulac_Length() {

						 MODULE_BL_MYNN_mp_BOULAC_LENGTH(&this->m_kts, &this->m_kte, &this->m_zw[0],
							 &this->m_dz[0], &this->m_qtke[0], &this->m_theta[0], &this->m_lb1[0], &this->m_lb2[0]);
			}



					 /*
						@Purpose:
									Member variables.
					 */

					 // Scalars - Input.

					 I32 m_kts;

					 I32 m_kte;

					 // Arrays 1D - Input.

_Field_size_(m_kte + 1)  R32* __restrict m_zw;

_Field_size_(m_kte)  R32* __restrict m_dz;

_Field_size_(m_kte)  R32* __restrict m_qtke;

_Field_size_(m_kte)  R32* __restrict m_theta;

				     // Arrays 1D - Output.

_Field_size_(m_kte)  R32* __restrict m_lb1; // the minimum of the length up and length down

_Field_size_(m_kte)  R32* __restrict m_lb2; // the average of the length up and length down

			static const int m_totArrays = 6;


			};









	}
}











#endif /*__MODULE_BL_MYNN_BOULAC_LENGTH_IMPL_H__*/