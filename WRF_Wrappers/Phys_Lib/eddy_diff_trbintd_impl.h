#ifndef __EDDY_DIFF_TRBINTD_IMPL_H__
#define __EDDY_DIFF_TRBINTD_IMPL_H__

#ifndef EDDY_DIFF_TRBINTD_VERSION_MAJOR
#define EDDY_DIFF_TRBINTD_VERSION_MAJOR 1
#endif

#ifndef EDDY_DIFF_TRBINTD_VERSION_MINOR
#define EDDY_DIFF_TRBINTD_VERSION_MINOR 0
#endif

#ifndef EDDY_DIFF_TRBINTD_PATCH_VERSION
#define EDDY_DIFF_TRBINTD_PATCH_VERSION 0
#endif

#ifndef EDDY_DIFF_TRBINTD_CREATE_DATE
#define EDDY_DIFF_TRBINTD_CREATE_DATE "Date: 27-10-2016 , Time: 14:08 PM GMT+2"
#endif

#ifndef EDDY_DIFF_TRBINTD_BUILD_DATE
#define EDDY_DIFF_TRBINTD_BUILD_DATE ""
#endif

#ifndef EDDY_DIFF_TRBINTD_AUTHOR
#define EDDY_DIFF_TRBINTD_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


#include "module_cam_bl_eddy_diff_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

namespace  phys_lib_wrappers {
	namespace module_eddy_diff {


		/*
		*   Wrapping structure called 'Wrap_Trbintd' its main
		*   purpose is to present herself as high level wrapper interface
		*	to underlying Fortran 90 'TRBINTD' subroutine.
		*   Notification:
		*                 'EDDY_DIFF_mp_TRBINTD' subroutine is module
		*                  internal (private) and should not be called
		*                  directly by C++ code side.
		*/
		template<typename R64 = double,
				 typename I32 = int   >  struct Wrap_Trbintd {



					 /***************************************
						    Constructors and Destructor.
					 ****************************************/

					 /*
						@Purpose:
								 Default Constructor - explicitly default.
					 */
					 Wrap_Trbintd() = default;

					 /*
						@Purpose:
									1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Trbintd(_In_ const I32 pcols,
								  _In_ const I32 pver,
						          _In_ const I32 ncol,
						          _In_ const I32 qsat)
						         :
						       m_pcols{ pcols },
						       m_pver{ pver },
						       m_ncol{ ncol },
						       m_qsat{ qsat },
						       m_z{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_u{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_v{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_t{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_pmid{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_taux{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						       m_tauy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						       m_ustar{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						       m_rrho{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
						       m_s2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_n2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_ri{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						       m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						       m_cld{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_qt{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_qv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_qi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						       m_sfuh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_sflh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_sl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_slv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_slslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_qtslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
						       m_chs{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						       m_chu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						       m_cms{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						       m_cmu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
							   m_minpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) } {

						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_z)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Trbintd'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_z)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Zero-initialize arrays.
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
								 this->m_z[i + m_pcols * j] = 0.0;
								 this->m_u[i + m_pcols * j] = 0.0;
								 this->m_v[i + m_pcols * j] = 0.0;
								 this->m_t[i + m_pcols * j] = 0.0;
								 this->m_pmid[i + m_pcols * j] = 0.0;
								 this->m_s2[i + m_pcols * j] = 0.0;
								 this->m_n2[i + m_pcols * j] = 0.0;
								 this->m_ri[i + m_pcols * j] = 0.0;
								 this->m_zi[i + m_pcols * j] = 0.0;
								 this->m_pi[i + m_pcols * j] = 0.0;
								 this->m_cld[i + m_pcols * j] = 0.0;
								 this->m_qt[i + m_pcols * j] = 0.0;
								 this->m_qv[i + m_pcols * j] = 0.0;
								 this->m_ql[i + m_pcols * j] = 0.0;
								 this->m_qi[i + m_pcols * j] = 0.0;
								 this->m_sfi[i + m_pcols * j] = 0.0;
								 this->m_sfuh[i + m_pcols * j] = 0.0;
								 this->m_sflh[i + m_pcols * j] = 0.0;
								 this->m_sl[i + m_pcols * j] = 0.0;
								 this->m_slv[i + m_pcols * j] = 0.0;
								 this->m_slslope[i + m_pcols * j] = 0.0;
								 this->m_qtslope[i + m_pcols * j] = 0.0;
								 this->m_chs[i + m_pcols * j] = 0.0;
								 this->m_chu[i + m_pcols * j] = 0.0;
								 this->m_cms[i + m_pcols * j] = 0.0;
								 this->m_cmu[i + m_pcols * j] = 0.0;

							 }
						 }
						 const int top = this->m_pcols * (this->m_pver + 1);
						 this->m_zi[top] = 0.0;
						 this->m_pi[top] = 0.0;
						 this->m_sfi[top] = 0.0;
						 this->m_chs[top] = 0.0;
						 this->m_chu[top] = 0.0;
						 this->m_cms[top] = 0.0;
						 this->m_cmu[top] = 0.0;

						 // Initialize arrays 1D.
						 // Using loop strip mining.
						 // Warning:
						 //         You must not #undef 'USE_STRIP_MINING' macro.
#if defined (USE_STRIP_MINING)
						 for (int i{ 0 }; i < this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
							 for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
								 this->m_taux[j] = 0.0;
								 this->m_tauy[j] = 0.0;
								 this->m_ustar[j] = 0.0;
								 this->m_rrho[j] = 0.0;
								 this->m_minpblh[j] = 0.0;
							 }
						 }
#endif


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
										 this->m_z[ii + m_pcols * jj] = 0.0;
										 this->m_u[ii + m_pcols * jj] = 0.0;
										 this->m_v[ii + m_pcols * jj] = 0.0;
										 this->m_t[ii + m_pcols * jj] = 0.0;
										 this->m_pmid[ii + m_pcols * jj] = 0.0;
										 this->m_s2[ii + m_pcols * jj] = 0.0;
										 this->m_n2[ii + m_pcols * jj] = 0.0;
										 this->m_ri[ii + m_pcols * jj] = 0.0;
										 this->m_zi[ii + m_pcols * jj] = 0.0;
										 this->m_pi[ii + m_pcols * jj] = 0.0;
										 this->m_cld[ii + m_pcols * jj] = 0.0;
										 this->m_qt[ii + m_pcols * jj] = 0.0;
										 this->m_qv[ii + m_pcols * jj] = 0.0;
										 this->m_ql[ii + m_pcols * jj] = 0.0;
										 this->m_qi[ii + m_pcols * jj] = 0.0;
										 this->m_sfi[ii + m_pcols * jj] = 0.0;
										 this->m_sfuh[ii + m_pcols * jj] = 0.0;
										 this->m_sflh[ii + m_pcols * jj] = 0.0;
										 this->m_sl[ii + m_pcols * jj] = 0.0;
										 this->m_slv[ii + m_pcols * jj] = 0.0;
										 this->m_slslope[ii + m_pcols * jj] = 0.0;
										 this->m_qtslope[ii + m_pcols * jj] = 0.0;
										 this->m_chs[ii + m_pcols * jj] = 0.0;
										 this->m_chu[ii + m_pcols * jj] = 0.0;
										 this->m_cms[ii + m_pcols * jj] = 0.0;
										 this->m_cmu[ii + m_pcols * jj] = 0.0;
									 }
								 }
							 }
						 }

#endif
						 const int top = this->m_pcols * (this->m_pver + 1);
						 this->m_zi[top] = 0.0;
						 this->m_pi[top] = 0.0;
						 this->m_sfi[top] = 0.0;
						 this->m_chs[top] = 0.0;
						 this->m_chu[top] = 0.0;
						 this->m_cms[top] = 0.0;
						 this->m_cmu[top] = 0.0;

						 // Initialize arrays 1D.
						 // Using loop strip mining.
						 // Warning:
						 //         You must not #undef 'USE_STRIP_MINING' macro.
#if defined (USE_STRIP_MINING)
						 for (int i{ 0 }; i < this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
							 for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
								 this->m_taux[j] = 0.0;
								 this->m_tauy[j] = 0.0;
								 this->m_ustar[j] = 0.0;
								 this->m_rrho[j] = 0.0;
								 this->m_minpblh[j] = 0.0;
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
			Wrap_Trbintd(_In_ const I32 pcols,
					     _In_ const I32 pver,
				         _In_ const I32 ncol,
				         _In_ const I32 qsat,
				         _In_ R64* __restrict const z,
				         _In_ R64* __restrict const u,
				         _In_ R64* __restrict const v,
				         _In_ R64* __restrict const t,
				         _In_ R64* __restrict const pmid,
				         _In_ R64* __restrict const taux,
				         _In_ R64* __restrict const tauy,
				         _In_ R64* __restrict const zi,
				         _In_ R64* __restrict const pi,
				         _In_ R64* __restrict const cld,
				         _In_ R64* __restrict const qv,
				         _In_ R64* __restrict const ql,
				         _In_ R64* __restrict const qi)
				              :
				        m_pcols{ pcols },
				        m_pver{ pver },
				        m_ncol{ ncol },
				        m_qsat{ qsat },
				        m_z{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_u{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_v{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_t{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_pmid{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_taux{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				        m_tauy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				        m_ustar{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				        m_rrho{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				        m_s2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_n2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_ri{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				        m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				        m_cld{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_qt{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_qv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_qi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				        m_sfuh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_sflh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_sl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_slv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_slslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_qtslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				        m_chs{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				        m_chu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				        m_cms{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				        m_cmu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
						m_minpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) } {

				// Check for memory allocation errors i.e (malloc failures).
				for (int i{ 0 }; i != this->m_nArrays; ++i) {
					if ((&this->m_z)[i] == NULL) {
						std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Trbintd'!!\n";
						std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
						std::cerr << "***** ERROR-DETAILS ***** \n";
						std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_z)[i] << "\n";
						std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
						std::exit(-1);
					}
				}
				// Check for memory allocation errors - input array arguments.
				if (z    == NULL ||
					u    == NULL ||
					v    == NULL ||
					t    == NULL ||
					pmid == NULL ||
					taux == NULL ||
					tauy == NULL ||
					zi   == NULL ||
					pi   == NULL ||
					cld  == NULL ||
					qv   == NULL ||
					ql   == NULL ||
					qi   == NULL) {

					std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Trbintd'!!\n";
					std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					std::cerr << "***** ERROR-DETAILS ***** \n";
					std::cerr << "One or more caller's arrays contains invalid pointer!!\n";
					std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
					std::exit(-1);
				}
				// Begin OpenMP copy loop of arrays 2D.
				// Fall back is single threaded loop blocking method.
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 20))
				for (int i{ 0 }; i != m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
					for (int j{ 0 }; j != m_pver; ++j) {
						this->m_z[i + m_pcols * j] = z[i + m_pcols * j];
						this->m_u[i + m_pcols * j] = u[i + m_pcols * j];
						this->m_v[i + m_pcols * j] = v[i + m_pcols * j];
						this->m_t[i + m_pcols * j] = t[i + m_pcols * j];
						this->m_pmid[i + m_pcols * j] = pmid[i + m_pcols * j];
						this->m_s2[i + m_pcols * j] = 0.0;
						this->m_n2[i + m_pcols * j] = 0.0;
						this->m_ri[i + m_pcols * j] = 0.0;
						this->m_zi[i + m_pcols * j] = zi[i + m_pcols * j];
						this->m_pi[i + m_pcols * j] = pi[i + m_pcols * j];
						this->m_cld[i + m_pcols * j] = cld[i + m_pcols * j];
						this->m_qt[i + m_pcols * j] = 0.0;
						this->m_qv[i + m_pcols * j] = qv[i + m_pcols * j];
						this->m_ql[i + m_pcols * j] = ql[i + m_pcols * j];
						this->m_qi[i + m_pcols * j] = qi[i + m_pcols * j];
						this->m_sfi[i + m_pcols * j] = 0.0;
						this->m_sfuh[i + m_pcols * j] = 0.0;
						this->m_sflh[i + m_pcols * j] = 0.0;
						this->m_sl[i + m_pcols * j] = 0.0;
						this->m_slv[i + m_pcols * j] = 0.0;
						this->m_slslope[i + m_pcols * j] = 0.0;
						this->m_qtslope[i + m_pcols * j] = 0.0;
						this->m_chs[i + m_pcols * j] = 0.0;
						this->m_chu[i + m_pcols * j] = 0.0;
						this->m_cms[i + m_pcols * j] = 0.0;
						this->m_cmu[i + m_pcols * j] = 0.0;

					}
				}
				// Initialize last element of size = m_pcols * m_pver + 1,
				// with values passed by caller's input arrays.
				// Output arrays are null initialized.
				const int top = this->m_pcols * (this->m_pver + 1);
				this->m_zi[top] = zi[top];
				this->m_pi[top] = pi[top];
				this->m_sfi[top] = 0.0;
				this->m_chs[top] = 0.0;
				this->m_chu[top] = 0.0;
				this->m_cms[top] = 0.0;
				this->m_cmu[top] = 0.0;
				// Copy to arrays 1D , vectorize only.
				// Strip mining is enabled by default.
				// Warning:
				//          You must not #undef 'USE_STRIP_MINING' macro!!
#if defined (USE_STRIP_MINING)
				for (int i{ 0 }; i != this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
					for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
						this->m_taux[j] = taux[j];
						this->m_tauy[j] = tauy[j];
						this->m_ustar[j] = 0.0;
						this->m_rrho[j] = 0.0;
						this->m_minpblh[j] = 0.0;
					}
				}


#endif

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
								this->m_z[ii + m_pcols * jj] = z[ii + m_pcols * jj];
								this->m_u[ii + m_pcols * jj] = u[ii + m_pcols * jj];
								this->m_v[ii + m_pcols * jj] = v[ii + m_pcols * jj];
								this->m_t[ii + m_pcols * jj] = t[ii + m_pcols * jj];
								this->m_pmid[ii + m_pcols * jj] = pmid[ii + m_pcols * jj];
								this->m_s2[ii + m_pcols * jj] = 0.0;
								this->m_n2[ii + m_pcols * jj] = 0.0;
								this->m_ri[ii + m_pcols * jj] = 0.0;
								this->m_zi[ii + m_pcols * jj] = zi[ii + m_pcols * jj];
								this->m_pi[ii + m_pcols * jj] = pi[ii + m_pcols * jj];
								this->m_cld[ii + m_pcols * jj] = cld[ii + m_pcols * jj];
								this->m_qt[ii + m_pcols * jj] = 0.0;
								this->m_qv[ii + m_pcols * jj] = qv[ii + m_pcols * jj];
								this->m_ql[ii + m_pcols * jj] = ql[ii + m_pcols * jj];
								this->m_qi[ii + m_pcols * jj] = qi[ii + m_pcols * jj];
								this->m_sfi[ii + m_pcols * jj] = 0.0;
								this->m_sfuh[ii + m_pcols * jj] = 0.0;
								this->m_sflh[ii + m_pcols * jj] = 0.0;
								this->m_sl[ii + m_pcols * jj] = 0.0;
								this->m_slv[ii + m_pcols * jj] = 0.0;
								this->m_slslope[ii + m_pcols * jj] = 0.0;
								this->m_qtslope[ii + m_pcols * jj] = 0.0;
								this->m_chs[ii + m_pcols * jj] = 0.0;
								this->m_chu[ii + m_pcols * jj] = 0.0;
								this->m_cms[ii + m_pcols * jj] = 0.0;
								this->m_cmu[ii + m_pcols * jj] = 0.0;
							}
						}
					}
				}

#endif
				// Initialize last element of size = m_pcols * m_pver + 1,
				// with values passed by caller's input arrays.
				// Output arrays are null initialized.
				const int top = this->m_pcols * (this->m_pver + 1);
				this->m_zi[top] = zi[top];
				this->m_pi[top] = pi[top];
				this->m_sfi[top] = 0.0;
				this->m_chs[top] = 0.0;
				this->m_chu[top] = 0.0;
				this->m_cms[top] = 0.0;
				this->m_cmu[top] = 0.0;
				// Copy to arrays 1D , vectorize only.
				// Strip mining is enabled by default.
				// Warning:
				//          You must not #undef 'USE_STRIP_MINING' macro!!
#if defined (USE_STRIP_MINING)
				for (int i{ 0 }; i != this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
					for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
						this->m_taux[j] = taux[j];
						this->m_tauy[j] = tauy[j];
						this->m_ustar[j] = 0.0;
						this->m_rrho[j] = 0.0;
						this->m_minpblh[j] = 0.0;
					}
				}


#endif


#endif				
				
				
					
			}

			         /*
						@Purpose:
								  Copy Constructor implements deep copy semantics.
			          */
			Wrap_Trbintd(_In_ const Wrap_Trbintd &x)
						:
				    m_pcols{ x.m_pcols },
				    m_pver{ x.m_pver },
				    m_ncol{ x.m_ncol },
				    m_qsat{ x.m_qsat },
				    m_z{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_u{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_v{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_t{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_pmid{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_taux{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				    m_tauy{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				    m_ustar{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				    m_rrho{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) },
				    m_s2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_n2{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_ri{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_cld{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_qt{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_qv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_qi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_sfuh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_sflh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_sl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_slv{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_slslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_qtslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_chs{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_chu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_cms{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_cmu{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
					m_minpblh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)), align32B)) } {

				//Check for memory allocations errors i.e (malloc failures).
				for (int i{ 0 }; i != this->m_nArrays; ++i){
					if ((&this->m_z)[i] == NULL) {
						std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor: 'Wrap_Trbintd'!!\n";
						std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
						std::cerr << "***** ERROR-DETAILS ***** \n";
						std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_z)[i] << "\n";
						std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
						std::exit(-1);
					}
				}
				// Begin OpenMP copy loop of arrays 2D.
				// Fall back is single threaded loop blocking method.
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
						this->m_z[i + m_pcols * j] = x.m_z[i + x.m_pcols * j];
						this->m_u[i + m_pcols * j] = x.m_u[i + x.m_pcols * j];
						this->m_v[i + m_pcols * j] = x.m_v[i + x.m_pcols * j];
						this->m_t[i + m_pcols * j] = x.m_t[i + x.m_pcols * j];
						this->m_pmid[i + m_pcols * j] = x.m_pmid[i + x.m_pcols * j];
						this->m_s2[i + m_pcols * j] = x.m_s2[i + x.m_pcols * j];
						this->m_n2[i + m_pcols * j] = x.m_n2[i + x.m_pcols * j];
						this->m_ri[i + m_pcols * j] = x.m_ri[i + x.m_pcols * j];
						this->m_zi[i + m_pcols * j] = x.m_zi[i + x.m_pcols * j];
						this->m_pi[i + m_pcols * j] = x.m_pi[i + x.m_pcols * j];
						this->m_cld[i + m_pcols * j] = x.m_cld[i + x.m_pcols * j];
						this->m_qt[i + m_pcols * j] = x.m_qt[i + x.m_pcols * j];
						this->m_qv[i + m_pcols * j] = x.m_qv[i + x.m_pcols * j];
						this->m_ql[i + m_pcols * j] = x.m_ql[i + x.m_pcols * j];
						this->m_qi[i + m_pcols * j] = x.m_qi[i + x.m_pcols * j];
						this->m_sfi[i + m_pcols * j] = x.m_sfi[i + x.m_pcols * j];
						this->m_sfuh[i + m_pcols * j] = x.m_sfuh[i + x.m_pcols * j];
						this->m_sflh[i + m_pcols * j] = x.m_sflh[i + x.m_pcols * j];
						this->m_sl[i + m_pcols * j] = x.m_sl[i + x.m_pcols * j];
						this->m_slv[i + m_pcols * j] = x.m_slv[i + x.m_pcols * j];
						this->m_slslope[i + m_pcols * j] = x.m_slslope[i + x.m_pcols * j];
						this->m_qtslope[i + m_pcols * j] = x.m_qtslope[i + x.m_pcols * j];
						this->m_chs[i + m_pcols * j] = x.m_chs[i + x.m_pcols * j];
						this->m_chu[i + m_pcols * j] = x.m_chu[i + x.m_pcols * j];
						this->m_cms[i + m_pcols * j] = x.m_cms[i + x.m_pcols * j];
						this->m_cmu[i + m_pcols * j] = x.m_cmu[i + x.m_pcols * j];
					}
				}
				// Initialize last element of size = m_pcols * m_pver + 1,
				// with values passed by caller's input arrays.
				// Output arrays are null initialized.
				const int top = this->m_pcols * (this->m_pver + 1);
				this->m_zi[top] = x.m_zi[top];
				this->m_pi[top] = x.m_pi[top];
				this->m_sfi[top] = x.m_sfi[top];
				this->m_chs[top] = x.m_chs[top];
				this->m_chu[top] = x.m_chu[top];
				this->m_cms[top] = x.m_cms[top];
				this->m_cmu[top] = x.m_cmu[top];
				// Copy to arrays 1D , vectorize only.
				// Strip mining is enabled by default.
				// Warning:
				//          You must not #undef 'USE_STRIP_MINING' macro!!
#if defined (USE_STRIP_MINING)
				for (int i{ 0 }; i != this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
					for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
						this->m_taux[j] = x.m_taux[j];
						this->m_tauy[j] = x.m_tauy[j];
						this->m_ustar[j] = x.m_ustar[j];
						this->m_rrho[j] = x.m_rrho[j];
						this->m_minpblh[j] = x.m_minpblh[j];
					}
				}


#endif




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
								this->m_z[ii + m_pcols * jj] = x.m_z[ii + x.m_pcols * jj];
								this->m_u[ii + m_pcols * jj] = x.m_u[ii + x.m_pcols * jj];
								this->m_v[ii + m_pcols * jj] = x.m_v[ii + x.m_pcols * jj];
								this->m_t[ii + m_pcols * jj] = x.m_t[ii + x.m_pcols * jj];
								this->m_pmid[ii + m_pcols * jj] = x.m_pmid[ii + x.m_pcols * jj];
								this->m_s2[ii + m_pcols * jj] = x.m_s2[ii + x.m_pcols * jj];
								this->m_n2[ii + m_pcols * jj] = x.m_n2[ii + x.m_pcols * jj];
								this->m_ri[ii + m_pcols * jj] = x.m_ri[ii + x.m_pcols * jj];
								this->m_zi[ii + m_pcols * jj] = x.m_zi[ii + x.m_pcols * jj];
								this->m_pi[ii + m_pcols * jj] = x.m_pi[ii + x.m_pcols * jj];
								this->m_cld[ii + m_pcols * jj] = x.m_cld[ii + x.m_pcols * jj];
								this->m_qt[ii + m_pcols * jj] = x.m_qt[ii + x.m_pcols * jj];
								this->m_qv[ii + m_pcols * jj] = x.m_qv[ii + x.m_pcols * jj];
								this->m_ql[ii + m_pcols * jj] = x.m_ql[ii + x.m_pcols * jj];
								this->m_qi[ii + m_pcols * jj] = x.m_qi[ii + x.m_pcols * jj];
								this->m_sfi[ii + m_pcols * jj] = x.m_sfi[ii + x.m_pcols * jj];
								this->m_sfuh[ii + m_pcols * jj] = x.m_sfuh[ii + x.m_pcols * jj];
								this->m_sflh[ii + m_pcols * jj] = x.m_sflh[ii + x.m_pcols * jj];
								this->m_sl[ii + m_pcols * jj] = x.m_sl[ii + x.m_pcols * jj];
								this->m_slv[ii + m_pcols * jj] = x.m_slv[ii + x.m_pcols * jj];
								this->m_slslope[ii + m_pcols * jj] = x.m_slslope[ii + x.m_pcols * jj];
								this->m_qtslope[ii + m_pcols * jj] = x.m_qtslope[ii + x.m_pcols * jj];
								this->m_chs[ii + m_pcols * jj] = x.m_chs[ii + x.m_pcols * jj];
								this->m_chu[ii + m_pcols * jj] = x.m_chu[ii + x.m_pcols * jj];
								this->m_cms[ii + m_pcols * jj] = x.m_cms[ii + x.m_pcols * jj];
								this->m_cmu[ii + m_pcols * jj] = x.m_cmu[ii + x.m_pcols * jj];
							}
						}
					}
				}

#endif
				// Initialize last element of size = m_pcols * m_pver + 1,
				// with values passed by caller's input arrays.
				// Output arrays are null initialized.
				const int top = this->m_pcols * (this->m_pver + 1);
				this->m_zi[top] = x.m_zi[top];
				this->m_pi[top] = x.m_pi[top];
				this->m_sfi[top] = x.m_sfi[top];
				this->m_chs[top] = x.m_chs[top];
				this->m_chu[top] = x.m_chu[top];
				this->m_cms[top] = x.m_cms[top];
				this->m_cmu[top] = x.m_cmu[top];
				// Copy to arrays 1D , vectorize only.
				// Strip mining is enabled by default.
				// Warning:
				//          You must not #undef 'USE_STRIP_MINING' macro!!
#if defined (USE_STRIP_MINING)
				for (int i{ 0 }; i != this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
					for (int j = i; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
						this->m_taux[j] = x.m_taux[j];
						this->m_tauy[j] = x.m_tauy[j];
						this->m_ustar[j] = x.m_ustar[j];
						this->m_rrho[j] = x.m_rrho[j];
						this->m_minpblh[j] = x.m_minpblh[j];
					}
				}


#endif

#endif

		    }

			 
			          /*
						@Purpose:
									Move Constructor implements shallow copy semantics.
			          */
					 Wrap_Trbintd(_In_ Wrap_Trbintd &&x)
				                    :
				              m_pcols{ x.m_pcols },
				              m_pver{ x.m_pver },
				              m_ncol{ x.m_ncol },
							  m_qsat{ x.m_qsat } {

						 // Copy pointers from x to *this.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&this->m_z)[i] = (&x.m_z)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&x.m_z)[i]) {
								 (&x.m_z)[i] = NULL;
							 }
						 }
						 x.m_pcols = 0;
						 x.m_pver = 0;
			}

					 /*
						@Purpose:
								 Class Destructor.
					 */
					 ~Wrap_Trbintd() {
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_z)[i]) {
								 _mm_free((&this->m_z)[i]);
							 }
						 }
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&this->m_z)[i] = NULL;
						 }
						 this->m_pcols = 0;
						 this->m_pver = 0;
					 
			}

					 /*
						@Purpose:
							      Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Trbintd & operator=(_In_ const Wrap_Trbintd &x) {
						 if (this == &x) return (*this);

						 this->m_pcols = x.m_pcols;
						 this->m_pver = x.m_pver;
						 this->m_ncol = x.m_ncol;
						 this->m_qsat = x.m_qsat;
						 constexpr int ntPtrs2D{19};
						 R64  *tPtrs2D[ntPtrs2D] = {};
						 // Begin an allocation of temporary array of pointers
						 // to arrays 2D.
						 for (int i{ 0 }; i != this->m_nArray2D; ++i) {
							 tPtrs2D[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_nArray2D; ++i) {
							 if (tPtrs2D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Trbintd'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs2D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 constexpr int ntPtrs2Dp1{7};
						 R64  *tPtrs2Dp1[ntPtrs2Dp1] = {};
						 for (int i{ 0 }; i != this->m_nArray2Dp1; ++i) {
							 tPtrs2Dp1[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_nArray2Dp1; ++i) {
							 if (tPtrs2Dp1[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Trbintd'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs2Dp1[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 constexpr int ntPtrs1D{5};
						 R64  *tPtrs1D[ntPtrs1D] = {};
						 for (int i{ 0 }; i != this->m_nArray1D; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * sizeof(R64)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_nArray1D; ++i) {
							 if (tPtrs1D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Trbintd'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 1D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs1D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 // Begin arrays 2D - large copy loop. First arrays 2D.
						 // OpenMP will be in use if total size >= (1 << 20).
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for shared(tPtrs2D,tPtrs2Dp1) if((m_pcols * m_pver) >= (1 << 20))
						 for (int i{ 0 }; i != this->m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int j{ 0 }; j != this->m_pver;  ++j) {
								 tPtrs2D[0][i + m_pcols * j] = x.m_z[i + x.m_pcols * j];
								 tPtrs2D[1][i + m_pcols * j] = x.m_u[i + x.m_pcols * j];
								 tPtrs2D[2][i + m_pcols * j] = x.m_v[i + x.m_pcols * j];
								 tPtrs2D[3][i + m_pcols * j] = x.m_t[i + x.m_pcols * j];
								 tPtrs2D[4][i + m_pcols * j] = x.m_pmid[i + x.m_pcols * j];
								 tPtrs2D[5][i + m_pcols * j] = x.m_s2[i + x.m_pcols * j];
								 tPtrs2D[6][i + m_pcols * j] = x.m_n2[i + x.m_pcols * j];
								 tPtrs2D[7][i + m_pcols * j] = x.m_ri[i + x.m_pcols * j];
								 tPtrs2Dp1[0][i + m_pcols * j] = x.m_zi[i + x.m_pcols * j];
								 tPtrs2Dp1[1][i + m_pcols * j] = x.m_pi[i + x.m_pcols * j];
								 tPtrs2D[8][i + m_pcols * j] = x.m_cld[i + x.m_pcols * j];
								 tPtrs2D[9][i + m_pcols * j] = x.m_qt[i + x.m_pcols * j];
								 tPtrs2D[10][i + m_pcols * j] = x.m_qv[i + x.m_pcols * j];
								 tPtrs2D[11][i + m_pcols * j] = x.m_ql[i + x.m_pcols * j];
								 tPtrs2D[12][i + m_pcols * j] = x.m_qi[i + x.m_pcols * j];
								 tPtrs2Dp1[2][i + m_pcols * j] = x.m_sfi[i + x.m_pcols * j];
								 tPtrs2D[13][i + m_pcols * j] = x.m_sfuh[i + x.m_pcols * j];
								 tPtrs2D[14][i + m_pcols * j] = x.m_sflh[i + x.m_pcols * j];
								 tPtrs2D[15][i + m_pcols * j] = x.m_sl[i + x.m_pcols * j];
								 tPtrs2D[16][i + m_pcols * j] = x.m_slv[i + x.m_pcols * j];
								 tPtrs2D[17][i + m_pcols * j] = x.m_slslope[i + x.m_pcols * j];
								 tPtrs2D[18][i + m_pcols * j] = x.m_qtslope[i + x.m_pcols * j];
								 tPtrs2Dp1[3][i + m_pcols * j] = x.m_chs[i + x.m_pcols * j];
								 tPtrs2Dp1[4][i + m_pcols * j] = x.m_chu[i + x.m_pcols * j];
								 tPtrs2Dp1[5][i + m_pcols * j] = x.m_cms[i + x.m_pcols * j];
								 tPtrs2D[19][i + m_pcols * j] = x.m_cmu[i + x.m_pcols * j];

							 }
						 }
						 const int top = this->m_pcols * (this->m_pver + 1);
						 tPtrs2Dp1[0][top] = x.m_zi[top];
						 tPtrs2Dp1[1][top] = x.m_pi[top];
						 tPtrs2Dp1[2][top] = x.m_sfi[top];
						 tPtrs2Dp1[3][top] = x.m_chs[top];
						 tPtrs2Dp1[4][top] = x.m_chu[top];
						 tPtrs2Dp1[5][top] = x.m_cms[top];
						 tPtrs2Dp1[6][top] = x.m_cmu[top];
						 // Begin copy loop of arrays 1D.
						 // Using vectorization and strip mining.
						 // USE_STRIP_MINING should not be udefined.
#if defined (USE_STRIP_MINING)
						 for (int i{ 0 }; i != this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
							 for (int j{ 0 }; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
								 tPtrs1D[0][j] = x.m_taux[j];
								 tPtrs1D[1][j] = x.m_tauy[j];
								 tPtrs1D[2][j] = x.m_ustar[j];
								 tPtrs1D[3][j] = x.m_rrho[j];
								 tPtrs1D[4][j] = x.m_minpblh[j];
							 }
						 }


#endif
						 // Deallocate current context of *this.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_z)[i]) {
								 _mm_free((&this->m_z)[i]);
							 }
						 }
						 // Reassign temporay pointers to member pointers.
						 this->m_z = tPtrs2D[0];
						 this->m_u = tPtrs2D[1];
						 this->m_v = tPtrs2D[2];
						 this->m_t = tPtrs2D[3];
						 this->m_pmid = tPtrs2D[4];
						 this->m_taux = tPtrs1D[0];
						 this->m_tauy = tPtrs1D[1];
						 this->m_ustar = tPtrs1D[2];
						 this->m_rrho = tPtrs1D[3];
						 this->m_s2 = tPtrs2D[5];
						 this->m_n2 = tPtrs2D[6];
						 this->m_ri = tPtrs2D[7];
						 this->m_zi = tPtrs2Dp1[0];
						 this->m_pi = tPtrs2Dp1[1];
						 this->m_cld = tPtrs2D[8];
						 this->m_qt = tPtrs2D[9];
						 this->m_qv = tPtrs2D[10];
						 this->m_ql = tPtrs2D[11];
						 this->m_qi = tPtrs2D[12];
						 this->m_sfi = tPtrs2Dp1[2];
						 this->m_sfuh = tPtrs2D[13];
						 this->m_sflh = tPtrs2D[14];
						 this->m_sl = tPtrs2D[15];
						 this->m_slv = tPtrs2D[16];
						 this->m_slslope = tPtrs2D[17];
						 this->m_qtslope = tPtrs2D[18];
						 this->m_chs = tPtrs2Dp1[3];
						 this->m_chu = tPtrs2Dp1[4];
						 this->m_cms = tPtrs2Dp1[5];
						 this->m_cmu = tPtrs2Dp1[6];
						 this->m_minpblh = tPtrs1D[4];

						 return (*this);
#else
// Using loop blocking optimization.
// Single-threaded execution.
// You should not #undef USE_LOOP_BLOCKING macro!!

#if defined (USE_LOOP_BLOCKING)
                         for(int i{0}; i != m_pcols; i += DEFAULT_BLOCK_SIZE) {
							 for(int j{0}; j != m_pver; j += DEFAULT_BLOCK_SIZE) {
								 for(int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
									 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
										 tPtrs2D[0][ii + m_pcols * jj] = x.m_z[ii + x.m_pcols * jj];
										 tPtrs2D[1][ii + m_pcols * jj] = x.m_u[ii + x.m_pcols * jj];
										 tPtrs2D[2][ii + m_pcols * jj] = x.m_v[ii + x.m_pcols * jj];
										 tPtrs2D[3][ii + m_pcols * jj] = x.m_t[ii + x.m_pcols * jj];
										 tPtrs2D[4][ii + m_pcols * jj] = x.m_pmid[ii + x.m_pcols * jj];
										 tPtrs2D[5][ii + m_pcols * jj] = x.m_s2[ii + x.m_pcols * jj];
										 tPtrs2D[6][ii + m_pcols * jj] = x.m_n2[ii + x.m_pcols * jj];
										 tPtrs2D[7][ii + m_pcols * jj] = x.m_ri[ii + x.m_pcols * jj];
										 tPtrs2Dp1[0][ii + m_pcols * jj] = x.m_zi[ii + x.m_pcols * jj];
										 tPtrs2Dp1[1][ii + m_pcols * jj] = x.m_pi[ii + x.m_pcols * jj];
										 tPtrs2D[8][ii + m_pcols * jj] = x.m_cld[ii + x.m_pcols * jj];
										 tPtrs2D[9][ii + m_pcols * jj] = x.m_qt[ii + x.m_pcols * jj];
										 tPtrs2D[10][ii + m_pcols * jj] = x.m_qv[ii + x.m_pcols * jj];
										 tPtrs2D[11][ii + m_pcols * jj] = x.m_ql[ii + x.m_pcols * jj];
										 tPtrs2D[12][ii + m_pcols * jj] = x.m_qi[ii + x.m_pcols * jj];
										 tPtrs2Dp1[2][ii + m_pcols * jj] = x.m_sfi[ii + x.m_pcols * jj];
										 tPtrs2D[13][ii + m_pcols * jj] = x.m_sfuh[ii + x.m_pcols * jj];
										 tPtrs2D[14][ii + m_pcols * jj] = x.m_sflh[ii + x.m_pcols * jj];
										 tPtrs2D[15][ii + m_pcols * jj] = x.m_sl[ii + x.m_pcols * jj];
										 tPtrs2D[16][ii + m_pcols * jj] = x.m_slv[ii + x.m_pcols * jj];
										 tPtrs2D[17][ii + m_pcols * jj] = x.m_slslope[ii + x.m_pcols * jj];
										 tPtrs2D[18][ii + m_pcols * jj] = x.m_qtslope[ii + x.m_pcols * jj];
										 tPtrs2Dp1[3][ii + m_pcols * jj] = x.m_chs[ii + x.m_pcols * jj];
										 tPtrs2Dp1[4][ii + m_pcols * jj] = x.m_chu[ii + x.m_pcols * jj];
										 tPtrs2Dp1[5][ii + m_pcols * jj] = x.m_cms[ii + x.m_pcols * jj];
										 tPtrs2D[19][ii + m_pcols * jj] = x.m_cmu[ii + x.m_pcols * jj];
									 }
								 }
							 }
                     }


#endif
						 const int top = this->m_pcols * (this->m_pver + 1);
						 tPtrs2Dp1[0][top] = x.m_zi[top];
						 tPtrs2Dp1[1][top] = x.m_pi[top];
						 tPtrs2Dp1[2][top] = x.m_sfi[top];
						 tPtrs2Dp1[3][top] = x.m_chs[top];
						 tPtrs2Dp1[4][top] = x.m_chu[top];
						 tPtrs2Dp1[5][top] = x.m_cms[top];
						 tPtrs2Dp1[6][top] = x.m_cmu[top];
						 // Begin copy loop of arrays 1D.
						 // Using vectorization and strip mining.
						 // USE_STRIP_MINING should not be udefined.
#if defined (USE_STRIP_MINING)
						 for (int i{ 0 }; i != this->m_pcols; i += DEFAULT_STRIP_SIZE) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
							 for (int j{ 0 }; j < std::min(m_pcols, i + DEFAULT_STRIP_SIZE); ++j) {
								 tPtrs1D[0][j] = x.m_taux[j];
								 tPtrs1D[1][j] = x.m_tauy[j];
								 tPtrs1D[2][j] = x.m_ustar[j];
								 tPtrs1D[3][j] = x.m_rrho[j];
								 tPtrs1D[4][j] = x.m_minpblh[j];
							 }
						 }


#endif
						 // Deallocate current context of *this.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_z)[i]) {
								 _mm_free((&this->m_z)[i]);
							 }
						 }
						 // Reassign temporay pointers to member pointers.
						 this->m_z = tPtrs2D[0];
						 this->m_u = tPtrs2D[1];
						 this->m_v = tPtrs2D[2];
						 this->m_t = tPtrs2D[3];
						 this->m_pmid = tPtrs2D[4];
						 this->m_taux = tPtrs1D[0];
						 this->m_tauy = tPtrs1D[1];
						 this->m_ustar = tPtrs1D[2];
						 this->m_rrho = tPtrs1D[3];
						 this->m_s2 = tPtrs2D[5];
						 this->m_n2 = tPtrs2D[6];
						 this->m_ri = tPtrs2D[7];
						 this->m_zi = tPtrs2Dp1[0];
						 this->m_pi = tPtrs2Dp1[1];
						 this->m_cld = tPtrs2D[8];
						 this->m_qt = tPtrs2D[9];
						 this->m_qv = tPtrs2D[10];
						 this->m_ql = tPtrs2D[11];
						 this->m_qi = tPtrs2D[12];
						 this->m_sfi = tPtrs2Dp1[2];
						 this->m_sfuh = tPtrs2D[13];
						 this->m_sflh = tPtrs2D[14];
						 this->m_sl = tPtrs2D[15];
						 this->m_slv = tPtrs2D[16];
						 this->m_slslope = tPtrs2D[17];
						 this->m_qtslope = tPtrs2D[18];
						 this->m_chs = tPtrs2Dp1[3];
						 this->m_chu = tPtrs2Dp1[4];
						 this->m_cms = tPtrs2Dp1[5];
						 this->m_cmu = tPtrs2Dp1[6];
						 this->m_minpblh = tPtrs1D[4];

						 return (*this);

#endif


			}

						/*
							@Purpose:
								      Move-assign Operator implements shallow copy semantics.
						*/
					 Wrap_Trbintd & operator=(_In_ Wrap_Trbintd &&x) {
						 if (this == &x) return (*this);

						 this->m_pcols = x.m_pcols;
						 this->m_pver = x.m_pver;
						 this->m_ncol = x.m_ncol;
						 this->m_qsat = x.m_qsat;
						 // Deallocate current context.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_z)[i]) {
								 _mm_free((&this->m_z)[i]);
							 }
						 }
						 // Reassign x's pointers to *this's pointers.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&this->m_z)[i] = (&x.m_z)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&x.m_z)[i] = NULL;
						 }
						 x.m_pcols = 0;
						 x.m_pver = 0;

						 return (*this);
			}

					 /*
						@Purpose:
								  Calls Fortran 90 'TRBINTD' subroutine.
								  Warning:
											'TRBINTD' probably will not
								  be accessible from outside eddy_diff module.
					 */
					 void  Call_Trbintd() {

						 EDDY_DIFF_mp_TRBINTD(&this->m_chs, &this->m_pver, &this->m_ncol,
							 &this->m_z[0], &this->m_u[0], &this->m_v[0], &this->m_t[0],
							 &this->m_pmid[0], &this->m_taux[0], &this->m_tauy[0], 
							 &this->m_ustar[0], &this->m_rrho[0], &this->m_s2[0], &this->m_n2[0],
							 &this->m_ri[0], &this->m_zi[0], &this->m_pi[0], &this->m_cld[0],
							 &this->m_qt[0], &this->m_qv[0], &this->m_ql[0], &this->m_qi[0],
							 &this->m_sfi[0], &this->m_sfuh[0], &this->m_sflh[0], &this->m_sl[0],
							 &this->m_slv[0], &this->m_slslope[0], &this->m_qtslope[0], &this->m_chs[0],
							 &this->m_chu[0], &this->m_cms[0], &this->m_cmu[0], &this->m_minpblh[0],
							 &this->m_qsat);
					 }

					 /*
						@Purpose:
									Member variables.
					 */
					 I32 m_pcols;

					 I32 m_pver;

					 I32 m_ncol;

					 I32 m_qsat;

_Field_size_(m_pcols * m_pver) R64* __restrict m_z;

_Field_size_(m_pcols * m_pver) R64* __restrict m_u;

_Field_size_(m_pcols * m_pver) R64* __restrict m_v;

_Field_size_(m_pcols * m_pver) R64* __restrict m_t;

_Field_size_(m_pcols * m_pver) R64* __restrict m_pmid;

_Field_size_(m_pcols) R64* __restrict m_taux;

_Field_size_(m_pcols) R64* __restrict m_tauy;

_Field_size_(m_pcols) R64* __restrict m_ustar;

_Field_size_(m_pcols) R64* __restrict m_rrho;

_Field_size_(m_pcols * m_pver) R64* __restrict m_s2;

_Field_size_(m_pcols * m_pver) R64* __restrict m_n2;

_Field_size_(m_pcols * m_pver) R64* __restrict m_ri;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_zi;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_pi;

_Field_size_(m_pcols * m_pver) R64* __restrict m_cld;

_Field_size_(m_pcols * m_pver) R64* __restrict m_qt;

_Field_size_(m_pcols * m_pver) R64* __restrict m_qv;

_Field_size_(m_pcols * m_pver) R64* __restrict m_ql;

_Field_size_(m_pcols * m_pver) R64* __restrict m_qi;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_sfi;

_Field_size_(m_pcols * m_pver) R64* __restrict m_sfuh;

_Field_size_(m_pcols * m_pver) R64* __restrict m_sflh;

_Field_size_(m_pcols * m_pver) R64* __restrict m_sl;

_Field_size_(m_pcols * m_pver) R64* __restrict m_slv;

_Field_size_(m_pcols * m_pver) R64* __restrict m_slslope;

_Field_size_(m_pcols * m_pver) R64* __restrict m_qtslope;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_chs;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_chu;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_cms;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_cmu;

_Field_size_(m_pcols) R64* __restrict m_minpblh;

                      static const int m_nArrays = 31;

					  static const int m_nArray1D = 5;

					  static const int m_nArray2D = 19;

					  static const int m_nArray2Dp1 = 7;




			};


	}
}






#endif /*__EDDY_DIFF_TRBINTD_IMPL_H__*/