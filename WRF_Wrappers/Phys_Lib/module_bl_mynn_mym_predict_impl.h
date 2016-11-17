#ifndef __MODULE_BL_MYNN_MYM_PREDICT_IMPL_H__
#define __MODULE_BL_MYNN_MYM_PREDICT_IMPL_H__

// File version granularity.
#ifndef MODULE_BL_MYNN_MYM_PREDICT_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_MYM_PREDICT_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_MYM_PREDICT_IMPL_VERSION_MINOR
#define MODULE_BL_MYNN_MYM_PREDICT_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_MYM_PREDICT_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_MYM_PREDICT_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_MYM_PREDICT_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_MYM_PREDICT_IMPL_CREATE_DATE "Date: 11-11-2016 , Time: 15:36 PM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_MYM_PREDICT_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_MYM_PREDICT_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_MYM_PREDICT_IMPL_AUTHOR
#define MODULE_BL_MYNN_MYM_PREDICT_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif

#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

namespace wrf_phys_wrappers {
	namespace module_bl_mynn {


		template<typename R32 = float,
				 typename I32 = int >  struct Wrap_Mym_Predict {



					 /******************************************
						      Constructors and Destructor.
					 ******************************************/

					 /*
						@Purpose:
									Default Constructor - explicitly default.
					 */
					 Wrap_Mym_Predict() = default;

					 /*
						@Purpose:
									1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Mym_Predict(_In_ const I32 kts,
						              _In_ const I32 kte,
						              _In_ const I32 levflag,
						              _In_ const I32 bl_mynn_edmf_tke,
						              _In_ const R32 delt,
						              _In_ const R32 flt,
						              _In_ const R32 flq,
						              _In_ const R32 ust,
						              _In_ const R32 pmz,
						              _In_ const R32 phh)
						                :
						           m_kts{ kts },
						           m_kte{ kte },
								   m_levflag{ levflag },
						           m_bl_mynn_edmf_tke{ bl_mynn_edmf_tke },
						           m_delt{ delt },
						           m_flt{ flt },
						           m_flq{ flq },
						           m_ust{ ust },
						           m_pmz{ pmz },
						           m_phh{ phh },
						           m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_pdk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_pdt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_pdq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_pdc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_qke{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						           m_s_awqke{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
								   m_s_aw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) } {

						 if (0 > (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 1st Ctor: 'Wrap_Mym_Predict'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Lower range value m_kts: " << m_kts << "\n";
							 std::cerr << "Upper range value m_kte: " << m_kte << "\n";
							 std::cerr << "Range value difference: " << m_kte - m_kts << "\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Mym_Predict'!!\n";
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
							 m_dfq[i] = 0.f;
							 m_el[i] = 0.f;
							 m_pdk[i] = 0.f;
							 m_pdt[i] = 0.f;
							 m_pdq[i] = 0.f;
							 m_pdc[i] = 0.f;
							 m_qke[i] = 0.f;
							 m_tsq[i] = 0.f;
							 m_qsq[i] = 0.f;
							 m_cov[i] = 0.f;
							 m_s_awqke[i] = 0.f;
							 m_s_aw[i] = 0.f;
						 }
						 const int top = m_kte + 1;
						 m_s_awqke[top] = 0.f;
						 m_s_aw[top] = 0.f;

#else
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = 0.f;
							 m_dfq[i] = 0.f;
							 m_el[i] = 0.f;
							 m_pdk[i] = 0.f;
							 m_pdt[i] = 0.f;
							 m_pdq[i] = 0.f;
							 m_pdc[i] = 0.f;
							 m_qke[i] = 0.f;
							 m_tsq[i] = 0.f;
							 m_qsq[i] = 0.f;
							 m_cov[i] = 0.f;
							 m_s_awqke[i] = 0.f;
							 m_s_aw[i] = 0.f;
						 }
						 const int top = m_kte + 1;
						 m_s_awqke[top] = 0.f;
						 m_s_aw[top] = 0.f;


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
			         Wrap_Mym_Predict(_In_ const I32 kts,
				                      _In_ const I32 kte,
				                      _In_ const I32 levflag,
				                      _In_ const I32 bl_mynn_edmf_tke,
				                      _In_ const R32 delt,
				                      _In_ const R32 flt,
				                      _In_ const R32 flq,
				                      _In_ const R32 ust,
				                      _In_ const R32 pmz,
				                      _In_ const R32 phh,
				                      _In_ R32* __restrict const dz,
				                      _In_ R32* __restrict const dfq,
						              _In_ R32* __restrict const el,
				                      _In_ R32* __restrict const pdk,
				                      _In_ R32* __restrict const pdt,
				                      _In_ R32* __restrict const pdq,
				                      _In_ R32* __restrict const pdc,
				                      _In_ R32* __restrict const qke,
				                      _In_ R32* __restrict const tsq,
				                      _In_ R32* __restrict const qsq,
				                      _In_ R32* __restrict const cov,
				                      _In_ R32* __restrict const s_awqke,
				                      _In_ R32* __restrict const s_aw)
				                              :
			                            m_kts{ kts },
				                        m_kte{ kte },
				                        m_levflag{ levflag },
				                        m_bl_mynn_edmf_tke{ bl_mynn_edmf_tke },
				                        m_delt{ delt },
				                        m_flt{ flt },
				                        m_flq{ flq },
				                        m_ust{ ust },
				                        m_pmz{ pmz },
				                        m_phh{ phh },
				                        m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_pdk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_pdt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_pdq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_pdc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_qke{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                        m_s_awqke{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                        m_s_aw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) } {


						 if (0 > (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 2nd Ctor: 'Wrap_Mym_Predict'!!\n";
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
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Predict'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 
						 if (dz      == NULL ||
							 dfq     == NULL ||
							 el      == NULL ||
							 pdk     == NULL ||
							 pdt     == NULL ||
							 pdq     == NULL ||
							 pdc     == NULL ||
							 qke     == NULL ||
							 tsq     == NULL ||
							 qsq     == NULL ||
							 cov     == NULL ||
							 s_awqke == NULL ||
							 s_aw    == NULL) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Predict'!!\n";
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
							 m_dfq[i] = dfq[i];
							 m_el[i] = el[i];
							 m_pdk[i] = pdk[i];
							 m_pdt[i] = pdt[i];
							 m_pdq[i] = pdq[i];
							 m_pdc[i] = pdc[i];
							 m_qke[i] = qke[i];
							 m_tsq[i] = tsq[i];
							 m_qsq[i] = qsq[i];
							 m_cov[i] = cov[i];
							 m_s_awqke[i] = s_awqke[i];
							 m_s_aw[i] = s_aw[i];
						 }
						 const int top = m_kte + 1;
						 m_s_awqke[top] = s_awqke[top];
						 m_s_aw[top] = s_aw[top];


#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = dz[i];
							 m_dfq[i] = dfq[i];
							 m_el[i] = el[i];
							 m_pdk[i] = pdk[i];
							 m_pdt[i] = pdt[i];
							 m_pdq[i] = pdq[i];
							 m_pdc[i] = pdc[i];
							 m_qke[i] = qke[i];
							 m_tsq[i] = tsq[i];
							 m_qsq[i] = qsq[i];
							 m_cov[i] = cov[i];
							 m_s_awqke[i] = s_awqke[i];
							 m_s_aw[i] = s_aw[i];
						 }
						 const int top = m_kte + 1;
						 m_s_awqke[top] = s_awqke[top];
						 m_s_aw[top] = s_aw[top];

#endif
						 
			}

					/*
						@Purpose:
									Copy Constructor implements deep copy semantics.
					 */
					 Wrap_Mym_Predict(_In_ const Wrap_Mym_Predict &x)
				                        :
				                  m_kts{ x.m_kts },
				                  m_kte{ x.m_kte },
				                  m_levflag{ x.m_levflag },
				                  m_bl_mynn_edmf_tke{ x.m_bl_mynn_edmf_tke },
				                  m_delt{ x.m_delt },
				                  m_flt{ x.m_flt },
				                  m_flq{ x.m_flq },
				                  m_ust{ x.m_ust },
				                  m_pmz{ x.m_pmz },
				                  m_phh{ x.m_phh },
				                  m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_pdk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_pdt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_pdq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_pdc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_qke{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                  m_s_awqke{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
								  m_s_aw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) } {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor: 'Wrap_Mym_Predict'!!\n";
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
							 m_dfq[i] = x.m_dfq[i];
							 m_el[i] = x.m_el[i];
							 m_pdk[i] = x.m_pdk[i];
							 m_pdt[i] = x.m_pdt[i];
							 m_pdq[i] = x.m_pdq[i];
							 m_pdc[i] = x.m_pdc[i];
							 m_qke[i] = x.m_qke[i];
							 m_tsq[i] = x.m_tsq[i];
							 m_qsq[i] = x.m_qsq[i];
							 m_cov[i] = x.m_cov[i];
							 m_s_awqke[i] = x.m_s_awqke[i];
							 m_s_aw[i] = x.m_s_aw[i];
						 }
						 const int top = m_kte + 1;
						 m_s_awqke[top] = x.m_s_awqke[top];
						 m_s_aw[top] = x.m_s_aw[top];


#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = x.m_dz[i];
							 m_dfq[i] = x.m_dfq[i];
							 m_el[i] = x.m_el[i];
							 m_pdk[i] = x.m_pdk[i];
							 m_pdt[i] = x.m_pdt[i];
							 m_pdq[i] = x.m_pdq[i];
							 m_pdc[i] = x.m_pdc[i];
							 m_qke[i] = x.m_qke[i];
							 m_tsq[i] = x.m_tsq[i];
							 m_qsq[i] = x.m_qsq[i];
							 m_cov[i] = x.m_cov[i];
							 m_s_awqke[i] = x.m_s_awqke[i];
							 m_s_aw[i] = x.m_s_aw[i];
						 }
						 const int top = m_kte + 1;
						 m_s_awqke[top] = x.m_s_awqke[top];
						 m_s_aw[top] = x.m_s_aw[top];

#endif
			}

					 /*
						@Purpose:
									Move Constructor implements shallow copy semantics.
					 */
					 Wrap_Mym_Predict(_In_ Wrap_Mym_Predict &&x)
									  :
									m_kts{ x.m_kts },
								    m_kte{ x.m_kte },
									m_levflag{ x.m_levflag },
									m_bl_mynn_edmf_tke{ x.m_bl_mynn_edmf_tke },
									m_delt{ x.m_delt },
									m_flt{ x.m_flt },
									m_flq{ x.m_flq },
									m_ust{ x.m_ust },
									m_pmz{ x.m_pmz },
									m_phh{ x.m_phh } {

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
					 ~Wrap_Mym_Predict() {
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i]) {
								 _mm_free((&this->m_dz)[i]);
							 }
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (this->m_dz)[i] = NULL;
						 }
						 m_kts = 0;
						 m_kte = 0;
					 }
					 /*
						@Purpose:
									Copy-assign Operator implements deep copy seamntics.
					 */
					 Wrap_Mym_Predict & operator=(_In_ const Wrap_Mym_Predict &x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 m_levflag = x.m_levflag;
						 m_bl_mynn_edmf_tke = x.m_bl_mynn_edmf_tke;
						 m_delt = x.m_delt;
						 m_flt = x.m_flt;
						 m_flq = x.m_flq;
						 m_ust = x.m_ust;
						 m_pmz = x.m_pmz;
						 m_phh = x.m_phh;
						 constexpr int ntPtrs1D{13};
						 R32 *tPtrs1D[ntPtrs1D] = {};
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if (tPtrs1D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mym_Predict'!!\n";
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
							 for (int i = m_kts; i != m_kte; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }
						 const int top = m_kte + 1;
						 tPtrs1D[11][top] = x.m_s_awqke[top];
						 tPtrs1D[12][top] = x.m_s_aw[top];

						 for (int i {0}; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
							
						 for (int i {0}; i != this->m_totArrays; ++i) {
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
							 for (int i = m_kts; i != m_kte; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }
						 const int top = m_kte + 1;
						 tPtrs1D[11][top] = x.m_s_awqke[top];
						 tPtrs1D[12][top] = x.m_s_aw[top];

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }

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
					 Wrap_Mym_Predict & operator=(_In_ Wrap_Mym_Predict &&x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 m_levflag = x.m_levflag;
						 m_bl_mynn_edmf_tke = x.m_bl_mynn_edmf_tke;
						 m_delt = x.m_delt;
						 m_flt = x.m_flt;
						 m_flq = x.m_flq;
						 m_ust = x.m_ust;
						 m_pmz = x.m_pmz;
						 m_phh = x.m_phh;

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }
						 for (int i{ 0 }; i != x.m_totArrays; ++i) {
							 (x.m_dz)[i] = NULL;
						 }
						 return (*this);
			}

					 /*
						@Purpose:
									Call Fortran 90 'MYM_PREDICT' subroutine.
					 */
					 void  Call_Mym_Predict() {

						 MODULE_BL_MYNN_mp_MYM_PREDICT(&this->m_kts,&this->m_kte,
														&this->m_levflag,
														&this->m_delt,
														&this->m_dz[0],
														&this->m_ust, &this->m_flt, &this->m_flq, &this->m_pmz, &this->m_phh,
														&this->m_el[0], &this->m_dfq[0],
														&this->m_pdk[0], &this->m_pdt[0], &this->m_pdq[0], &this->m_pdc[0],
														&this->m_qke[0], &this->m_tsq[0], &this->m_qsq[0], &this->m_cov[0],
														&this->m_s_aw[0], &this->m_s_awqke[0], &this->m_bl_mynn_edmf_tke);
			}



					 /*
						@Purpose:
									Member variables.
					 */

					 I32 m_kts;

					 I32 m_kte;

					 I32 m_levflag;

					 I32 m_bl_mynn_edmf_tke;

					 R32 m_delt;

					 R32 m_flt;

					 R32 m_flq;

					 R32 m_ust;

					 R32 m_pmz;

					 R32 m_phh;

					 // Input arrays.

_Field_size_(m_kte)  R32* __restrict m_dz;

_Field_size_(m_kte)  R32* __restrict m_dfq;

_Field_size_(m_kte)  R32* __restrict m_el;

					// Input/Output arrays.

_Field_size_(m_kte)	 R32* __restrict m_pdk;

_Field_size_(m_kte)  R32* __restrict m_pdt;

_Field_size_(m_kte)  R32* __restrict m_pdq;

_Field_size_(m_kte)  R32* __restrict m_pdc;

_Field_size_(m_kte)  R32* __restrict m_qke;

_Field_size_(m_kte)  R32* __restrict m_tsq;

_Field_size_(m_kte)  R32* __restrict m_qsq;

_Field_size_(m_kte)  R32* __restrict m_cov;

_Field_size_(m_kte)  R32* __restrict m_s_awqke;

_Field_size_(m_kte)  R32* __restrict m_s_aw;

				static const int  m_totArrays = 13;

			};










	}
}






#endif /*__MODULE_BL_MYNN_MYM_PREDICT_IMPL_H__*/