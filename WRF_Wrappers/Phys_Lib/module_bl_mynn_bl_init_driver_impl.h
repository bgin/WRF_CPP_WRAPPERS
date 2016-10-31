
#ifndef __MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_H__
#define __MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_H__

// File granularity version.
#ifndef MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_VERSION_MINOR 
#define MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_CREATE_DATE "Date: 30-10-2016 , Time: 14:39 PM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_AUTHOR
#define MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

namespace phys_lib_wrappers {
	namespace module_bl_mynn {


		template<typename R32 = float,
			     typename I32 = int >  struct Wrap_Mynn_Bl_Init_Driver {

						
					 /*******************************************
								Constructors and Destructor.
					 ********************************************/

					 /*
						@Purpose:
								  Default Constructor - explicitly default.
					 */
					 Wrap_Mynn_Bl_Init_Driver() = default;

					 /*
						@Purpose:
								    1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Mynn_Bl_Init_Driver(_In_ const I32 IDS,
						                      _In_ const I32 IDE,
						                      _In_ const I32 JDS,
						                      _In_ const I32 JDE,
						                      _In_ const I32 KDS,
						                      _In_ const I32 KDE,
						                      _In_ const I32 IMS,
						                      _In_ const I32 IME,
						                      _In_ const I32 JMS,
						                      _In_ const I32 JME,
						                      _In_ const I32 KMS,
						                      _In_ const I32 KME,
						                      _In_ const I32 ITS,
						                      _In_ const I32 ITE,
						                      _In_ const I32 JTS,
						                      _In_ const I32 JTE,
						                      _In_ const I32 KTS,
						                      _In_ const I32 KTE,
						                      _In_ const I32 ALLOWED_TO_READ,
						                      _In_ const I32 RESTART,
						                      _In_ const I32 LEVEL)
						                          :
						                  m_IDS{ IDS },
						                  m_IDE{ IDE },
						                  m_JDS{ JDS },
						                  m_JDE{ JDE },
						                  m_KDS{ KDS },
						                  m_KDE{ KDE },
						                  m_IMS{ IMS },
						                  m_IME{ IME },
						                  m_JMS{ JMS },
						                  m_JME{ JME },
						                  m_KMS{ KMS },
						                  m_KME{ KME },
						                  m_ITS{ ITS },
						                  m_ITE{ ITE },
						                  m_JTS{ JTS },
						                  m_JTE{ JTE },
						                  m_KTS{ KTS },
						                  m_KTE{ KTE },
						                  m_ALLOWED_TO_READ{ ALLOWED_TO_READ },
						                  m_RESTART{ RESTART },
						                  m_LEVEL{ LEVEL },
						                  m_RUBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
						                  m_RVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
						                  m_RTHBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
						                  m_RQVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
						                  m_RQCBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
						                  m_RQIBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
						                  m_QKE{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
						                  m_TKE_PBL{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
										  m_EXCH_H{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) } {

						 // Check for memory allocation errors i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 if ((&this->m_RUBLTEN)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Mynn_Bl_Init_Driver'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_RUBLTEN)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }

						 // Zero-initialize arrays.
						 // Using OpenMP and vectorization for
						 // innermost stride.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_IME * m_KME * m_JME) >= (1 << 20))
						 for (int i = m_IMS; i != m_IME; ++i) {
							 for(int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for (int j = m_JMS; j != m_JME; ++j) {
									 this->m_RUBLTEN[i + m_IME * k + m_KME * j] = 0.0;
									 this->m_RVBLTEN[i + m_IME * k + m_KME * j] = 0.0;
									 this->m_RTHBLTEN[i + m_IME * k + m_KME * j] = 0.0;
									 this->m_RQVBLTEN[i + m_IME * k + m_KME * j] = 0.0;
									 this->m_RQCBLTEN[i + m_IME * k + m_KME * j] = 0.0;
									 this->m_RQIBLTEN[i + m_IME * k + m_KME * j] = 0.0;
									 this->m_QKE[i + m_IME * k + m_KME * j] = 0.0;
									 this->m_TKE_PBL[i + m_IME * k + m_KME * j] = 0.0;
									 this->m_EXCH_H[i + m_IME * k + m_KME * j] = 0.0;
								 }
							 }
						 }

#else
						 // Use loop blocking.
						 // Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
						 for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
							 for (int k = m_KMS; k != m_KME; k += DEFAULT_BLOCK_SIZE) {
								 for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
									 for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
										 for (int kk = k; kk < DEFAULT_BLOCK_SIZE; ++kk) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
											 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
												 this->m_RUBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
												 this->m_RVBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
												 this->m_RTHBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
												 this->m_RQVBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
												 this->m_RQCBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
												 this->m_RQIBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
												 this->m_QKE[ii + m_IME * kk + m_KME * jj] = 0.0;
												 this->m_TKE_PBL[ii + m_IME * kk + m_KME * jj] = 0.0;
												 this->m_EXCH_H[ii + m_IME * kk + m_KME * jj] = 0.0;
											 }
										 }
									 }
								 }
							 }
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

			         Wrap_Mynn_Bl_Init_Driver(_In_ const I32 IDS,
				                              _In_ const I32 IDE,
				                              _In_ const I32 JDS,
				                              _In_ const I32 JDE,
				                              _In_ const I32 KDS,
				                              _In_ const I32 KDE,
				                              _In_ const I32 IMS,
				                              _In_ const I32 IME,
				                              _In_ const I32 JMS,
				                              _In_ const I32 JME,
				                              _In_ const I32 KMS,
				                              _In_ const I32 KME,
				                              _In_ const I32 ITS,
				                              _In_ const I32 ITE,
				                              _In_ const I32 JTS,
				                              _In_ const I32 JTE,
				                              _In_ const I32 KTS,
				                              _In_ const I32 KTE,
				                              _In_ const I32 ALLOWED_TO_READ,
				                              _In_ const I32 RESTART,
				                              _In_ const I32 LEVEL,
				                              _In_ R32* __restrict const RUBLTEN,
				                              _In_ R32* __restrict const RVBLTEN,
				                              _In_ R32* __restrict const RTHBLTEN,
				                              _In_ R32* __restrict const RQVBLTEN,
				                              _In_ R32* __restrict const RQCBLTEN,
				                              _In_ R32* __restrict const RQIBLTEN,
				                              _In_ R32* __restrict const QKE,
				                              _In_ R32* __restrict const TKE_PBL,
				                              _In_ R32* __restrict const EXCH_H)
				                               :
			                             m_IDS{ IDS },
				                         m_IDE{ IDE },
				                         m_JDS{ JDS },
				                         m_JDE{ JDE },
				                         m_KDS{ KDS },
				                         m_KDE{ KDE },
				                         m_IMS{ IMS },
				                         m_IME{ IME },
				                         m_JMS{ JMS },
				                         m_JME{ JME },
				                         m_KMS{ KMS },
				                         m_KME{ KME },
				                         m_ITS{ ITS },
				                         m_ITE{ ITE },
				                         m_JTS{ JTS },
				                         m_JTE{ JTE },
				                         m_KTS{ KTS },
				                         m_KTE{ KTE },
				                         m_ALLOWED_TO_READ{ ALLOWED_TO_READ },
				                         m_RESTART{ RESTART },
				                         m_LEVEL{ LEVEL },
				                         m_RUBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                         m_RVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                         m_RTHBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                         m_RQVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                         m_RQCBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                         m_RQIBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                         m_QKE{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                         m_TKE_PBL{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
										 m_EXCH_H{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) } {

						 // Check for occurrence of memory allocation errors i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 if ((&this->m_RUBLTEN)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mynn_Bl_Init_Driver'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_RUBLTEN)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Check for null pointers in call input arrays.
						 if (RUBLTEN  == NULL ||
							 RVBLTEN  == NULL ||
							 RTHBLTEN == NULL ||
							 RQVBLTEN == NULL ||
							 RQCBLTEN == NULL ||
							 RQIBLTEN == NULL ||
							 QKE      == NULL ||
							 TKE_PBL  == NULL ||
							 EXCH_H   == NULL  )  {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mynn_Bl_Init_Driver'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "One or more caller's arrays contains invalid pointer!!\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

						 // Copy caller's input arrays.
						 // Using OpenMP for outermost loop 
						 // and vectorization for innermost loop.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_IME * m_KME * m_JME) >= (1 << 20))
						 for (int i = m_IMS; i != m_IME; ++i) {
							 for(int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for(int j = m_JMS; j != m_JME; ++j) {
									 this->m_RUBLTEN[i + m_IME * k + m_KME * j] = RUBLTEN[i + m_IME * k + m_KME * j];
									 this->m_RVBLTEN[i + m_IME * k + m_KME * j] = RVBLTEN[i + m_IME * k + m_KME * j];
									 this->m_RTHBLTEN[i + m_IME * k + m_KME * j] = RTHBLTEN[i + m_IME * k + m_KME * j];
									 this->m_RQVBLTEN[i + m_IME * k + m_KME * j] = RQVBLTEN[i + m_IME * k + m_KME * j];
									 this->m_RQCBLTEN[i + m_IME * k + m_KME * j] = RQCBLTEN[i + m_IME * k + m_KME * j];
									 this->m_RQIBLTEN[i + m_IME * k + m_KME * j] = RQIBLTEN[i + m_IME * k + m_KME * j];
									 this->m_QKE[i + m_IME * k + m_KME * j] = QKE[i + m_IME * k + m_KME * j];
									 this->m_TKE_PBL[i + m_IME * k + m_KME * j] = TKE_PBL[i + m_IME * k + m_KME * j];
									 this->m_EXCH_H[i + m_IME * k + m_KME * j] = EXCH_H[i + m_IME * k + m_KME * j];
								 }
							 }
						 }

#else
						 // Use loop blocking.
						 // Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
						 for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
							 for (int k = m_KMS; k != m_KME; k += DEFAULT_BLOCK_SIZE) {
								 for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
									 for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
										 for (int kk = k; kk < DEFAULT_BLOCK_SIZE; ++kk) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
											 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
												 this->m_RUBLTEN[ii + m_IME * kk + m_KME * jj] = RUBLTEN[ii + m_IME * kk + m_KME * jj];
												 this->m_RVBLTEN[ii + m_IME * kk + m_KME * jj] = RVBLTEN[ii + m_IME * kk + m_KME * jj];
												 this->m_RTHBLTEN[ii + m_IME * kk + m_KME * jj] = RTHBLTEN[ii + m_IME * kk + m_KME * jj];
												 this->m_RQVBLTEN[ii + m_IME * kk + m_KME * jj] = RQVBLTEN[ii + m_IME * kk + m_KME * jj];
												 this->m_RQCBLTEN[ii + m_IME * kk + m_KME * jj] = RQCBLTEN[ii + m_IME * kk + m_KME * jj];
												 this->m_RQIBLTEN[ii + m_IME * kk + m_KME * jj] = RQIBLTEN[ii + m_IME * kk + m_KME * jj];
												 this->m_QKE[ii + m_IME * kk + m_KME * jj] = QKE[ii + m_IME * kk + m_KME * jj];
												 this->m_TKE_PBL[ii + m_IME * kk + m_KME * jj] = TKE_PBL[ii + m_IME * kk + m_KME * jj];
												 this->m_EXCH_H[ii + m_IME * kk + m_KME * jj] = EXCH_H[ii + m_IME * kk + m_KME * jj];
											 }
										 }
									 }
								 }
							 }
						 }



#endif

			}

					 /*
						@Purpose:
								  Copy Constructor implements deep copy semantics.
					 */
			         Wrap_Mynn_Bl_Init_Driver(_In_ const Wrap_Mynn_Bl_Init_Driver &x)
				                           :
				                       m_IDS{ x.m_IDS },
				                       m_IDE{ x.m_IDE },
				                       m_JDS{ x.m_JDS },
				                       m_JDE{ x.m_JDE },
				                       m_KDS{ x.m_KDS },
				                       m_KDE{ x.m_KDE },
				                       m_IMS{ x.m_IMS },
				                       m_IME{ x.m_IME },
				                       m_JMS{ x.m_JMS },
				                       m_JME{ x.m_JME },
				                       m_KMS{ x.m_KMS },
				                       m_KME{ x.m_KME },
				                       m_ITS{ x.m_ITS },
				                       m_ITE{ x.m_ITE },
				                       m_JTS{ x.m_JTS },
				                       m_JTE{ x.m_JTE },
				                       m_KTS{ x.m_KTS },
				                       m_KTE{ x.m_KTE },
				                       m_ALLOWED_TO_READ{ x.m_ALLOWED_TO_READ },
				                       m_RESTART{ x.m_RESTART },
				                       m_LEVEL{ x.m_LEVEL },
				                       m_RUBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                       m_RVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                       m_RTHBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                       m_RQVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                       m_RQCBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                       m_RQIBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                       m_QKE{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
				                       m_TKE_PBL{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									   m_EXCH_H{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) } {

						 // Check for memory allocation errors i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 if ((&this->m_RUBLTEN)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Ctor: 'Wrap_Mynn_Bl_Init_Driver'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_RUBLTEN)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Copy caller's input arrays.
						 // Using OpenMP for outermost loop 
						 // and vectorization for innermost loop.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_IME * m_KME * m_JME) >= (1 << 20))
						 for (int i = m_IMS; i != m_IME; ++i) {
							 for (int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for(int j = m_JMS; j != m_JME; ++j) {
									 this->m_RUBLTEN[i + m_IME * k + m_KME * j] = x.m_RUBLTEN[i + x.m_IME * k + x.m_KME * j];
									 this->m_RVBLTEN[i + m_IME * k + m_KME * j] = x.m_RVBLTEN[i + x.m_IME * k + x.m_KME * j];
									 this->m_RTHBLTEN[i + m_IME * k + m_KME * j] = x.m_RTHBLTEN[i + x.m_IME * k + x.m_KME * j];
									 this->m_RQVBLTEN[i + m_IME * k + m_KME * j] = x.m_RQVBLTEN[i + x.m_IME * k + x.m_KME * j];
									 this->m_RQCBLTEN[i + m_IME * k + m_KME * j] = x.m_RQCBLTEN[i + x.m_IME * k + x.m_KME * j];
									 this->m_RQIBLTEN[i + m_IME * k + m_KME * j] = x.m_RQIBLTEN[i + x.m_IME * k + x.m_KME * j];
									 this->m_QKE[i + m_IME * k + m_KME * j] = x.m_QKE[i + x.m_IME * k + x.m_KME * j];
									 this->m_TKE_PBL[i + m_IME * k + m_KME * j] = x.m_TKE_PBL[i + x.m_IME * k + x.m_KME * j];
									 this->m_EXCH_H[i + m_IME * k + m_KME * j] = x.m_EXCH_H[i + x.m_IME * k + x.m_KME * j];
								 }
							 }
						 }


#else

						 // Use loop blocking.
						 // Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
						 for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
							 for (int k = m_KMS; k != m_KME; k += DEFAULT_BLOCK_SIZE) {
								 for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
									 for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
										 for (int kk = k; kk < DEFAULT_BLOCK_SIZE; ++kk) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
											 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
												 this->m_RUBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RUBLTEN[ii + x.m_IME * kk + x.m_KME * jj];
												 this->m_RVBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RVBLTEN[ii + x.m_IME * kk + x.m_KME * jj];
												 this->m_RTHBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RTHBLTEN[ii + x.m_IME * kk + x.m_KME * jj];
												 this->m_RQVBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RQVBLTEN[ii + x.m_IME * kk + x.m_KME * jj];
												 this->m_RQCBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RQCBLTEN[ii + x.m_IME * kk + x.m_KME * jj];
												 this->m_RQIBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RQIBLTEN[ii + x.m_IME * kk + x.m_KME * jj];
												 this->m_QKE[ii + m_IME * kk + m_KME * jj] = x.m_QKE[ii + x.m_IME * kk + x.m_KME * jj];
												 this->m_TKE_PBL[ii + m_IME * kk + m_KME * jj] = x.m_TKE_PBL[ii + x.m_IME * kk + x.m_KME * jj];
												 this->m_EXCH_H[ii + m_IME * kk + m_KME * jj] = x.m_EXCH_H[ii + x.m_IME * kk + x.m_KME * jj];
											 }
										 }
									 }
								 }
							 }
						 }


#endif


			}

					 /*
						@Purpose:
								 Move Constructor implements shallow copy semantics.
					 */
			         Wrap_Mynn_Bl_Init_Driver(_In_ Wrap_Mynn_Bl_Init_Driver &&x)
				                             :
				                       m_IDS{ x.m_IDS },
				                       m_IDE{ x.m_IDE },
				                       m_JDS{ x.m_JDS },
				                       m_JDE{ x.m_JDE },
				                       m_KDS{ x.m_KDS },
				                       m_KDE{ x.m_KDE },
				                       m_IMS{ x.m_IMS },
				                       m_IME{ x.m_IME },
				                       m_JMS{ x.m_JMS },
				                       m_JME{ x.m_JME },
				                       m_KMS{ x.m_KMS },
				                       m_KME{ x.m_KME },
				                       m_ITS{ x.m_ITS },
				                       m_ITE{ x.m_ITE },
				                       m_JTS{ x.m_JTS },
				                       m_JTE{ x.m_JTE },
				                       m_KTS{ x.m_KTS },
				                       m_KTE{ x.m_KTE },
				                       m_ALLOWED_TO_READ{ x.m_ALLOWED_TO_READ },
				                       m_RESTART{ x.m_RESTART },
									   m_LEVEL{ x.m_LEVEL } {

						 // Reassign x's pointers to *this.
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 if ((&x.m_RUBLTEN)[i]) {
								 (&this->m_RUBLTEN)[i] = (&x.m_RUBLTEN)[i];
							 }
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 (&x.m_RUBLTEN)[i] = NULL;
						 }
						 x.m_IMS = 0;
						 x.m_IME = 0;
						 x.m_KMS = 0;
						 x.m_KME = 0;
						 x.m_JMS = 0;
						 x.m_JME = 0;
			}

					 /*
						@Purpose:
						          Class Destructor.
					 */
					 ~Wrap_Mynn_Bl_Init_Driver() {
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 if ((&this->m_RUBLTEN)[i]) {
								 _mm_free((&this->m_RUBLTEN)[i]);
							 }
						 }
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 (&this->m_RUBLTEN)[i] = NULL;
						 }
						 this->m_IMS = 0;
						 this->m_IME = 0;
						 this->m_JMS = 0;
						 this->m_JME = 0;
						 this->m_KMS = 0;
						 this->m_KME = 0;
			}

					 /*
						@Purpose:
								 Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Mynn_Bl_Init_Driver & operator=(_In_ const Wrap_Mynn_Bl_Init_Driver &x) {
						 if (this == &x) return (*this);

						 this->m_IDS = x.m_IDS;
						 this->m_IDE = x.m_IDE;
						 this->m_JDS = x.m_JDS;
						 this->m_JDE = x.m_JDE;
						 this->m_KDS = x.m_KDS;
						 this->m_KDE = x.m_KDE;
						 this->m_IMS = x.m_IMS;
						 this->m_IME = x.m_IME;
						 this->m_JMS = x.m_JMS;
						 this->m_JME = x.m_JME;
						 this->m_KMS = x.m_KMS;
						 this->m_KME = x.m_KME;
						 this->m_ITS = x.m_ITS;
						 this->m_ITE = x.m_ITE;
						 this->m_JTS = x.m_JTS;
						 this->m_JTE = x.m_JTE;
						 this->m_KTS = x.m_KTS;
						 this->m_KTE = x.m_KTE;
						 this->m_ALLOWED_TO_READ = x.m_ALLOWED_TO_READ;
						 this->m_RESTART = x.m_RESTART;
						 this->m_LEVEL = x.m_LEVEL;
						 constexpr int ntPtrs3D = 9;
						 R32  *tPtrs3D[ntPtrs3D] = {};
						 for (int i{ 0 }; i != ntPtrs3D; ++i) {
							 tPtrs3D[i] = reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)),align32B));
						 }
						 // Check for memory allocation errors.
						 for (int i{ 0 }; i != m_nArrays3D; ++i) {
							 if (tPtrs3D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mynn_Bl_Init_Driver'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs3D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 }
						 }
						 // Copy caller's input arrays.
						 // Using OpenMP for outermost loop 
						 // and vectorization for innermost loop.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_IME * m_KME * m_JME) >= (1 << 20))
						 for (int i = m_IMS; i != m_IME; ++i) {
							 for(int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for (int j = m_JMS; j != m_JME; ++j) {
									 tPtrs3D[0][i + m_IME * k + m_KME * j] = x.m_RUBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[1][i + m_IME * k + m_KME * j] = x.m_RVBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[2][i + m_IME * k + m_KME * j] = x.m_RTHBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[3][i + m_IME * k + m_KME * j] = x.m_RQVBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[4][i + m_IME * k + m_KME * j] = x.m_RQCBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[5][i + m_IME * k + m_KME * j] = x.m_RQIBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[6][i + m_IME * k + m_KME * j] = x.m_QKE[i + m_IME * k + m_KME * j];
									 tPtrs3D[7][i + m_IME * k + m_KME * j] = x.m_TKE_PBL[i + m_IME * k + m_KME * j];
									 tPtrs3D[8][i + m_IME * k + m_KME * j] = x.m_EXCH_H[i + m_IME * k + m_KME * j];
								 }
                             }
						 }
						 // Deallocate current context of *this.
						 for(int i{0}; i != this->m_nArrays3D; ++i) {
							 _mm_free((&this->m_RUBLTEN)[i]);
						 }
						 // Reassign temporay pointers to member pointers.
						 this->m_RUBLTEN = tPtrs3D[0];
						 this->m_RVBLTEN = tPtrs3D[1];
						 this->m_RTHBLTEN = tPtrs3D[2];
						 this->m_RQVBLTEN = tPtrs3D[3];
						 this->m_RQCBLTEN = tPtrs3D[4];
						 this->m_RQIBLTEN = tPtrs3D[5];
						 this->m_QKE = tPtrs3D[6];
						 this->m_TKE_PBL = tPtrs3D[7];
						 this->m_EXCH_H = tPtrs3D[8];

						 return (*this);

#else
						 // Use loop blocking.
						 // Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
						 for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
							 for (int k = m_KMS; k != m_KME; k += DEFAULT_BLOCK_SIZE) {
								 for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
									 for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
										 for (int kk = k; kk < DEFAULT_BLOCK_SIZE; ++kk) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
											 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
												 tPtrs3D[0][ii + m_IME * kk + m_KME * jj] = x.m_RUBLTEN[ii + m_IME * kk + m_KME * jj];
												 tPtrs3D[1][ii + m_IME * kk + m_KME * jj] = x.m_RVBLTEN[ii + m_IME * kk + m_KME * jj];
												 tPtrs3D[2][ii + m_IME * kk + m_KME * jj] = x.m_RTHBLTEN[ii + m_IME * kk + m_KME * jj];
												 tPtrs3D[3][ii + m_IME * kk + m_KME * jj] = x.m_RQVBLTEN[ii + m_IME * kk + m_KME * jj];
												 tPtrs3D[4][ii + m_IME * kk + m_KME * jj] = x.m_RQCBLTEN[ii + m_IME * kk + m_KME * jj];
												 tPtrs3D[5][ii + m_IME * kk + m_KME * jj] = x.m_RQIBLTEN[ii + m_IME * kk + m_KME * jj];
												 tPtrs3D[6][ii + m_IME * kk + m_KME * jj] = x.m_QKE[ii + m_IME * kk + m_KME * jj];
												 tPtrs3D[7][ii + m_IME * kk + m_KME * jj] = x.m_TKE_PBL[ii + m_IME * kk + m_KME * jj];
												 tPtrs3D[8][ii + m_IME * kk + m_KME * jj] = x.m_EXCH_H[ii + m_IME * kk + m_KME * jj];
											 }
										 }
									 }
								 }
							 }
						 }
						 // Deallocate current context of *this.
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 _mm_free((&this->m_RUBLTEN)[i]);
						 }
						 // Reassign temporay pointers to member pointers.
						 this->m_RUBLTEN = tPtrs3D[0];
						 this->m_RVBLTEN = tPtrs3D[1];
						 this->m_RTHBLTEN = tPtrs3D[2];
						 this->m_RQVBLTEN = tPtrs3D[3];
						 this->m_RQCBLTEN = tPtrs3D[4];
						 this->m_RQIBLTEN = tPtrs3D[5];
						 this->m_QKE = tPtrs3D[6];
						 this->m_TKE_PBL = tPtrs3D[7];
						 this->m_EXCH_H = tPtrs3D[8];

						 return (*this);
#endif

			}

					  /*
						 @Purpose:
								  Move-assign Operator implements shallow copy semantics.
					  */
			         Wrap_Mynn_Bl_Init_Driver & operator=(_In_ Wrap_Mynn_Bl_Init_Driver &&x) {
						 if (this == &x) return (*this);

						 this->m_IDS = x.m_IDS;
						 this->m_IDE = x.m_IDE;
						 this->m_JDS = x.m_JDS;
						 this->m_JDE = x.m_JDE;
						 this->m_KDS = x.m_KDS;
						 this->m_KDE = x.m_KDE;
						 this->m_IMS = x.m_IMS;
						 this->m_IME = x.m_IME;
						 this->m_JMS = x.m_JMS;
						 this->m_JME = x.m_JME;
						 this->m_KMS = x.m_KMS;
						 this->m_KME = x.m_KME;
						 this->m_ITS = x.m_ITS;
						 this->m_ITE = x.m_ITE;
						 this->m_JTS = x.m_JTS;
						 this->m_JTE = x.m_JTE;
						 this->m_KTS = x.m_KTS;
						 this->m_KTE = x.m_KTE;
						 this->m_ALLOWED_TO_READ = x.m_ALLOWED_TO_READ;
						 this->m_RESTART = x.m_RESTART;
						 this->m_LEVEL = x.m_LEVEL;
						 // Deallocate current context.
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 if ((&this->m_RUBLTEN)[i]) {
								 _mm_free((&this->m_RUBLTEN)[i]);
							 }
						 }
						 // Reassign x's pointers to *this's pointers.
						 for (int i{ 0 }; i != this->m_nArrays3D; ++i) {
							 (&this->m_RUBLTEN)[i] = (x.m_RUBLTEN)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != x.m_nArrays3D; ++i) {
							 (x.m_RUBLTEN)[i] = NULL;
						 }
						 x.m_IMS = 0;
						 x.m_IME = 0;
						 x.m_KMS = 0;
						 x.m_KME = 0;
						 x.m_JMS = 0;
						 x.m_JME = 0;

						 return (*this);
			}

					 /*
						@Purpose:
						          Call Fortran 90 'MYNN_BL_INIT_DRIVER' subroutine.
					 */
					 void  Call_Mynn_Bl_Init_Driver() {

						 MODULE_BL_MYNN_mp_MYNN_BL_INIT_DRIVER(&this->m_RUBLTEN[0], &this->m_RUBLTEN[0], &this->m_RTHBLTEN[0],
							 &this->m_RQVBLTEN[0], &this->m_RQCBLTEN[0], &this->m_RQIBLTEN[0],
							 &this->m_QKE[0], &this->m_TKE_PBL[0], &this->m_EXCH_H[0],
							 &this->m_RESTART, &this->m_ALLOWED_TO_READ, &this->m_LEVEL,
							 &this->m_IDS, &this->m_IDE, &this->m_JDS, &this->m_JDE, &this->m_KDS, &this->m_KDE,
							 &this->m_IMS, &this->m_IME, &this->m_JMS, &this->m_JME, &this->m_KMS, &this->m_KME,
							 &this->m_ITS, &this->m_ITE, &this->m_JTS, &this->m_JTE, &this->m_KTS, &this->m_KTE);
					 }


					 /*
						@Purpose:
								  Member variables.
					 */

					 // Memory and patch dimension variables.

					 I32 m_IDS;

					 I32 m_IDE;

					 I32 m_JDS;

					 I32 m_JDE;

					 I32 m_KDS;

					 I32 m_KDE;

					 I32 m_IMS;

					 I32 m_IME;

					 I32 m_JMS;

					 I32 m_JME;

					 I32 m_KMS;

					 I32 m_KME;

					 I32 m_ITS;

					 I32 m_ITE;

					 I32 m_JTS;

					 I32 m_JTE;

					 I32 m_KTS;

					 I32 m_KTE;

					 I32 m_ALLOWED_TO_READ;

					 I32 m_RESTART;

					 I32 m_LEVEL;

					 // Array variables.

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RUBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RVBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RTHBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RQVBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RQCBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RQIBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_QKE;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_TKE_PBL;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_EXCH_H;

					 static const int m_nArrays3D = 9;

			};









	}
}


#endif /*__MODULE_BL_MYNN_BL_INIT_DRIVER_IMPL_H__*/