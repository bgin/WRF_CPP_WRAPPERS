
#ifndef __EDDY_DIFF_INIT_EDDY_DIFF_IMPL_H__
#define __EDDY_DIFF_INIT_EDDY_DIFF_IMPL_H__

#ifndef EDDY_DIFF_INIT_EDDY_DIFF_IMPL_VERSION_MAJOR 
#define EDDY_DIFF_INIT_EDDY_DIFF_IMPL_VERSION_MAJOR 1
#endif

#ifndef EDDY_DIFF_INIT_EDDY_DIFF_IMPL_VERSION_MINOR
#define EDDY_DIFF_INIT_EDDY_DIFF_IMPL_VERSION_MINOR 0
#endif

#ifndef EDDY_DIFF_INIT_EDDY_DIFF_IMPL_PATCH_VERSION
#define EDDY_DIFF_INIT_EDDY_DIFF_IMPL_PATCH_VERSION 0
#endif

#ifndef EDDY_DIFF_INIT_EDDY_DIFF_IMPL_CREATE_DATE
#define EDDY_DIFF_INIT_EDDY_DIFF_IMPL_CREATE_DATE "Date: 19-10-2016 , Time: 15:55 PM GMT+2"
#endif

#ifndef EDDY_DIFF_INIT_EDDY_DIFF_IMPL_BUILD_DATE
#define EDDY_DIFF_INIT_EDDY_DIFF_IMPL_BUILD_DATE ""
#endif

#ifndef EDDY_DIFF_INIT_EDDY_DIFF_IMPL_AUTHOR
#define EDDY_DIFF_INIT_EDDY_DIFF_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif

#include "module_cam_bl_eddy_diff_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

namespace phys_lib_wrappers {
	namespace module_eddy_diff {



		template<typename R64 = double,
			     typename I32 = int >  struct WrapInitEddyDiff {



					 /********************************
					   Constructors and Destructor.
					 *********************************/

					 /*
						@Purpose:
						          Default Constructor - explicitly default.
					 */
					 WrapInitEddyDiff() = default;

					 /*
						@Purpose:
						         1st Main class Constructor initializes class
								 member variables.
								 Array member 'm_hypm' is null initialized, hence
								 caller must set it to reference pressure values
								 at midpoints.
					 */
					 WrapInitEddyDiff(_In_ const I32 kind,
									  _In_ const I32 pver,
						              _In_ const I32 ntop_eddy,
						              _In_ const I32 nbot_eddy,
						              _In_ const R64 gravx,
						              _In_ const R64 cpairx,
						              _In_ const R64 rairx,
						              _In_ const R64 zvirx,
						              _In_ const R64 latvapx,
						              _In_ const R64 laticex,
						              _In_ const R64 vkx)
						       :
						 m_kind{ kind },
						 m_pver{ pver },
						 m_ntop_eddy{ ntop_eddy },
						 m_nbot_eddy{ nbot_eddy },
						 m_gravx{ gravx },
						 m_cpairx{ cpairx },
						 m_rairx{ rairx },
						 m_zvirx{ zvirx },
						 m_latvapx{ latvapx },
						 m_laticex{ laticex },
						 m_hypm{ reinterpret_cast<R64*>(_mm_malloc((m_pver * sizeof(R64)),align32B)) },
						 m_vkx{ vkx } {

						 if (this->m_hypm) {
#pragma ivdep
#pragma simd
#pragma unroll(4)
							 for (int i{ 0 }; i != this->m_pver; ++i) {
								 this->m_hypm[i] = 0.0;
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor WrapInitEddyDiff!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Failure detected at  heap address: " << std::hex << "0x" << m_hypm << "\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

		 }

					 /*
						@Purpose:
									2nd Main class Constructor initializes class
								    member variables.
								    Array member 'm_hypm' is  initialized to user passer
									array argument hypm, hence
								    caller must set it to reference pressure values
								    at midpoints.
					 */
					 WrapInitEddyDiff(_In_ const I32 kind,
									  _In_ const I32 pver,
						              _In_ const I32 ntop_eddy,
						              _In_ const I32 nbot_eddy,
						              _In_ const R64 gravx,
						              _In_ const R64 cpairx,
						              _In_ const R64 rairx,
						              _In_ const R64 zvirx,
						              _In_ const R64 latvapx,
						              _In_ const R64 laticex,
						              _In_ R64* __restrict hypm,
						              _In_ const R64 vkx)
						           :
						        m_kind{ kind },
						        m_pver{ pver },
						        m_ntop_eddy{ ntop_eddy },
						        m_nbot_eddy{ nbot_eddy },
						        m_gravx{ gravx },
						        m_cpairx{ cpairx },
						        m_rairx{ rairx },
						        m_zvirx{ zvirx },
						        m_latvapx{ latvapx },
						        m_laticex{ laticex },
						        m_hypm{ reinterpret_cast<R64*>(_mm_malloc((m_pver * sizeof(R64)), align32B)) },
						        m_vkx{ vkx } {

						 if (this->m_hypm && hypm) {

#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
							 for (int i{ 0 }; i != this->m_pver; ++i) {
								 this->m_hypm[i] = hypm[i];
							 }
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor WrapInitEddyDiff!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 m_hypm == NULL ? std::cerr << " 'm_hypm' contains invalid pointer of value: " << std::hex << "0x" << m_hypm << "\n" :
								              std::cerr << " 'm_hypm' contains a valid pointer of value: " << std::hex << "0x" << m_hypm << "\n";
							 hypm == NULL ?   std::cerr << " 'hypm' contains invalid pointer of value: " << std::hex << "0x" << hypm << "\n" : 
								              std::cerr << " 'hypm' contains valid pointer of value: " << std::hex << "0x" << hypm << "\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }
		 }

					 /*
						@Purpose:
								  Copy Constructor implements deep copy semantics.
					 */
					 WrapInitEddyDiff(_In_ const WrapInitEddyDiff &x)
								:
						     m_kind{ x.m_kind },
						     m_pver{ x.m_pver },
						     m_gravx{ x.m_gravx },
						     m_cpairx{ x.m_cpairx },
						     m_rairx{ x.m_rairx },
						     m_zvirx{ x.m_zvirx },
						     m_latvapx{ x.m_latvapx },
						     m_laticex{ x.m_laticex },
						     m_ntop_eddy{ x.m_ntop_eddy },
						     m_nbot_eddy{ x.m_nbot_eddy },
						     m_hypm{ reinterpret_cast<R64*>(_mm_malloc((m_pver * sizeof(R64)), align32B)) },
						     m_vkx{ x.m_vkx } {

						 if (this->m_hypm) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(4)
							 for (int i{ 0 }; i != this->m_pver; ++i) {
								 this->m_hypm[i] = x.m_hypm[i];
							 }
#endif						

						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Ctor WrapInitEddyDiff!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Failure detected at  heap address: " << std::hex << "0x" << m_hypm << "\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }
		  }

					 /*
						@Purpose:
								 Move Constructor implements shallow copy semantics.
					 */
					 WrapInitEddyDiff(_In_ WrapInitEddyDiff &&x)
								:
						    m_kind{ x.m_kind },
						    m_pver{ x.m_pver },
						    m_gravx{ x.m_gravx },
						    m_cpairx{ x.m_cpairx },
						    m_rairx{ x.m_rairx },
						    m_zvirx{ x.m_zvirx },
						    m_latvapx{ x.m_latvapx },
						    m_laticex{ x.m_laticex },
						    m_ntop_eddy{ x.m_ntop_eddy },
						    m_nbot_eddy{ x.m_nbot_eddy },
						    m_hypm{ x.m_hypm },
						    m_vkx{ x.m_vkx } {

							x.m_hypm = NULL;
							x.m_pver = 0;
		 }

					 /*
						@Purpose:
								 Class Destructor.
					 */
					 ~WrapInitEddyDiff() {

						 if (this->m_hypm) {
							 _mm_free(this->m_hypm);
							 this->m_hypm = NULL;
							 this->m_pver = 0;

						 }
		 }

					 /*
						@Purpose:
								  Copy-assign Operator implements deep copy semantics.
					 */
					 WrapInitEddyDiff & operator=(_In_ const WrapInitEddyDiff &x) {
						 if (this == &x) return (*this);

						 this->m_kind = x.m_kind;
						 this->m_pver = x.m_pver;
						 this->m_gravx = x.m_gravx;
						 this->m_cpairx = x.m_cpairx;
						 this->m_rairx = x.m_rairx;
						 this->m_zvirx = x.m_zvirx;
						 this->m_latvapx = x.m_latvapx;
						 this->m_laticex = x.m_laticex;
						 this->m_ntop_eddy = x.m_ntop_eddy;
						 this->m_nbot_eddy = x.m_nbot_eddy;
						 R64* __restrict thypm = reinterpret_cast<R64*>(_mm_malloc((m_pver * sizeof(R64)),align32B));
						 if (thypm) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(4)
#endif
							 for (int i{ 0 }; i != this->m_pver; ++i) {
								 thypm[i] = x.m_hypm[i];
							 }
							 _mm_free(this->m_hypm);
							 this->m_hypm = thypm;

						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator WrapInitEddyDiff!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Failure detected at  heap address: " << std::hex << "0x" << m_hypm << "\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }
						 this->m_vkx = x.m_vkx;
						 return (*this);
			 }

					 /*
						@Purpose:
								 Move-assign Operator implements shallow copy semantics.
					 */
					 WrapInitEddyDiff & operator=(_In_ WrapInitEddyDiff &&x) {
						 if (this == &x) return (*this);

						 this->m_kind = x.m_kind;
						 this->m_pver = x.m_pver;
						 this->m_gravx = x.m_gravx;
						 this->m_cpairx = x.m_cpairx;
						 this->m_rairx = x.m_rairx;
						 this->m_zvirx = x.m_zvirx;
						 this->m_latvapx = x.m_latvapx;
						 this->m_laticex = x.m_laticex;
						 this->m_ntop_eddy = x.m_ntop_eddy;
						 this->m_nbot_eddy = x.m_nbot_eddy;
						 _mm_free(this->m_hypm);
						 this->m_hypm = x.m_hypm;
						 this->m_vkx = x.m_vkx;
						 x.m_hypm = NULL;
						 x.m_pver = 0;
						 return (*this);
			 }

					 /*
						@Purpose:
								 Call Fortran 90 INIT_EDDY_DIFF subroutine.
					 */
					 void  Call_InitEddyDiff() {

						 EDDY_DIFF_mp_INIT_EDDY_DIFF(&this->m_kind, &this->m_pver, &this->m_cpairx, &this->m_cpairx,
													 &this->m_rairx, &this->m_zvirx, &this->m_latvapx, &this->m_laticex,
													 &this->m_ntop_eddy, &this->m_nbot_eddy, &this->m_hypm[0], &this->m_vkx);
					 }



					 /*
					    @Purpose:
						          Member variables.
					 */
					   // Input variables.
					 I32 m_kind; // Kind of reals being passed in

					 I32 m_pver; // Number of vertical layers

					 I32 m_ntop_eddy; // Top interface level to which eddy vertical diffusivity is applied ( = 1 )

					 I32 m_nbot_eddy; // Bottom interface level to which eddy vertical diffusivity is applied ( = pver )

					 R64 m_gravx; // Acceleration of gravity

					 R64 m_cpairx; //  Specific heat of dry air

					 R64 m_rairx; // Gas constant for dry air

					 R64 m_zvirx; // rh2o/rair - 1

					 R64 m_latvapx; // Latent heat of vaporization

					 R64 m_laticex; // Latent heat of fusion

					 R64* __restrict m_hypm; // Reference pressures at midpoints

					 R64 m_vkx; // Von Karman's constant

			};
	}
}


#endif /*__EDDY_DIFF_INIT_EDDY_DIFF_IMPL_H__*/