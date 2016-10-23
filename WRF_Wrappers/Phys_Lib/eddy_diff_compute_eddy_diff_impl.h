#ifndef __EDDY_DIFF_COMPUTE_EDDY_DIFF_IMPL_H__
#define __EDDY_DIFF_COMPUTE_EDDY_DIFF_IMPL_H__

// File granularity version.
#ifndef EDDY_DIFF_COMPUTE_EDDY_DIFF_VERSION_MAJOR
#define EDDY_DIFF_COMPUTE_EDDY_DIFF_VERSION_MAJOR 1
#endif

#ifndef EDDY_DIFF_COMPUTE_EDDY_DIFF_VERSION_MINOR
#define EDDY_DIFF_COMPUTE_EDDY_DIFF_VERSION_MINOR 0
#endif

#ifndef EDDY_DIFF_COMPUTE_EDDY_DIFF_PATCH_VERSION
#define EDDY_DIFF_COMPUTE_EDDY_DIFF_PATCH_VERSION 0
#endif

#ifndef EDDY_DIFF_COMPUTE_EDDY_DIFF_CREATE_DATE
#define EDDY_DIFF_COMPUTE_EDDY_DIFF_CREATE_DATE "Date: 21-10-2016 , Time: 12:33 PM GMT+2"
#endif

// Set this value to successfull build date/time.
#ifndef EDDY_DIFF_COMPUTE_EDDY_DIFF_BUILD_DATE
#define EDDY_DIFF_COMPUTE_EDDY_DIFF_BUILD_DATE ""
#endif

#ifndef EDDY_DIFF_COMPUTE_EDDY_DIFF_AUTHOR
#define EDDY_DIFF_COMPUTE_EDDY_DIFF_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif

#include "module_cam_bl_eddy_diff_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

namespace phys_lib_wrappers {
	namespace module_eddy_diff {



		/*
		 *  Wrapping structure called 'Wrap_Compute_Eddy_Diff' its main
		 *  purpose is to present herself as high level wrapper interface
		 *	to underlying Fortran 90 'COMPUTE_EDDY_DIFF' subroutine.
         */

		template<typename R64 = double,
				 typename I32 = int >   struct Wrap_Compute_Eddy_Diff {



					 /*****************************************
						   Constructors and Destructor.
					 *******************************************/

					 /*
						@Purpose:
								 Default Constructor - explictly default.
					 */
					 Wrap_Compute_Eddy_Diff() = default;

					 /*
						@Purpose:
								  1st 'main' Constructor which purpose
								  is to allocate and initialize scalar
								  and array members. Array members are
								  zero-filled. Caller must later initialize
								  input arrays to correct physical state.

					 */
					 Wrap_Compute_Eddy_Diff(_In_ const I32 lchnk,
						                    _In_ const I32 pcols,
						                    _In_ const I32 pver,
						                    _In_ const I32 ncol,
						                    _In_ const I32 wstarent,
						                    _In_ const I32 nturb,
						                    _In_ const I32 qsat,
						                    _In_ const I32 kvinit,
						                    _In_ const R64 ztdot)
						                  :
						           m_lchnk{ lchnk },
						           m_pcols{ pcols },
						           m_pver{ pver },
						           m_ncol{ ncol },
						           m_wstarent{ wstarent },
						           m_nturb{ nturb },
						           m_qsat{ qsat },
						           m_kvinit{ kvinit },
						           m_ztdot{ ztdot },
						           m_t{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_qv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_qi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_s{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_rpdel{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_cldn{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_qrl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_wsedl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_z{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_pmid{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_u{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_v{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						           m_taux{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)) align32B)) },
						           m_tauy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_shflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_qflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_ustar{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_pblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_kvm_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_kvh_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_kvm_out{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_kvh_out{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_kvq{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_cgh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_cgs{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_tpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_qpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_wpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_tke{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_bprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_sprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						           m_tauresx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_tauresy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_ksrftms{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_ipbl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_kpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_wstarPBL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						           m_turbtype{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)), align32B)) },
								   m_sm_aw{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)), align32B)) } {

						 // Begin  member pointers validity check.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_t)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor Wrap_Compute_Eddy_Diff!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_t)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }

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
								 this->m_t[i + m_pcols * j] = 0.0;
								 this->m_qv[i + m_pcols * j] = 0.0;
								 this->m_ql[i + m_pcols * j] = 0.0;
								 this->m_qi[i + m_pcols * j] = 0.0;
								 this->m_s[i  + m_pcols * j] = 0.0;
								 this->m_rpdel[i + m_pcols * j] = 0.0;
								 this->m_cldn[i + m_pcols * j] = 0.0;
								 this->m_qrl[i + m_pcols * j] = 0.0;
								 this->m_wsedl[i + m_pcols * j] = 0.0;
								 this->m_z[i + m_pcols * j] = 0.0;
								 this->m_zi[i + m_pcols * j] = 0.0;
								 this->m_pmid[i + m_pcols * j] = 0.0;
								 this->m_pi[i + m_pcols * j] = 0.0;
								 this->m_u[i + m_pcols * j] = 0.0;
								 this->m_v[i + m_pcols * j] = 0.0;
								 this->m_kvm_in[i + m_pcols * j] = 0.0;
								 this->m_kvh_in[i + m_pcols * j] = 0.0;
								 this->m_kvm_out[i + m_pcols * j] = 0.0;
								 this->m_kvh_out[i + m_pcols * j] = 0.0;
								 this->m_kvq[i + m_pcols * j] = 0.0;
								 this->m_cgh[i + m_pcols * j] = 0.0;
								 this->m_cgs[i + m_pcols * j] = 0.0;
								 this->m_tke[i + m_pcols * j] = 0.0;
								 this->m_bprod[i + m_pcols * j] = 0.0;
								 this->m_sprod[i + m_pcols * j] = 0.0;
								 this->m_sfi[i + m_pcols * j] = 0.0;
								 this->m_turbtype[i + m_pcols * j] = 0.0;
								 this->m_sm_aw[i + m_pcols * j] = 0.0;
							 }
						 }
						 // Initialize last element of size = m_pcols * m_pver + 1,
						 // with null.
						 const int top = m_pcols * m_pver + 1;
						 this->m_zi[top] = 0.0;
						 this->m_pi[top] = 0.0;
						 this->m_kvm_in[top] = 0.0;
						 this->m_kvh_in[top] = 0.0;
						 this->m_kvm_out[top] = 0.0;
						 this->m_kvh_out[top] = 0.0;
						 this->m_kvq[top] = 0.0;
						 this->m_cgh[top] = 0.0;
						 this->m_cgs[top] = 0.0;
						 this->m_tke[top] = 0.0;
						 this->m_bprod[top] = 0.0;
						 this->m_sprod[top] = 0.0;
						 this->m_sfi[top] = 0.0;
						 this->m_turbtype[top] = 0.0;
						 this->m_sm_aw[top] = 0.0;

						 /* Arrays 1D vectorize only.
						 Strip mining is enabled by default.*/
#if defined (USE_STRIP_MINING)
						 for (int i{ 0 }; i < this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)

#endif
							 for (int j = i; j < std::min(this->m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
								 this->m_taux[j] = 0.0;
								 this->m_tauy[j] = 0.0;
								 this->m_shflx[j] = 0.0;
								 this->m_qflx[j] = 0.0;
								 this->m_ustar[j] = 0.0;
								 this->m_pblh[j] = 0.0;
								 this->m_tpert[j] = 0.0;
								 this->m_qpert[j] = 0.0;
								 this->m_wpert[j] = 0.0;
								 this->m_tauresx[j] = 0.0;
								 this->m_tauresy[j] = 0.0;
								 this->m_ksrftms[j] = 0.0;
								 this->m_ipbl[j] = 0.0;
								 this->m_kpblh[j] = 0.0;
								 this->m_wstarPBL[j] = 0.0;
							 }
						 }

#else
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
							 this->m_taux[i] = 0.0;
							 this->m_tauy[i] = 0.0;
							 this->m_shflx[i] = 0.0;
							 this->m_qflx[i] = 0.0;
							 this->m_ustar[i] = 0.0;
							 this->m_pblh[i] = 0.0;
							 this->m_tpert[i] = 0.0;
							 this->m_qpert[i] = 0.0;
							 this->m_wpert[i] = 0.0;
							 this->m_tauresx[i] = 0.0;
							 this->m_tauresy[i] = 0.0;
							 this->m_ksrftms[i] = 0.0;
							 this->m_ipbl[i] = 0.0;
							 this->m_kpblh[i] = 0.0;
							 this->m_wstarPBL[i] = 0.0;
						 }

#endif





#else 

							 for (int i{ 0 }; i != this->m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
	                              for (int j{ 0 }; j != this->m_pver; ++j) {
		                               this->m_t[i + m_pcols * j] = 0.0;
		                               this->m_qv[i + m_pcols * j] = 0.0;
		                               this->m_ql[i + m_pcols * j] = 0.0;
		                               this->m_qi[i + m_pcols * j] = 0.0;
		                               this->m_s[i + m_pcols * j] = 0.0;
		                               this->m_rpdel[i + m_pcols * j] = 0.0;
		                               this->m_cldn[i + m_pcols * j] = 0.0;
		                               this->m_qrl[i + m_pcols * j] = 0.0;
		                               this->m_wsedl[i + m_pcols * j] = 0.0;
		                               this->m_z[i + m_pcols * j] = 0.0;
		                               this->m_zi[i + m_pcols * j] = 0.0;
		                               this->m_pmid[i + m_pcols * j] = 0.0;
		                               this->m_pi[i + m_pcols * j] = 0.0;
		                               this->m_u[i + m_pcols * j] = 0.0;
		                               this->m_v[i + m_pcols * j] = 0.0;
		                               this->m_kvm_in[i + m_pcols * j] = 0.0;
		                               this->m_kvh_in[i + m_pcols * j] = 0.0;
		                               this->m_kvm_out[i + m_pcols * j] = 0.0;
		                               this->m_kvh_out[i + m_pcols * j] = 0.0;
		                               this->m_kvq[i + m_pcols * j] = 0.0;
		                               this->m_cgh[i + m_pcols * j] = 0.0;
		                               this->m_cgs[i + m_pcols * j] = 0.0;
		                               this->m_tke[i + m_pcols * j] = 0.0;
		                               this->m_bprod[i + m_pcols * j] = 0.0;
		                               this->m_sprod[i + m_pcols * j] = 0.0;
		                               this->m_sfi[i + m_pcols * j] = 0.0;
		                               this->m_turbtype[i + m_pcols * j] = 0.0;
		                               this->m_sm_aw[i + m_pcols * j] = 0.0;
	}
}
                          // Initialize last element of size = m_pcols * m_pver + 1,
                         // with null.
                                     const int top = m_pcols * m_pver + 1;
                                     this->m_zi[top] = 0.0;
                                     this->m_pi[top] = 0.0;
                                     this->m_kvm_in[top] = 0.0;
                                     this->m_kvh_in[top] = 0.0;
                                     this->m_kvm_out[top] = 0.0;
                                     this->m_kvh_out[top] = 0.0;
                                     this->m_kvq[top] = 0.0;
                                     this->m_cgh[top] = 0.0;
                                     this->m_cgs[top] = 0.0;
                                     this->m_tke[top] = 0.0;
                                     this->m_bprod[top] = 0.0;
                                     this->m_sprod[top] = 0.0;
                                     this->m_sfi[top] = 0.0;
                                     this->m_turbtype[top] = 0.0;
                                     this->m_sm_aw[top] = 0.0;


									 /* Arrays 1D vectorize only.
									 Strip mining is enabled by default.*/
#if defined (USE_STRIP_MINING)
									 for (int i{ 0 }; i < this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)

#endif
										 for (int j = i; j < std::min(this->m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
											 this->m_taux[j] = 0.0;
											 this->m_tauy[j] = 0.0;
											 this->m_shflx[j] = 0.0;
											 this->m_qflx[j] = 0.0;
											 this->m_ustar[j] = 0.0;
											 this->m_pblh[j] = 0.0;
											 this->m_tpert[j] = 0.0;
											 this->m_qpert[j] = 0.0;
											 this->m_wpert[j] = 0.0;
											 this->m_tauresx[j] = 0.0;
											 this->m_tauresy[j] = 0.0;
											 this->m_ksrftms[j] = 0.0;
											 this->m_ipbl[j] = 0.0;
											 this->m_kpblh[j] = 0.0;
											 this->m_wstarPBL[j] = 0.0;
										 }
									 }

#else
									 for (int i{ 0 }; i != this->m_pcols; ++i) {
										 this->m_taux[i] = 0.0;
										 this->m_tauy[i] = 0.0;
										 this->m_shflx[i] = 0.0;
										 this->m_qflx[i] = 0.0;
										 this->m_ustar[i] = 0.0;
										 this->m_pblh[i] = 0.0;
										 this->m_tpert[i] = 0.0;
										 this->m_qpert[i] = 0.0;
										 this->m_wpert[i] = 0.0;
										 this->m_tauresx[i] = 0.0;
										 this->m_tauresy[i] = 0.0;
										 this->m_ksrftms[i] = 0.0;
										 this->m_ipbl[i] = 0.0;
										 this->m_kpblh[i] = 0.0;
										 this->m_wstarPBL[i] = 0.0;
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
			Wrap_Compute_Eddy_Diff(_In_ const I32 lchnk,
				                   _In_ const I32 pcols,
				                   _In_ const I32 pver,
				                   _In_ const I32 ncol,
				                   _In_ const I32 wstarent,
				                   _In_ const I32 nturb,
				                   _In_ const I32 qsat,
				                   _In_ const I32 kvinit,
				                   _In_ const R64 ztdot,
				                   _In_ R64* __restrict const t,
				                   _In_ R64* __restrict const qv,
				                   _In_ R64* __restrict const ql,
				                   _In_ R64* __restrict const qi,
				                   _In_ R64* __restrict const s,
							       _In_ R64* __restrict const rpdel,
				                   _In_ R64* __restrict const cldn,
				                   _In_ R64* __restrict const qrl,
				                   _In_ R64* __restrict const wsedl,
				                   _In_ R64* __restrict const z,
				                   _In_ R64* __restrict const zi,
				                   _In_ R64* __restrict const pmid,
				                   _In_ R64* __restrict const pi,
				                   _In_ R64* __restrict const u,
				                   _In_ R64* __restrict const v,
				                   _In_ R64* __restrict const taux,
				                   _In_ R64* __restrict const tauy,
				                   _In_ R64* __restrict const shflx,
				                   _In_ R64* __restrict const qflx,
				                   _In_ R64* __restrict const kvm_in,
				                   _In_ R64* __restrict const kvh_in,
				                   _Inout_ R64* __restrict tauresx,
				                   _Inout_ R64* __restrict const tauresy,
				                   _In_ R64* __restrict ksrftms,
				                                               )
				                    :
			                   m_lchnk{ lchnk },
				               m_pcols{ pcols },
				               m_pver{ pver },
				               m_ncol{ ncol },
				               m_wstarent{ wstarent },
				               m_nturb{ nturb },
				               m_qsat{ qsat },
				               m_kvinit{ kvinit },
				               m_ztdot{ ztdot },
				               m_t{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_qv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_qi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_s{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_rpdel{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_cldn{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_qrl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_wsedl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_z{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_pmid{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_u{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_v{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_taux{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)) align32B)) },
				               m_tauy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_shflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_qflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_ustar{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_pblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_kvm_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_kvh_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_kvm_out{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_kvh_out{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_kvq{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_cgh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_cgs{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_tpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_qpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_wpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_tke{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_bprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_sprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_tauresx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_tauresy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_ksrftms{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_ipbl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_kpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_wstarPBL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_turbtype{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)), align32B)) },
				               m_sm_aw{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)), align32B)) } {

							   // Begin member arrays memory allocation check.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_t)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor Wrap_Compute_Eddy_Diff!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_t)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
				         }
						     // Begin caller passed input arrays memory allocation check.
						 if (t       == NULL ||
							 qv      == NULL ||
							 ql      == NULL ||
							 qi      == NULL ||
							 s       == NULL ||
							 rpdel   == NULL ||
							 cldn    == NULL ||
							 qrl     == NULL ||
							 wsedl   == NULL ||
							 z       == NULL ||
							 zi      == NULL ||
							 pmid    == NULL ||
							 pi      == NULL ||
							 u       == NULL ||
							 v       == NULL ||
							 taux    == NULL ||
							 tauy    == NULL ||
							 shflx   == NULL ||
							 qflx    == NULL ||
							 kvm_in  == NULL ||
							 kvh_in  == NULL ||
							 tauresx == NULL ||
							 tauresy == NULL ||
							 ksrftms == NULL || ) {

							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor Wrap_Compute_Eddy_Diff!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "One or more caller's arrays contains invalid pointer!!\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40

#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 20))
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
// Such an extensive prefetching to L1D should be tested.
#if defined (USE_SOFT_PREFETCHING)
#pragma prefetch t:0:L1_NCYCLES
#pragma prefetch qv:0:L1_NCYCLES
#pragma prefetch ql:0:L1_NCYCLES
#pragma prefetch qi:0:L1_NCYCLES
#pragma prefetch s:0:L1_NCYCLES
#pragma prefetch rpdel:0:L1_NCYCLES
#pragma prefetch cldn:0:L1_NCYCLES
#pragma prefetch qrl:0:L1_NCYCLES
#pragma prefetch wsedl:0:L1_NCYCLES
#pragma prefetch z:0:L1_NCYCLES
#pragma prefetch zi:0:L1_NCYCLES
#pragma prefetch pmid:0:L1_NCYCLES
#pragma prefetch pi:0:L1_NCYCLES
#pragma prefetch u:0:L1_NCYCLES
#pragma prefetch v:0:L1_NCYCLES
#pragma prefetch kvm_in:0:L1_NCYCLES
#pragma prefetch kvh_in:0:L1_NCYCLES
#endif
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for(int j{ 0 }; j != this->m_pver;  ++j ) {
								 this->m_t[i + m_pcols * j] = t[i + m_pcols * j];
								 this->m_qv[i + m_pcols * j] = qv[i + m_pcols * j];
								 this->m_ql[i + m_pcols * j] = ql[i + m_pcols * j];
								 this->m_qi[i + m_pcols * j] = qi[i + m_pcols * j];
								 this->m_s[i  + m_pcols * j] = s[i + m_pcols * j];
								 this->m_rpdel[i + m_pcols * j] = rpdel[i + m_pcols * j];
								 this->m_cldn[i + m_pcols * j] = cldn[i + m_pcols * j];
								 this->m_qrl[i + m_pcols * j] = qrl[i + m_pcols * j];
								 this->m_wsedl[i + m_pcols * j] = wsedl[i + m_pcols * j];
								 this->m_z[i + m_pcols * j] = z[i + m_pcols * j];
								 this->m_zi[i + m_pcols * j] = zi[i + m_pcols * j];
								 this->m_pmid[i + m_pcols * j] = pmid[i + m_pcols * j];
								 this->m_pi[i + m_pcols * j] = pi[i + m_pcols * j];
								 this->m_u[i + m_pcols * j] = u[i + m_pcols * j];
								 this->m_v[i + m_pcols * j] = v[i + m_pcols * j];
								 this->m_kvm_in[i + m_pcols * j] = kvm_in[i + m_pcols * j];
								 this->m_kvh_in[i + m_pcols * j] = kvh_in[i + m_pcols * j];
								 this->m_kvm_out[i + m_pcols * j] = 0.0;
								 this->m_kvh_out[i + m_pcols * j] = 0.0;
								 this->m_kvq[i + m_pcols * j] = 0.0;
								 this->m_cgh[i + m_pcols * j] = 0.0;
								 this->m_cgs[i + m_pcols * j] = 0.0;
								 this->m_tke[i + m_pcols * j] = 0.0;
								 this->m_bprod[i + m_pcols * j] = 0.0;
								 this->m_sprod[i + m_pcols * j] = 0.0;
								 this->m_sfi[i + m_pcols * j] = 0.0;
								 this->m_turbtype[i + m_pcols * j] = 0.0;
								 this->m_sm_aw[i + m_pcols * j] = 0.0;

							 }
						 }
						 // Initialize last element of size = m_pcols * m_pver + 1,
						 // with values passed by caller's input arrays.
						 // Output arrays are null initialized.
						 const int top = this->m_pcols * this->m_pver + 1;
						 this->m_zi[top] = zi[top];
						 this->m_pi[top] = pi[top];
						 this->m_kvm_in[top] = kvm_in[top];
						 this->m_kvh_in[top] = kvh_in[top];
						 this->m_kvm_out[top] = 0.0;
						 this->m_kvh_out[top] = 0.0;
						 this->m_kvq[top] = 0.0;
						 this->m_cgh[top] = 0.0;
						 this->m_cgs[top] = 0.0;
						 this->m_tke[top] = 0.0;
						 this->m_bprod[top] = 0.0;
						 this->m_sprod[top] = 0.0;
						 this->m_sfi[top] = 0.0;
						 this->m_turbtype[top] = 0.0;
						 this->m_sm_aw[top] = 0.0;


						 // Copy to arrays 1D , vectorize only.
						 // Strip mining is enabled by default.
#if defined (USE_STRIP_MINING)

						 for (int i{ 0 }; i < this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
								 this->m_taux[j] = taux[j];
								 this->m_tauy[j] = tauy[j];
								 this->m_shflx[j] = shflx[j];
								 this->m_qflx[j] = qflx[j];
								 this->m_ustar[j] = 0.0;
								 this->m_pblh[j] = 0.0;
								 this->m_tpert[j] = 0.0;
								 this->m_qpert[j] = 0.0;
								 this->m_wpert[j] = 0.0;
								 this->m_tauresx[j] = tauresx[j];
								 this->m_tauresy[j] = tauresy[j];
								 this->m_ksrftms[j] = ksrftms[j];
								 this->m_ipbl[j] = 0.0;
								 this->m_kpblh[j] = 0.0;
								 this->m_wstarPBL[j] = 0.0;

						 }
					}

#else
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
						 for(int i {0}; i != this->m_pcols; ++i) {
							 this->m_taux[j] = taux[j];
							 this->m_tauy[j] = tauy[j];
							 this->m_shflx[j] = shflx[j];
							 this->m_qflx[j] = qflx[j];
							 this->m_ustar[j] = 0.0;
							 this->m_pblh[j] = 0.0;
							 this->m_tpert[j] = 0.0;
							 this->m_qpert[j] = 0.0;
							 this->m_wpert[j] = 0.0;
							 this->m_tauresx[j] = tauresx[j];
							 this->m_tauresy[j] = tauresy[j];
							 this->m_ksrftms[j] = ksrftms[j];
							 this->m_ipbl[j] = 0.0;
							 this->m_kpblh[j] = 0.0;
							 this->m_wstarPBL[j] = 0.0;
						 }

#endif


#else
// LOOP_BLOCKING must not be undefined!!
#if defined (USE_LOOP_BLOCKING)

                             for(int i {0}; i < m_pcols; i += DEFAULT_BLOCK_SIZE) {
								 for(int j {0}; j < m_pver; j += DEFAULT_BLOCK_SIZE) {
									 for(int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
										 for(int jj = j; jj < DEFAULT_BLOCK_SIZE; ++j) {
											 this->m_t[ii + m_pcols * jj] = t[ii + m_pcols * jj];
											 this->m_qv[ii + m_pcols * jj] = qv[ii + m_pcols * jj];
											 this->m_ql[ii + m_pcols * jj] = ql[ii + m_pcols * jj];
											 this->m_qi[ii + m_pcols * jj] = qi[ii + m_pcols * jj];
											 this->m_s[ii  + m_pcols * jj] = s[i i+ m_pcols * jj];
											 this->m_rpdel[ii + m_pcols * jj] = rpdel[ii + m_pcols * jj];
											 this->m_cldn[ii + m_pcols * jj] = cldn[ii + m_pcols * jj];
											 this->m_qrl[ii + m_pcols * jj] = qrl[ii + m_pcols * jj];
											 this->m_wsedl[ii + m_pcols * jj] = wsedl[ii + m_pcols * jj];
											 this->m_z[ii + m_pcols * jj] = z[ii + m_pcols * jj];
											 this->m_zi[ii + m_pcols * jj] = zi[ii + m_pcols * jj];
											 this->m_pmid[ii + m_pcols * jj] = pmid[ii + m_pcols * jj];
											 this->m_pi[ii + m_pcols * jj] = pi[ii + m_pcols * jj];
											 this->m_u[ii + m_pcols * jj] = u[ii + m_pcols * jj];
											 this->m_v[ii + m_pcols * jj] = v[ii + m_pcols * jj];
											 this->m_kvm_in[ii + m_pcols * jj] = kvm_in[ii + m_pcols * jj];
											 this->m_kvh_in[ii + m_pcols * jj] = kvh_in[ii + m_pcols * jj];
											 this->m_kvm_out[ii + m_pcols * jj] = 0.0;
											 this->m_kvh_out[ii + m_pcols * jj] = 0.0;
											 this->m_kvq[ii + m_pcols * jj] = 0.0;
											 this->m_cgh[ii + m_pcols * jj] = 0.0;
											 this->m_cgs[ii + m_pcols * jj] = 0.0;
											 this->m_tke[ii + m_pcols * jj] = 0.0;
											 this->m_bprod[ii + m_pcols * jj] = 0.0;
											 this->m_sprod[ii + m_pcols * jj] = 0.0;
											 this->m_sfi[ii + m_pcols * jj] = 0.0;
											 this->m_turbtype[ii + m_pcols * jj] = 0.0;
											 this->m_sm_aw[ii + m_pcols * jj] = 0.0;
										 }
									 }
								 }
                          }

#endif
                            
							 // Initialize last element of size = m_pcols * m_pver + 1,
							 // with values passed by caller's input arrays.
							 // Output arrays are null initialized.
							 const int top = this->m_pcols * this->m_pver + 1;
							 this->m_zi[top] = zi[top];
							 this->m_pi[top] = pi[top];
							 this->m_kvm_in[top] = kvm_in[top];
							 this->m_kvh_in[top] = kvh_in[top];
							 this->m_kvm_out[top] = 0.0;
							 this->m_kvh_out[top] = 0.0;
							 this->m_kvq[top] = 0.0;
							 this->m_cgh[top] = 0.0;
							 this->m_cgs[top] = 0.0;
							 this->m_tke[top] = 0.0;
							 this->m_bprod[top] = 0.0;
							 this->m_sprod[top] = 0.0;
							 this->m_sfi[top] = 0.0;
							 this->m_turbtype[top] = 0.0;
							 this->m_sm_aw[top] = 0.0;

							 // Copy to arrays 1D , vectorize only.
							 // Strip mining is enabled by default.
#if defined (USE_STRIP_MINING)

							 for (int i{ 0 }; i < this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
									 this->m_taux[j] = taux[j];
									 this->m_tauy[j] = tauy[j];
									 this->m_shflx[j] = shflx[j];
									 this->m_qflx[j] = qflx[j];
									 this->m_ustar[j] = 0.0;
									 this->m_pblh[j] = 0.0;
									 this->m_tpert[j] = 0.0;
									 this->m_qpert[j] = 0.0;
									 this->m_wpert[j] = 0.0;
									 this->m_tauresx[j] = tauresx[j];
									 this->m_tauresy[j] = tauresy[j];
									 this->m_ksrftms[j] = ksrftms[j];
									 this->m_ipbl[j] = 0.0;
									 this->m_kpblh[j] = 0.0;
									 this->m_wstarPBL[j] = 0.0;

								 }
							 }

#endif

#endif
			}

			          /*
						@Purpose:
								 Copy Constructor implements deep copy semantics.
					  */
			Wrap_Compute_Eddy_Diff(_In_ const Wrap_Compute_Eddy_Diff &x)
				                      :
				               m_lchnk{ x.m_lchnk },
				               m_pcols{ x.m_pcols },
				               m_pver{ x.m_pver },
				               m_ncol{ x.m_ncol },
				               m_wstarent{ x.m_wstarent },
				               m_nturb{ x.m_nturb },
				               m_qsat{ x.m_qsat },
				               m_kvinit{ x.m_kvinit },
				               m_ztdot{ x.m_ztdot },
				               m_t{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_qv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_qi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_s{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_rpdel{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_cldn{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_qrl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_wsedl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_z{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_pmid{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_u{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_v{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				               m_taux{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)) align32B)) },
				               m_tauy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_shflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_qflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_ustar{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_pblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_kvm_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_kvh_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_kvm_out{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_kvh_out{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_kvq{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_cgh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_cgs{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_tpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_qpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_wpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_tke{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_bprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_sprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				               m_tauresx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_tauresy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_ksrftms{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_ipbl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_kpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_wstarPBL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				               m_turbtype{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)), align32B)) },
				               m_sm_aw{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver + 1 * sizeof(R64)), align32B)) } {

							   // Checking for arrays allocation errors.
				                  for (int i{ 0 }; i != this->m_nArrays; ++i) {
									  if ((&this->m_t)[i] == NULL) {
										  std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor Wrap_Compute_Eddy_Diff!!\n";
										  std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
										  std::cerr << "***** ERROR-DETAILS ***** \n";
										  std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_t)[i] << "\n";
										  std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
										  std::exit(-1);
									  }
								  }
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 20))
								  for (int i{ 0 }; i != this->m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
									  for (int j{ 0 }; j != this->m_pver; ++j ) {
										  this->m_t[i + m_pcols * j] = x.m_t[i + x.m_pcols * j];
										  this->m_qv[i + m_pcols * j] = x.m_qv[i + x.m_pcols * j];
										  this->m_ql[i + m_pcols * j] = x.m_ql[i + x.m_pcols * j];
										  this->m_qi[i + m_pcols * j] = x.m_pi[i + x.m_pcols * j];
										  this->m_s[i  + m_pcols * j] = x.m_s[i  + x.m_pcols * j];
										  this->m_rpdel[i + m_pcols * j] = x.m_rpdel[i + x.m_pcols * j];
										  this->m_cldn[i + m_pcols * j] = x.m_cldn[i + x.m_pcols * j];
										  this->m_qrl[i + m_pcols * j] = x.m_qrl[i + x.m_pcols * j];
										  this->m_wsedl[i + m_pcols * j] = x.m_wsedl[i + x.m_pcols * j];
										  this->m_z[i + m_pcols * j] = x.m_z[i + x.m_pcols * j];
										  this->m_zi[i + m_pcols * j] = x.m_zi[i + x.m_pcols * j];
										  this->m_pmid[i + m_pcols * j] = x.m_pmid[i + x.m_pcols * j];
										  this->m_pi[i + m_pcols * j] = x.m_pi[i + x.m_pcols * j];
										  this->m_u[i + m_pcols * j] = x.m_u[i + x.m_pcols * j];
										  this->m_v[i + m_pcols * j] = x.m_v[i + x.m_pcols * j];
										  this->m_kvm_in[i + m_pcols * j] = x.m_kvm_in[i + x.m_pcols * j];
										  this->m_kvh_in[i + m_pcols * j] = x.m_kvh_in[i + x.m_pcols * j];
										  this->m_kvm_out[i + m_pcols * j] = x.m_kvm_out[i + x.m_pcols * j];
										  this->m_kvq[i + m_pcols * j] = x.m_kvq[i + x.m_pcols * j];
										  this->m_cgh[i + m_pcols * j] = x.m_cgh[i + x.m_pcols * j];
										  this->m_cgs[i + m_pcols * j] = x.m_cgs[i + x.m_pcols * j];
										  this->m_tke[i + m_pcols * j] = x.m_tke[i + x.m_pcols * j];
										  this->m_bprod[i + m_pcols * j] = x.m_bprod[i + x.m_pcols * j];
										  this->m_sprod[i + m_pcols * j] = x.m_sprod[i + x.m_pcols * j];
										  this->m_sfi[i + m_pcols * j] = x.m_sfi[i + x.m_pcols * j];
										  this->m_turbtype[i + m_pcols * j] = x.m_turbtype[i + x.m_pcols * j];
										  this->m_sm_aw[i + m_pcols * j] = x.m_sm_aw[i + x.m_pcols * j];
									  }
								  }

								  // Copy arrays 2D , where (pver = pver + 1) 
								  // top element from x to *this.
								  const int top = this->m_pcols * (this->m_pver + 1);
								  this->m_zi[top] = x.m_zi[top];
								  this->m_pi[top] = x.m_pi[top];
								  this->m_kvm_in[top] = x.m_kvm_in[top];
								  this->m_kvh_in[top] = x.m_kvh_in[top];
								  this->m_kvm_out[top] = x.m_kvm_out[top];
								  this->m_kvh_out[top] = x.m_kvh_out[top];
								  this->m_kvq[top] = x.m_kvq[top];
								  this->m_cgh[top] = x.m_cgh[top];
								  this->m_cgs[top] = x.m_cgs[top];
								  this->m_tke[top] = x.m_tke[top];
								  this->m_bprod[top] = x.m_bprod[top];
								  this->m_sprod[top] = x.m_sprod[top];
								  this->m_sfi[top] = x.m_sfi[top];
								  this->m_turbtype[top] = x.m_turbtype[top];
								  this->m_sm_aw[top] = x.m_sm_aw[top];

								  // Copy content of arrays 1D , vectorize only.
								  // For speed up using Strip mining.
#if defined (USE_STRIP_MINING)

								  for (int i{ 0 }; i < m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
									  for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
										  this->m_taux[j] = x.m_taux[j];
										  this->m_tauy[j] = x.m_tauy[j];
										  this->m_shflx[j] = x.m_shflx[j];
										  this->m_qflx[j] = x.m_qflx[j];
										  this->m_ustar[j] = x.m_ustar[j];
										  this->m_pblh[j] = x.m_pblh[j];
										  this->m_tpert[j] = x.m_tpert[j];
										  this->m_qpert[j] = x.m_qpert[j];
										  this->m_wpert[j] = x.m_wpert[j];
										  this->m_tauresx[j] = x.m_tauresx[j];
										  this->m_tauresy[j] = x.m_tauresy[j];
										  this->m_ksrftms[j] = x.m_ksrftms[j];
										  this->m_ipbl[j] = x.m_ipbl[j];
										  this->m_kpblh[j] = x.m_kpblh[j];
										  this->m_wstarPBL[j] = x.m_wstarPBL[j];
									  }
								  }
#endif

#else
								  //Using loop blocking technique.
								  // 'USE_LOOP_BLOCKING' -- must not be undefined.

#if defined (USE_LOOP_BLOCKING)
								  for (int i{ 0 }; i < m_pcols; i += DEFAULT_BLOCK_SIZE) {
									  for (int j{ 0 }; j < m_pver; j += DEFAULT_BLOCK_SIZE) {
										  for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
											  for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++j) {
												  this->m_t[ii + m_pcols * jj] = x.m_t[ii + x.m_pcols * jj];
												  this->m_qv[ii + m_pcols * jj] = x.m_qv[ii + x.m_pcols * jj];
												  this->m_ql[ii + m_pcols * jj] = x.m_ql[ii + x.m_pcols * jj];
												  this->m_qi[ii + m_pcols * jj] = x.m_pi[ii + x.m_pcols * jj];
												  this->m_s[ii + m_pcols * jj] = x.m_s[ii + x.m_pcols * jj];
												  this->m_rpdel[ii + m_pcols * jj] = x.m_rpdel[ii + x.m_pcols * jj];
												  this->m_cldn[ii + m_pcols * jj] = x.m_cldn[ii + x.m_pcols * jj];
												  this->m_qrl[ii + m_pcols * jj] = x.m_qrl[ii + x.m_pcols * jj];
												  this->m_wsedl[ii + m_pcols * jj] = x.m_wsedl[ii + x.m_pcols * jj];
												  this->m_z[ii + m_pcols * jj] = x.m_z[ii + x.m_pcols * jj];
												  this->m_zi[ii + m_pcols * jj] = x.m_zi[ii + x.m_pcols * jj];
												  this->m_pmid[ii + m_pcols * jj] = x.m_pmid[ii + x.m_pcols * jj];
												  this->m_pi[ii + m_pcols * jj] = x.m_pi[ii + x.m_pcols * jj];
												  this->m_u[ii + m_pcols * jj] = x.m_u[ii + x.m_pcols * jj];
												  this->m_v[ii + m_pcols * jj] = x.m_v[ii + x.m_pcols * jj];
												  this->m_kvm_in[ii + m_pcols * jj] = x.m_kvm_in[ii + x.m_pcols * jj];
												  this->m_kvh_in[ii + m_pcols * jj] = x.m_kvh_in[ii + x.m_pcols * jj];
												  this->m_kvm_out[ii + m_pcols * jj] = x.m_kvm_out[ii + x.m_pcols * jj];
												  this->m_kvq[ii + m_pcols * jj] = x.m_kvq[ii + x.m_pcols * jj];
												  this->m_cgh[ii + m_pcols * jj] = x.m_cgh[ii + x.m_pcols * jj];
												  this->m_cgs[ii + m_pcols * jj] = x.m_cgs[ii + x.m_pcols * jj];
												  this->m_tke[ii + m_pcols * jj] = x.m_tke[ii + x.m_pcols * jj];
												  this->m_bprod[ii + m_pcols * jj] = x.m_bprod[ii + x.m_pcols * jj];
												  this->m_sprod[ii + m_pcols * jj] = x.m_sprod[ii + x.m_pcols * jj];
												  this->m_sfi[ii + m_pcols * jj] = x.m_sfi[ii + x.m_pcols * jj];
												  this->m_turbtype[ii + m_pcols * jj] = x.m_turbtype[ii + x.m_pcols * jj];
												  this->m_sm_aw[ii + m_pcols * jj] = x.m_sm_aw[ii + x.m_pcols * jj];
											  }
										  }
									  }
									  
								  }


#endif
								  // Copy arrays 2D , where (pver = pver + 1) 
								  // top element from x to *this.
								  const int top = this->m_pcols * (this->m_pver + 1);
								  this->m_zi[top] = x.m_zi[top];
								  this->m_pi[top] = x.m_pi[top];
								  this->m_kvm_in[top] = x.m_kvm_in[top];
								  this->m_kvh_in[top] = x.m_kvh_in[top];
								  this->m_kvm_out[top] = x.m_kvm_out[top];
								  this->m_kvh_out[top] = x.m_kvh_out[top];
								  this->m_kvq[top] = x.m_kvq[top];
								  this->m_cgh[top] = x.m_cgh[top];
								  this->m_cgs[top] = x.m_cgs[top];
								  this->m_tke[top] = x.m_tke[top];
								  this->m_bprod[top] = x.m_bprod[top];
								  this->m_sprod[top] = x.m_sprod[top];
								  this->m_sfi[top] = x.m_sfi[top];
								  this->m_turbtype[top] = x.m_turbtype[top];
								  this->m_sm_aw[top] = x.m_sm_aw[top];

								  // Copy arrays 1D content.
								  // Using strip mining and auto vectorization.
#if defined (USE_STRIP_MINING)

								  for (int i{ 0 }; i < m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
									  for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
										  this->m_taux[j] = x.m_taux[j];
										  this->m_tauy[j] = x.m_tauy[j];
										  this->m_shflx[j] = x.m_shflx[j];
										  this->m_qflx[j] = x.m_qflx[j];
										  this->m_ustar[j] = x.m_ustar[j];
										  this->m_pblh[j] = x.m_pblh[j];
										  this->m_tpert[j] = x.m_tpert[j];
										  this->m_qpert[j] = x.m_qpert[j];
										  this->m_wpert[j] = x.m_wpert[j];
										  this->m_tauresx[j] = x.m_tauresx[j];
										  this->m_tauresy[j] = x.m_tauresy[j];
										  this->m_ksrftms[j] = x.m_ksrftms[j];
										  this->m_ipbl[j] = x.m_ipbl[j];
										  this->m_kpblh[j] = x.m_kpblh[j];
										  this->m_wstarPBL[j] = x.m_wstarPBL[j];
									  }
								  }

#endif

#endif

			}

					/*
						@Purpose:
									Move Constructor implements shallow copy semantics.
					*/
			Wrap_Compute_Eddy_Diff(_In_ Wrap_Compute_Eddy_Diff &&x)
									   :
				                m_lchnk{ x.m_lchnk },
				                m_pcols{ x.m_pcols },
				                m_pver{ x.m_pver },
				                m_ncol{ x.m_ncol },
				                m_wstarent{ x.m_wstarent },
				                m_nturb{ x.m_nturb },
				                m_qsat{ x.m_qsat },
				                m_kvinit{ x.m_kvinit },
				                m_ztdot{ x.m_ztdot } {

								// Copy pointers from x to *this.
				               for (int i{ 0 }; i != this->m_nArrays; ++i) {
								   (&this->m_t)[i] = (&x.m_t)[i];
							   }
							   // Nullify x's pointers.
							   for (int i{ 0 }; i != this->m_nArrays; ++i) {
								   (&x.m_t)[i] = NULL;
							   }
							   x.m_pcols = 0;
							   x.m_pver = 0;
			}

			         /*
						@Purpose:
									Class Destructor.
					 */
			         ~Wrap_Compute_Eddy_Diff() {

						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_t)[i]) {
								 _mm_free((&this->m_t)[i]);
							 }
						 }
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&this->m_t)[i] = NULL;
						 }
						 this->m_pcols = 0;
						 this->m_pver = 0;
			}
					
					 /*
						@Purpose:
								  Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Compute_Eddy_Diff & operator=(_In_ const Wrap_Compute_Eddy_Diff &x) {
						 if (this == &x) return (*this);

						 this->m_lchnk = x.m_lchnk;
						 this->m_pcols = x.m_pcols;
						 this->m_pver = x.m_pver;
						 this->m_ncol = x.m_ncol;
						 this->m_wstarent = x.m_wstarent;
						 this->m_nturb = x.m_nturb;
						 this->m_qsat = x.m_qsat;
						 this->m_kvinit = x.m_kvinit;
						 this->m_ztdot = x.m_ztdot;
						 // Begin an allocation of temporary array of pointers
						 // to arrays 1D.
						 constexpr int nPtrs1D{15};
						 R64 *tPtrs1D[nPtrs1D] = {};
						 for (int i{ 0 }; i != this->m_nArrays1D; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)),align32B));

						 }
						 // Check for occurrence of null pointer (malloc failure).
						 for (int i{ 0 }; i != this->m_nArrays1D; ++i) {
							 if (tPtrs1D[i] = NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator Wrap_Compute_Eddy_Diff!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 1D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs1D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Begin an allocation of temporary array of pointers
						 // to arrays 2D.
						 constexpr int nPtrs2D{13};
						 R64* tPtrs2D[nPtrs2D] = {};
						 for (int i{ 0 }; i != this->m_nArrays2D; ++i) {
							 tPtrs2D[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)),align32B));
						 }
						 // Check for occurrence of null pointer(s) (malloc failure).
						 for (int i{ 0 }; i != this->m_nArrays2D; ++i) {
							 if (tPtrs2D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator Wrap_Compute_Eddy_Diff!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs2D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Begin an allocation of temporary array of pointers
						 // to arrays 2D, where m_pver == m_pver + 1.
						 constexpr int nPtrs2Dp1{15};
						 R64* tPtrs2Dp1[nPtrs2Dp1] = {};
						 for (int i{ 0 }; i != this->m_nArrays2Dp1; ++i) {
							 tPtrs2Dp1[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)),align32B));
						 }
						 // Check for occurrence of null pointer(s) (malloc failure).
						 for (int i{ 0 }; i != this->m_nArrays2Dp1; ++i) {
							 if (tPtrs2Dp1[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator Wrap_Compute_Eddy_Diff!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D, m_pver + 1\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs2D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Begin arrays 2D - large copy loop. First arrays 2D.
						 // OpenMP will be in use if total size >= (1 << 20).
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
								 tPtrs2D[0][i + m_pcols * j] = x.m_t[i + x.m_pcols * j];
								 tPtrs2D[1][i + m_pcols * j] = x.m_qv[i + x.m_pcols * j];
								 tPtrs2D[2][i + m_pcols * j] = x.m_ql[i + x.m_pcols * j];
								 tPtrs2D[3][i + m_pcols * j] = x.m_qi[i + x.m_pcols * j];
							 }
						 }


#else




#endif


					 }

					 /*
						@Purpose:
								  Member variables.
					 */

					 // Scalar variables
					 I32 m_lchnk;

					 I32 m_pcols;

					 I32 m_pver;

					 I32 m_ncol;

					 I32 m_wstarent;

					 I32 m_nturb;

					 I32 m_qsat;

					 I32 m_kvinit;

					 R64 m_ztdot;

					 // Array variables
					 /*
					  * Layout of array members is optimized for linear continous 
					  * memory access.
					  */

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_t;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_qv;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_ql;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_qi;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_s;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_rpdel;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_cldn;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_qrl;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_wsedl;

_Field_size_(m_pcols * m_pver)	 R64* __restrict m_z;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_zi;

_Field_size_(m_pcols * m_pver)	R64* __restrict m_pmid;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_pi;

_Field_size_(m_pcols * m_pver)		 R64* __restrict m_u;

_Field_size_(m_pcols * m_pver)		 R64* __restrict m_v;

_Field_size_(m_pcols)		 R64* __restrict m_taux;

_Field_size_(m_pcols)		 R64* __restrict m_tauy;

_Field_size_(m_pcols)	     R64* __restrict m_shflx;

_Field_size_(m_pcols)		 R64* __restrict m_qflx;

_Field_size_(m_pcols)		 R64* __restrict m_ustar;

_Field_size_(m_pcols)		 R64* __restrict m_pblh;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_kvm_in;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_kvh_in;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_kvm_out;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_kvh_out;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_kvq;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_cgh;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_cgs;

_Field_size_(m_pcols)		  R64* __restrict m_tpert;

_Field_size_(m_pcols)		  R64* __restrict m_qpert;

_Field_size_(m_pcols)		  R64* __restrict m_wpert;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_tke;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_bprod;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_sprod;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_sfi;

_Field_size_(m_pcols)				 R64* __restrict m_tauresx;

_Field_size_(m_pcols)				 R64* __restrict m_tauresy;

_Field_size_(m_pcols)				 R64* __restrict m_ksrftms;

_Field_size_(m_pcols)				 R64* __restrict m_ipbl;

_Field_size_(m_pcols)				 R64* __restrict m_kpblh;

_Field_size_(m_pcols)				 R64* __restrict m_wstarPBL;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_turbtype;

_Field_size_(m_pcols * m_pver + 1)	 R64* __restrict m_sm_aw;

									 static const int m_nArrays = 43;

									 static const int m_nArrays1D = 15;

									 static const int m_nArrays2D = 13;

									 static const int m_nArrays2Dp1 = 15;

		};






	}
}


#endif /*__EDDY_DIFF_COMPUTE_EDDY_DIFF_IMPL_H__*/