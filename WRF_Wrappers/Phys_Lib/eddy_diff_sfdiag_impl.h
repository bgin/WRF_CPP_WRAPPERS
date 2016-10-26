
#ifndef __EDDY_DIFF_SFDIAG_IMPL_H__
#define __EDDY_DIFF_SFDIAG_IMPL_H__

#ifndef EDDY_DIFF_SFDIAG_IMPL_VERSION_MAJOR
#define EDDY_DIFF_SFDIAG_IMPL_VERSION_MAJOR 1
#endif

#ifndef EDDY_DIFF_SFDIAG_IMPL_VERSION_MINOR
#define EDDY_DIFF_SFDIAG_IMPL_VERSION_MINOR 0
#endif

#ifndef EDDY_DIFF_SFDIAG_IMPL_PATCH_VERSION
#define EDDY_DIFF_SFDIAG_IMPL_PATCH_VERSION 0
#endif

#ifndef EDDY_DIFF_SFDIAG_IMPL_CREATE_DATE
#define EDDY_DIFF_SFDIAG_IMPL_CREATE_DATE "Date: 25-10-2016 , Time: 18:09 PM GMT+2"
#endif

#ifndef EDDY_DIFF_SFDIAG_IMPL_BUILD_DATE
#define EDDY_DIFF_SFDIAG_IMPL_BUILD_DATE ""
#endif

#ifndef EDDY_DIFF_SFDIAG_IMPL_AUTHOR
#define EDDY_DIFF_SFDIAG_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif



#include "module_cam_bl_eddy_diff_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"



namespace  phys_lib_wrappers {
	namespace module_eddy_diff {


		/*
		*   Wrapping structure called 'Wrap_Sfdiag' its main
		*   purpose is to present herself as high level wrapper interface
		*	to underlying Fortran 90 'SFDIAG' subroutine.
		*   Notification:
		*                 'EDDY_DIFF_mp_SFDIAG' subroutine is module
		*                  internal (private) and should not be called
		*                  directly by C++ code side.
		*/

		template<typename R64 = double,
			typename I32 = int   > struct  Wrap_Sfdiag {



				/*******************************
				   Constructors and Destructor.
				********************************/

				/*
					@Purpose:
								Default Constructor - explicitly default.
				*/
				Wrap_Sfdiag() = default;

				/*
					@Purpose:
								  1st 'main' Constructor which purpose
								  is to allocate and initialize scalar
								  and array members. Array members are
								  zero-filled. Caller must later initialize
								  input arrays to correct physical state.
				*/
				Wrap_Sfdiag(_In_ const I32 pcols,
					        _In_ const I32 pver,
					        _In_ const I32 ncol,
					        _In_ const I32 qsat)
					      :
					  m_pcols{ pcols },
					  m_pver{ pver },
					  m_ncol{ ncol },
					  m_qsat{ qsat },
					  m_qt{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					  m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					  m_sl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					  m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
					  m_pm{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					  m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
					  m_cld{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					  m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
					  m_sfuh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					  m_sflh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					  m_slslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					  m_qtslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) } {

					// Check for memory allocation errors (malloc failure).
					for (int i{ 0 }; i != this->m_nArrays; ++i) {
						if ((&this->m_qt)[i] == NULL) {
							std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor Wrap_Sfdiag!!\n";
							std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							std::cerr << "***** ERROR-DETAILS ***** \n";
							std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_qt)[i] << "\n";
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
						for(int j{ 0 }; j != this->m_pver;  ++j) {
							this->m_qt[i + m_pcols * j] = 0.0;
							this->m_ql[i + m_pcols * j] = 0.0;
							this->m_sl[i + m_pcols * j] = 0.0;
							this->m_pi[i + m_pcols * j] = 0.0;
							this->m_pm[i + m_pcols * j] = 0.0;
							this->m_zi[i + m_pcols * j] = 0.0;
							this->m_cld[i + m_pcols * j] = 0.0;
							this->m_sfi[i + m_pcols * j] = 0.0;
							this->m_sfuh[i + m_pcols * j] = 0.0;
							this->m_sflh[i + m_pcols * j] = 0.0;
							this->m_slslope[i + m_pcols * j] = 0.0;
							this->m_qtslope[i + m_pcols * j] = 0.0;
						}
					}
					// Copy top element == 0.0 to arrays 2D 
					// where m_pver == m_pver + 1.
					const int top = this->m_pcols * (this->m_pver + 1);
					this->m_pi[top] = 0.0;
					this->m_zi[top] = 0.0;
					this->m_sfi[top] = 0.0;
#else
					// Use loop blocking.
					// Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)

					for (int i{ 0 }; i < m_pcols; i += DEFAULT_BLOCK_SIZE) {
						for (int j{ 0 }; j < m_pver; j += DEFAULT_BLOCK_SIZE) {
							for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif

								for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
									this->m_qt[ii + m_pcols * jj] = 0.0;
									this->m_ql[ii + m_pcols * jj] = 0.0;
									this->m_sl[ii + m_pcols * jj] = 0.0;
									this->m_pi[ii + m_pcols * jj] = 0.0;
									this->m_pm[ii + m_pcols * jj] = 0.0;
									this->m_zi[ii + m_pcols * jj] = 0.0;
									this->m_cld[ii + m_pcols * jj] = 0.0;
									this->m_sfi[ii + m_pcols * jj] = 0.0;
									this->m_sfuh[ii + m_pcols * jj] = 0.0;
									this->m_sflh[ii + m_pcols * jj] = 0.0;
									this->m_slslope[ii + m_pcols * jj] = 0.0;
									this->m_qtslope[ii + m_pcols * jj] = 0.0;
								}
							}
						}
					}
#endif
					// Copy top element == 0.0 to arrays 2D 
					// where m_pver == m_pver + 1.
					const int top = this->m_pcols * (this->m_pver + 1);
					this->m_pi[top] = 0.0;
					this->m_zi[top] = 0.0;
					this->m_sfi[top] = 0.0;
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
			Wrap_Sfdiag(_In_ const I32 pcols,
						_In_ const I32 pver,
				        _In_ const I32 ncol,
				        _In_ const I32 qsat,
				        _In_ R64* __restrict const qt,
				        _In_ R64* __restrict const ql,
				        _In_ R64* __restrict const sl,
				        _In_ R64* __restrict const pi,
				        _In_ R64* __restrict const pm,
				        _In_ R64* __restrict const zi,
				        _In_ R64* __restrict const cld,
				        _In_ R64* __restrict const slslope,
				        _In_ R64* __restrict const qtslope)
				         :
				    m_pcols{ pcols },
				    m_pver{ pver },
				    m_ncol{ ncol },
				    m_qsat{ qsat },
				    m_qt{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_sl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_pm{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_cld{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				    m_sfuh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_sflh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				    m_slslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					m_qtslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) } {

				// Check for memory allocation errors (malloc failures).
				for (int i{ 0 }; i != this->m_nArrays; ++i) {
					if ((&this->m_qt)[i] == NULL) {
						std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor Wrap_Sfdiag!!\n";
						std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
						std::cerr << "***** ERROR-DETAILS ***** \n";
						std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_qt)[i] << "\n";
						std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
						std::exit(-1);
					}
				}
				// Check input arrays for existance of NULL pointers.
				if (qt      == NULL ||
					ql      == NULL ||
					sl      == NULL ||
					pi      == NULL ||
					pm      == NULL ||
					zi      == NULL ||
					cld     == NULL ||
					slslope == NULL ||
					qtslope == NULL) {

					std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor Wrap_Sfdiag!!\n";
					std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
					std::cerr << "***** ERROR-DETAILS ***** \n";
					std::cerr << "One or more caller's arrays contains invalid pointer!!\n";
					std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
					std::exit(-1);
				}
				// Copy input arrays and zero-initialize output arrays.
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_pcols * m_pver) >= (1 << 20))
				for (int i{ 0 }; i != this->m_m_pcols; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
					for (int j { 0 }; j != this->m_pver;  ++j) {
						this->m_qt[i + m_pcols * j] = qt[i + m_pcols * j];
						this->m_ql[i + m_pcols * j] = ql[i + m_pcols * j];
						this->m_sl[i + m_pcols * j] = sl[i + m_pcols * j];
						this->m_pi[i + m_pcols * j] = pi[i + m_pcols * j];
						this->m_pm[i + m_pcols * j] = pm[i + m_pcols * j];
						this->m_zi[i + m_pcols * j] = zi[i + m_pcols * j];
						this->m_cld[i + m_pcols * j] = cld[i + m_pcols * j];
						this->m_sfi[i + m_pcols * j] = 0.0;
						this->m_sfuh[i + m_pcols * j] = 0.0;
						this->m_sflh[i + m_pcols * j] = 0.0;
						this->m_slslope[i + m_pcols * j] = slslope[i + m_pcols * j];
						this->m_qtslope[i + m_pcols * j] = qtslope[i + m_pcols * j];
					}
				}
				// Copy top element from caller's input arrays to arrays 2D 
				// where m_pver == m_pver + 1.
				const int top = this->m_pcols * (this->m_pver + 1);
				this->m_pi[top] = pi[top];
				this->m_zi[top] = zi[top];
				this->m_sfi[top] = 0.0;

#else
				// Use loop blocking.
				// Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)

				for (int i{ 0 }; i < m_pcols; i += DEFAULT_BLOCK_SIZE) {
					for (int j{ 0 }; j < m_pver; j += DEFAULT_BLOCK_SIZE) {
						for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif

							for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
								this->m_qt[ii + m_pcols * jj] = qt[ii + m_pcols * jj];
								this->m_ql[ii + m_pcols * jj] = ql[ii + m_pcols * jj];
								this->m_sl[ii + m_pcols * jj] = sl[ii + m_pcols * jj];
								this->m_pi[ii + m_pcols * jj] = pi[ii + m_pcols * jj];
								this->m_pm[ii + m_pcols * jj] = pm[ii + m_pcols * jj];
								this->m_zi[ii + m_pcols * jj] = zi[ii + m_pcols * jj];
								this->m_cld[ii + m_pcols * jj] = cld[ii + m_pcols * jj];
								this->m_sfi[ii + m_pcols * jj] = 0.0;
								this->m_sfuh[ii + m_pcols * jj] = 0.0;
								this->m_sflh[ii + m_pcols * jj] = 0.0;
								this->m_slslope[ii + m_pcols * jj] = slslope[ii + m_pcols * jj];
								this->m_qtslope[ii + m_pcols * jj] = qtslope[ii + m_pcols * jj];
							}
						}
					}
				}
#endif
				// Copy top element from caller's input arrays to arrays 2D 
				// where m_pver == m_pver + 1.
				const int top = this->m_pcols * (this->m_pver + 1);
				this->m_pi[top] = pi[top];
				this->m_zi[top] = zi[top];
				this->m_sfi[top] = 0.0;


#endif




			}

					/*
					  @Purpose:
								Copy Constructor implements deep copy semantics.
					*/
			Wrap_Sfdiag(_In_ const Wrap_Sfdiag &x)
				        :
				     m_pcols{ x.m_pcols },
				     m_pver{ x.m_pver },
				     m_ncol{ x.m_ncol },
				     m_qsat{ x.m_qsat },
				     m_qt{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				     m_ql{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				     m_sl{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				     m_pi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				     m_pm{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				     m_zi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				     m_cld{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				     m_sfi{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B)) },
				     m_sfuh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				     m_sflh{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
				     m_slslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) },
					 m_qtslope{ reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)), align32B)) } {

				// Check for memory allocation error (malloc failures)
				for (int i{ 0 }; i != this->m_nArrays; ++i) {
					if ((&this->m_qt)[i] == NULL) {
						std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor Wrap_Sfdiag!!\n";
						std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
						std::cerr << "***** ERROR-DETAILS ***** \n";
						std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_qt)[i] << "\n";
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
					for (int j { 0 }; j != this->m_pver; ++j) {
						this->m_qt[i + m_pcols * j] = x.m_qt[i + x.m_pcols * j];
						this->m_ql[i + m_pcols * j] = x.m_ql[i + x.m_pcols * j];
						this->m_sl[i + m_pcols * j] = x.m_sl[i + x.m_pcols * j];
						this->m_pi[i + m_pcols * j] = x.m_pi[i + x.m_pcols * j];
						this->m_pm[i + m_pcols * j] = x.m_pm[i + x.m_pcols * j];
						this->m_zi[i + m_pcols * j] = x.m_zi[i + x.m_pcols * j];
						this->m_cld[i + m_pcols * j] = x.m_cld[i + x.m_pcols * j];
						this->m_sfi[i + m_pcols * j] = x.m_sfi[i + x.m_pcols * j];
						this->m_sfuh[i + m_pcols * j] = x.m_sfuh[i + x.m_pcols * j];
						this->m_sflh[i + m_pcols * j] = x.m_sflh[i + x.m_pcols * j];
						this->m_slslope[i + m_pcols * j] = x.m_slslope[i + x.m_pcols * j];
						this->m_qtslope[i + m_pcols * j] = x.m_qtslope[i + x.m_pcols * j];
					}
				}

				// Copy top element from caller's input arrays to arrays 2D 
				// where m_pver == m_pver + 1.
				const int top = this->m_pcols * (this->m_pver + 1);
				this->m_pi[top] = x.m_pi[top];
				this->m_zi[top] = x.m_zi[top];
				this->m_sfi[top] = x.m_sfi[top];
#else

				// Use loop blocking.
				// Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)

				for (int i{ 0 }; i < m_pcols; i += DEFAULT_BLOCK_SIZE) {
					for (int j{ 0 }; j < m_pver; j += DEFAULT_BLOCK_SIZE) {
						for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif

							for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
								this->m_qt[ii + m_pcols * jj] = x.m_qt[ii + x.m_pcols * jj];
								this->m_ql[ii + m_pcols * jj] = x.m_ql[ii + x.m_pcols * jj];
								this->m_sl[ii + m_pcols * jj] = x.m_sl[ii + x.m_pcols * jj];
								this->m_pi[ii + m_pcols * jj] = x.m_pi[ii + x.m_pcols * jj];
								this->m_pm[ii + m_pcols * jj] = x.m_pm[ii + x.m_pcols * jj];
								this->m_zi[ii + m_pcols * jj] = x.m_zi[ii + x.m_pcols * jj];
								this->m_cld[ii + m_pcols * jj] = x.m_cld[ii + x.m_pcols * jj];
								this->m_sfi[ii + m_pcols * jj] = x.m_sfi[ii + x.m_pcols * jj];
								this->m_sfuh[ii + m_pcols * jj] = x.m_sfuh[ii + x.m_pcols * jj];
								this->m_sflh[ii + m_pcols * jj] = x.m_sflh[ii + x.m_pcols * jj];
								this->m_slslope[ii + m_pcols * jj] = x.m_slslope[ii + x.m_pcols * jj];
								this->m_qtslope[ii + m_pcols * jj] = x.m_qtslope[ii + x.m_pcols * jj];
							}
						}
					}
				}
#endif
				// Copy top element from caller's input arrays to arrays 2D 
				// where m_pver == m_pver + 1.
				const int top = this->m_pcols * (this->m_pver + 1);
				this->m_pi[top] = x.m_pi[top];
				this->m_zi[top] = x.m_zi[top];
				this->m_sfi[top] = x.m_sfi[top];
#endif


			}

					 /*
						@Purpose:
								 Move Constructor implements shallow copy semantics.
					 */
					 Wrap_Sfdiag(_In_ Wrap_Sfdiag &&x)
						         :
						    m_pcols{ x.m_pcols },
						    m_pver{ x.m_pver },
						    m_ncol{ x.m_ncol },
							m_qsat{ x.m_qsat } {

						 // Assign *this pointers to x's pointers.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&this->m_qt)[i] = (&x.m_qt)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&x.m_qt)[i] = NULL;
						 }
						 x.m_pcols = 0;
						 x.m_pver = 0;
			}

					 /*
						@Purpose:
								  Class Destructor.
					 */
					 ~Wrap_Sfdiag() {

						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_qt)[i]) {
								 _mm_free((&this->m_qt)[i]);
							 }
						 }
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&this->m_qt)[i] = NULL;
						 }
						 this->m_pcols = 0;
						 this->m_pver = 0;
					 }

					 /*
						@Purpose:
								 Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Sfdiag & operator=(_In_ const Wrap_Sfdiag &x) {
						 if (this == &x) return (*this);

						 this->m_pcols = x.m_pcols;
						 this->m_pver = x.m_pver;
						 this->m_ncol = x.m_ncol;
						 this->m_qsat = x.m_qsat;
						 constexpr int ntPtrs2D{9};
						 R64  *tPtrs2D[ntPtrs2D] = {};
						 for (int i{ 0 }; i != ntPtrs2D; ++i) {
							 tPtrs2D[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * m_pver * sizeof(R64)),align32B));
						 }
						 for (int i{ 0 }; i != ntPtrs2D; ++i) {
							 if (tPtrs2D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator Wrap_Sfdiag!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs2D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
						 constexpr int ntPtrs2Dp1{3};
						 R64  *tPtrs2Dp1[ntPtrs2Dp1] = {};
						 for (int i{ 0 }; i != ntPtrs2Dp1; ++i) {
							 tPtrs2Dp1[i] = reinterpret_cast<R64*>(_mm_malloc((m_pcols * (m_pver + 1) * sizeof(R64)), align32B));
						 }
						 for (int i{ 0 }; i != ntPtrs2Dp1; ++i) {
							 if (tPtrs2Dp1[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator Wrap_Sfdiag!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs2Dp1[i] << "\n";
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
								 tPtrs2D[0][i + m_pcols * j] = x.m_qt[i + x.m_pcols * j];
								 tPtrs2D[1][i + m_pcols * j] = x.m_ql[i + x.m_pcols * j];
								 tPtrs2D[2][i + m_pcols * j] = x.m_sl[i + x.m_pcols * j];
								 tPtrs2Dp1[0][i + m_pcols * j] = x.m_pi[i + x.m_pcols * j];
								 tPtrs2D[3][i + m_pcols * j] = x.m_pm[i + x.m_pcols * j];
								 tPtrs2Dp1[1][i + m_pcols * j] = x.m_zi[i + x.m_pcols * j];
								 tPtrs2D[4][i + m_pcols * j] = x.m_cld[i + x.m_pcols * j];
								 tPtrs2Dp1[2][i + m_pcols * j] = x.m_sfi[i + x.m_pcols * j];
								 tPtrs2D[5][i + m_pcols * j] = x.m_sfuh[i + x.m_pcols * j];
								 tPtrs2D[6][i + m_pcols * j] = x.m_sflh[i + x.m_pcols * j];
								 tPtrs2D[7][i + m_pcols * j] = x.m_slslope[i + x.m_pcols * j];
								 tPtrs2D[8][i + m_pcols * j] = x.m_qtslope[i + x.m_pcols * j];
							 }
						 }
						 const int top = this->m_pcols * (this->m_pver + 1);
						 tPtrs2Dp1[0][top] = x.m_pi[top];
						 tPtrs2Dp1[1][top] = x.m_zi[top];
						 tPtrs2Dp1[2][top] = x.m_sfi[top];
						 // Deallocate current state.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 _mm_free((&this->m_qt)[i]);
						 }
						 // Copy temporary pointers to *this.
						 this->m_qt = tPtrs2D[0];
						 this->m_ql = tPtrs2D[1];
						 this->m_sl = tPtrs2D[2];
						 this->m_pi = tPtrs2Dp1[0];
						 this->m_pm = tPtrs2D[3];
						 this->m_zi = tPtrs2Dp1[1];
						 this->m_cld = tPtrs2D[4];
						 this->m_sfi = tPtrs2Dp1[2];
						 this->m_sfuh = tPtrs2D[5];
						 this->m_sflh = tPtrs2D[6];
						 this->m_slslope = tPtrs2D[7];
						 this->m_qtslope = tPtrs2D[8];

						 return (*this);
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
										 tPtrs2D[0][ii + m_pcols * jj] = x.m_qt[ii + x.m_pcols * jj];
										 tPtrs2D[1][ii + m_pcols * jj] = x.m_ql[ii + x.m_pcols * jj];
										 tPtrs2D[2][ii + m_pcols * jj] = x.m_sl[ii + x.m_pcols * jj];
										 tPtrs2Dp1[0][ii + m_pcols * jj] = x.m_pi[ii + x.m_pcols * jj];
										 tPtrs2D[3][ii + m_pcols * jj] = x.m_pm[ii + x.m_pcols * jj];
										 tPtrs2Dp1[1][ii + m_pcols * jj] = x.m_zi[ii + x.m_pcols * jj];
										 tPtrs2D[4][ii + m_pcols * jj] = x.m_cld[ii + x.m_pcols * jj];
										 tPtrs2Dp1[2][ii + m_pcols * jj] = x.m_sfi[ii + x.m_pcols * jj];
										 tPtrs2D[5][ii + m_pcols * jj] = x.m_sfuh[ii + x.m_pcols * jj];
										 tPtrs2D[6][ii + m_pcols * jj] = x.m_sflh[ii + x.m_pcols * jj];
										 tPtrs2D[7][ii + m_pcols * jj] = x.m_slslope[ii + x.m_pcols * jj];
										 tPtrs2D[8][ii + m_pcols * jj] = x.m_qtslope[ii + x.m_pcols * jj];
									 }
								 }
							 }
						 }


#endif
						 const int top = this->m_pcols * (this->m_pver + 1);
						 tPtrs2Dp1[0][top] = x.m_pi[top];
						 tPtrs2Dp1[1][top] = x.m_zi[top];
						 tPtrs2Dp1[2][top] = x.m_sfi[top];
						 // Deallocate current state.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 _mm_free((&this->m_qt)[i]);
						 }
						 // Copy temporary pointers to *this.
						 this->m_qt = tPtrs2D[0];
						 this->m_ql = tPtrs2D[1];
						 this->m_sl = tPtrs2D[2];
						 this->m_pi = tPtrs2Dp1[0];
						 this->m_pm = tPtrs2D[3];
						 this->m_zi = tPtrs2Dp1[1];
						 this->m_cld = tPtrs2D[4];
						 this->m_sfi = tPtrs2Dp1[2];
						 this->m_sfuh = tPtrs2D[5];
						 this->m_sflh = tPtrs2D[6];
						 this->m_slslope = tPtrs2D[7];
						 this->m_qtslope = tPtrs2D[8];

						 return (*this);
#endif


			 }


			     /*
					@Purpose:
								Move Operator implements shallow copy semantics.
			      */
					 Wrap_Sfdiag & operator=(_In_ Wrap_Sfdiag &&x) {
						 if (this == &x) return (*this);

						 this->m_pcols = x.m_pcols;
						 this->m_pver = x.m_pver;
						 this->m_ncol = x.m_ncol;
						 this->m_qsat = x.m_qsat;
						 // Deallocate current state.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 if ((&this->m_qt)[i]) {
								 _mm_free((&this->m_qt)[i]);
							 }
						 }
						 //Reassign x's pointers.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&this->m_qt)[i] = (&x.m_qt)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_nArrays; ++i) {
							 (&x.m_qt)[i] = NULL;
						 }
						 x.m_pcols = 0;
						 x.m_pver = 0;
						 return (*this);
			}

					 /*
						@Purpose:
									Calls Fortran 90 'SFDIAG' subroutine.
									Warning:
											 'SFDIAG' probably will not
											 be accessible from outside eddy_diff module.
					 */
					 void  Call_SFDIAG() {

						 EDDY_DIFF_mp_SFDIAG(&this->m_cld, &this->m_pver, &this->m_ncol, &this->m_qt[0],
							 &this->m_ql[0], &this->m_sl[0], &this->m_pi[0], &this->m_pm[0], &this->m_zi[0],
							 &this->m_cld[0], &this->m_sfi[0], &this->m_sfuh[0], &this->m_sflh[0], 
							 &this->m_slslope[0], &this->m_qtslope[0], &this->m_qsat[0]);
					 }
				/*
					@Purpose:
								Member variables:
				*/
				I32 m_pcols;

				I32 m_pver;

				I32 m_ncol;

				I32 m_qsat;

_Field_size_(m_pcols * m_pver) R64* __restrict m_qt;

_Field_size_(m_pcols * m_pver) R64* __restrict m_ql;

_Field_size_(m_pcols * m_pver) R64* __restrict m_sl;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_pi;

_Field_size_(m_pcols * m_pver)  R64* __restrict m_pm;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_zi;

_Field_size_(m_pcols * m_pver) R64* __restrict m_cld;

_Field_size_(m_pcols * m_pver + 1) R64* __restrict m_sfi;

_Field_size_(m_pcols * m_pver) R64* __restrict m_sfuh;

_Field_size_(m_pcols * m_pver) R64* __restrict m_sflh;

_Field_size_(m_pcols * m_pver) R64* __restrict m_slslope;

_Field_size_(m_pcols * m_pver) R64* __restrict m_qtslope;

								static const int m_nArrays = 12;

								static const int m_nArrays2D = 9;

								static const int m_nArrays2Dp1 = 3;
				
			};



	}
}



#endif /*__EDDY_DIFF_SFDIAG_IMPL_H__*/