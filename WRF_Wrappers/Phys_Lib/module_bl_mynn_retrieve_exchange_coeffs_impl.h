
#ifndef __MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_H__
#define __MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_H__

/* File granularity version */
#ifndef MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_VERSION_MINOR
#define MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_CREATE_DATE "Date: 14-11-2016 , Time: 09:27 AM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_RETRIVE_EXCHANGE_COEFFS_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_RETRIVE_EXCHANGE_COEFFS_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_AUTHOR
#define MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif



#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"



namespace wrf_phys_wrappers {
	namespace module_bl_mynn {


		template<typename R32 = float,
			     typename I32 = int >  struct  Wrap_Retrieve_Exchange_Coeffs{


					 /**********************************
						Constructors and Destructor.
					 ***********************************/

					 /*
						@Purpose:
									Default Constructor - explicitly default.
					 */
					 Wrap_Retrieve_Exchange_Coeffs() = default;

					 /*
						@Purpose:
									1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Retrieve_Exchange_Coeffs(_In_ const I32 kts,
						                _In_ const I32 kte)
						               :
						 m_kts{ kts },
						 m_kte{ kte },
						 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_m{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_h{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_q{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 if (0 >= (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 1st Ctor: 'Wrap_Retrieve_Exchange_Coeffs'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Lower range value m_kts: " << m_kts << "\n";
							 std::cerr << "Upper range value m_kte: " << m_kte << "\n";
							 std::cerr << "Range value difference: " << m_kte - m_kts << "\n";
							 std::cerr << "Cannot recover --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Retrieve_Exchange_Coeffs'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kte >= (1 << 16))
						 for (int idx = 0; i != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_dz)[idx][i] = 0.f;
							 }
						 }




#else
						// You must not #undef 'USE_AUTO_VECTORIZATION' macro!!
#if defined (USE_AUTO_VECTORIZATION)
						 for (int idx = 0; i != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_dz)[idx][i] = 0.f;
							 }
						 }


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
					 Wrap_Retrieve_Exchange_Coeffs(_In_ const I32 kts,
						 _In_ const I32 kte,
						 _In_ R32* __restrict const dz,
						 _In_ R32* __restrict const dfm,
						 _In_ R32* __restrict const dfh,
						 _In_ R32* __restrict const dfq)
						 :
						 m_kts{ kts },
						 m_kte{ kte },
						 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_m{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_h{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_q{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 if (0 >= (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 2nd Ctor: 'Wrap_Retrieve_Exchange_Coeffs'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Lower range value m_kts: " << m_kts << "\n";
							 std::cerr << "Upper range value m_kte: " << m_kte << "\n";
							 std::cerr << "Range value difference: " << m_kte - m_kts << "\n";
							 std::cerr << "Cannot recover --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Retrieve_Exchange_Coeffs'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }

						 if (dz  == NULL ||
							 dfm == NULL ||
							 dfh == NULL ||
							 dfq == NULL  ) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Retrieve_Exchange_Coeffs'!!\n";
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
							 m_dz[i] = dz[i];
							 m_dfm[i] = dfm[i];
							 m_dfh[i] = dfh[i];
							 m_dfq[i] = dfq[i];
							 m_K_m[i] = 0.f;
							 m_K_h[i] = 0.f;
							 m_K_q[i] = 0.f;
						 }

#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = dz[i];
							 m_dfm[i] = dfm[i];
							 m_dfh[i] = dfh[i];
							 m_dfq[i] = dfq[i];
							 m_K_m[i] = 0.f;
							 m_K_h[i] = 0.f;
							 m_K_q[i] = 0.f;
						 }

#endif

#endif
			}

					 /*
						@Purpose:
									Copy Constructor implements deep copy semantics.
					 */
					 Wrap_Retrieve_Exchange_Coeffs(_In_ const Wrap_Retrieve_Exchange_Coeffs &x)
						 :
						 m_kts{ x.m_kts },
						 m_kte{ x.m_kte },
						 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_m{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_h{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_K_q{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor: 'Wrap_Retrieve_Exchange_Coeffs'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
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
								 (&this->m_dz)[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }


#else
					// You must not #undef 'USE_AUTO_VECTORIZATION' macro!!
#if defined (USE_AUTO_VECTORIZATION)

						 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_dz)[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }



#endif



#endif
			}

					 /*
						@Purpose:
									Move Constructor implements shallow copy semantics.
					 */
					 Wrap_Retrieve_Exchange_Coeffs(_In_ Wrap_Retrieve_Exchange_Coeffs &&x)
						 :
						 m_kts{ x.m_kts },
						 m_kte{ x.m_kte } {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 x.m_kts = 0;
						 x.m_kte = 0;
			}

					 /*
						@Purpose:
								  Class Destructor.
					 */
					 ~Wrap_Retrieve_Exchange_Coeffs() {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i]) {
								 _mm_free((&this->m_dz)[i]);
							 }
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = NULL;
						 }

						 m_kts = 0;
						 m_kte = 0;
			}

					 /*
						@Purpose:
								  Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Retrieve_Exchange_Coeffs & operator=(_In_ const Wrap_Retrieve_Exchange_Coeffs &x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 constexpr int ntPtrs1{7};
						 R32 *tPtrs1D[ntPtrs1] = {};
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)),align32B));
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if (tPtrs1D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Retrieve_Exchange_Coeffs'!!\n";
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
							 for (int i {0}; i != this->m_totArrays; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = tPtrs1D[i];
						 }

						 return (*this);
#else

#if defined (USE_AUTO_VECTORIZATION)

						 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = tPtrs1D[i];
						 }

						 return (*this);


#endif


#endif
			}

					 /*
						@Purpose:
									Move-assign Operator implements shallow copy semantics.
					 */
					 Wrap_Retrieve_Exchange_Coeffs & operator=(_In_ Wrap_Retrieve_Exchange_Coeffs &&x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 x.m_kts = 0;
						 x.m_kte = 0;

						 return (*this);
			}

					 /*
						@Purpose:
									Call Fortran 90 'RETRIEVE_EXCHANGE_COEFFS' subroutine.
					 */
					 void  Call_Retrieve_Exchange_Coeffs() {

						 MODULE_BL_MYNN_mp_RETRIEVE_EXCHANGE_COEFFS(&this->m_kts, &this->m_kte,
							 &this->m_dz[0], &this->m_dfm[0], &this->m_dfh[0], &this->m_dfq[0],
							 &this->m_K_m[0], &this->m_K_h[0], &this->m_K_q[0]);
			}


					 /*
					   @Purpose:
									Member variables:
					 */

					 // Scalars - Input.

					 I32 m_kts;

					 I32 m_kte;

					 // Arrays 1D - Input.

_Field_size_(m_kte)  R32* __restrict m_dz;

_Field_size_(m_kte)	 R32* __restrict m_dfm;

_Field_size_(m_kte)  R32* __restrict m_dfh;

_Field_size_(m_kte)  R32* __restrict m_dfq;

					// Arrays 1D - Output.

_Field_size_(m_kte)	 R32* __restrict m_K_m;

_Field_size_(m_kte)  R32* __restrict m_K_h;

_Field_size_(m_kte)  R32* __restrict m_K_q;

				static const int m_totArrays = 7;


			};













	}
}







#endif /*__MODULE_BL_MYNN_RETRIEVE_EXCHANGE_COEFFS_IMPL_H__*/