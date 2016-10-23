
#ifndef __EDDY_DIFF_CALEDDY_IMPL_H__
#define __EDDY_DIFF_CALEDDY_IMPL_H__

#ifndef EDDY_DIFF_CALEDDY_IMPL_VERSION_MAJOR
#define EDDY_DIFF_CALEDDY_IMPL_VERSION_MAJOR 1
#endif

#ifndef EDDY_DIFF_CALEDDY_IMPL_VERSION_MINOR
#define EDDY_DIFF_CALEDDY_IMPL_VERSION_MINOR 0
#endif

#ifndef EDDY_DIFF_CALEDDY_IMPL_PATCH_VERSION
#define EDDY_DIFF_CALEDDY_IMPL_PATCH_VERSION 0
#endif

#ifndef EDDY_DIFF_CALEDDY_IMPL_CREATE_DATE
#define EDDY_DIFF_CALEDDY_IMPL_CREATE_DATE "Date: 13-10-2016  Time: 11:08 AM GMT+2"
#endif

#ifndef EDDY_DIFF_CALEDDY_IMPL_BUILD_DATE
#define EDDY_DIFF_CALEDDY_IMPL_BUILD_DATE ""
#endif

#ifndef EDDY_DIFF_CALEDDY_IMPL_AUTHOR
#define EDDY_DIFF_CALEDDY_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif

#include "module_cam_bl_eddy_diff_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"


namespace phys_lib_wrappers {
	namespace module_eddy_diff {



		template<typename R64 = double,
			     typename I32 = int >   struct WrapCalEddy {

			   /******************************
			     Subroutine caleddy wrapper
				 Should not be called directly
				 from C++ side.
			   *******************************/

					 /***********************************
					      Constructors and Destructor.
					 *************************************/

					 /*
					   @Purpose:
								 Default Constructor explicitly default.
					 */
					 WrapCalEddy() = default;

					 /*
					    @Purpose:
						          1st Constructor allocates and zero
								  initializes Input/Output member arrays.
								  Caller must later initialize Input arrays
								  with proper physical state.
					 */
					 WrapCalEddy(_In_ const I32 pcols,
						 _In_ const I32 pver,
						 _In_ const I32 ncol,
						 _In_ const I32 wstarent)
						 :
						 m_pcols{ pcols },
						 m_pver{ pver },
						 m_ncol{ ncol },
						 m_wstarent{ wstarent },
						 m_sl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_qt{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_slv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_u{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_v{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_z{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_qflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_shflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_slslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_qtslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_chu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_chs{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_cmu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_cms{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_sfuh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_sfhl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_n2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_s2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ri{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_rrho{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_pblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_ustar{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_kvh_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_kvm_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_kvh{reinterpret_cast<R64*>( _mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_kvm{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_tpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_qpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_qrlin{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_kvf{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_tke{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						
						 m_bprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_sprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_minpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_wpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_tkes{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_turbtype_f{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_sm_aw{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_kbase_o{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ktop_o{ reinterpret_cast<R64*>( _mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ncvfin_o{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_kbase_mg{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ktop_mg{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ncvfin_mg{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_kbase_f{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ktop_f{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ncvfin_f{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_wet_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_web_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_jtbu_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_jbbu_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_evhc_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_jt2slv_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_n2ht_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_n2hb_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_lwp_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_opt_depth_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_radinvfrac_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_radf_CL{ reinterpret_cast<R64*>( _mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_wstart{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_wstar3fact_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ebrk{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_wbrk{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_lbrk{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ricl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ghcl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_shcl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_smcl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_gh_a{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_sh_a{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_sm_a{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_ri_a{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_leng{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_wcap{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						 m_pblhp{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_cld{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						 m_ipbl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_kpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						 m_wsedl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) } {

						 constexpr int nArrays{ 82 };
						 for (int i{ 0 }; i != nArrays; ++i) {
							 if ((&this->m_sl)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor WrapCalEddy!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_sl)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }

#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER == 40

#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 24))
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int j{ 0 }; j != this->m_pver; ++j) {
								 this->m_sl[i + this->m_pcols * j] = 0.0;
								 this->m_qt[i + this->m_pcols * j] = 0.0;
								 this->m_ql[i + this->m_pcols * j] = 0.0;
								 this->m_slv[i + this->m_pcols * j] = 0.0;
								 this->m_u[i + this->m_pcols * j] = 0.0;
								 this->m_v[i + this->m_pcols * j] = 0.0;
								 this->m_pi[i + this->m_pcols * j] = 0.0;
								 this->m_z[i + this->m_pcols * j] = 0.0;
								 this->m_zi[i + this->m_pcols * j] = 0.0;
								 this->m_slslope[i + this->m_pcols * j] = 0.0;
								 this->m_qtslope[i + this->m_pcols * j] = 0.0;
								 this->m_chu[i + this->m_pcols * j] = 0.0;
								 this->m_chs[i + this->m_pcols * j] = 0.0;
								 this->m_cmu[i + this->m_pcols * j] = 0.0;
								 this->m_cms[i + this->m_pcols * j] = 0.0;
								 this->m_sfuh[i + this->m_pcols * j] = 0.0;
								 this->m_sfhl[i + this->m_pcols * j] = 0.0;
								 this->m_n2[i + this->m_pcols * j] = 0.0;
								 this->m_s2[i + this->m_pcols * j] = 0.0;
								 this->m_ri[i + this->m_pcols * j] = 0.0;
								 this->m_kvh_in[i + this->m_pcols * j] = 0.0;
								 this->m_kvm_in[i + this->m_pcols * j] = 0.0;
								 this->m_kvh[i + this->m_pcols * j] = 0.0;
								 this->m_kvm[i + this->m_pcols * j] = 0.0;
								 this->m_qrlin[i + this->m_pcols * j] = 0.0;
								 this->m_kvf[i + this->m_pcols * j] = 0.0;
								 this->m_tke[i + this->m_pcols * j] = 0.0;
								 this->m_bprod[i + this->m_pcols * j] = 0.0;
								 this->m_sprod[i + this->m_pcols * j] = 0.0;
								 this->m_turbtype_f[i + this->m_pcols * j] = 0.0;
								 this->m_sm_aw[i + this->m_pcols * j] = 0.0;
								 this->m_kbase_o[i + this->m_pcols * j] = 0.0;
								 this->m_ktop_o[i + this->m_pcols * j] = 0.0;
								 this->m_kbase_mg[i + this->m_pcols * j] = 0.0;
								 this->m_ktop_mg[i + this->m_pcols * j] = 0.0;
								 this->m_kbase_f[i + this->m_pcols * j] = 0.0;
								 this->m_ktop_f[i + this->m_pcols * j] = 0.0;
								 this->m_wet_CL[i + this->m_pcols * j] = 0.0;
								 this->m_web_CL[i + this->m_pcols * j] = 0.0;
								 this->m_jtbu_CL[i + this->m_pcols * j] = 0.0;
								 this->m_jbbu_CL[i + this->m_pcols * j] = 0.0;
								 this->m_evhc_CL[i + this->m_pcols * j] = 0.0;
								 this->m_jt2slv_CL[i + this->m_pcols * j] = 0.0;
								 this->m_n2ht_CL[i + this->m_pcols * j] = 0.0;
								 this->m_n2hb_CL[i + this->m_pcols * j] = 0.0;
								 this->m_lwp_CL[i + this->m_pcols * j] = 0.0;
								 this->m_opt_depth_CL[i + this->m_pcols * j] = 0.0;
								 this->m_radinvfrac_CL[i + this->m_pcols * j] = 0.0;
								 this->m_radf_CL[i + this->m_pcols * j] = 0.0;
								 this->m_wstar3fact_CL[i + this->m_pcols * j] = 0.0;
								 this->m_ebrk[i + this->m_pcols * j] = 0.0;
								 this->m_wbrk[i + this->m_pcols * j] = 0.0;
								 this->m_lbrk[i + this->m_pcols * j] = 0.0;
								 this->m_ricl[i + this->m_pcols * j] = 0.0;
								 this->m_ghcl[i + this->m_pcols * j] = 0.0;
								 this->m_shcl[i + this->m_pcols * j] = 0.0;
								 this->m_smcl[i + this->m_pcols * j] = 0.0;
								 this->m_gh_a[i + this->m_pcols * j] = 0.0;
								 this->m_sh_a[i + this->m_pcols * j] = 0.0;
								 this->m_sm_a[i + this->m_pcols * j] = 0.0;
								 this->m_ri_a[i + this->m_pcols * j] = 0.0;
								 this->m_leng[i + this->m_pcols * j] = 0.0;
								 this->m_wcap[i + this->m_pcols * j] = 0.0;
								 this->m_cld[i +  this->m_pcols * j] = 0.0;
								 this->m_wsedl[i + this->m_pcols * j] = 0.0;

							 }
						 }
						 // Arrays 1D , vectorize only.
#pragma ivdep
#pragma simd
#pragma unroll(4)
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
							 this->m_qflx[i] = 0.0;
							 this->m_shflx[i] = 0.0;
							 this->m_rrho[i] = 0.0;
							 this->m_pblh[i] = 0.0;
							 this->m_ustar[i] = 0.0;
							 this->m_tpert[i] = 0.0;
							 this->m_qpert[i] = 0.0;
							 this->m_minpblh[i] = 0.0;
							 this->m_wpert[i] = 0.0;
							 this->m_tkes[i] = 0.0;
							 this->m_ncvfin_o[i] = 0.0;
							 this->m_ncvfin_mg[i] = 0.0;
							 this->m_ncvfin_f[i] = 0.0;
							 this->m_pblhp[i] = 0.0;
							 this->m_ipbl[i] = 0.0;
							 this->m_kpblh[i] = 0.0;

						 }

						 const int top{this->m_pcols * this->m_pver + 1};
						 // Initialize to 0.0 Arrays 2d last element.
						 this->m_pi[top] = 0.0;
						 this->m_zi[top] = 0.0;
						 this->m_chu[top] = 0.0;
						 this->m_chs[top] = 0.0;
						 this->m_cmu[top] = 0.0;
						 this->m_cms[top] = 0.0;
						 this->m_kvh_in[top] = 0.0;
						 this->m_kvm_in[top] = 0.0;
						 this->m_kvh[top] = 0.0;
						 this->m_kvm[top] = 0.0;
						 this->m_kvf[top] = 0.0;
						 this->m_tke[top] = 0.0;
						 this->m_bprod[top] = 0.0;
						 this->m_sprod[top] = 0.0;
						 this->m_turbtype_f[top] = 0.0;
						 this->m_sm_aw[top] = 0.0;
						 this->m_gh_a[top] = 0.0;
						 this->m_sh_a[top] = 0.0;
						 this->m_sm_a[top] = 0.0;
						 this->m_ri_a[top] = 0.0;
						 this->m_leng[top] = 0.0;
						 this->m_wcap[top] = 0.0;

#else

                         for (int i{ 0 }; i != this->m_pcols; ++i) {
#pragma ivdep
#pragma simd
#pragma unroll(4)
	                          for (int j{ 0 }; j != this->m_pver; ++j) {
		                           this->m_sl[i + this->m_pcols * j] = 0.0;
		                           this->m_qt[i + this->m_pcols * j] = 0.0;
		                           this->m_ql[i + this->m_pcols * j] = 0.0;
		                           this->m_slv[i + this->m_pcols * j] = 0.0;
		                           this->m_u[i + this->m_pcols * j] = 0.0;
		                           this->m_v[i + this->m_pcols * j] = 0.0;
		                           this->m_pi[i + this->m_pcols * j] = 0.0;
		                           this->m_z[i + this->m_pcols * j] = 0.0;
		                           this->m_zi[i + this->m_pcols * j] = 0.0;
		                           this->m_slslope[i + this->m_pcols * j] = 0.0;
		                           this->m_qtslope[i + this->m_pcols * j] = 0.0;
		                           this->m_chu[i + this->m_pcols * j] = 0.0;
		                           this->m_chs[i + this->m_pcols * j] = 0.0;
		                           this->m_cmu[i + this->m_pcols * j] = 0.0;
		                           this->m_cms[i + this->m_pcols * j] = 0.0;
		                           this->m_sfuh[i + this->m_pcols * j] = 0.0;
		                           this->m_sfhl[i + this->m_pcols * j] = 0.0;
		                           this->m_n2[i + this->m_pcols * j] = 0.0;
		                           this->m_s2[i + this->m_pcols * j] = 0.0;
		                           this->m_ri[i + this->m_pcols * j] = 0.0;
		                           this->m_kvh_in[i + this->m_pcols * j] = 0.0;
		                           this->m_kvm_in[i + this->m_pcols * j] = 0.0;
		                           this->m_kvh[i + this->m_pcols * j] = 0.0;
		                           this->m_kvm[i + this->m_pcols * j] = 0.0;
		                           this->m_qrlin[i + this->m_pcols * j] = 0.0;
		                           this->m_kvf[i + this->m_pcols * j] = 0.0;
		                           this->m_tke[i + this->m_pcols * j] = 0.0;
		                           this->m_bprod[i + this->m_pcols * j] = 0.0;
		                           this->m_sprod[i + this->m_pcols * j] = 0.0;
		                           this->m_turbtype_f[i + this->m_pcols * j] = 0.0;
								   this->m_sm_aw[i + this->m_pcols * j] = 0.0;
		                           this->m_kbase_o[i + this->m_pcols * j] = 0.0;
		                           this->m_ktop_o[i + this->m_pcols * j] = 0.0;
		                           this->m_kbase_mg[i + this->m_pcols * j] = 0.0;
		                           this->m_ktop_mg[i + this->m_pcols * j] = 0.0;
		                           this->m_kbase_f[i + this->m_pcols * j] = 0.0;
		                           this->m_ktop_f[i + this->m_pcols * j] = 0.0;
		                            this->m_wet_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_web_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_jtbu_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_jbbu_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_evhc_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_jt2slv_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_n2ht_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_n2hb_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_lwp_CL[i + this->m_pcols * j] = 0.0;
	                      	       this->m_opt_depth_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_radinvfrac_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_radf_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_wstar3fact_CL[i + this->m_pcols * j] = 0.0;
		                           this->m_ebrk[i + this->m_pcols * j] = 0.0;
		                           this->m_wbrk[i + this->m_pcols * j] = 0.0;
		                           this->m_lbrk[i + this->m_pcols * j] = 0.0;
		                           this->m_ricl[i + this->m_pcols * j] = 0.0;
		                           this->m_ghcl[i + this->m_pcols * j] = 0.0;
		                           this->m_shcl[i + this->m_pcols * j] = 0.0;
		                           this->m_smcl[i + this->m_pcols * j] = 0.0;
		                           this->m_gh_a[i + this->m_pcols * j] = 0.0;
		                           this->m_sh_a[i + this->m_pcols * j] = 0.0;
		                           this->m_sm_a[i + this->m_pcols * j] = 0.0;
		                           this->m_ri_a[i + this->m_pcols * j] = 0.0;
		                           this->m_leng[i + this->m_pcols * j] = 0.0;
		                           this->m_wcap[i + this->m_pcols * j] = 0.0;
		                           this->m_cld[i + this->m_pcols * j] = 0.0;
		                           this->m_wsedl[i + this->m_pcols * j] = 0.0;

	}
}

#pragma ivdep
#pragma simd
#pragma unroll(4)
						
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
							 this->m_qflx[i] = 0.0;
							 this->m_shflx[i] = 0.0;
							 this->m_rrho[i] = 0.0;
							 this->m_pblh[i] = 0.0;
							 this->m_ustar[i] = 0.0;
							 this->m_tpert[i] = 0.0;
							 this->m_qpert[i] = 0.0;
							 this->m_minpblh[i] = 0.0;
							 this->m_wpert[i] = 0.0;
							 this->m_tkes[i] = 0.0;
							 this->m_ncvfin_o[i] = 0.0;
							 this->m_ncvfin_mg[i] = 0.0;
							 this->m_ncvfin_f[i] = 0.0;
							 this->m_pblhp[i] = 0.0;
							 this->m_ipbl[i] = 0.0;
							 this->m_kpblh[i] = 0.0;

						 }

						 const int top{ this->m_pcols * this->m_pver + 1 };
						 // Initialize to 0.0 Arrays 2d last element.	
						 this->m_pi[top] = 0.0;
						 this->m_zi[top] = 0.0;
						 this->m_chu[top] = 0.0;
						 this->m_chs[top] = 0.0;
						 this->m_cmu[top] = 0.0;
						 this->m_cms[top] = 0.0;
						 this->m_kvh_in[top] = 0.0;
						 this->m_kvm_in[top] = 0.0;
						 this->m_kvh[top] = 0.0;
						 this->m_kvm[top] = 0.0;
						 this->m_kvf[top] = 0.0;
						 this->m_tke[top] = 0.0;
						 this->m_bprod[top] = 0.0;
						 this->m_sprod[top] = 0.0;
						 this->m_turbtype_f[top] = 0.0;
						 this->m_sm_aw[top] = 0.0;
						 this->m_gh_a[top] = 0.0;
						 this->m_sh_a[top] = 0.0;
						 this->m_sm_a[top] = 0.0;
						 this->m_ri_a[top] = 0.0;
						 this->m_leng[top] = 0.0;
						 this->m_wcap[top] = 0.0;
#endif
						

		 }

					/*
					  @Purpose:
					            Copy Constructor implements deep copy semantics.
		             */
		              WrapCalEddy(_In_ const WrapCalEddy &x)
			                     :
			                    m_pcols{ x.m_pcols },
			                    m_pver{ x.m_pver },
			                    m_ncol{ x.m_ncol },
			                    m_wstarent{ x.m_wstarent },
								m_sl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_qt{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_slv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_u{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_v{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_z{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_qflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_shflx{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_slslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_qtslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_chu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_chs{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_cmu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_cms{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_sfuh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_sfhl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_n2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_s2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ri{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_rrho{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_pblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_ustar{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_kvh_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_kvm_in{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_kvh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_kvm{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_tpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_qpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_qrlin{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_kvf{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_tke{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },

								m_bprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_sprod{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_minpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_wpert{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_tkes{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_turbtype_f{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_sm_aw{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_kbase_o{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ktop_o{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ncvfin_o{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_kbase_mg{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ktop_mg{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ncvfin_mg{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_kbase_f{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ktop_f{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ncvfin_f{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_wet_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_web_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_jtbu_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_jbbu_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_evhc_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_jt2slv_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_n2ht_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_n2hb_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_lwp_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_opt_depth_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_radinvfrac_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_radf_CL{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_wstart{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B) },
			                    m_wstar3fact_CL{ _mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ebrk{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_wbrk{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_lbrk{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ricl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ghcl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_shcl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_smcl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_gh_a{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_sh_a{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_sm_a{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_ri_a{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_leng{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_wcap{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
								m_pblhp{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_cld{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
								m_ipbl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_kpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
								m_wsedl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) } {

						  constexpr int nArrays{ 82 };
						  for (int i{ 0 }; i != nArrays; ++i) {
							  if ((&this->m_sl)[i] == NULL) {
								  std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor WrapCalEddy!!\n";
								  std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								  std::cerr << "***** ERROR-DETAILS ***** \n";
								  std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_sl)[i] << "\n";
								  std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								  std::exit(-1);
							  }
						  }

#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER == 40

#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 24))
						  for (int i{ 0 }; i != this->m_pcols; ++i) {

#pragma ivdep
#pragma simd
#pragma unroll(4)
							  for(int j{ 0 }; j != this->m_pver;   ++j) {
								  this->m_sl[i + this->m_pcols * j] = x.m_sl[i + x.m_pcols * j];
								  this->m_qt[i + this->m_pcols * j] = x.m_qt[i + x.m_pcols * j];
								  this->m_ql[i + this->m_pcols * j] = x.m_ql[i + x.m_pcols * j];
								  this->m_slv[i + this->m_pcols * j] = x.m_slv[i + x.m_pcols * j];
								  this->m_u[i + this->m_pcols * j] = x.m_u[i + x.m_pcols * j];
								  this->m_v[i + this->m_pcols * j] = x.m_v[i + x.m_pcols * j];
								  this->m_pi[i + this->m_pcols * j] = x.m_pi[i + x.m_pcols * j];
								  this->m_z[i + this->m_pcols * j] = x.m_z[i + x.m_pcols * j];
								  this->m_zi[i + this->m_pcols * j] = x.m_zi[i + x.m_pcols * j];
								  this->m_slslope[i + this->m_pcols * j] = x.m_slslope[i + x.m_pcols * j];
								  this->m_qtslope[i + this->m_pcols * j] = x.m_qtslope[i + x.m_pcols * j];
								  this->m_chu[i + this->m_pcols * j] = x.m_chu[i + x.m_pcols * j];
								  this->m_chs[i + this->m_pcols * j] = x.m_chs[i + x.m_pcols * j];
								  this->m_cmu[i + this->m_pcols * j] = x.m_cmu[i + x.m_pcols * j];
								  this->m_cms[i + this->m_pcols * j] = x.m_cms[i + x.m_pcols * j];
								  this->m_sfuh[i + this->m_pcols * j] = x.m_sfuh[i + x.m_pcols * j];
								  this->m_sfhl[i + this->m_pcols * j] = x.m_sfhl[i + x.m_pcols * j];
								  this->m_n2[i + this->m_pcols * j] = x.m_n2[i + x.m_pcols * j];
								  this->m_s2[i + this->m_pcols * j] = x.m_s2[i + x.m_pcols * j];
								  this->m_ri[i + this->m_pcols * j] = x.m_ri[i + x.m_pcols * j];
								  this->m_kvh_in[i + this->m_pcols * j] = x.m_kvh_in[i + x.m_pcols * j];
								  this->m_kvm_in[i + this->m_pcols * j] = x.m_kvm_in[i + x.m_pcols * j];
								  this->m_kvh[i + this->m_pcols * j] = x.m_kvh[i + x.m_pcols * j];
								  this->m_kvm[i + this->m_pcols * j] = x.m_kvm[i + x.m_pcols * j];
								  this->m_qrlin[i + this->m_pcols * j] = x.m_qrlin[i x.m_cols * j];
								  this->m_kvf[i + this->m_pcols * j] = x.m_kvf[i + x.m_pcols * j];
								  this->m_tke[i + this->m_pcols * j] = x.m_tke[i + x.m_pcols * j];
								  this->m_bprod[i + this->m_pcols * j] = x.m_bprod[i + x.m_pcols * j];
								  this->m_sprod[i + this->m_pcols * j] = x.m_sprod[i + x.m_pcols * j];
								  this->m_turbtype_f[i + this->m_pcols * j] = x.m_turbtype_f[i + x.m_pcols * j];
								  this->m_sm_aw[i + this->m_pcols * j] = x.m_sm_aw[i + x.m_pcols * j];
								  this->m_kbase_o[i + this->m_pcols * j] = x.m_kbase_o[i + x.m_pcols * j];
								  this->m_ktop_o[i + this->m_pcols * j] = x.m_ktop_o[i + x.m_pcols * j];
								  this->m_kbase_mg[i + this->m_pcols * j] = x.m_kbase_mg[i + x.m_pcols * j];
								  this->m_ktop_mg[i + this->m_pcols * j] = x.m_ktop_mg[i + x.m_pcols * j];
								  this->m_kbase_f[i + this->m_pcols * j] = x.m_kbase_f[i + x.m_pcols * j];
								  this->m_ktop_f[i + this->m_pcols * j] = x.m_ktop_f[i + x.m_pcols * j];
								  this->m_wet_CL[i + this->m_pcols * j] = x.m_wet_CL[i + x.m_pcols * j];
								  this->m_web_CL[i + this->m_pcols * j] = x.m_web_CL[i + x.m_pcols * j];
								  this->m_jtbu_CL[i + this->m_pcols * j] = x.m_jtbu_CL[i + x.m_pcols * j];
								  this->m_jbbu_CL[i + this->m_pcols * j] = x.m_jbbu_CL[i + x.m_pcols * j];
								  this->m_evhc_CL[i + this->m_pcols * j] = x.m_evhc_CL[i + x.m_pcols * j];
								  this->m_jt2slv_CL[i + this->m_pcols * j] = x.m_jt2slv_CL[i + x.m_pcols * j];
								  this->m_n2ht_CL[i + this->m_pcols * j] = x.m_n2ht_CL[i + x.m_pcols * j];
								  this->m_n2hb_CL[i + this->m_pcols * j] = x.m_n2hb_CL[i + x.m_pcols * j];
								  this->m_lwp_CL[i + this->m_pcols * j] = x.m_lwp_CL[i + x.m_pcols * j];
								  this->m_opt_depth_CL[i + this->m_pcols * j] = x.m_opt_depth_CL[i + x.m_pcols * j];
								  this->m_radinvfrac_CL[i + this->m_pcols * j] = x.m_radinvfrac_CL[i + x.m_pcols * j];
								  this->m_radf_CL[i + this->m_pcols * j] = x.m_radf_CL[i + x.m_pcols * j];
								  this->m_wstar_CL[i + this->m_pcols * j] = x.m_wstar_CL[i + x.m_pcols * j];
								  this->m_wstar3fact_CL[i + this->m_pcols * j] = x.m_wstar3fact_CL[i + x.m_pcols * j];
								  this->m_ebrk[i + this->m_pcols * j] = x.m_ebrk[i + x.m_pcols * j];
								  this->m_wbrk[i + this->m_pcols * j] = x.m_wbrk[i + x.m_pcols * j];
								  this->m_lbrk[i + this->m_pcols * j] = x.m_lbrk[i + x.m_pcols * j];
								  this->m_ricl[i + this->m_pcols * j] = x.m_ricl[i + x.m_pcols * j];
								  this->m_ghcl[i + this->m_pcols * j] = x.m_ghcl[i + x.m_pcols * j];
								  this->m_shcl[i + this->m_pcols * j] = x.m_shcl[i + x.m_pcols * j];
								  this->m_smcl[i + this->m_pcols * j] = x.m_smcl[i + x.m_pcols * j];
								  this->m_gh_a[i + this->m_pcols * j] = x.m_gh_a[i + x.m_pcols * j];
								  this->m_sh_a[i + this->m_pcols * j] = x.m_sh_a[i + x.m_pcols * j];
								  this->m_sm_a[i + this->m_pcols * j] = x.m_sm_a[i + x.m_pcols * j];
								  this->m_ri_a[i + this->m_pcols * j] = x.m_ri_a[i + x.m_pcols * j];
								  this->m_leng[i + this->m_pcols * j] = x.m_leng[i + x.m_pcols * j];
								  this->m_wcap[i + this->m_pcols * j] = x.m_wcap[i + x.m_pcols * j];
								  this->m_cld[i + this->m_pcols * j] = x.m_cld[i + x.m_pcols * j];
								  this->m_wsedl[i + this->m_pcols * j] = x.m_wsedl[i + x.m_pcols * j];
							  }
						  }
						  // Arrays 1D - vectorize only.
#pragma ivdep
#pragma simd
#pragma unroll(4)
						  for (int i{ 0 }; i != this->m_pcols; ++i) {
							  this->m_qflx[i] = x.m_qflx[i];
							  this->m_shflx[i] = x.m_shflx[i];
							  this->m_rrho[i] = x.m_rrho[i];
							  this->m_pblhp[i] = x.m_pblh[i];
							  this->m_ustar[i] = x.m_ustar[i];
							  this->m_tpert[i] = x.m_tpert[i];
							  this->m_qpert[i] = x.m_qpert[i];
							  this->m_minpblh[i] = x.m_minpblh[i];
							  this->m_wpert[i] = x.m_wpert[i];
							  this->m_tkes[i] = x.m_tkes[i];
							  this->m_ncvfin_o[i] = x.m_ncvfin_o[i];
							  this->m_ncvfin_mg[i] = x.m_ncvfin_mg[i];
							  this->m_ncvfin_f[i] = x.m_ncvfin_f[i];
							  this->m_pblhp[i] = x.m_pblhp[i];
							  this->m_ipbl[i] = x.m_ipbl[i];
							  this->m_kpblh[i] = x.m_kpblh[i];

						  }

						  const int top{ this->m_pcols * (this->m_pver + 1) };
						  // Initialize  Arrays 2d last element.
						  this->m_pi[top] = x.m_pi[top];
						  this->m_zi[top] = x.m_zi[top];
						  this->m_chu[top] = x.m_chu[top];
						  this->m_chs[top] = x.m_chs[top];
						  this->m_cmu[top] = x.m_cmu[top];
						  this->m_cms[top] = x.m_cms[top];
						  this->m_kvh_in[top] = x.m_kvh_in[top];
						  this->m_kvm_in[top] = x.m_kvm_in[top];
						  this->m_kvh[top] = x.m_kvh[top];
						  this->m_kvm[top] = x.m_kvm[top];
						  this->m_kvf[top] = x.m_kvf[top];
						  this->m_tke[top] = x.m_tke[top];
						  this->m_bprod[top] = x.m_bprod[top];
						  this->m_sprod[top] = x.m_sprod[top];
						  this->m_turbtype_f[top] = x.m_turbtype_f[top];
						  this->m_sm_aw[top] = x.m_sm_aw[top];
						  this->m_gh_a[top] = x.m_gh_a[top];
						  this->m_sh_a[top] = x.m_sh_a[top];
						  this->m_sm_a[top] = x.m_sm_a[top];
						  this->m_ri_a[top] = x.m_ri_a[top];
						  this->m_leng[top] = x.m_leng[top];
						  this->m_wcap[top] = x.m_wcap[top];

#else

                
                         for (int i{ 0 }; i != this->m_pcols; ++i) {

#pragma ivdep
#pragma simd
#pragma unroll(4)
	                          for (int j{ 0 }; j != this->m_pver; ++j) {
		                           this->m_sl[i + this->m_pcols * j] = x.m_sl[i + x.m_pcols * j];
		                           this->m_qt[i + this->m_pcols * j] = x.m_qt[i + x.m_pcols * j];
		                           this->m_ql[i + this->m_pcols * j] = x.m_ql[i + x.m_pcols * j];
		                           this->m_slv[i + this->m_pcols * j] = x.m_slv[i + x.m_pcols * j];
		                           this->m_u[i + this->m_pcols * j] = x.m_u[i + x.m_pcols * j];
		                           this->m_v[i + this->m_pcols * j] = x.m_v[i + x.m_pcols * j];
		                           this->m_pi[i + this->m_pcols * j] = x.m_pi[i + x.m_pcols * j];
		                           this->m_z[i + this->m_pcols * j] = x.m_z[i + x.m_pcols * j];
		                           this->m_zi[i + this->m_pcols * j] = x.m_zi[i + x.m_pcols * j];
		                           this->m_slslope[i + this->m_pcols * j] = x.m_slslope[i + x.m_pcols * j];
		                           this->m_qtslope[i + this->m_pcols * j] = x.m_qtslope[i + x.m_pcols * j];
		                           this->m_chu[i + this->m_pcols * j] = x.m_chu[i + x.m_pcols * j];
		                           this->m_chs[i + this->m_pcols * j] = x.m_chs[i + x.m_pcols * j];
		                           this->m_cmu[i + this->m_pcols * j] = x.m_cmu[i + x.m_pcols * j];
		                           this->m_cms[i + this->m_pcols * j] = x.m_cms[i + x.m_pcols * j];
		                           this->m_sfuh[i + this->m_pcols * j] = x.m_sfuh[i + x.m_pcols * j];
		                           this->m_sfhl[i + this->m_pcols * j] = x.m_sfhl[i + x.m_pcols * j];
		                           this->m_n2[i + this->m_pcols * j] = x.m_n2[i + x.m_pcols * j];
		                           this->m_s2[i + this->m_pcols * j] = x.m_s2[i + x.m_pcols * j];
		                           this->m_ri[i + this->m_pcols * j] = x.m_ri[i + x.m_pcols * j];
		                           this->m_kvh_in[i + this->m_pcols * j] = x.m_kvh_in[i + x.m_pcols * j];
		                           this->m_kvm_in[i + this->m_pcols * j] = x.m_kvm_in[i + x.m_pcols * j];
		                           this->m_kvh[i + this->m_pcols * j] = x.m_kvh[i + x.m_pcols * j];
		                           this->m_kvm[i + this->m_pcols * j] = x.m_kvm[i + x.m_pcols * j];
		                           this->m_qrlin[i + this->m_pcols * j] = x.m_qrlin[i x.m_cols * j];
		                           this->m_kvf[i + this->m_pcols * j] = x.m_kvf[i + x.m_pcols * j];
		                           this->m_tke[i + this->m_pcols * j] = x.m_tke[i + x.m_pcols * j];
		                           this->m_bprod[i + this->m_pcols * j] = x.m_bprod[i + x.m_pcols * j];
		                           this->m_sprod[i + this->m_pcols * j] = x.m_sprod[i + x.m_pcols * j];
		                           this->m_turbtype_f[i + this->m_pcols * j] = x.m_turbtype_f[i + x.m_pcols * j];
		                           this->m_sm_aw[i + this->m_pcols * j] = x.m_sm_aw[i + x.m_pcols * j];
		                           this->m_kbase_o[i + this->m_pcols * j] = x.m_kbase_o[i + x.m_pcols * j];
		                           this->m_ktop_o[i + this->m_pcols * j] = x.m_ktop_o[i + x.m_pcols * j];
		                           this->m_kbase_mg[i + this->m_pcols * j] = x.m_kbase_mg[i + x.m_pcols * j];
		                           this->m_ktop_mg[i + this->m_pcols * j] = x.m_ktop_mg[i + x.m_pcols * j];
		                           this->m_kbase_f[i + this->m_pcols * j] = x.m_kbase_f[i + x.m_pcols * j];
		                           this->m_ktop_f[i + this->m_pcols * j] = x.m_ktop_f[i + x.m_pcols * j];
		                           this->m_wet_CL[i + this->m_pcols * j] = x.m_wet_CL[i + x.m_pcols * j];
		                           this->m_web_CL[i + this->m_pcols * j] = x.m_web_CL[i + x.m_pcols * j];
		                           this->m_jtbu_CL[i + this->m_pcols * j] = x.m_jtbu_CL[i + x.m_pcols * j];
		                           this->m_jbbu_CL[i + this->m_pcols * j] = x.m_jbbu_CL[i + x.m_pcols * j];
		                           this->m_evhc_CL[i + this->m_pcols * j] = x.m_evhc_CL[i + x.m_pcols * j];
		                           this->m_jt2slv_CL[i + this->m_pcols * j] = x.m_jt2slv_CL[i + x.m_pcols * j];
		                           this->m_n2ht_CL[i + this->m_pcols * j] = x.m_n2ht_CL[i + x.m_pcols * j];
		                           this->m_n2hb_CL[i + this->m_pcols * j] = x.m_n2hb_CL[i + x.m_pcols * j];
		                           this->m_lwp_CL[i + this->m_pcols * j] = x.m_lwp_CL[i + x.m_pcols * j];
		                           this->m_opt_depth_CL[i + this->m_pcols * j] = x.m_opt_depth_CL[i + x.m_pcols * j];
		                           this->m_radinvfrac_CL[i + this->m_pcols * j] = x.m_radinvfrac_CL[i + x.m_pcols * j];
		                           this->m_radf_CL[i + this->m_pcols * j] = x.m_radf_CL[i + x.m_pcols * j];
		                           this->m_wstar_CL[i + this->m_pcols * j] = x.m_wstar_CL[i + x.m_pcols * j];
		                           this->m_wstar3fact_CL[i + this->m_pcols * j] = x.m_wstar3fact_CL[i + x.m_pcols * j];
		                           this->m_ebrk[i + this->m_pcols * j] = x.m_ebrk[i + x.m_pcols * j];
		                           this->m_wbrk[i + this->m_pcols * j] = x.m_wbrk[i + x.m_pcols * j];
		                           this->m_lbrk[i + this->m_pcols * j] = x.m_lbrk[i + x.m_pcols * j];
		                           this->m_ricl[i + this->m_pcols * j] = x.m_ricl[i + x.m_pcols * j];
		                           this->m_ghcl[i + this->m_pcols * j] = x.m_ghcl[i + x.m_pcols * j];
		                           this->m_shcl[i + this->m_pcols * j] = x.m_shcl[i + x.m_pcols * j];
		                           this->m_smcl[i + this->m_pcols * j] = x.m_smcl[i + x.m_pcols * j];
		                           this->m_gh_a[i + this->m_pcols * j] = x.m_gh_a[i + x.m_pcols * j];
		                           this->m_sh_a[i + this->m_pcols * j] = x.m_sh_a[i + x.m_pcols * j];
		                           this->m_sm_a[i + this->m_pcols * j] = x.m_sm_a[i + x.m_pcols * j];
		                           this->m_ri_a[i + this->m_pcols * j] = x.m_ri_a[i + x.m_pcols * j];
		                           this->m_leng[i + this->m_pcols * j] = x.m_leng[i + x.m_pcols * j];
		                           this->m_wcap[i + this->m_pcols * j] = x.m_wcap[i + x.m_pcols * j];
		                           this->m_cld[i + this->m_pcols * j] = x.m_cld[i + x.m_pcols * j];
		                           this->m_wsedl[i + this->m_pcols * j] = x.m_cld[i + x.m_pcols * j];
	}
}
							// Copy arrays 1D - vectorize only.
#pragma ivdep
#pragma simd
#pragma unroll(4)
                                   
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
							 this->m_qflx[i] = x.m_qflx[i];
							 this->m_shflx[i] = x.m_shflx[i];
							 this->m_rrho[i] = x.m_rrho[i];
							 this->m_pblhp[i] = x.m_pblh[i];
							 this->m_ustar[i] = x.m_ustar[i];
							 this->m_tpert[i] = x.m_tpert[i];
							 this->m_qpert[i] = x.m_qpert[i];
							 this->m_minpblh[i] = x.m_minpblh[i];
							 this->m_wpert[i] = x.m_wpert[i];
							 this->m_tkes[i] = x.m_tkes[i];
							 this->m_ncvfin_o[i] = x.m_ncvfin_o[i];
							 this->m_ncvfin_mg[i] = x.m_ncvfin_mg[i];
							 this->m_ncvfin_f[i] = x.m_ncvfin_f[i];
							 this->m_pblhp[i] = x.m_pblhp[i];
							 this->m_ipbl[i] = x.m_ipbl[i];
							 this->m_kpblh[i] = x.m_kpblh[i];

						 }

						 const int top{ this->m_pcols * this->m_pver + 1 };
						 // Initialize  Arrays 2d last element.
						 this->m_pi[top] = x.m_pi[top];
						 this->m_zi[top] = x.m_zi[top];
						 this->m_chu[top] = x.m_chu[top];
						 this->m_chs[top] = x.m_chs[top];
						 this->m_cmu[top] = x.m_cmu[top];
						 this->m_cms[top] = x.m_cms[top];
						 this->m_kvh_in[top] = x.m_kvh_in[top];
						 this->m_kvm_in[top] = x.m_kvm_in[top];
						 this->m_kvh[top] = x.m_kvh[top];
						 this->m_kvm[top] = x.m_kvm[top];
						 this->m_kvf[top] = x.m_kvf[top];
						 this->m_tke[top] = x.m_tke[top];
						 this->m_bprod[top] = x.m_bprod[top];
						 this->m_sprod[top] = x.m_sprod[top];
						 this->m_turbtype_f[top] = x.m_turbtype_f[top];
						 this->m_sm_aw[top] = x.m_sm_aw[top];
						 this->m_gh_a[top] = x.m_gh_a[top];
						 this->m_sh_a[top] = x.m_sh_a[top];
						 this->m_sm_a[top] = x.m_sm_a[top];
						 this->m_ri_a[top] = x.m_ri_a[top];
						 this->m_leng[top] = x.m_leng[top];
						 this->m_wcap[top] = x.m_wcap[top];
#endif




		 }
				 
				 /*
				   @Purpose:
							 Move Constructor implements shallow copy semantics.
				 */
		               WrapCalEddy(_In_ WrapCalEddy &&x)
			                      :
			              m_pcols{ x.m_pcols },
			              m_pver{ x.m_pver },
			              m_ncol{ x.m_ncol },
			              m_wstarent{ x.m_wstarent },
			              m_sl{ x.m_sl },
			              m_qt{ x.m_qt },
			              m_ql{ x.m_ql },
			              m_slv{ x.m_slv },
			              m_u{ x.m_u },
			              m_v{ x.m_v },
			              m_pi{ x.m_pi },
			              m_z{ x.m_z },
			              m_zi{ x.m_zi },
			              m_qflx{ x.m_qflx },
			              m_shflx{ x.m_shflx },
			              m_slslope{ x.m_slslope },
			              m_qtslope{ x.m_qtslope },
			              m_chu{ x.m_chu },
			              m_chs{ x.m_chs },
			              m_cmu{ x.m_cmu },
			              m_cms{ x.m_cms },
			              m_sfuh{ x.m_sfuh },
			              m_sfhl{ x.m_sfhl },
			              m_n2{ x.m_n2 },
			              m_s2{ x.m_s2 },
			              m_ri{ x.m_ri },
			              m_rho{ x.m_rho },
			              m_pblh{ x.m_pblh },
			              m_ustar{ x.m_ustar },
			              m_kvh_in{ x.m_kvh_in },
			              m_kvm_in{ x.m_kvm_in },
			              m_kvh{ x.m_kvh },
			              m_kvm{ x.m_kvm },
			              m_tpert{ x.m_tpert },
			              m_qpert{ x.m_qpert },
			              m_qrlin{ x.m_qrlin },
			              m_kvf{ x.m_kvf },
			              m_tke{ x.m_tke },
			              m_bprod{ x.m_bprod },
			              m_sprod{ x.m_sprod },
			              m_minpblh{ x.m_minpblh },
			              m_wpert{ x.m_wpert },
			              m_tkes{ x.m_tkes },
			              m_turbtype_f{ x.m_turbtype_f },
			              m_sm_aw{ x.m_sm_aw },
			              m_kbase_o{ x.m_kbase_o },
			              m_ktop_o{ x.m_ktop_o },
			              m_ncvfin_o{ x.m_ncvfin_o },
			              m_kbase_mg{ x.m_kbase_mg },
			              m_ktop_mg{ x.m_ktop_mg },
			              m_ncvfin_mg{ x.m_ncvfin_mg },
			              m_kbase_f{ x.m_kbase_f },
			              m_ktop_f{ x.m_ktop_f },
			              m_ncvfin_f{ x.m_ncvfin_f },
			              m_wet_CL{ x.m_wet_CL },
			              m_web_CL{ x.m_web_CL },
			              m_jtbu_CL{ x.m_jtbu_CL },
			              m_jbbu_CL{ x.m_jbbu_CL },
			              m_evhc_CL{ x.m_evhc_CL },
			              m_jt2slv_CL{ x.m_jt2slv_CL },
			              m_n2ht_CL{ x.m_n2ht_CL },
			              m_n2hb_CL{ x.m_n2hb_CL },
			              m_lwp_CL{ x.m_lwp_CL },
			              m_opt_depth_CL{ x.m_opt_depth_CL },
			              m_radinvfrac_CL{ x.m_radinvfrac_CL },
			              m_radf_CL{ x.m_radf_CL },
			              m_wstar_CL{ x.m_wstar_CL },
			              m_wstar3fact_CL{ x.m_wstar3fact_CL },
			              m_ebrk{ x.m_ebrk },
			              m_wbrk{ x.m_wbrk },
			              m_lbrk{ x.m_lbrk },
			              m_ricl{ x.m_ricl },
			              m_ghcl{ x.m_ghcl },
			              m_shcl{ x.m_shcl },
			              m_smcl{ x.m_smcl },
			              m_gh_a{ x.m_gh_a },
			              m_sh_a{ x.m_sh_a },
			              m_sm_a{ x.m_sm_a },
			              m_ri_a{ x.m_ri_a },
			              m_leng{ x.m_leng },
			              m_wcap{ x.m_wcap },
			              m_pblhp{ x.m_pblhp },
			              m_cld{ x.m_cld },
			              m_ipbl{ x.m_ipbl },
			              m_kpblh{ x.m_kpblh },
			              m_wsedl{ x.m_wsedl } {

						  x.m_pcols = 0;
						  x.m_pver = 0;
						  x.m_ncol = 0;
						  x.m_sl = nullptr;
						  x.m_qt = nullptr;
						  x.m_ql = nullptr;
						  x.m_slv = nullptr;
						  x.m_u = nullptr;
						  x.m_v = nullptr;
						  x.m_pi = nullptr;
						  x.m_z = nullptr;
						  x.m_zi = nullptr;
						  x.m_qflx = nullptr;
						  x.m_shflx = nullptr;
						  x.m_n2 = nullptr;
						  x.m_s2 = nullptr;
						  x.m_slslope = nullptr;
						  x.m_qtslope = nullptr;
						  x.m_chu = nullptr;
						  x.m_chs = nullptr;
						  x.m_cmu = nullptr;
						  x.m_cms = nullptr;
						  x.m_sfuh = nullptr;
						  x.m_sfhl = nullptr;
						  x.m_n2 = nullptr;
						  x.m_s2 = nullptr;
						  x.m_ri = nullptr;
						  x.m_rrho = nullptr;
						  x.m_pblh = nullptr;
						  x.m_ustar = nullptr;
						  x.m_kvh_in = nullptr;
						  x.m_kvm_in = nullptr;
						  x.m_kvh = nullptr;
						  x.m_kvm = nullptr;
						  x.m_tpert = nullptr;
						  x.m_qpert = nullptr;
						  x.m_qrlin = nullptr;
						  x.m_kvf = nullptr;
						  x.m_tke = nullptr;
						  x.m_bprod = nullptr;
						  x.m_sprod = nullptr;
						  x.m_minpblh = nullptr;
						  x.m_wpert = nullptr;
						  x.m_tkes = nullptr;
						  x.m_turbtype_f = nullptr;
						  x.m_sm_aw = nullptr;
						  x.m_kbase_o = nullptr;
						  x.m_ktop_o = nullptr;
						  x.m_ncvfin_o = nullptr;
						  x.m_kbase_mg = nullptr;
						  x.m_ktop_mg = nullptr;
						  x.m_ncvfin_mg = nullptr;
						  x.m_kbase_f = nullptr;
						  x.m_ktop_f = nullptr;
						  x.m_ncvfin_f = nullptr;
						  x.m_wet_CL = nullptr;
						  x.m_web_CL = nullptr;
						  x.m_jtbu_CL = nullptr;
						  x.m_jbbu_CL = nullptr;
						  x.m_evhc_CL = nullptr;
						  x.m_jt2slv_CL = nullptr;
						  x.m_n2ht_CL = nullptr;
						  x.m_n2hb_CL = nullptr;
						  x.m_lwp_CL = nullptr;
						  x.m_opt_depth_CL = nullptr;
						  x.m_radinvfrac_CL = nullptr;
						  x.m_radf_CL = nullptr;
						  x.m_wstar_CL = nullptr;
						  x.m_wstar3fact_CL = nullptr;
						  x.m_ebrk = nullptr;
						  x.m_wbrk = nullptr;
						  x.m_lbrk = nullptr;
						  x.m_ricl = nullptr;
						  x.m_ghcl = nullptr;
						  x.m_shcl = nullptr;
						  x.m_smcl = nullptr;
						  x.m_hg_a = nullptr;
						  x.m_sh_a = nullptr;
						  x.m_sm_a = nullptr;
						  x.m_ri_a = nullptr;
						  x.m_leng = nullptr;
						  x.m_wcap = nullptr;
						  x.m_pblhp = nullptr;
						  x.m_cld = nullptr;
						  x.m_ipbl = nullptr;
						  x.m_kpblh = nullptr;
						  x.m_wsedl = nullptr;

	 }


						  /*
							@Purpose:
							          Class Destructor 
						  */
						  ~WrapCalEddy() {
						  
							  
							  for (int i{ 0 }; i != this->m_nArrays; ++i) {
								  if ((&this->m_sl)[i]) {
									  _mm_free((&this->m_sl)[i]);
									  (&this->m_sl)[i] = nullptr;
								  }
							  }
							  this->m_pcols = 0;
							  this->m_pver = 0;
							  this->m_ncol = 0;
						  }

						  /*
						    @Purpose:
									  Copy-assignment Operator implements deep copy semantics.
						  */
						  WrapCalEddy & operator=(_In_ const WrapCalEddy &x) {
							  if (this == &x) return (*this);

							  this->m_pcols = x.m_pcols;
							  this->m_pver = x.m_pver;
							  this->m_ncol = x.m_ncol;
							  this->m_wstarent = x.m_wstarent;

							  // Begin memory allocation block.
							  // Temporary storage for 16 arrays 1D.
							  R64 *tptrs1D[16] = {};
							  for (int i{ 0 }; i != this->m_ptrs1D; ++i) {
								  tptrs1D[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)),align32B));
							  }
							  // Check for allocation errors.
							  for (int i{ 0 }; i != this->m_ptrs1D; ++i) {
								  if (tptrs1D[i] == NULL) {
									  std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator WrapCalEddy!!\n";
									  std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
									  std::cerr << "***** ERROR-DETAILS ***** \n";
									  std::cerr << "Checking allocation of temporary arrays 1D\.n";
									  std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tptrs1D[i] << "\n";
									  std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
									  std::exit(-1);
								  }
							  }
							  //  Storage for 22 temporary arrays 2D (pver + 1).
							  R64 *tptrs2D1[22] = {};
							  for (int i{ 0 }; i != this->m_ptrs2D1; ++i) {
								  tptrs2D1[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)),align32B));
							  }
							  // Check for allocation errors.
							  for (int i{ 0 }; i != this->m_ptrs2D1; ++i) {
								  if (tptrs2D1[i] == NULL) {
									  std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator WrapCalEddy!!\n";
									  std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
									  std::cerr << "***** ERROR-DETAILS ***** \n";
									  std::cerr << "Checking allocation of temporary arrays 2D, where dimension pver = pver + 1.\n";
									  std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tptrs2D1[i] << "\n";
									  std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
									  std::exit(-1);
								  }
							  }
							  //  Storage for 44 temporary arrays 2D (pver).
							  R64 *tptrs2D[44] = {};
							  for (int i{ 0 }; i != this->m_ptrs2D; ++i) {
								  tptrs2D[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)),align32B));
							  }
							  // Check for allocation errors.
							  for (int i{ 0 }; i != this->m_ptrs2D; ++i) {
								  if (tptrs2D[i] == NULL) {
									  std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator WrapCalEddy!!\n";
									  std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
									  std::cerr << "***** ERROR-DETAILS ***** \n";
									  std::cerr << "Checking allocation of temporary arrays 2D, where dimension pver = pver.\n";
									  std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tptrs2D1[i] << "\n";
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
#pragma ivdep
#pragma simd
#pragma unroll(4)
								   for(int j{ 0 }; j != this->m_pver;  ++j ) {
										
									   tptrs2D[0][i + this->m_pcols * j] = x.m_sl[i + x.m_pcols * j];
									   tptrs2D[1][i + this->m_pcols * j] = x.m_qt[i + x.m_pcols * j];
									   tptrs2D[2][i + this->m_pcols * j] = x.m_ql[i + x.m_pcols * j];
									   tptrs2D[3][i + this->m_pcols * j] = x.m_slv[i + x.m_pcols * j];
									   tptrs2D[4][i + this->m_pcols * j] = x.m_u[i + x.m_pcols * j];
									   tptrs2D[5][i + this->m_pcols * j] = x.m_v[i + x.m_pcols * j];
									   tptrs2D1[0][i + this->m_pcols * j] = x.m_pi[i + x.m_pcols * j];
									   tptrs2D[6][i + this->m_pcols * j] = x.m_z[i + x.m_pcols * j];
									   tptrs2D1[1][i + this->m_pcols * j] = x.m_zi[i + x.m_pcols * j];
									   tptrs2D[7][i + this->m_pcols * j] = x.m_slslope[i + x.m_pcols * j];
									   tptrs2D[8][i + this->m_pcols * j] = x.m_qtslope[i + x.m_pcols * j];
									   tptrs2D1[2][i + this->m_pcols * j] = x.m_chu[i + x.m_pcols * j];
									   tptrs2D1[3][i + this->m_pcols * j] = x.m_chs[i + x.m_pcols * j];
									   tptrs2D1[4][i + this->m_pcols * j] = x.m_cmu[i + x.m_pcols * j];
									   tptrs2D1[5][i + this->m_pcols * j] = x.m_cms[i + x.m_pcols * j];
									   tptrs2D[9][i + this->m_pcols * j] = x.m_sfuh[i + x.m_pcols* j];
									   tptrs2D[10][i + this->m_pcols * j] = x.m_sfhl[i + x.m_pcols * j];
									   tptrs2D[11][i + this->m_pcols * j] = x.m_n2[i + x.m_pcols * j];
									   tptrs2D[12][i + this->m_pcols * j] = x.m_s2[i + x.m_pcols * j];
									   tptrs2D[13][i + this->m_pcols * j] = x.m_ri[i + x.m_pcols * j];
									   tptrs2D1[6][i + this->m_pcols * j] = x.m_kvh_in[i + x.m_pcols * j];
									   tptrs2D1[7][i + this->m_pcols * j] = x.m_kvm_in[i + x.m_pcols * j];
									   tptrs2D1[8][i + this->m_pcols * j] = x.m_kvh[i + x.m_pcols * j];
									   tptrs2D1[9][i + this->m_pcols * j] = x.m_kvm[i + x.m_pcols * j];
									   tptrs2D[14][i + this->m_pcols * j] = x.m_qrlin[i + x.m_pcols * j];
									   tptrs2D1[10][i + this->m_pcols * j] = x.m_kvf[i + x.m_pcols * j];
									   tptrs2D1[11][i + this->m_pcols * j] = x.m_tke[i + x.m_pcols * j];
									   tptrs2D1[12][i + this->m_pcols * j] = x.m_bprod[i + x.m_pcols * j];
									   tptrs2D1[13][i + this->m_pcols * j] = x.m_sprod[i + x.m_pcols * j];
									   tptrs2D1[14][i + this->m_pcols * j] = x.m_turbtype_f[i + x.m_pcols * j];
									   tptrs2D1[15][i + this->m_pcols * j] = x.m_sm_aw[i + x.m_pcols * j];
									   tptrs2D[15][i + this->m_pcols * j] = x.m_kbase_o[i + x.m_pcols * j];
									   tptrs2D[16][i + this->m_pcols * j] = x.m_ktop_o[i + x.m_pcols * j];
									   tptrs2D[17][i + this->m_pcols * j] = x.m_kbase_mg[i + x.m_pcols * j];
									   tptrs2D[18][i + this->m_pcols * j] = x.m_ktop_mg[i + x.m_pcols * j];
									   tptrs2D[19][i + this->m_pcols * j] = x.m_kbase_f[i + x.m_pcols * j];
									   tptrs2D[20][i + this->m_pcols * j] = x.m_ktop_f[i + x.m_pcols * j];
									   tptrs2D[21][i + this->m_pcols * j] = x.m_wet_CL[i + x.m_pcols * j];
									   tptrs2D[22][i + this->m_pcols * j] = x.m_web_CL[i + x.m_pcols * j];
									   tptrs2D[23][i + this->m_pcols * j] = x.m_jtbu_CL[i + x.m_pcols * j];
									   tptrs2D[24][i + this->m_pcols * j] = x.m_jbbu_CL[i + x.m_pcols * j];
									   tptrs2D[25][i + this->m_pcols * j] = x.m_evhc_CL[i + x.m_pcols * j];
									   tptrs2D[26][i + this->m_pcols * j] = x.m_jt2slv_CL[i + x.m_pcols * j];
									   tptrs2D[27][i + this->m_pcols * j] = x.m_n2ht_CL[i + x.m_pcols * j];
									   tptrs2D[28][i + this->m_pcols * j] = x.m_n2hb_CL[i + x.m_pcols * j];
									   tptrs2D[29][i + this->m_pcols * j] = x.m_lwp_CL[i + x.m_pcols * j];
									   tptrs2D[30][i + this->m_pcols * j] = x.m_opt_depth_CL[i + x.m_pcols * j];
									   tptrs2D[31][i + this->m_pcols * j] = x.m_radinvfrac_CL[i + x.m_pcols * j];
									   tptrs2D[32][i + this->m_pcols * j] = x.m_radf_CL[i + x.m_pcols * j];
									   tptrs2D[33][i + this->m_pcols * j] = x.m_wstar_CL[i + x.m_pcols * j];
									   tptrs2D[34][i + this->m_pcols * j] = x.m_wstar3fact_CL[i + x.m_pcols * j];
									   tptrs2D[35][i + this->m_pcols * j] = x.m_ebrk[i + x.m_pcols * j];
									   tptrs2D[36][i + this->m_pcols * j] = x.m_wbrk[i + x.m_pcols * j];
									   tptrs2D[37][i + this->m_pcols * j] = x.m_lbrk[i + x.m_pcols * j];
									   tptrs2D[38][i + this->m_pcols * j] = x.m_ricl[i + x.m_pcols * j];
									   tptrs2D[39][i + this->m_pcols * j] = x.m_ghcl[i + x.m_pcols * j];
									   tptrs2D[40][i + this->m_pcols * j] = x.m_shcl[i + x.m_pcols * j];
									   tptrs2D[41][i + this->m_pcols * j] = x.m_smcl[i + x.m_pcols * j];
									   tptrs2D1[16][i + this->m_pcols * j] = x.m_gh_a[i + x.m_pcols * j];
									   tptrs2D1[17][i + this->m_pcols * j] = x.m_sh_a[i + x.m_pcols * j];
									   tptrs2D1[18][i + this->m_pcols * j] = x.m_sm_a[i + x.m_pcols * j];
									   tptrs2D1[19][i + this->m_pcols * j] = x.m_ri_a[i + x.m_pcols * j];
									   tptrs2D1[20][i + this->m_pcols * j] = x.m_leng[i + x.m_pcols * j];
									   tptrs2D1[21][i + this->m_pcols * j] = x.m_wcap[i + x.m_pcols * j];
									   tptrs2D[42][i + this->m_pcols * j] = x.m_cld[i + x.m_pcols * j];
									   tptrs2D[43][i + this->m_pcols * j] = x.m_wsedl[i + x.m_pcols * j];
                                   }
							  }

							  // Begin arrays 1D copy loop - vectorize only.
#pragma ivdep
#pragma simd
#pragma unroll(4)                 
							  for (int i{ 0 }; i != this->m_pcols; ++i) {
								  tptrs1D[0][i] = x.m_qflx[i];
								  tptrs1D[1][i] = x.m_shflx[i];
								  tptrs1D[2][i] = x.m_rrho[i];
								  tptrs1D[3][i] = x.m_pblh[i];
								  tptrs1D[4][i] = x.m_ustar[i];
								  tptrs1D[5][i] = x.m_tpert[i];
								  tptrs1D[6][i] = x.m_qpert[i];
								  tptrs1D[7][i] = x.m_minpblh[i];
								  tptrs1D[8][i] = x.m_wpert[i];
								  tptrs1D[9][i] = x.m_tkes[i];
								  tptrs1D[10][i] = x.m_ncvfin_o[i];
								  tptrs1D[11][i] = x.m_ncvfin_mg[i];
								  tptrs1D[12][i] = x.m_ncvfin_f[i];
								  tptrs1D[13][i] = x.m_pblhp[i];
								  tptrs1D[14][i] = x.m_ipbl[i];
								  tptrs1D[15][i] = x.m_kpblh[i];
							  }

							  // Copy top element for arrays 2D , where pver = pver + 1.
							  const int top = this->m_pcols * this->m_pver + 1;
							  tptrs2D1[0][top] = x.m_pi[top];
							  tptrs2D1[1][top] = x.m_zi[top];
							  tptrs2D1[2][top] = x.m_chu[top];
							  tptrs2D1[3][top] = x.m_chs[top];
							  tptrs2D1[4][top] = x.m_cmu[top];
							  tptrs2D1[5][top] = x.m_cms[top];
							  tptrs2D1[6][top] = x.m_kvh_in[top];
							  tptrs2D1[7][top] = x.m_kvm_in[top];
							  tptrs2D1[8][top] = x.m_kvh[top];
							  tptrs2D1[9][top] = x.m_kvm[top];
							  tptrs2D1[10][top] = x.m_kvf[top];
							  tptrs2D1[11][top] = x.m_tke[top];
							  tptrs2D1[12][top] = x.m_bprod[top];
							  tptrs2D1[13][top] = x.m_sprod[top];
							  tptrs2D1[14][top] = x.m_turbtype_f[top];
							  tptrs2D1[15][top] = x.m_sm_aw[top];
							  tptrs2D1[16][top] = x.m_gh_a[top];
							  tptrs2D1[17][top] = x.m_sh_a[top];
							  tptrs2D1[18][top] = x.m_sm_a[top];
							  tptrs2D1[19][top] = x.m_ri_a[top];
							  tptrs2D1[20][top] = x.m_leng[top];
							  tptrs2D1[21][top] = x.m_wcap[top];

							  // Deallocate current context of *this.
							  for (int i{ 0 }; i != this->m_nArrays; ++i) {
								  if ((&this->m_sl)[i]) {
									  _mm_free((&this->m_sl)[i]);
								  }
							  }

							  // Copy temporary state to *this.
							  this->m_sl = tptrs2D[0];
							  this->m_qt = tptrs2D[1];
							  this->m_ql = tptrs2D[2];
							  this->m_slv = tptrs2D[3];
							  this->m_u = tptrs2D[4];
							  this->m_v = tptrs2D[5];
							  this->m_pi = tptrs2D1[0];
							  this->m_z = tptrs2D[6];
							  this->m_zi = tptrs2D1[1];
							  this->m_qflx = tptrs1D[0];
							  this->m_shflx = tptrs1D[1];
							  this->m_slslope = tptrs2D[7];
							  this->m_qtslope = tptrs2D[8];
							  this->m_chu = tptrs2D1[2];
							  this->m_chs = tptrs2D1[3];
							  this->m_cmu = tptrs2D1[4];
							  this->m_cms = tptrs2D1[5];
							  this->m_sfuh = tptrs2D[9];
							  this->m_sfhl = tptrs2D[10];
							  this->m_n2 = tptrs2D[11];
							  this->m_s2 = tptrs2D[12];
							  this->m_ri = tptrs2D[13];
							  this->m_rrho = tptrs1D[2];
							  this->m_pblh = tptrs1D[3];
							  this->m_ustar = tptrs1D[4];
							  this->m_kvh_in = tptrs2D1[6];
							  this->m_kvm_in = tptrs2D1[7];
							  this->m_kvh = tptrs2D1[8];
							  this->m_kvm = tptrs2D1[9];
							  this->m_tpert = tptrs1D[5];
							  this->m_qpert = tptrs1D[6];
							  this->m_qrlin = tptrs2D[14];
							  this->m_kvf = tptrs2D1[10];
							  this->m_tke = tptrs2D1[11];
							  this->m_bprod = tptrs2D1[12];
							  this->m_sprod = tptrs2D1[13];
							  this->m_minpblh = tptrs1D[7];
							  this->m_wpert = tptrs1D[8];
							  this->m_tkes = tptrs1D[9];
							  this->m_turbtype_f = tptrs2D1[14];
							  this->m_sm_aw = tptrs2D1[15];
							  this->m_kbase_o = tptrs2D[15];
							  this->m_ktop_o = tptrs2D[16];
							  this->m_ncvfin_o = tptrs1D[10];
							  this->m_kbase_mg = tptrs2D[17];
							  this->m_ktop_mg = tptrs2D[18];
							  this->m_ncvfin_mg = tptrs1D[11];
							  this->m_kbase_f = tptrs2D[19];
							  this->m_ktop_f = tptrs2D[20];
							  this->m_ncvfin_f = tptrs1D[12];
							  this->m_wet_CL = tptrs2D[21];
							  this->m_web_CL = tptrs2D[22];
							  this->m_jtbu_CL = tptrs2D[23];
							  this->m_jbbu_CL = tptrs2D[24];
							  this->m_evhc_CL = tptrs2D[25];
							  this->m_jt2slv_CL = tptrs2D[26];
							  this->m_n2ht_CL = tptrs2D[27];
							  this->m_n2hb_CL = tptrs2D[28];
							  this->m_lwp_CL = tptrs2D[29];
							  this->m_opt_depth_CL = tptrs2D[30];
							  this->m_radinvfrac_CL = tptrs2D[31];
							  this->m_radf_CL = tptrs2D[32];
							  this->m_wstar_CL = tptrs2D[33];
							  this->m_wstar3fact_CL = tptrs2D[34];
							  this->m_ebrk = tptrs2D[35];
							  this->m_wbrk = tptrs2D[36];
							  this->m_lbrk = tptrs2D[37];
							  this->m_ricl = tptrs2D[38];
							  this->m_ghcl = tptrs2D[39];
							  this->m_shcl = tptrs2D[40];
							  this->m_smcl = tptrs2D[41];
							  this->m_gh_a = tptrs2D1[16];
							  this->m_sh_a = tptrs2D1[17];
							  this->m_sm_a = tptrs2D1[18];
							  this->m_ri_a = tptrs2D1[19];
							  this->m_leng = tptrs2D1[20];
							  this->m_wcap = tptrs2D1[21];
							  this->m_pblhp = tptrs1D[13];
							  this->m_cld = tptrs2D[42];
							  this->m_ipbl = tptrs1D[14];
							  this->m_kpblh = tptrs1D[15];
							  this->m_wsedl = tptrs2D[43];

							  return (*this);
#else
							for (int i{ 0 }; i != this->m_pcols; ++i) {
#pragma ivdep
#pragma simd
#pragma unroll(4)
								for (int j{ 0 }; j != this->m_pver; ++j) {

									tptrs2D[0][i + this->m_pcols * j] = x.m_sl[i + x.m_pcols * j];
		                            tptrs2D[1][i + this->m_pcols * j] = x.m_qt[i + x.m_pcols * j];
		                            tptrs2D[2][i + this->m_pcols * j] = x.m_ql[i + x.m_pcols * j];
		                            tptrs2D[3][i + this->m_pcols * j] = x.m_slv[i + x.m_pcols * j];
		                            tptrs2D[4][i + this->m_pcols * j] = x.m_u[i + x.m_pcols * j];
		                            tptrs2D[5][i + this->m_pcols * j] = x.m_v[i + x.m_pcols * j];
		                            tptrs2D1[0][i + this->m_pcols * j] = x.m_pi[i + x.m_pcols * j];
		                            tptrs2D[6][i + this->m_pcols * j] = x.m_z[i + x.m_pcols * j];
		                            tptrs2D1[1][i + this->m_pcols * j] = x.m_zi[i + x.m_pcols * j];
		                            tptrs2D[7][i + this->m_pcols * j] = x.m_slslope[i + x.m_pcols * j];
		                            tptrs2D[8][i + this->m_pcols * j] = x.m_qtslope[i + x.m_pcols * j];
		                            tptrs2D1[2][i + this->m_pcols * j] = x.m_chu[i + x.m_pcols * j];
		                            tptrs2D1[3][i + this->m_pcols * j] = x.m_chs[i + x.m_pcols * j];
		                            tptrs2D1[4][i + this->m_pcols * j] = x.m_cmu[i + x.m_pcols * j];
		                            tptrs2D1[5][i + this->m_pcols * j] = x.m_cms[i + x.m_pcols * j];
		                            tptrs2D[9][i + this->m_pcols * j] = x.m_sfuh[i + x.m_pcols* j];
		                            tptrs2D[10][i + this->m_pcols * j] = x.m_sfhl[i + x.m_pcols * j];
		                            tptrs2D[11][i + this->m_pcols * j] = x.m_n2[i + x.m_pcols * j];
		                            tptrs2D[12][i + this->m_pcols * j] = x.m_s2[i + x.m_pcols * j];
		                            tptrs2D[13][i + this->m_pcols * j] = x.m_ri[i + x.m_pcols * j];
		                            tptrs2D1[6][i + this->m_pcols * j] = x.m_kvh_in[i + x.m_pcols * j];
		                            tptrs2D1[7][i + this->m_pcols * j] = x.m_kvm_in[i + x.m_pcols * j];
		                            tptrs2D1[8][i + this->m_pcols * j] = x.m_kvh[i + x.m_pcols * j];
		                            tptrs2D1[9][i + this->m_pcols * j] = x.m_kvm[i + x.m_pcols * j];
		                            tptrs2D[14][i + this->m_pcols * j] = x.m_qrlin[i + x.m_pcols * j];
		                            tptrs2D1[10][i + this->m_pcols * j] = x.m_kvf[i + x.m_pcols * j];
		                            tptrs2D1[11][i + this->m_pcols * j] = x.m_tke[i + x.m_pcols * j];
		                            tptrs2D1[12][i + this->m_pcols * j] = x.m_bprod[i + x.m_pcols * j];
		                            tptrs2D1[13][i + this->m_pcols * j] = x.m_sprod[i + x.m_pcols * j];
		                            tptrs2D1[14][i + this->m_pcols * j] = x.m_turbtype_f[i + x.m_pcols * j];
		                            tptrs2D1[15][i + this->m_pcols * j] = x.m_sm_aw[i + x.m_pcols * j];
		                            tptrs2D[15][i + this->m_pcols * j] = x.m_kbase_o[i + x.m_pcols * j];
		                            tptrs2D[16][i + this->m_pcols * j] = x.m_ktop_o[i + x.m_pcols * j];
		                            tptrs2D[17][i + this->m_pcols * j] = x.m_kbase_mg[i + x.m_pcols * j];
		                            tptrs2D[18][i + this->m_pcols * j] = x.m_ktop_mg[i + x.m_pcols * j];
		                            tptrs2D[19][i + this->m_pcols * j] = x.m_kbase_f[i + x.m_pcols * j];
		                            tptrs2D[20][i + this->m_pcols * j] = x.m_ktop_f[i + x.m_pcols * j];
		                            tptrs2D[21][i + this->m_pcols * j] = x.m_wet_CL[i + x.m_pcols * j];
		                            tptrs2D[22][i + this->m_pcols * j] = x.m_web_CL[i + x.m_pcols * j];
		                            tptrs2D[23][i + this->m_pcols * j] = x.m_jtbu_CL[i + x.m_pcols * j];
		                            tptrs2D[24][i + this->m_pcols * j] = x.m_jbbu_CL[i + x.m_pcols * j];
		                            tptrs2D[25][i + this->m_pcols * j] = x.m_evhc_CL[i + x.m_pcols * j];
		                            tptrs2D[26][i + this->m_pcols * j] = x.m_jt2slv_CL[i + x.m_pcols * j];
		                            tptrs2D[27][i + this->m_pcols * j] = x.m_n2ht_CL[i + x.m_pcols * j];
		                            tptrs2D[28][i + this->m_pcols * j] = x.m_n2hb_CL[i + x.m_pcols * j];
		                            tptrs2D[29][i + this->m_pcols * j] = x.m_lwp_CL[i + x.m_pcols * j];
		                            tptrs2D[30][i + this->m_pcols * j] = x.m_opt_depth_CL[i + x.m_pcols * j];
		                            tptrs2D[31][i + this->m_pcols * j] = x.m_radinvfrac_CL[i + x.m_pcols * j];
		                            tptrs2D[32][i + this->m_pcols * j] = x.m_radf_CL[i + x.m_pcols * j];
		                            tptrs2D[33][i + this->m_pcols * j] = x.m_wstar_CL[i + x.m_pcols * j];
		                            tptrs2D[34][i + this->m_pcols * j] = x.m_wstar3fact_CL[i + x.m_pcols * j];
		                            tptrs2D[35][i + this->m_pcols * j] = x.m_ebrk[i + x.m_pcols * j];
		                            tptrs2D[36][i + this->m_pcols * j] = x.m_wbrk[i + x.m_pcols * j];
		                            tptrs2D[37][i + this->m_pcols * j] = x.m_lbrk[i + x.m_pcols * j];
		                             tptrs2D[38][i + this->m_pcols * j] = x.m_ricl[i + x.m_pcols * j];
		                            tptrs2D[39][i + this->m_pcols * j] = x.m_ghcl[i + x.m_pcols * j];
		                            tptrs2D[40][i + this->m_pcols * j] = x.m_shcl[i + x.m_pcols * j];
		                            tptrs2D[41][i + this->m_pcols * j] = x.m_smcl[i + x.m_pcols * j];
		                            tptrs2D1[16][i + this->m_pcols * j] = x.m_gh_a[i + x.m_pcols * j];
		                            tptrs2D1[17][i + this->m_pcols * j] = x.m_sh_a[i + x.m_pcols * j];
		                            tptrs2D1[18][i + this->m_pcols * j] = x.m_sm_a[i + x.m_pcols * j];
		                            tptrs2D1[19][i + this->m_pcols * j] = x.m_ri_a[i + x.m_pcols * j];
		                            tptrs2D1[20][i + this->m_pcols * j] = x.m_leng[i + x.m_pcols * j];
		                            tptrs2D1[21][i + this->m_pcols * j] = x.m_wcap[i + x.m_pcols * j];
		                            tptrs2D[42][i + this->m_pcols * j] = x.m_cld[i + x.m_pcols * j];
		                            tptrs2D[43][i + this->m_pcols * j] = x.m_wsedl[i + x.m_pcols * j];
	}
}

							// Begin arrays 1D copy loop - vectorize only.
#pragma ivdep
#pragma simd
#pragma unroll(4)                 
							for (int i{ 0 }; i != this->m_pcols; ++i) {
								tptrs1D[0][i] = x.m_qflx[i];
								tptrs1D[1][i] = x.m_shflx[i];
								tptrs1D[2][i] = x.m_rrho[i];
								tptrs1D[3][i] = x.m_pblh[i];
								tptrs1D[4][i] = x.m_ustar[i];
								tptrs1D[5][i] = x.m_tpert[i];
								tptrs1D[6][i] = x.m_qpert[i];
								tptrs1D[7][i] = x.m_minpblh[i];
								tptrs1D[8][i] = x.m_wpert[i];
								tptrs1D[9][i] = x.m_tkes[i];
								tptrs1D[10][i] = x.m_ncvfin_o[i];
								tptrs1D[11][i] = x.m_ncvfin_mg[i];
								tptrs1D[12][i] = x.m_ncvfin_f[i];
								tptrs1D[13][i] = x.m_pblhp[i];
								tptrs1D[14][i] = x.m_ipbl[i];
								tptrs1D[15][i] = x.m_kpblh[i];
							}


							// Copy top element for arrays 2D , where pver = pver + 1.
							const int top = this->m_pcols * this->m_pver + 1;
							tptrs2D1[0][top] = x.m_pi[top];
							tptrs2D1[1][top] = x.m_zi[top];
							tptrs2D1[2][top] = x.m_chu[top];
							tptrs2D1[3][top] = x.m_chs[top];
							tptrs2D1[4][top] = x.m_cmu[top];
							tptrs2D1[5][top] = x.m_cms[top];
							tptrs2D1[6][top] = x.m_kvh_in[top];
							tptrs2D1[7][top] = x.m_kvm_in[top];
							tptrs2D1[8][top] = x.m_kvh[top];
							tptrs2D1[9][top] = x.m_kvm[top];
							tptrs2D1[10][top] = x.m_kvf[top];
							tptrs2D1[11][top] = x.m_tke[top];
							tptrs2D1[12][top] = x.m_bprod[top];
							tptrs2D1[13][top] = x.m_sprod[top];
							tptrs2D1[14][top] = x.m_turbtype_f[top];
							tptrs2D1[15][top] = x.m_sm_aw[top];
							tptrs2D1[16][top] = x.m_gh_a[top];
							tptrs2D1[17][top] = x.m_sh_a[top];
							tptrs2D1[18][top] = x.m_sm_a[top];
							tptrs2D1[19][top] = x.m_ri_a[top];
							tptrs2D1[20][top] = x.m_leng[top];
							tptrs2D1[21][top] = x.m_wcap[top];

							// Deallocate current context of *this.
							for (int i{ 0 }; i != this->m_nArrays; ++i) {
								if ((&this->m_sl)[i]) {
									_mm_free((&this->m_sl)[i]);
								}
							}

							// Copy temporary state to *this.
							this->m_sl = tptrs2D[0];
							this->m_qt = tptrs2D[1];
							this->m_ql = tptrs2D[2];
							this->m_slv = tptrs2D[3];
							this->m_u = tptrs2D[4];
							this->m_v = tptrs2D[5];
							this->m_pi = tptrs2D1[0];
							this->m_z = tptrs2D[6];
							this->m_zi = tptrs2D1[1];
							this->m_qflx = tptrs1D[0];
							this->m_shflx = tptrs1D[1];
							this->m_slslope = tptrs2D[7];
							this->m_qtslope = tptrs2D[8];
							this->m_chu = tptrs2D1[2];
							this->m_chs = tptrs2D1[3];
							this->m_cmu = tptrs2D1[4];
							this->m_cms = tptrs2D1[5];
							this->m_sfuh = tptrs2D[9];
							this->m_sfhl = tptrs2D[10];
							this->m_n2 = tptrs2D[11];
							this->m_s2 = tptrs2D[12];
							this->m_ri = tptrs2D[13];
							this->m_rrho = tptrs1D[2];
							this->m_pblh = tptrs1D[3];
							this->m_ustar = tptrs1D[4];
							this->m_kvh_in = tptrs2D1[6];
							this->m_kvm_in = tptrs2D1[7];
							this->m_kvh = tptrs2D1[8];
							this->m_kvm = tptrs2D1[9];
							this->m_tpert = tptrs1D[5];
							this->m_qpert = tptrs1D[6];
							this->m_qrlin = tptrs2D[14];
							this->m_kvf = tptrs2D1[10];
							this->m_tke = tptrs2D1[11];
							this->m_bprod = tptrs2D1[12];
							this->m_sprod = tptrs2D1[13];
							this->m_minpblh = tptrs1D[7];
							this->m_wpert = tptrs1D[8];
							this->m_tkes = tptrs1D[9];
							this->m_turbtype_f = tptrs2D1[14];
							this->m_sm_aw = tptrs2D1[15];
							this->m_kbase_o = tptrs2D[15];
							this->m_ktop_o = tptrs2D[16];
							this->m_ncvfin_o = tptrs1D[10];
							this->m_kbase_mg = tptrs2D[17];
							this->m_ktop_mg = tptrs2D[18];
							this->m_ncvfin_mg = tptrs1D[11];
							this->m_kbase_f = tptrs2D[19];
							this->m_ktop_f = tptrs2D[20];
							this->m_ncvfin_f = tptrs1D[12];
							this->m_wet_CL = tptrs2D[21];
							this->m_web_CL = tptrs2D[22];
							this->m_jtbu_CL = tptrs2D[23];
							this->m_jbbu_CL = tptrs2D[24];
							this->m_evhc_CL = tptrs2D[25];
							this->m_jt2slv_CL = tptrs2D[26];
							this->m_n2ht_CL = tptrs2D[27];
							this->m_n2hb_CL = tptrs2D[28];
							this->m_lwp_CL = tptrs2D[29];
							this->m_opt_depth_CL = tptrs2D[30];
							this->m_radinvfrac_CL = tptrs2D[31];
							this->m_radf_CL = tptrs2D[32];
							this->m_wstar_CL = tptrs2D[33];
							this->m_wstar3fact_CL = tptrs2D[34];
							this->m_ebrk = tptrs2D[35];
							this->m_wbrk = tptrs2D[36];
							this->m_lbrk = tptrs2D[37];
							this->m_ricl = tptrs2D[38];
							this->m_ghcl = tptrs2D[39];
							this->m_shcl = tptrs2D[40];
							this->m_smcl = tptrs2D[41];
							this->m_gh_a = tptrs2D1[16];
							this->m_sh_a = tptrs2D1[17];
							this->m_sm_a = tptrs2D1[18];
							this->m_ri_a = tptrs2D1[19];
							this->m_leng = tptrs2D1[20];
							this->m_wcap = tptrs2D1[21];
							this->m_pblhp = tptrs1D[13];
							this->m_cld = tptrs2D[42];
							this->m_ipbl = tptrs1D[14];
							this->m_kpblh = tptrs1D[15];
							this->m_wsedl = tptrs2D[43];

							return (*this);
#endif				  
			 }

			 /*
				@Purpose:
				         Move-assignment Operator implements shallow copy semantics.
			 */
					  WrapCalEddy & operator=(_In_ WrapCalEddy &&x) {
						  if (this == &x) return (*this);

						  this->m_pcols = x.m_pcols;
						  this->m_pver = x.m_pver;
						  this->m_ncol = x.m_ncol;
						  this->m_wstarent = x.m_wstarent;
						  // Deallocate current state(storage)
						  for (int i{ 0 }; i != this->m_nArrays; ++i) {
							  if ((&this->m_sl)[i]) {
								  _mm_free((&this->m_sl)[i]);
							  }
						  }
						  // Copy x'pointers to *this.
						  for (int i{ 0 }; i != this->m_nArrays; ++i) {
							  (&this->m_sl)[i] = (&x.m_sl)[i];
						  }
						  //  Nullify  x'pointers.
						  for (int i{ 0 }; i != x.m_nArrays; ++i) {
							  if ((&x.m_sl)[i]) {
								  
								  (&x.m_sl)[i] = nullptr;
							  }
						  }
						  x.m_pcols = 0;
						  x.m_pver = 0;
						  x.m_ncol = 0;

						  return (*this);
			 }

					  /*
					     @Purpose:
						           Call Fortan CALEDDY subroutine.
								   Notification:
								               Although direct call to CALEDDY is implemented
											   here potential caller must not call it directly
											   mainly because aforementioned subroutine is private
											   in her module.
					  */

					  void  CALL_CALEDDY() {

						  EDDY_DIFF_mp_CALEDDY(&this->m_pcols,&this->m_pver,&this->m_ncol,
							  &this->m_sl[0], &this->m_qt[0], &this->m_ql[0], &this->m_slv[0], &this->m_u[0],
							  &this->m_v[0], &this->m_pi[0], &this->m_z[0], &this->m_zi[0],
							  &this->m_qflx[0], &this->m_shflx, &this->m_slslope[0], &this->m_qtslope[0],
							  &this->m_chu[0], &this->m_chs[0], &this->m_cmu[0], &this->m_cms[0], &this->m_sfuh[0],
							  &this->m_sfhl[0], &this->m_n2[0], &this->m_s2[0], &this->m_ri[0], &this->m_rrho[0],
							  &this->m_pblh[0], &this->m_ustar[0],
							  &this->m_kvh_in[0], &this->m_kvm_in[0], &this->m_kvh[0], &this->m_kvm[0],
							  &this->m_tpert[0], &this->m_qpert[0], &this->m_qrlin[0], &this->m_kvf[0], &this->m_tke[0],
							  &this->m_wstarent, &this->m_bprod[0], &this->m_sprod[0], &this->m_minpblh[0], &this->m_wpert[0],
							  &this->m_tkes[0], &this->m_turbtype_f[0], &this->m_sm_aw[0],
							  &this->m_kbase_o[0], &this->m_ktop_o[0], &this->m_ncvfin_o[0],
							  &this->m_kbase_mg[0], &this->m_ktop_mg[0], &this->m_ncvfin_mg[0],
							  &this->m_kbase_f[0], &this->m_ktop_f[0], &this->m_ncvfin_f[0],
							  &this->m_wet_CL[0], &this->m_web_CL[0], &this->m_jtbu_CL[0], &this->m_jbbu_CL[0],
							  &this->m_evhc_CL[0], &this->m_jt2slv_CL[0], &this->m_n2ht_CL[0], this->m_n2hb_CL[0], &this->m_lwp_CL[0],
							  &this->m_opt_depth_CL[0], &this->m_radinvfrac_CL[0], &this->m_radf_CL[0], &this->m_wstar_CL[0], &this->m_wstar3fact_CL[0],
							  &this->m_ebrk[0], &this->m_wbrk[0], &this->m_lbrk[0], &this->m_ricl[0], &this->m_ghcl[0],
							  &this->m_shcl[0], &this->m_smcl[0],
							  &this->m_gh_a[0], &this->m_sh_a[0], &this->m_sm_a[0], &this->m_ri_a[0], &this->m_leng[0],
							  &this->m_wcap[0], &this->m_pblhp[0], &this->m_cld[0], &this->m_ipbl[0], &this->m_kpblh[0],
							  &this->m_wsedl[0] );
					  }

			 /*
			   @Purpose:
			             Member variables.   
			 */

			 

			 // Input member variables.

			 I32 m_pcols; // Number of atmospheric columns 

			 I32 m_pver;  // Number of atmospheric layers 

			 I32 m_ncol;  // Number of atmospheric columns 

			 I32 m_wstarent; // Switch for choosing wstar3 entrainment parameterization

		_In_ R64* __restrict m_sl; // Liquid water static energy, cp * T + g * z - Lv * ql - Ls * qi [ J/kg ]

		_In_ R64* __restrict m_qt; // Total speccific humidity  qv + ql + qi [ kg/kg ] 

		_In_ R64* __restrict m_ql; // Liquid water specific humidity [ kg/kg ]

		_In_ R64* __restrict m_slv; // Liquid water virtual static energy, sl * ( 1 + 0.608 * qt ) [ J/kg ]

		_In_ R64* __restrict m_u;  //  U wind [ m/s ]

		_In_ R64* __restrict m_v;  //  V wind [ m/s ]

		_In_ R64* __restrict m_pi; //  Interface pressures [ Pa ]

		_In_ R64* __restrict m_z;  //  Layer midpoint height above surface [ m ]

		_In_ R64* __restrict m_zi; //  Interface height above surface, i.e., zi(pver+1) = 0 all over the globe [ m ]

		_In_ R64* __restrict m_qflx; // Kinematic surface constituent ( water vapor ) flux [ kg/m2/s ]

		_In_ R64* __restrict m_shflx; // Kinematic surface heat flux [ unit ? ] 

		_In_ R64* __restrict m_slslope; // Slope of 'sl' in each layer [ J/kg/Pa ]

		_In_ R64* __restrict m_qtslope; // Slope of 'qt' in each layer [ kg/kg/Pa ]

		_In_ R64* __restrict m_chu; // Buoyancy coeffi. unsaturated sl (heat) coef. at all interfaces. [ unit ? ]

		_In_ R64* __restrict m_chs; // Buoyancy coeffi. saturated sl (heat) coef. at all interfaces. [ unit ? ]

		_In_ R64* __restrict m_cmu; // Buoyancy coeffi. unsaturated qt (moisture) coef. at all interfaces [ unit ? ]

		_In_ R64* __restrict m_cms; // Buoyancy coeffi. saturated qt (moisture) coef. at all interfaces [ unit ? ]

		_In_ R64* __restrict m_sfuh; // Saturation fraction in upper half-layer [ fraction ]

		_In_ R64* __restrict m_sfhl; // Saturation fraction in lower half-layer [ fraction ]

		_In_ R64* __restrict m_n2; // Interfacial (except surface) moist buoyancy frequency [ s-2 ]

		_In_ R64* __restrict m_s2; // Interfacial (except surface) shear frequency [ s-2 ]

		_In_ R64* __restrict m_ri; // Interfacial (except surface) Richardson number

		_In_ R64* __restrict m_rrho; // 1./bottom mid-point density. Specific volume [ m3/kg ]

		_Out_ R64* __restrict m_pblh; // PBL top height [ m ]

		_In_ R64* __restrict m_ustar; // Surface friction velocity [ m/s ]

		_In_ R64* __restrict m_kvh_in; // kvh saved from last timestep or last iterative step [ m2/s ] 

		_In_ R64* __restrict m_kvm_in; // kvm saved from last timestep or last iterative step [ m2/s ]

		_Out_ R64* __restrict m_kvh; // Eddy diffusivity for heat, moisture, and tracers [ m2/s ]

		_Out_ R64* __restrict m_kvm; // Eddy diffusivity for momentum [ m2/s ]

		_Out_ R64* __restrict m_tpert; // Convective temperature excess [ K ]

		_Out_ R64* __restrict m_qpert; // Convective humidity excess [ kg/kg ]

		_In_ R64* __restrict m_qrlin; // Input grid-mean LW heating rate : [ K/s ] * cpair * dp = [ W/kg*Pa ]

		_In_ R64* __restrict m_kvf; // Free atmosphere eddy diffusivity [ m2/s ]

		_Out_ R64* __restrict m_tke; // Turbulent kinetic energy [ m2/s2 ], 'tkes' at surface, pver+1.

		    
			 
		_Out_ R64* __restrict m_bprod; //  Buoyancy production [ m2/s3 ],     'bflxs' at surface, pver+1.

		_Out_ R64* __restrict m_sprod; //  Shear production [ m2/s3 ], (ustar(i)**3)/(vk*z(i,pver))  at surface, pver+1.

		_In_  R64* __restrict m_minpblh; //  Minimum PBL height based on surface stress [ m ]

		_Out_ R64* __restrict m_wpert; //  Turbulent velocity excess [ m/s ]

		_Out_ R64* __restrict m_tkes; //  TKE at surface [ m2/s2 ] 

		_Out_ R64* __restrict m_turbtype_f; // Turbulence type at each interface:

		_Out_ R64* __restrict m_sm_aw; //  Galperin instability function of momentum for use in the microphysics [ no unit ]

		_Out_ R64* __restrict m_kbase_o; // Original external base interface index of CL just after 'exacol'

		_Out_ R64* __restrict m_ktop_o; // Original external top  interface index of CL just after 'exacol'

		_Out_ R64* __restrict m_ncvfin_o; // Original number of CLs just after 'exacol'

		_Out_ R64* __restrict m_kbase_mg; //  Original external base interface index of CL just after 'exacol'

		_Out_ R64* __restrict m_ktop_mg; // ktop   just after extending-merging (after 'zisocl') but without SRCL

		_Out_ R64* __restrict m_ncvfin_mg; // ncvfin just after extending-merging (after 'zisocl') but without SRCL

		_Out_ R64* __restrict m_kbase_f; //  Final kbase  after adding SRCL

		_Out_ R64* __restrict m_ktop_f; //  Final ktop   after adding SRCL

		_Out_ R64* __restrict m_ncvfin_f; // Final ncvfin after adding SRCL
		
		_Out_ R64* __restrict m_wet_CL; //  Entrainment rate at the CL top [ m/s ] 

		_Out_ R64* __restrict m_web_CL; //  Entrainment rate at the CL base [ m/s ]

		_Out_ R64* __restrict m_jtbu_CL; // Buoyancy jump across the CL top [ m/s2 ]  

		_Out_ R64* __restrict m_jbbu_CL; // Buoyancy jump across the CL base [ m/s2 ]  

		_Out_ R64* __restrict m_evhc_CL; // Evaporative enhancement factor at the CL top

		_Out_ R64* __restrict m_jt2slv_CL; // Jump of slv ( across two layers ) at CL top for use only in evhc [ J/kg ]

		_Out_ R64* __restrict m_n2ht_CL; // n2 defined at the CL top  interface but using sfuh(kt)   instead of sfi(kt) [ s-2 ]

		_Out_ R64* __restrict m_n2hb_CL; // n2 defined at the CL base interface but using sflh(kb-1) instead of sfi(kb) [ s-2 ]

		_Out_ R64* __restrict m_lwp_CL; // LWP in the CL top layer [ kg/m2 ]

		_Out_ R64* __restrict m_opt_depth_CL; // Optical depth of the CL top layer

		_Out_ R64* __restrict m_radinvfrac_CL; // Fraction of LW radiative cooling confined in the top portion of CL

		_Out_ R64* __restrict m_radf_CL; // Buoyancy production at the CL top due to radiative cooling [ m2/s3 ]

		_Out_ R64* __restrict m_wstar_CL; // Convective velocity of CL including entrainment contribution finally [ m/s ]

		_Out_ R64* __restrict m_wstar3fact_CL; // "wstar3fact" of CL. Entrainment enhancement of wstar3 (inverse)

		_Out_ R64* __restrict m_ebrk; // Net CL mean TKE [ m2/s2 ]

		_Out_ R64* __restrict m_wbrk; // Net CL mean normalized TKE [ m2/s2 ]

		_Out_ R64* __restrict m_lbrk; // Net energetic integral thickness of CL [ m ]

		_Out_ R64* __restrict m_ricl; // Mean Richardson number of CL ( l2n2/l2s2 )

		_Out_ R64* __restrict m_ghcl; // Half of normalized buoyancy production of CL   

		_Out_ R64* __restrict m_shcl; // Instability function of heat and moisture of CL

		_Out_ R64* __restrict m_smcl; // Instability function of momentum of CL

		_Out_ R64* __restrict m_gh_a; // Half of normalized buoyancy production, -l2n2/2e. [ no unit ]

		_Out_ R64* __restrict m_sh_a; // Galperin instability function of heat-moisture at all interfaces [ no unit ]

		_Out_ R64* __restrict m_sm_a; // Galperin instability function of momentum      at all interfaces [ no unit ]

		_Out_ R64* __restrict m_ri_a; // Interfacial Richardson number                  at all interfaces [ no unit ]

		_Out_ R64* __restrict m_leng; // Turbulent length scale [ m ], 0 at the surface.

		_Out_ R64* __restrict m_wcap; // Normalized TKE [m2/s2], 'tkes/b1' at the surface and 'tke/b1' at
		                              // the top / bottom entrainment interfaces of CL assuming no transport.

		_Out_ R64* __restrict m_pblhp; // PBL top height pressure [ Pa ]

		_In_ R64*  __restrict m_cld; // Stratus Cloud Fraction [ fraction ]

		_Out_ R64* __restrict m_ipbl; // If 1, PBL is CL, while if 0, PBL is STL.

		_Out_ R64* __restrict m_kpblh; // Layer index containing PBL within or at the base interface

		_In_ R64*  __restrict m_wsedl; // Sedimentation velocity of liquid stratus cloud droplet [ m/s ]

		static const int m_nArrays = 82;

		static const int m_ptrs1D = 16;

		static const int m_ptrs2D1 = 22;

		static const int m_ptrs2D = 44;
	};






	}
}

#endif /*__EDDY_DIFF_CALEDDY_IMPL_H__*/