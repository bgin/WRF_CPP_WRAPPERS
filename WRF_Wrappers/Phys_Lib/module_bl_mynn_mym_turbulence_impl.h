
#ifndef __MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_H__
#define __MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_H__

// File version granularity.
#ifndef MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_VERSION_MINOR
#define MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_CREATE_DATE "Date: 10-11-2016 , Time: 11:57 AM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_AUTHOR
#define MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"



namespace wrf_phys_wrappers {
	namespace module_bl_mynn {


		template<typename R32 = float,
			     typename I32 = int  >  struct Wrap_Mym_Turbulence {




					 /*************************************
						Constructors and Destructor.
					 **************************************/

					 /*
						@Purpose:
									Deafult Constructor - explicitly default.
					 */
					 Wrap_Mym_Turbulence() = default;

					 /*
						@Purpose:
									1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Mym_Turbulence(_In_ const I32 kts,
						                 _In_ const I32 kte,
						                 _In_ const I32 levflag,
						                 _In_ const I32 bl_mynn_mixlength,
						                 _In_ const I32 bl_mynn_edmf,
						                 _In_ const I32 bl_mynn_tkebudget,
						                 _In_ const R32 rmo,
						                 _In_ const R32 flt,
						                 _In_ const R32 flq,
						                 _In_ const R32 Psig_bl,
						                 _In_ const R32 Psig_shcu,
						                 _In_ const R32 zi)
						                   :
						            m_kts{ kts },
						            m_kte{ kte },
						            m_levflag{ levflag },
						            m_bl_mynn_mixlength{ bl_mynn_mixlength },
						            m_bl_mynn_edmf{ bl_mynn_edmf },
						            m_bl_mynn_tkebudget{ bl_mynn_tkebudget },
						            m_rmo{ rmo },
						            m_flt{ flt },
						            m_flq{ flq },
						            m_Psig_bl{ Psig_bl },
						            m_Psig_shcu{ Psig_shcu },
						            m_zi{ zi },
						            m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						            m_u{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_v{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_ql{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_qke{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_edmf_a1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_pdk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_pdt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_pdq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_pdc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_tcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_qcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_qWT1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_qSHEAR1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						            m_qBUOY1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
									m_qDISS1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Mym_Turbulence'!!\n";
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
							 m_zw[i] = 0.f;
							 m_u[i] = 0.f;
							 m_v[i] = 0.f;
							 m_thl[i] = 0.f;
							 m_ql[i] = 0.f;
							 m_qw[i] = 0.f;
							 m_qke[i] = 0.f;
							 m_tsq[i] = 0.f;
							 m_qsq[i] = 0.f;
							 m_cov[i] = 0.f;
							 m_vt[i] = 0.f;
							 m_vq[i] = 0.f;
							 m_cldfra_bl1D[i] = 0.f;
							 m_edmf_a1[i] = 0.f;
							 m_edmf_qc1[i] = 0.f;
							 m_el[i] = 0.f;
							 m_dfm[i] = 0.f;
							 m_dfh[i] = 0.f;
							 m_dfq[i] = 0.f;
							 m_pdk[i] = 0.f;
							 m_pdt[i] = 0.f;
							 m_pdq[i] = 0.f;
							 m_pdc[i] = 0.f;
							 m_tcd[i] = 0.f;
							 m_qcd[i] = 0.f;
							 m_qWT1D[i] = 0.f;
							 m_qSHEAR1D[i] = 0.f;
							 m_qBUOY1D[i] = 0.f;
							 m_qDISS1D[i] = 0.f;
						 }
						 const int top = m_kte + 1;
						 m_zw[top] = 0.f;
							 
#else

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = 0.f;
							 m_zw[i] = 0.f;
							 m_u[i] = 0.f;
							 m_v[i] = 0.f;
							 m_thl[i] = 0.f;
							 m_ql[i] = 0.f;
							 m_qw[i] = 0.f;
							 m_qke[i] = 0.f;
							 m_tsq[i] = 0.f;
							 m_qsq[i] = 0.f;
							 m_cov[i] = 0.f;
							 m_vt[i] = 0.f;
							 m_vq[i] = 0.f;
							 m_cldfra_bl1D[i] = 0.f;
							 m_edmf_a1[i] = 0.f;
							 m_edmf_qc1[i] = 0.f;
							 m_el[i] = 0.f;
							 m_dfm[i] = 0.f;
							 m_dfh[i] = 0.f;
							 m_dfq[i] = 0.f;
							 m_pdk[i] = 0.f;
							 m_pdt[i] = 0.f;
							 m_pdq[i] = 0.f;
							 m_pdc[i] = 0.f;
							 m_tcd[i] = 0.f;
							 m_qcd[i] = 0.f;
							 m_qWT1D[i] = 0.f;
							 m_qSHEAR1D[i] = 0.f;
							 m_qBUOY1D[i] = 0.f;
							 m_qDISS1D[i] = 0.f;
						 }
						 const int top = m_kte + 1;
						 m_zw[top] = 0.f;

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
					 Wrap_Mym_Turbulence(_In_ const I32 kts,
				                         _In_ const I32 kte,
				                         _In_ const I32 levflag,
				                         _In_ const I32 bl_mynn_mixlength,
				                         _In_ const I32 bl_mynn_edmf,
				                         _In_ const I32 bl_mynn_tkebudget,
				                         _In_ const R32 rmo,
				                         _In_ const R32 flt,
				                         _In_ const R32 flq,
				                         _In_ const R32 Psig_bl,
				                         _In_ const R32 Psig_shcu,
				                         _In_ const R32 zi,
				                         _In_ R32* __restrict dz,
				                         _In_ R32* __restrict zw,
				                         _In_ R32* __restrict u,
				                         _In_ R32* __restrict v,
				                         _In_ R32* __restrict thl,
				                         _In_ R32* __restrict qw,
				                         _In_ R32* __restrict ql,
				                         _In_ R32* __restrict qke,
				                         _In_ R32* __restrict tsq,
				                         _In_ R32* __restrict qsq,
				                         _In_ R32* __restrict cov,
				                         _In_ R32* __restrict vt,
				                         _In_ R32* __restrict vq,
				                         _In_ R32* __restrict cldfra_bl1D,
				                         _In_ R32* __restrict edmf_a1,
				                         _In_ R32* __restrict edmf_qc1,
				                         _In_ R32* __restrict theta,
				                         _In_ R32* __restrict qWT1D,
				                         _In_ R32* __restrict qSHEAR1D,
				                         _In_ R32* __restrict qBUOY1D,
				                         _In_ R32* __restrict qDISS1)
				                              :
			                             m_kts{ kts },
				                         m_kte{ kte },
				                         m_levflag{ levflag },
				                         m_bl_mynn_mixlength{ bl_mynn_mixlength },
				                         m_bl_mynn_edmf{ bl_mynn_edmf },
				                         m_bl_mynn_tkebudget{ bl_mynn_tkebudget },
				                         m_rmo{ rmo },
				                         m_flt{ flt },
				                         m_flq{ flq },
				                         m_Psig_bl{ Psig_bl },
				                         m_Psig_shcu{ Psig_shcu },
				                         m_zi{ zi },
				                         m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                         m_u{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_v{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_ql{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_qke{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_edmf_a1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_pdk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_pdt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_pdq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_pdc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_tcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_qcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_qWT1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_qSHEAR1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                         m_qBUOY1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
										 m_qDISS1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Turbulence'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }

						 if (dz          == NULL ||
							 zw          == NULL ||
							 u           == NULL ||
							 v           == NULL ||
							 thl         == NULL ||
							 qw          == NULL ||
							 ql          == NULL ||
							 qke         == NULL ||
							 tsq         == NULL ||
							 qsq         == NULL ||
							 cov         == NULL ||
							 vt          == NULL ||
							 vq          == NULL ||
							 cldfra_bl1D == NULL ||
							 edmf_a1     == NULL ||
							 edmf_qc1    == NULL ||
							 qWT1D       == NULL ||
							 qSHEAR1D    == NULL ||
							 qBUOY1D     == NULL ||
							 qDISS1      == NULL ) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mym_Turbulence'!!\n";
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
							 m_zw[i] = zw[i];
							 m_u[i] = u[i];
							 m_v[i] = v[i];
							 m_thl[i] = thl[i];
							 m_ql[i] = ql[i];
							 m_qw[i] = qw[i];
							 m_qke[i] = qke[i];
							 m_tsq[i] = tsq[i];
							 m_qsq[i] = qsq[i];
							 m_cov[i] = cov[i];
							 m_vt[i] = vt[i];
							 m_vq[i] = vq[i];
							 m_cldfra_bl1D[i] = cldfra_bl1D[i];
							 m_edmf_a1[i] = edmf_a1[i];
							 m_edmf_qc1[i] = edmf_qc1[i];
							 m_el[i] = 0.f;
							 m_dfm[i] = 0.f;
							 m_dfh[i] = 0.f;
							 m_dfq[i] = 0.f;
							 m_pdk[i] = 0.f;
							 m_pdt[i] = 0.f;
							 m_pdq[i] = 0.f;
							 m_pdc[i] = 0.f;
							 m_tcd[i] = 0.f;
							 m_qcd[i] = 0.f;
							 m_qWT1D[i] = qWT1D[i];
							 m_qSHEAR1D[i] = qSHEAR1D[i];
							 m_qBUOY1D[i] = qBUOY1D[i];
							 m_qDISS1D[i] = qDISS1[i];
						 }
						 const int top = m_kte + 1;
						 m_zw[top] = zw[top];


#else
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = dz[i];
							 m_zw[i] = zw[i];
							 m_u[i] = u[i];
							 m_v[i] = v[i];
							 m_thl[i] = thl[i];
							 m_ql[i] = ql[i];
							 m_qw[i] = qw[i];
							 m_qke[i] = qke[i];
							 m_tsq[i] = tsq[i];
							 m_qsq[i] = qsq[i];
							 m_cov[i] = cov[i];
							 m_vt[i] = vt[i];
							 m_vq[i] = vq[i];
							 m_cldfra_bl1D[i] = cldfra_bl1D[i];
							 m_edmf_a1[i] = edmf_a1[i];
							 m_edmf_qc1[i] = edmf_qc1[i];
							 m_el[i] = 0.f;
							 m_dfm[i] = 0.f;
							 m_dfh[i] = 0.f;
							 m_dfq[i] = 0.f;
							 m_pdk[i] = 0.f;
							 m_pdt[i] = 0.f;
							 m_pdq[i] = 0.f;
							 m_pdc[i] = 0.f;
							 m_tcd[i] = 0.f;
							 m_qcd[i] = 0.f;
							 m_qWT1D[i] = qWT1D[i];
							 m_qSHEAR1D[i] = qSHEAR1D[i];
							 m_qBUOY1D[i] = qBUOY1D[i];
							 m_qDISS1D[i] = qDISS1[i];
						 }
						 const int top = m_kte + 1;
						 m_zw[top] = zw[top];

#endif



			}

			         /*
						@Purpose:
						           Copy Constructor implements deep copy semantics.
			          */
					 Wrap_Mym_Turbulence(_In_ const Wrap_Mym_Turbulence &x)
				                           :
				                    m_kts{ x.m_kts },
				                    m_kte{ x.m_kte },
				                    m_levflag{ x.m_levflag },
				                    m_bl_mynn_mixlength{ x.m_bl_mynn_mixlength },
				                    m_bl_mynn_edmf{ x.m_bl_mynn_edmf },
				                    m_bl_mynn_tkebudget{ x.m_bl_mynn_tkebudget },
				                    m_rmo{ x.m_rmo },
				                    m_flt{ x.m_flt },
				                    m_flq{ x.m_flq },
				                    m_Psig_bl{ x.m_Psig_bl },
				                    m_Psig_shcu{ x.m_Psig_shcu },
				                    m_zi{ x.m_zi },
				                    m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_zw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                    m_u{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_v{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_qw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_ql{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_qke{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_vt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_vq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_edmf_a1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_edmf_qc1{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_theta{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_sh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_el{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_pdk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_pdt{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_pdq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_pdc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_tcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_qcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_qWT1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_qSHEAR1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                    m_qBUOY1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
									m_qDISS1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Ctor: 'Wrap_Mym_Turbulence'!!\n";
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
							 m_zw[i] = x.m_zw[i];
							 m_u[i] = x.m_u[i];
							 m_v[i] = x.m_v[i];
							 m_thl[i] = x.m_thl[i];
							 m_ql[i] = x.m_ql[i];
							 m_qw[i] = x.m_qw[i];
							 m_qke[i] = x.m_qke[i];
							 m_tsq[i] = x.m_tsq[i];
							 m_qsq[i] = x.m_qsq[i];
							 m_cov[i] = x.m_cov[i];
							 m_vt[i] = x.m_vt[i];
							 m_vq[i] = x.m_vq[i];
							 m_cldfra_bl1D[i] = x.m_cldfra_bl1D[i];
							 m_edmf_a1[i] = x.m_edmf_a1[i];
							 m_edmf_qc1[i] = x.m_edmf_qc1[i];
							 m_el[i] = x.m_el[i];
							 m_dfm[i] = x.m_dfm[i];
							 m_dfh[i] = x.m_dfh[i];
							 m_dfq[i] = x.m_dfq[i];
							 m_pdk[i] = x.m_pdk[i];
							 m_pdt[i] = x.m_pdt[i];
							 m_pdq[i] = x.m_pdq[i];
							 m_pdc[i] = x.m_pdc[i];
							 m_tcd[i] = x.m_tcd[i];
							 m_qcd[i] = x.m_qcd[i];
							 m_qWT1D[i] = x.m_qWT1D[i];
							 m_qSHEAR1D[i] = x.m_qSHEAR1D[i];
							 m_qBUOY1D[i] = x.m_qBUOY1D[i];
							 m_qDISS1D[i] = x.m_qDISS1[i];
						 }

						 const int top = m_kte + 1;
						 m_zw[top] = x.m_zw[top];

#else

#if defined (USE_AUTO_VECTRORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for (int i = m_kts; i != m_kte; ++i) {
							 m_dz[i] = x.m_dz[i];
							 m_zw[i] = x.m_zw[i];
							 m_u[i] = x.m_u[i];
							 m_v[i] = x.m_v[i];
							 m_thl[i] = x.m_thl[i];
							 m_ql[i] = x.m_ql[i];
							 m_qw[i] = x.m_qw[i];
							 m_qke[i] = x.m_qke[i];
							 m_tsq[i] = x.m_tsq[i];
							 m_qsq[i] = x.m_qsq[i];
							 m_cov[i] = x.m_cov[i];
							 m_vt[i] = x.m_vt[i];
							 m_vq[i] = x.m_vq[i];
							 m_cldfra_bl1D[i] = x.m_cldfra_bl1D[i];
							 m_edmf_a1[i] = x.m_edmf_a1[i];
							 m_edmf_qc1[i] = x.m_edmf_qc1[i];
							 m_el[i] = x.m_el[i];
							 m_dfm[i] = x.m_dfm[i];
							 m_dfh[i] = x.m_dfh[i];
							 m_dfq[i] = x.m_dfq[i];
							 m_pdk[i] = x.m_pdk[i];
							 m_pdt[i] = x.m_pdt[i];
							 m_pdq[i] = x.m_pdq[i];
							 m_pdc[i] = x.m_pdc[i];
							 m_tcd[i] = x.m_tcd[i];
							 m_qcd[i] = x.m_qcd[i];
							 m_qWT1D[i] = x.m_qWT1D[i];
							 m_qSHEAR1D[i] = x.m_qSHEAR1D[i];
							 m_qBUOY1D[i] = x.m_qBUOY1D[i];
							 m_qDISS1D[i] = x.m_qDISS1[i];
						 }

						 const int top = m_kte + 1;
						 m_zw[top] = x.m_zw[top];

#endif
			}

					 /*
						@Purpose:
									Move Constructor implements shallow copy semantics.
					 */
			         Wrap_Mym_Turbulence(_In_ Wrap_Mym_Turbulence &&x)
				                       :
				                 m_kts{ x.m_kts },
				                 m_kte{ x.m_kte },
				                 m_levflag{ x.m_levflag },
				                 m_bl_mynn_mixlength{ x.m_bl_mynn_mixlength },
				                 m_bl_mynn_edmf{ x.m_bl_mynn_edmf },
				                 m_bl_mynn_tkebudget{ x.m_bl_mynn_tkebudget },
				                 m_rmo{ x.m_rmo },
				                 m_flt{ x.m_flt },
				                 m_flq{ x.m_flq },
				                 m_Psig_bl{ x.m_Psig_bl },
				                 m_Psig_shcu{ x.m_Psig_shcu },
								 m_zi{ x.m_zi }              {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 this->m_kts = 0;
						 this->m_kte = 0;
			}

					 /*
						@Purpose:
									Class Destructor.
					 */
					 ~Wrap_Mym_Turbulence() {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i]) {
								 _mm_free((&this->m_dz)[i]);
							 }
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = NULL;
						 }
						 this->m_kts = 0;
						 this->m_kte = 0;
			}

					 /*
						@Purpose:
									Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Mym_Turbulence & operator=(_In_ const Wrap_Mym_Turbulence &x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 m_levflag = x.m_levflag;
						 m_bl_mynn_mixlength = x.m_bl_mynn_mixlength;
						 m_bl_mynn_edmf = x.m_bl_mynn_edmf;
						 m_bl_mynn_tkebudget = x.m_bl_mynn_tkebudget;
						 m_rmo = x.m_rmo;
						 m_flt = x.m_flt;
						 m_flq = x.m_flq;
						 m_Psig_bl = x.m_Psig_bl;
						 m_Psig_shcu = x.m_Psig_shcu;
						 m_zi = x.m_zi;
						 constexpr int ntPtrs1{32};
						 R32 *tPtrs1D[ntPtrs1] = {};
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if (ntPtrs1[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mym_Turbulence'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs1D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kme >= (1 << 16))
						 for (int idx = 0; idx != this->m_totArrays; ++i) {
							 for (int i = m_kms; i != m_kme; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }
						 const int top = m_kte + 1;
						 tPtrs1D[0][top] = x.m_dz[top];

						 for (int i {0}; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
						 for (int i {0}; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = tPtrs1D[i];
						 }

						 return (*this);
#else


						 for (int idx = 0; idx != this->m_totArrays; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int i = m_kms; i != m_kme; ++i) {
								 tPtrs1D[idx][i] = (&x.m_dz)[idx][i];
							 }
						 }

						 const int top = m_kte + 1;
						 tPtrs1D[0][top] = x.m_dz[top];
						 for (int i {0}; i != this->m_totArrays; ++i) {
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
					 Wrap_Mym_Turbulence & operator=(_In_ Wrap_Mym_Turbulence &&x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 m_levflag = x.m_levflag;
						 m_bl_mynn_mixlength = x.m_bl_mynn_mixlength;
						 m_bl_mynn_edmf = x.m_bl_mynn_edmf;
						 m_bl_mynn_tkebudget = x.m_bl_mynn_tkebudget;
						 m_rmo = x.m_rmo;
						 m_flt = x.m_flt;
						 m_flq = x.m_flq;
						 m_Psig_bl = x.m_Psig_bl;
						 m_Psig_shcu = x.m_Psig_shcu;
						 m_zi = x.m_zi;
						 for (int i{ 0 }; i != m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
						 for (int i{ 0 }; i != m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 m_kts = 0;
						 m_kte = 0;

						 return (*this);
			}

					 /*
						@Purpose:
									Call Fortran 90 'MYM_TURBULENCE' subroutine.
					 */
					 void  Call_Mym_Turbulence() {

						 MODULE_BL_MYNN_mp_MYM_TURBULENCE(&this->m_kts, &this->m_kte,
							 &this->m_levflag, &this->m_dz[0], &this->m_zw[0],
							 &this->m_u[0], &this->m_v[0], &this->m_thl[0], &this->m_ql[0],
							 &this->m_qw[0], &this->m_qke[0], &this->m_tsq[0], &this->m_qsq[0],
							 &this->m_cov[0], &this->m_vt[0], &this->m_vq[0],
							 &this->m_rmo, &this->m_flt, &this->m_flq, &this->m_zi,
							 &this->m_theta[0], &this->m_sh[0], &this->m_el[0],
							 &this->m_dfm[0], &this->m_dfh[0], &this->m_dfq[0], &this->m_tcd[0],
							 &this->m_qcd[0], &this->m_pdk[0], &this->m_pdt[0], &this->m_pdq[0],
							 &this->m_pdc[0], &this->m_qWT1D[0], &this->m_qSHEAR1D[0], &this->m_qBUOY1D[0],
							 &this->m_qDISS1D[0], &this->m_bl_mynn_tkebudget,
							 &this->m_Psig_bl, &this->m_Psig_shcu, &this->m_cldfra_bl1D[0], 
							 &this->m_bl_mynn_mixlength, &this->m_edmf_a1[0], &this->m_edmf_qc1[0],
							 &this->m_bl_mynn_edmf);
			}
					 /*
						@Purpose:
									Member variables.
					 */

					 I32 m_kts;

					 I32 m_kte;

					 I32 m_levflag;

					 I32 m_bl_mynn_mixlength;

					 I32 m_bl_mynn_edmf;

					 I32 m_bl_mynn_tkebudget;

					 R32 m_rmo;

					 R32 m_flt;

					 R32 m_flq;

					 R32 m_Psig_bl;

					 R32 m_Psig_shcu;

					 R32 m_zi;

					 // Input arrays.

_Field_size_(m_kte)  R32* __restrict m_dz;

_Field_size_(m_kte)  R32* __restrict m_zw;

_Field_size_(m_kte)  R32* __restrict m_u;

_Field_size_(m_kte)  R32* __restrict m_v;

_Field_size_(m_kte)  R32* __restrict m_thl;

_Field_size_(m_kte)  R32* __restrict m_qw;

_Field_size_(m_kte)  R32* __restrict m_ql;

_Field_size_(m_kte)  R32* __restrict m_qke;

_Field_size_(m_kte)  R32* __restrict m_tsq;

_Field_size_(m_kte)  R32* __restrict m_qsq;

_Field_size_(m_kte)  R32* __restrict m_cov;

_Field_size_(m_kte)  R32* __restrict m_vt;

_Field_size_(m_kte)  R32* __restrict m_vq;

_Field_size_(m_kte)  R32* __restrict m_cldfra_bl1D;

_Field_size_(m_kte)  R32* __restrict m_edmf_a1;

_Field_size_(m_kte)  R32* __restrict m_edmf_qc1;

_Field_size_(m_kte)  R32* __restrict m_theta;

_Field_size_(m_kte)  R32* __restrict m_sh;

				// Output arrays.

_Field_size_(m_kte)  R32* __restrict m_el;

_Field_size_(m_kte)  R32* __restrict m_dfm;

_Field_size_(m_kte)  R32* __restrict m_dfh;

_Field_size_(m_kte)  R32* __restrict m_dfq;

_Field_size_(m_kte)	 R32* __restrict m_pdk;

_Field_size_(m_kte)  R32* __restrict m_pdt;

_Field_size_(m_kte)  R32* __restrict m_pdq;

_Field_size_(m_kte)  R32* __restrict m_pdc;

_Field_size_(m_kte)  R32* __restrict m_tcd;

_Field_size_(m_kte)  R32* __restrict m_qcd;

_Field_size_(m_kte)  R32* __restrict m_qWT1D;

_Field_size_(m_kte)  R32* __restrict m_qSHEAR1D;

_Field_size_(m_kte)  R32* __restrict m_qBUOY1D;

_Field_size_(m_kte)  R32* __restrict m_qDISS1D;

				static const int m_totArrays = 32;

			};












	}
}




#endif /*__MODULE_BL_MYNN_MYM_TURBULENCE_IMPL_H__*/