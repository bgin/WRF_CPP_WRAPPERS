#ifndef __MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_H__
#define __MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_H__


#ifndef MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_VERSION_MINOR
#define MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_CREATE_DATE "Date: 12-11-2016 , Time: 13:18 PM GMT+2"
#endif

#ifndef MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_AUTHOR
#define MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif

#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

namespace wrf_phys_wrappers {
	namespace module_bl_mynn {


		template<typename R32 = float,
			     typename I32 = int >  struct  Wrap_Mym_Condensation {



					 /************************************
							Constructors and Destructors.
					 *************************************/

					 /*
						@Purpose:
									Default Constructor - explicitly default.
					 */
					 Wrap_Mym_Condensation() = default;

					 /*
						@Purpose:
									1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Mym_Condensation(_In_ const I32 kts,
								           _In_ const I32 kte,
						                   _In_ const I32 bl_mynn_cloudpdf,
						                   _In_ const R32 dx,
						                   _In_ const R32 PBLH1,
						                   _In_ const R32 HFX1)
						                        :
						                  m_kts{ kts },
						                  m_kte{ kte },
						                  m_bl_mynn_cloudpdf{ bl_mynn_cloudpdf },
						                  m_dx{ dx },
						                  m_PBLH1{ PBLH1 },
						                  m_HFX1{ HFX1 },
						                  m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_p{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_th{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_Sh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_qc_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						                  m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {
					 
											
						 if (0 > (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 1st Ctor: 'Wrap_Mym_Condensation'!!\n";
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
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Mym_Condensation'!!\n";
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
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = 0.f;
							 m_p[i]  = 0.f;
							 m_exner[i] = 0.f;
							 m_thl[i] = 0.f;
							 m_th[i] = 0.f;
							 m_qw[i] = 0.f;
							 m_tsq[i] = 0.f;
							 m_qsq[i] = 0.f;
							 m_cov[i] = 0.f;
							 m_Sh[i] = 0.f;
							 m_el[i] = 0.f;
							 m_edmf_qc1[i] = 0.f;
							 m_qc_bl1D[i] = 0.f;
							 m_cldfra_bl1D[i] = 0.f;
							 m_vt[i] = 0.f;
							 m_vq[i] = 0.f;
						 }


#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = 0.f;
							 m_p[i] = 0.f;
							 m_exner[i] = 0.f;
							 m_thl[i] = 0.f;
							 m_th[i] = 0.f;
							 m_qw[i] = 0.f;
							 m_tsq[i] = 0.f;
							 m_qsq[i] = 0.f;
							 m_cov[i] = 0.f;
							 m_Sh[i] = 0.f;
							 m_el[i] = 0.f;
							 m_edmf_qc1[i] = 0.f;
							 m_qc_bl1D[i] = 0.f;
							 m_cldfra_bl1D[i] = 0.f;
							 m_vt[i] = 0.f;
							 m_vq[i] = 0.f;
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
					 Wrap_Mym_Condensation(_In_ const I32 kts,
				                           _In_ const I32 kte,
				                           _In_ const I32 bl_mynn_cloudpdf,
				                           _In_ const R32 dx,
				                           _In_ const R32 PBLH1,
				                           _In_ const R32 HFX1,
				                           _In_ R32* __restrict const dz,
				                           _In_ R32* __restrict const p,
				                           _In_ R32* __restrict const exner,
				                           _In_ R32* __restrict const thl,
				                           _In_ R32* __restrict const th,
				                           _In_ R32* __restrict const qw,
				                           _In_ R32* __restrict const tsq,
				                           _In_ R32* __restrict const qsq,
				                           _In_ R32* __restrict const cov,
				                           _In_ R32* __restrict const Sh,
				                           _In_ R32* __restrict const el,
				                           _In_ R32* __restrict const edmf_qc1)
				                                  :
				                            m_kts{ kts },
				                            m_kte{ kte },
				                            m_bl_mynn_cloudpdf{ bl_mynn_cloudpdf },
				                            m_dx{ dx },
				                            m_PBLH1{ PBLH1 },
				                            m_HFX1{ HFX1 },
				                            m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_p{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_th{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_Sh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_qc_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                            m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 if (0 > (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 2nd Ctor: 'Wrap_Mym_Condensation'!!\n";
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
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Condensation'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }

						 if (dz       == NULL ||
							 p        == NULL ||
							 exner    == NULL ||
							 thl      == NULL ||
							 th       == NULL ||
							 qw       == NULL ||
							 tsq      == NULL ||
							 qsq      == NULL ||
							 cov      == NULL ||
							 Sh       == NULL ||
							 el       == NULL ||
							 edmf_qc1 == NULL   ) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Condensation'!!\n";
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
							 m_p[i]  = p[i];
							 m_exner[i] = exner[i];
							 m_thl[i] = thl[i];
							 m_th[i]  = th[i];
							 m_qw[i]  = qw[i];
							 m_tsq[i] = tsq[i];
							 m_qsq[i] = qsq[i];
							 m_cov[i] = cov[i];
							 m_Sh[i]  = Sh[i];
							 m_el[i]  = el[i];
							 m_edmf_qc1[i] = edmf_qc1[i];
							 m_qc_bl1D[i] = 0.f;
							 m_cldfra_bl1D[i] = 0.f;
							 m_vt[i] = 0.f;
							 m_vq[i] = 0.f;
						 }


#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = dz[i];
							 m_p[i] = p[i];
							 m_exner[i] = exner[i];
							 m_thl[i] = thl[i];
							 m_th[i] = th[i];
							 m_qw[i] = qw[i];
							 m_tsq[i] = tsq[i];
							 m_qsq[i] = qsq[i];
							 m_cov[i] = cov[i];
							 m_Sh[i] = Sh[i];
							 m_el[i] = el[i];
							 m_edmf_qc1[i] = edmf_qc1[i];
							 m_qc_bl1D[i] = 0.f;
							 m_cldfra_bl1D[i] = 0.f;
							 m_vt[i] = 0.f;
							 m_vq[i] = 0.f;
						 }
#endif
						 


#endif
			}

					 /*
						@Purpose:
								  Copy Constructor implements deep copy semantics.
					  */
			         Wrap_Mym_Condensation(_In_ const Wrap_Mym_Condensation &x)
				                           :
				                   m_kts{ x.m_kts },
				                   m_kte{ x.m_kte },
				                   m_bl_mynn_cloudpdf{ x.m_bl_mynn_cloudpdf },
				                   m_dx{ x.m_dx },
				                   m_PBLH1{ x.m_PBLH1 },
				                   m_HFX1{ x.m_HFX1 },
				                   m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_p{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_th{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_Sh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_qc_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                   m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
								   m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor: 'Wrap_Mym_Condensation'!!\n";
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
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = x.m_dz[i];
							 m_p[i]  = x.m_p[i];
							 m_exner[i] = x.m_exner[i];
							 m_thl[i] = x.m_thl[i];
							 m_th[i]  = x.m_th[i];
							 m_qw[i]  = x.m_qw[i];
							 m_tsq[i] = x.m_tsq[i];
							 m_qsq[i] = x.m_qsq[i];
							 m_cov[i] = x.m_cov[i];
							 m_Sh[i] = x.m_Sh[i];
							 m_el[i] = x.m_el[i];
							 m_edmf_qc1[i] = x.m_edmf_qc1[i];
							 m_qc_bl1D[i] = x.m_qc_bl1D[i];
							 m_cldfra_bl1D[i] = x.m_cldfra_bl1D[i];
							 m_vt[i] = x.m_vt[i];
							 m_vq[i] = x.m_vq[i];
						 }


#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = x.m_dz[i];
							 m_p[i] = x.m_p[i];
							 m_exner[i] = x.m_exner[i];
							 m_thl[i] = x.m_thl[i];
							 m_th[i] = x.m_th[i];
							 m_qw[i] = x.m_qw[i];
							 m_tsq[i] = x.m_tsq[i];
							 m_qsq[i] = x.m_qsq[i];
							 m_cov[i] = x.m_cov[i];
							 m_Sh[i] = x.m_Sh[i];
							 m_el[i] = x.m_el[i];
							 m_edmf_qc1[i] = x.m_edmf_qc1[i];
							 m_qc_bl1D[i] = x.m_qc_bl1D[i];
							 m_cldfra_bl1D[i] = x.m_cldfra_bl1D[i];
							 m_vt[i] = x.m_vt[i];
							 m_vq[i] = x.m_vq[i];
						 }
#endif
						 


#endif
			}

					 /*
						@Purpose:
									Move Constructor implements shallow copy semantics.
					 */
					 Wrap_Mym_Condensation(_In_ Wrap_Mym_Condensation &&x)
						                 :
						           m_kts{ x.m_kts },
						           m_kte{ x.m_kte },
						           m_bl_mynn_cloudpdf{ x.m_bl_mynn_cloudpdf },
						           m_dx{ x.m_dx },
						           m_PBLH1{ x.m_PBLH1 },
								   m_HFX1{ x.m_HFX1 } {

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
					 ~Wrap_Mym_Condensation() {
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
					 Wrap_Mym_Condensation & operator=(_In_ const Wrap_Mym_Condensation &x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 m_bl_mynn_cloudpdf = x.m_bl_mynn_cloudpdf;
						 m_dx = x.m_dx;
						 m_PBLH1 = x.m_PBLH1;
						 m_HFX1 = x.m_HFX1;
						 constexpr int ntPtrs1D{16};
						 R32  *tPtrs1D[ntPtrs1D] = {};
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if (tPtrs1D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mym_Condensation'!!\n";
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
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }

						 for (int i {0}; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }

						 for (int i {0}; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = tPtrs1D[i];

						 }

						 return (*this);
#else
#if defined (USE_AUTO_VECTORIZATION)


						 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }
#endif
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = tPtrs1D[i];

						 }

						 return (*this);

#endif
			}

					 Wrap_Mym_Condensation & operator=(_In_ Wrap_Mym_Condensation &&x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 m_bl_mynn_cloudpdf = x.m_bl_mynn_cloudpdf;
						 m_dx = x.m_dx;
						 m_PBLH1 = x.m_PBLH1;
						 m_HFX1 = x.m_HFX1;
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i]) {
								 _mm_free((&this->m_dz)[i]);
							 }
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }
						 for (int i{ 0 }; i != x.m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 x.m_kts = 0;
						 x.m_kte = 0;

						 return (*this);
			}

					 /*
						@Purpose:
									Call Fortran 90 'MYM_CONDENSATION' subroutine.
					 */
					 void  Call_Mym_Condensation() {

						 MODULE_BL_MYNN_mp_MYM_CONDENSATION(&this->m_kts, &this->m_kte,
							 &this->m_dx, &this->m_dz[0],
							 &this->m_thl[0], &this->m_qw[0],
							 &this->m_p[0], &this->m_exner[0],
							 &this->m_tsq[0], &this->m_qsq[0], &this->m_cov[0],
							 &this->m_Sh[0], &this->m_el[0], &this->m_bl_mynn_cloudpdf,
							 &this->m_qc_bl1D[0] ,&this->m_cldfra_bl1D[0],
							 &this->m_PBLH1, &this->m_HFX1,
							 &this->m_edmf_qc1[0],
							 &this->m_vt[0], &this->m_vq[0], &this->m_th[0]);
			}
					 /*
						@Purpose:
									Member variables:
					 */

					 I32 m_kts;

					 I32 m_kte;

					 I32 m_bl_mynn_cloudpdf;

					 R32 m_dx;

					 R32 m_PBLH1;

					 R32 m_HFX1;

					 // Input arrays.

_Field_size_(m_kte)  R32* __restrict m_dz;

_Field_size_(m_kte)  R32* __restrict m_p;

_Field_size_(m_kte)  R32* __restrict m_exner;

_Field_size_(m_kte)  R32* __restrict m_thl;

_Field_size_(m_kte)  R32* __restrict m_th;

_Field_size_(m_kte)  R32* __restrict m_qw;

_Field_size_(m_kte)  R32* __restrict m_tsq;

_Field_size_(m_kte)  R32* __restrict m_qsq;

_Field_size_(m_kte)  R32* __restrict m_cov;

_Field_size_(m_kte)  R32* __restrict m_Sh;

_Field_size_(m_kte)  R32* __restrict m_el;

_Field_size_(m_kte)  R32* __restrict m_edmf_qc1;

					// Output arrays.

_Field_size_(m_kte)  R32* __restrict m_qc_bl1D;

_Field_size_(m_kte)  R32* __restrict m_cldfra_bl1D;

_Field_size_(m_kte)  R32* __restrict m_vt;

_Field_size_(m_kte)  R32* __restrict m_vq;

				static const int m_totArrays = 16;

			};








	}
}







#endif /*__MODULE_BL_MYNN_MYM_CONDENSATION_IMPL_H__*/