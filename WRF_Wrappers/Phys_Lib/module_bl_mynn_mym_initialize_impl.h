#ifndef __MODULE_BL_MYNN_MYM_INITIALIZE_IMPL_H__
#define __MODULE_BL_MYNN_MYM_INITIALIZE_IMPL_H__


// File version granularity.
#ifndef MODULE_BL_MYNN_MYM_INITIALIZE_VERSION_MAJOR
#define MODULE_BL_MYNN_MYM_INITIALIZE_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_MYM_INITIALIZE_VERSION_MINOR 
#define MODULE_BL_MYNN_MYM_INITIALIZE_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_MYM_INITIALIZE_PATCH_VERSION
#define MODULE_BL_MYNN_MYM_INITIALIZE_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_MYM_INITIALIZE_CREATE_DATE
#define MODULE_BL_MYNN_MYM_INITIALIZE_CREATE_DATE "Date: 06-11-2016 , Time: 12:30 PM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_MYM_INITIALIZE_BUILD_DATE
#define MODULE_BL_MYNN_MYM_INITIALIZE_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_MYM_INITIALIZE_AUTHOR
#define MODULE_BL_MYNN_MYM_INITIALIZE_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"


namespace wrf_phys_wrappers {
	namespace module_bl_mynn {


		template<typename R32 = float,
			     typename I32 = int  >   struct Wrap_Mym_Initialize{



					 /******************************************
						   Constructors and Destructors.
					 *******************************************/

					 /*
						@Purpose:
								  Default Constructor - explicitly default.
					 */
					 Wrap_Mym_Initialize() = default;

					 /*
						@Purpose:
								    1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Mym_Initialize(_In_ const I32 KTS,
										 _In_ const I32 KTE,
						                 _In_ const I32 bl_mynn_mixlength,
						                 _In_ const I32 bl_mynn_edmf,
						                 _In_ const R32 ust,
						                 _In_ const R32 rmo,
						                 _In_ const R32 zi,
						                 _In_ const R32 Psig_bl)
						                 :
						            m_KTS{ KTS },
						            m_KTE{ KTE },
						            m_bl_mynn_mixlength{ bl_mynn_mixlength },
						            m_bl_mynn_edmf{ bl_mynn_edmf },
						            m_ust{ ust },
						            m_rmo{ rmo },
						            m_zi{ zi },
						            m_Psig_bl{ Psig_bl },
						            m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_KTE + 1) * sizeof(R32)), align32B)) },
						            m_u{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_v{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_edmf_a1{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_Qke{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
									m_Tsq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
									m_Qsq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_Cov{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
						            m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
									m_el{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) } {

						 // Check for memory allocation errors i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Mym_Initialize'!!\n";
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
							 this->m_zw[i] = 0.F;
							 this->m_u[i] = 0.F;
							 this->m_v[i] = 0.F;
							 this->m_thl[i] = 0.F;
							 this->m_qw[i] = 0.F;
							 this->m_theta[i] = 0.F;
							 this->m_cldfra_bl1D[i] = 0.F;
							 this->m_edmf_a1[i] = 0.F;
							 this->m_edmf_qc1[i] = 0.F;
							 this->m_Qke[i] = 0.F;
							 this->m_Tsq[i] = 0.F;
							 this->m_Qsq[i] = 0.F;
							 this->m_Cov[i] = 0.F;
							 this->m_sh[i] = 0.F;
							 this->m_el[i] = 0.F;
						 }
						 const int top = this->m_KTE + 1;
						 this->m_zw[top] = 0.F;


#else
						 
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)						
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = 0.F;
							 this->m_zw[i] = 0.F;
							 this->m_u[i] = 0.F;
							 this->m_v[i] = 0.F;
							 this->m_thl[i] = 0.F;
							 this->m_qw[i] = 0.F;
							 this->m_theta[i] = 0.F;
							 this->m_cldfra_bl1D[i] = 0.F;
							 this->m_edmf_a1[i] = 0.F;
							 this->m_edmf_qc1[i] = 0.F;
							 this->m_Qke[i] = 0.F;
							 this->m_Tsq[i] = 0.F;
							 this->m_Qsq[i] = 0.F;
							 this->m_Cov[i] = 0.F;
							 this->m_sh[i] = 0.F;
							 this->m_el[i] = 0.F;
						 }
						 const int top = this->m_KTE + 1;
						 this->m_zw[top] = 0.F;


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
					 Wrap_Mym_Initialize(_In_ const I32 KTS,
				                         _In_ const I32 KTE,
				                         _In_ const I32 bl_mynn_mixlength,
				                         _In_ const I32 bl_mynn_edmf,
				                         _In_ const R32 ust,
				                         _In_ const R32 rmo,
				                         _In_ const R32 zi,
				                         _In_ const R32 Psig_bl,
				                         _In_ R32* __restrict const dz,
				                         _In_ R32* __restrict const zw,
				                         _In_ R32* __restrict const u,
				                         _In_ R32* __restrict const v,
				                         _In_ R32* __restrict const thl,
				                         _In_ R32* __restrict const qw,
				                         _In_ R32* __restrict const cldfra_bl1D,
				                         _In_ R32* __restrict const edmf_a1,
				                         _In_ R32* __restrict const edmf_qc1,
				                         _In_ R32* __restrict const el,
				                         _In_ R32* __restrict const Qke)
				                              :
				                        m_KTS{ KTS },
				                        m_KTE{ KTE },
				                        m_bl_mynn_mixlength{ bl_mynn_mixlength },
				                        m_bl_mynn_edmf{ bl_mynn_edmf },
				                        m_ust{ ust },
				                        m_rmo{ rmo },
				                        m_zi{ zi },
				                        m_Psig_bl{ Psig_bl },
				                        m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_KTE + 1) * sizeof(R32)), align32B)) },
				                        m_u{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_v{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_edmf_a1{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_Qke{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_Tsq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_Qsq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_Cov{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                        m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
										m_el{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) } {

						 // Check for memory allocation errors i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Initialize'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Check for null pointers occurrence in arrays input args.
						 if (dz          == NULL,
							 zw          == NULL,
							 u           == NULL,
							 v           == NULL,
							 thl         == NULL,
							 qw          == NULL,
							 cldfra_bl1D == NULL,
							 edmf_a1     == NULL,
							 edmf_qc1    == NULL,
							 el          == NULL,
							 Qke         == NULL) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Initialize''!!\n";
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
#pragma omp parallel for if(m_KME >= (1 << 20))
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = dz[i];
							 this->m_zw[i] = zw[i];
							 this->m_u[i] = u[i];
							 this->m_v[i] = v[i];
							 this->m_thl[i] = thl[i];
							 this->m_qw[i] = qw[i];
							 this->m_theta[i] = 0.F;
							 this->m_cldfra_bl1D[i] = cldfra_bl1D[i];
							 this->m_edmf_a1[i] = edmf_a1[i];
							 this->m_edmf_qc1[i] = edmf_qc1[i];
							 this->m_Qke[i] = Qke[i];
							 this->m_Tsq[i] = 0.F;
							 this->m_Qsq[i] = 0.F;
							 this->m_Cov[i] = 0.F;
							 this->m_sh[i] = 0.F;
							 this->m_el[i] = el[i];
						 }
						 const int top = this->m_KTE + 1;
						 this->m_zw[top] = zw[top];


#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = dz[i];
							 this->m_zw[i] = zw[i];
							 this->m_u[i] = u[i];
							 this->m_v[i] = v[i];
							 this->m_thl[i] = thl[i];
							 this->m_qw[i] = qw[i];
							 this->m_theta[i] = 0.F;
							 this->m_cldfra_bl1D[i] = cldfra_bl1D[i];
							 this->m_edmf_a1[i] = edmf_a1[i];
							 this->m_edmf_qc1[i] = edmf_qc1[i];
							 this->m_Qke[i] = Qke[i];
							 this->m_Tsq[i] = 0.F;
							 this->m_Qsq[i] = 0.F;
							 this->m_Cov[i] = 0.F;
							 this->m_sh[i] = 0.F;
							 this->m_el[i] = el[i];
						 }
						 const int top = this->m_KTE + 1;
						 this->m_zw[top] = zw[top];



#endif



			}

			         /*
						@Purpose:
								  Copy Constructor implements deep copy semantics.
			          */
					 Wrap_Mym_Initialize(_In_ const Wrap_Mym_Initialize &x)
				                       :
				                  m_KTS{ x.m_KTS },
				                  m_KTE{ x.m_KTE },
				                  m_bl_mynn_mixlength{ x.m_bl_mynn_mixlength },
				                  m_bl_mynn_edmf{ x.m_bl_mynn_edmf },
				                  m_ust{ x.m_ust },
				                  m_rmo{ x.m_rmo },
				                  m_zi{ x.m_zi },
				                  m_Psig_bl{ x.m_Psig_bl },
				                  m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_KTE + 1) * sizeof(R32)), align32B)) },
				                  m_u{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_v{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_edmf_a1{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_Qke{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_Tsq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_Qsq{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_Cov{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
				                  m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) },
								  m_el{ reinterpret_cast<R32*>(_mm_malloc((m_KTE * sizeof(R32)), align32B)) } {

						 // Check for memory allocation errors i.e. (malloc failures).
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Ctor: 'Wrap_Mym_Initialize'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Copy caller's input arrays.
						 // Using OpenMP for outermost loop 
						 // and vectorization for innermost loop.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_KME >= (1 << 20))
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = x.m_dz[i];
							 this->m_zw[i] = x.m_zw[i];
							 this->m_u[i] = x.m_u[i];
							 this->m_v[i] = x.m_v[i];
							 this->m_thl[i] = x.m_thl[i];
							 this->m_qw[i] = x.m_qw[i];
							 this->m_theta[i] = x.m_theta[i];
							 this->m_cldfra_bl1D[i] = x.m_cldfra_bl1D[i];
							 this->m_edmf_a1[i] = x.m_edmf_a1[i];
							 this->m_edmf_qc1[i] = x.m_edmf_qc1[i];
							 this->m_Qke[i] = x.m_Qke[i];
							 this->m_Tsq[i] = x.m_Tsq[i];
							 this->m_Qsq[i] = x.m_Qsq[i];
							 this->m_Cov[i] = x.m_Cov[i];
							 this->m_sh[i] = x.m_sh[i];
							 this->m_el[i] = x.m_el[i];
						 }
						 const int top = this->m_KTE + 1;
						 this->m_zw[top] = x.m_zw[top];


#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_KTS; i != m_KTE; ++i) {
							 this->m_dz[i] = x.m_dz[i];
							 this->m_zw[i] = x.m_zw[i];
							 this->m_u[i] = x.m_u[i];
							 this->m_v[i] = x.m_v[i];
							 this->m_thl[i] = x.m_thl[i];
							 this->m_qw[i] = x.m_qw[i];
							 this->m_theta[i] = x.m_theta[i];
							 this->m_cldfra_bl1D[i] = x.m_cldfra_bl1D[i];
							 this->m_edmf_a1[i] = x.m_edmf_a1[i];
							 this->m_edmf_qc1[i] = x.m_edmf_qc1[i];
							 this->m_Qke[i] = x.m_Qke[i];
							 this->m_Tsq[i] = x.m_Tsq[i];
							 this->m_Qsq[i] = x.m_Qsq[i];
							 this->m_Cov[i] = x.m_Cov[i];
							 this->m_sh[i] = x.m_sh[i];
							 this->m_el[i] = x.m_el[i];
						 }
						 const int top = this->m_KTE + 1;
						 this->m_zw[top] = x.m_zw[top];





#endif



			}

					 /*
						@Purpose:
									Move Constructor implements shallow copy semantics.
					  */
					 Wrap_Mym_Initialize(_In_ Wrap_Mym_Initialize &&x)
								:
							 m_KTS{ x.m_KTS },
							 m_KTE{ x.m_KTE },
							 m_bl_mynn_mixlength{ x.m_bl_mynn_mixlength },
							 m_bl_mynn_edmf{ x.m_bl_mynn_edmf },
							 m_ust{ x.m_ust },
							 m_rmo{ x.m_rmo },
							 m_zi{ x.m_zi },
							 m_Psig_bl{ x.m_Psig_bl } {

						 // Reassign x's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 x.m_KTS = x.m_KTE = 0;
			}

					 /*
						@Purpose:
								  Class Destructor.
					 */
					 ~Wrap_Mym_Initialize() {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i]) {
								 _mm_free((&this->m_dz)[i]);
							 }
						 }
						 this->m_KTS = 0;
						 this->m_KTE = 0;
			}

					 /*
						@Purpose:
								  Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Mym_Initialize & operator=(_In_ const Wrap_Mym_Initialize &x) {
						 if (this == &x) return (*this);

						 this->m_KTS = x.m_KTS;
						 this->m_KTE = x.m_KTE;
						 this->m_bl_mynn_mixlength = x.m_bl_mynn_mixlength;
						 this->m_bl_mynn_edmf = x.m_bl_mynn_edmf;
						 this->m_ust = x.m_ust;
						 this->m_rmo = x.m_rmo;
						 this->m_zi = x.m_zi;
						 this->m_Psig_bl = x.m_Psig_bl;
						 constexpr int ntPtrs1D{16};
						 R32  *tPtrs1D[ntPtrs1D] = {};
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R32*>(_mm_malloc(((m_KME + 1) * sizeof(R32)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if (tPtrs1D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mym_Initialize'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs1D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_KME >= (1 << 20))
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
						 const int top = this->m_KTE + 1;
						 tPtrs1D[1][top] = x.m_zw[top];
						 // Deallocate current context of *this.
						 for(int i{0}; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
						 // Copy temp pointers to *this.
						 for(int i{0}; i != this->m_totArrays; ++i) {
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
						 const int top = this->m_KTE + 1;
						 tPtrs1D[1][top] = x.m_zw[top];
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
					 Wrap_Mym_Initialize & operator=(_In_ Wrap_Mym_Initialize &&x) {
						 if (this == &x) return (*this);

						 this->m_KTS = x.m_KTS;
						 this->m_KTE = x.m_KTE;
						 this->m_bl_mynn_mixlength = x.m_bl_mynn_mixlength;
						 this->m_bl_mynn_edmf = x.m_bl_mynn_edmf;
						 this->m_ust = x.m_ust;
						 this->m_rmo = x.m_rmo;
						 this->m_zi = x.m_zi;
						 this->m_Psig_bl = x.m_Psig_bl;
						 // Deallocate current context.
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
						 x.m_KTS = x.m_KTE = 0;

						 return (*this);
			}

					 /*
						@Purpose:
							      Call Fortran 90 'MYM_INITIALIZE' subroutine.
					 */
					 void  Call_Mym_Initialize() {

						 MODULE_BL_MYNN_mp_MYM_INITIALIZE(&this->m_KTS, &this->m_KTE,
							 &this->m_dz[0], &this->m_zw[0], &this->m_u[0], &this->m_v[0],
							 &this->m_thl[0], &this->m_qw[0], 
							 &this->m_zi, &this->m_theta[0], &this->m_sh[0],
							 &this->m_ust, &this->m_rmo, &this->m_el[0],
							 &this->m_Qke[0], &this->m_Tsq[0], &this->m_Qsq[0], &this->m_Cov[0],
							 &this->m_Psig_bl, &this->m_cldfra_bl1D[0],
							 &this->m_bl_mynn_mixlength, 
							 &this->m_edmf_a1[0], &this->m_edmf_qc1[0],  &this->m_bl_mynn_edmf);
					 }
					 /*
						@Purpose:
						          Member variables.
					 */
					 I32 m_KTS;

					 I32 m_KTE;

					 I32 m_bl_mynn_mixlength;

					 I32 m_bl_mynn_edmf;

					 R32 m_ust;

					 R32 m_rmo;

					 R32 m_zi;

					 R32 m_Psig_bl;

_Field_size_(m_KTE)  R32* __restrict m_dz;

_Field_size_(m_KTE + 1)  R32* __restrict m_zw;

_Field_size_(m_KTE)  R32* __restrict m_u;

_Field_size_(m_KTE)  R32* __restrict m_v;

_Field_size_(m_KTE)  R32* __restrict m_thl;

_Field_size_(m_KTE)  R32* __restrict m_qw;

_Field_size_(m_KTE)  R32* __restrict m_theta;

_Field_size_(m_KTE)  R32* __restrict m_cldfra_bl1D;

_Field_size_(m_KTE)  R32* __restrict m_edmf_a1;

_Field_size_(m_KTE)  R32* __restrict m_edmf_qc1;

_Field_size_(m_KTE)  R32* __restrict m_Qke;

_Field_size_(m_KTE)  R32* __restrict m_Tsq;

_Field_size_(m_KTE)  R32* __restrict m_Qsq;

_Field_size_(m_KTE)  R32* __restrict m_Cov;

_Field_size_(m_KTE)  R32* __restrict m_sh;

_Field_size_(m_KTE)  R32* __restrict m_el;

				static const int m_totArrays = 16;

			};




	}
}







#endif /*__MODULE_BL_MYNN_MYM_INITIALIZE_IMPL_H__*/