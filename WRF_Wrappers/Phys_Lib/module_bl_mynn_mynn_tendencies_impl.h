#ifndef __MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_H__
#define __MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_H__

// File granularity version.
#ifndef MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_VERSION_MINOR
#define MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_CREATE_DATE "Date: 13-11-2016 , Time: 11:18 AM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_AUTHOR
#define MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"


namespace wrf_phys_wrappers {
	namespace module_bl_mynn {


		template<typename R32 = float,
			     typename I32 = int >  struct  Wrap_Mynn_Tendencies {


					 /****************************************
						    Constructors and Destructor.
					 *****************************************/

					 /*
						@Purpose:
									Default Constructor - explicitly default.
					 */
					 Wrap_Mynn_Tendencies() = default;

					 /*
						@Purpose:
									1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
					 */
					 Wrap_Mynn_Tendencies(_In_ const I32 kts,
						 _In_ const I32 kte,
						 _In_ const I32 grav_settling,
						 _In_ const I32 levflag,
						 _In_ const I32 bl_mynn_cloudmix,
						 _In_ const I32 bl_mynn_mixqt,
						 _In_ const I32 bl_mynn_edmf,
						 _In_ const I32 bl_mynn_edmf_mom,
						 _In_ const I32 FLAG_QI,
						 _In_ const I32 FLAG_QNI,
						 _In_ const I32 FLAG_QC,
						 _In_ const I32 FLAG_QNC,
						 _In_ const R32 delt,
						 _In_ const R32 ust,
						 _In_ const R32 flt,
						 _In_ const R32 flq,
						 _In_ const R32 flqv,
						 _In_ const R32 flqc,
						 _In_ const R32 wspd,
						 _In_ const R32 uoce,
						 _In_ const R32 voce,
						 _In_ const R32 qcg,
						 _In_ const R32 vdfg1)
						 :
					     m_kts{ kts },
						 m_kte{ kte },
						 m_grav_settling{ grav_settling },
						 m_levflag{ levflag },
						 m_bl_mynn_cloudmix{ bl_mynn_cloudmix },
						 m_bl_mynn_mixqt{ bl_mynn_mixqt },
						 m_bl_mynn_edmf{ bl_mynn_edmf },
						 m_bl_mynn_edmf_mom{ bl_mynn_edmf_mom },
						 m_FLAG_QI{ FLAG_QI },
						 m_FLAG_QNI{ FLAG_QNI },
						 m_FLAG_QC{ FLAG_QC },
						 m_FLAG_QNC{ FLAG_QNC },
						 m_delt{ delt },
						 m_ust{ ust },
						 m_flt{ flt },
						 m_flq{ flq },
						 m_flqv{ flqv },
						 m_flqc{ flqc },
						 m_wspd{ wspd },
						 m_uoce{ uoce },
						 m_voce{ voce },
						 m_qcg{ qcg },
						 m_vdfg1{ vdfg1 },
						 m_s_aw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_s_awthl{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_s_awqt{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_s_awqv{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_s_awqc{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_s_awu{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_s_awv{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
						 m_u{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_v{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_th{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_tk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_qv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_qc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_qi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_qni{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_qnc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_p{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_tcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_qcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_sqw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_sqv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_sqc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_sqi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_du{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dth{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dqv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dqc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dqi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
						 m_dqni{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 if (0 > (m_kte - m_kts)) {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 1st Ctor: 'Wrap_Mynn_Tendencies'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Lower range value m_kts: " << m_kts << "\n";
							 std::cerr << "Upper range value m_kte: " << m_kte << "\n";
							 std::cerr << "Range value difference: " << m_kte - m_kts << "\n";
							 std::cerr << "Cannot recover --> calling exit(-1)!!\n";
							 std::exit(-1);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_s_aw)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Mynn_Tendencies'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_s_aw)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }

#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kte >= (1 << 16))
						 for (int idx = 0; i < this->m_totArrays; ++idx) {


#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_s_aw)[idx][i] = 0.f;
							 }
						 }
						 const int top = m_kte + 1;
						 (&this->m_s_aw)[0][top] = 0.f;
						 (&this->m_s_aw)[1][top] = 0.f;
						 (&this->m_s_aw)[2][top] = 0.f;
						 (&this->m_s_aw)[3][top] = 0.f;
						 (&this->m_s_aw)[4][top] = 0.f;
						 (&this->m_s_aw)[5][top] = 0.f;
						 (&this->m_s_aw)[6][top] = 0.f;



#else
				// You must not #undef 'USE_AUTO_VECTORIZATION' macro!!
#if defined (USE_AUTO_VECTORIZATION)
						 for (int idx = 0; i < this->m_totArrays; ++idx) {

#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)

							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_s_aw)[idx][i] = 0.f;
							 }
						 }
#endif
						 const int top = m_kte + 1;
						 (&this->m_s_aw)[0][top] = 0.f;
						 (&this->m_s_aw)[1][top] = 0.f;
						 (&this->m_s_aw)[2][top] = 0.f;
						 (&this->m_s_aw)[3][top] = 0.f;
						 (&this->m_s_aw)[4][top] = 0.f;
						 (&this->m_s_aw)[5][top] = 0.f;
						 (&this->m_s_aw)[6][top] = 0.f;
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
						 Wrap_Mynn_Tendencies(_In_ const I32 kts,
							 _In_ const I32 kte,
							 _In_ const I32 grav_settling,
							 _In_ const I32 levflag,
							 _In_ const I32 bl_mynn_cloudmix,
							 _In_ const I32 bl_mynn_mixqt,
							 _In_ const I32 bl_mynn_edmf,
							 _In_ const I32 bl_mynn_edmf_mom,
							 _In_ const I32 FLAG_QI,
							 _In_ const I32 FLAG_QNI,
							 _In_ const I32 FLAG_QC,
							 _In_ const I32 FLAG_QNC,
							 _In_ const R32 delt,
							 _In_ const R32 ust,
							 _In_ const R32 flt,
							 _In_ const R32 flq,
							 _In_ const R32 flqv,
							 _In_ const R32 flqc,
							 _In_ const R32 wspd,
							 _In_ const R32 uoce,
							 _In_ const R32 voce,
							 _In_ const R32 qcg,
							 _In_ const R32 vdfg1,
							 _In_ R32* __restrict const s_aw,
							 _In_ R32* __restrict const s_awthl,
							 _In_ R32* __restrict const s_awqt,
							 _In_ R32* __restrict const s_awqv,
							 _In_ R32* __restrict const s_awqc,
							 _In_ R32* __restrict const s_awu,
							 _In_ R32* __restrict const s_awv,
							 _In_ R32* __restrict const u,
							 _In_ R32* __restrict const v,
							 _In_ R32* __restrict const th,
							 _In_ R32* __restrict const tk,
							 _In_ R32* __restrict const qv,
							 _In_ R32* __restrict const qc,
							 _In_ R32* __restrict const qi,
							 _In_ R32* __restrict const qni,
							 _In_ R32* __restrict const qnc,
							 _In_ R32* __restrict const p,
							 _In_ R32* __restrict const exner,
							 _In_ R32* __restrict const dfq,
							 _In_ R32* __restrict const dz,
							 _In_ R32* __restrict const tsq,
							 _In_ R32* __restrict const qsq,
							 _In_ R32* __restrict const cov,
							 _In_ R32* __restrict const tcd,
							 _In_ R32* __restrict const qcd,
							 _In_ R32* __restrict const cldfra_bl1D,
							 _In_ R32* __restrict const thl,
							 _In_ R32* __restrict const sqw,
							 _In_ R32* __restrict const sqv,
							 _In_ R32* __restrict const sqc,
							 _In_ R32* __restrict const sqi,
							 _In_ R32* __restrict const dfm,
							 _In_ R32* __restrict const dfh,
							 _In_ R32* __restrict const du,
							 _In_ R32* __restrict const dv,
							 _In_ R32* __restrict const dth,
							 _In_ R32* __restrict const dqv,
							 _In_ R32* __restrict const dqc,
							 _In_ R32* __restrict const dqi,
							 _In_ R32* __restrict const dqni)
							 :
							 m_kts{ kts },
							 m_kte{ kte },
							 m_grav_settling{ grav_settling },
							 m_levflag{ levflag },
							 m_bl_mynn_cloudmix{ bl_mynn_cloudmix },
							 m_bl_mynn_mixqt{ bl_mynn_mixqt },
							 m_bl_mynn_edmf{ bl_mynn_edmf },
							 m_bl_mynn_edmf_mom{ bl_mynn_edmf_mom },
							 m_FLAG_QI{ FLAG_QI },
							 m_FLAG_QNI{ FLAG_QNI },
							 m_FLAG_QC{ FLAG_QC },
							 m_FLAG_QNC{ FLAG_QNC },
							 m_delt{ delt },
							 m_ust{ ust },
							 m_flt{ flt },
							 m_flq{ flq },
							 m_flqv{ flqv },
							 m_flqc{ flqc },
							 m_wspd{ wspd },
							 m_uoce{ uoce },
							 m_voce{ voce },
							 m_qcg{ qcg },
							 m_vdfg1{ vdfg1 },
							 m_s_aw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
							 m_s_awthl{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
							 m_s_awqt{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
							 m_s_awqv{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
							 m_s_awqc{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
							 m_s_awu{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
							 m_s_awv{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
							 m_u{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_v{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_th{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_tk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_qv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_qc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_qi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_qni{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_qnc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_p{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_tcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_qcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_sqw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_sqv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_sqc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_sqi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_du{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dth{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dqv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dqc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dqi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
							 m_dqni{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

							 if (0 > (m_kte - m_kts)) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Invalid array size 2nd Ctor: 'Wrap_Mynn_Tendencies'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Lower range value m_kts: " << m_kts << "\n";
								 std::cerr << "Upper range value m_kte: " << m_kte << "\n";
								 std::cerr << "Range value difference: " << m_kte - m_kts << "\n";
								 std::cerr << "Cannot recover --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }

							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 if ((&this->m_s_aw)[i] == NULL) {
									 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mynn_Tendencies'!!\n";
									 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
									 std::cerr << "***** ERROR-DETAILS ***** \n";
									 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_s_aw)[i] << "\n";
									 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
									 std::exit(-1);
								 }
							 }

							 if (s_aw        == NULL ||
								 s_awthl     == NULL ||
								 s_awqt      == NULL ||
								 s_awqv      == NULL ||
								 s_awqc      == NULL ||
								 s_awu       == NULL ||
								 s_awv       == NULL ||
								 u           == NULL ||
								 v           == NULL ||
								 th          == NULL ||
								 tk          == NULL ||
								 qv          == NULL ||
								 qc          == NULL ||
								 qi          == NULL ||
								 qni         == NULL ||
								 qnc         == NULL ||
								 p           == NULL ||
								 exner       == NULL ||
								 dfq         == NULL ||
								 dz          == NULL ||
								 tsq         == NULL ||
								 qsq         == NULL ||
								 cov         == NULL ||
								 tcd         == NULL ||
								 qcd         == NULL ||
								 cldfra_bl1D == NULL ||
								 thl         == NULL ||
								 sqw         == NULL ||
								 sqv         == NULL ||
								 sqc         == NULL ||
								 sqi         == NULL ||
								 dfm         == NULL ||
								 dfh         == NULL ||
								 du          == NULL ||
								 dv          == NULL ||
								 dth         == NULL ||
								 dqv         == NULL ||
								 dqc         == NULL ||
								 dqi         == NULL ||
								 dqni                ) {

								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mynn_Tendencies'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "One or more caller's arrays contains invalid pointer!!\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }

#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kte >= (1 << 16))
							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 m_s_aw[i] = s_aw[i];
								 m_s_awthl[i] = s_awthl[i];
								 m_s_awqt[i] = s_awqt[i];
								 m_s_awqv[i] = s_awqv[i];
								 m_s_awqc[i] = s_awqc[i];
								 m_s_awu[i] = s_awu[i];
								 m_s_awv[i] = s_awv[i];
								 m_u[i] = u[i];
								 m_v[i] = v[i];
								 m_th[i] = th[i];
								 m_tk[i] = tk[i];
								 m_qv[i] = qv[i];
								 m_qc[i] = qc[i];
								 m_qi[i] = qi[i];
								 m_qni[i] = qni[i];
								 m_qnc[i] = qnc[i];
								 m_p[i] = p[i];
								 m_exner[i] = exner[i];
								 m_dfq[i] = dfq[i];
								 m_dz[i] = dz[i];
								 m_tsq[i] = tsq[i];
								 m_qsq[i] = qsq;
								 m_cov = cov[i];
								 m_tcd[i] = tcd[i];
								 m_qcd[i] = qcd[i];
								 m_cldfra_bl1D[i] = cldfra_bl1D[i];
								 m_thl[i] = thl[i];
								 m_sqw[i] = sqw[i];
								 m_sqv[i] = sqv[i];
								 m_sqc[i] = sqc[i];
								 m_sqi[i] = sqi[i];
								 m_dfm[i] = dfm[i];
								 m_dfh[i] = dfh[i];
								 m_du[i] = du[i];
								 m_dv[i] = dv[i];
								 m_dth[i] = dth[i];
								 m_dqv[i] = dqv[i];
								 m_dqc[i] = dqc[i];
								 m_dqi[i] = dqi[i];
								 m_dqni[i] = dqni[i];

							 }

							 const int top = m_kte + 1;
							 m_s_aw[top] = s_aw[top];
							 m_s_awthl[top] = s_awthl[top];
							 m_s_awqt[top] = s_awqt[top];
							 m_s_awqv[top] = s_awqv[top];
							 m_s_awqc[top] = s_awqc[top];
							 m_s_awu[top] = s_awu[top];
							 m_s_awv[top] = s_awv[top];

#else
						// You must not #undef 'USE_AUTO_VECTORIZATION' macro!
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
								 for (int i{ 0 }; i != this->m_totArrays; ++i) {
									 m_s_aw[i] = s_aw[i];
									 m_s_awthl[i] = s_awthl[i];
									 m_s_awqt[i] = s_awqt[i];
									 m_s_awqv[i] = s_awqv[i];
									 m_s_awqc[i] = s_awqc[i];
									 m_s_awu[i] = s_awu[i];
									 m_s_awv[i] = s_awv[i];
									 m_u[i] = u[i];
									 m_v[i] = v[i];
									 m_th[i] = th[i];
									 m_tk[i] = tk[i];
									 m_qv[i] = qv[i];
									 m_qc[i] = qc[i];
									 m_qi[i] = qi[i];
									 m_qni[i] = qni[i];
									 m_qnc[i] = qnc[i];
									 m_p[i] = p[i];
									 m_exner[i] = exner[i];
									 m_dfq[i] = dfq[i];
									 m_dz[i] = dz[i];
									 m_tsq[i] = tsq[i];
									 m_qsq[i] = qsq;
									 m_cov = cov[i];
									 m_tcd[i] = tcd[i];
									 m_qcd[i] = qcd[i];
									 m_cldfra_bl1D[i] = cldfra_bl1D[i];
									 m_thl[i] = thl[i];
									 m_sqw[i] = sqw[i];
									 m_sqv[i] = sqv[i];
									 m_sqc[i] = sqc[i];
									 m_sqi[i] = sqi[i];
									 m_dfm[i] = dfm[i];
									 m_dfh[i] = dfh[i];
									 m_du[i] = du[i];
									 m_dv[i] = dv[i];
									 m_dth[i] = dth[i];
									 m_dqv[i] = dqv[i];
									 m_dqc[i] = dqc[i];
									 m_dqi[i] = dqi[i];
									 m_dqni[i] = dqni[i];

								 }

								 const int top = m_kte + 1;
								 m_s_aw[top] = s_aw[top];
								 m_s_awthl[top] = s_awthl[top];
								 m_s_awqt[top] = s_awqt[top];
								 m_s_awqv[top] = s_awqv[top];
								 m_s_awqc[top] = s_awqc[top];
								 m_s_awu[top] = s_awu[top];
								 m_s_awv[top] = s_awv[top];
#endif


#endif
			}

			         /*
						@Purpose:
									Copy Constructor implements deep copy semantics.
			          */
			         Wrap_Mynn_Tendencies(_In_ const Wrap_Mynn_Tendencies &x)
				                           :
				                m_kts{ x.m_kts },
				                m_kte{ x.m_kte },
				                m_grav_settling{ x.m_grav_settling },
				                m_levflag{ x.m_levflag },
				                m_bl_mynn_cloudmix{ x.m_bl_mynn_cloudmix },
				                m_bl_mynn_mixqt{ x.m_bl_mynn_mixqt },
				                m_bl_mynn_edmf{ x.m_bl_mynn_edmf },
				                m_bl_mynn_edmf_mom{ x.m_bl_mynn_edmf_mom },
				                m_FLAG_QI{ x.m_FLAG_QI },
				                m_FLAG_QNI{ x.m_FLAG_QNI },
				                m_FLAG_QC{ x.m_FLAG_QC },
				                m_FLAG_QNC{ x.m_FLAG_QNC },
				                m_delt{ x.m_delt },
				                m_ust{ x.m_ust },
				                m_flt{ x.m_flt },
				                m_flq{ x.m_flq },
				                m_flqv{ x.m_flqv },
				                m_flqc{ x.m_flqc },
				                m_wspd{ x.m_wspd },
				                m_uoce{ x.m_uoce },
				                m_voce{ x.m_voce },
				                m_qcg{ x.m_qcg },
				                m_vdfg1{ x.m_vdfg1 },
				                m_s_aw{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                m_s_awthl{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                m_s_awqt{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                m_s_awqv{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                m_s_awqc{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                m_s_awu{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                m_s_awv{ reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1) * sizeof(R32)), align32B)) },
				                m_u{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_v{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_th{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_tk{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_qv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_qc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_qi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_qni{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_qnc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_p{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dfq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_tsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_qsq{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_cov{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_tcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_qcd{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_cldfra_bl1D{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_thl{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_sqw{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_sqv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_sqc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_sqi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dfm{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dfh{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_du{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dth{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dqv{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dqc{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
				                m_dqi{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) },
								m_dqni{ reinterpret_cast<R32*>(_mm_malloc((m_kte * sizeof(R32)), align32B)) } {

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_s_aw)[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy-Ctor: 'Wrap_Mynn_Tendencies'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_s_aw)[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
								 std::exit(-1);
							 }
						 }
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if(m_kte >= (1 << 16))
						 for (int idx = 0; idx != this->m_totArrays; ++i) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_s_aw)[idx][i] = (&x.m_s_aw)[idx][i];
							 }
						 }

						 const int top = m_kte + 1;
						 (&this->m_s_aw)[0][top] = (&x.m_s_aw)[0][top];
						 (&this->m_s_aw)[1][top] = (&x.m_s_aw)[1][top];
						 (&this->m_s_aw)[2][top] = (&x.m_s_aw)[2][top];
						 (&this->m_s_aw)[3][top] = (&x.m_s_aw)[3][top];
						 (&this->m_s_aw)[4][top] = (&x.m_s_aw)[4][top];
						 (&this->m_s_aw)[5][top] = (&x.m_s_aw)[5][top];
						 (&this->m_s_aw)[6][top] = (&x.m_s_aw)[6][top];

#else
						// You must not #undef 'USE_AUTO_VECTORIZATION' macro !!
#if defined (USE_AUTO_VECTORIZATION)
						 for (int idx = 0; idx != this->m_totArrays; ++i) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 (&this->m_s_aw)[idx][i] = (&x.m_s_aw)[idx][i];
							 }
						 }

						 const int top = m_kte + 1;
						 (&this->m_s_aw)[0][top] = (&x.m_s_aw)[0][top];
						 (&this->m_s_aw)[1][top] = (&x.m_s_aw)[1][top];
						 (&this->m_s_aw)[2][top] = (&x.m_s_aw)[2][top];
						 (&this->m_s_aw)[3][top] = (&x.m_s_aw)[3][top];
						 (&this->m_s_aw)[4][top] = (&x.m_s_aw)[4][top];
						 (&this->m_s_aw)[5][top] = (&x.m_s_aw)[5][top];
						 (&this->m_s_aw)[6][top] = (&x.m_s_aw)[6][top];




#endif



#endif
			}

					 /*
						@Purpose:
						           Move Constructor implements shallow copy semantics.
					 */
								Wrap_Mynn_Tendencies(_In_ Wrap_Mynn_Tendencies &&x)
									       :
									m_kts{ x.m_kts },
									m_kte{ x.m_kte },
									m_grav_settling{ x.m_grav_settling },
									m_levflag{ x.m_levflag },
									m_bl_mynn_cloudmix{ x.m_bl_mynn_cloudmix },
									m_bl_mynn_mixqt{ x.m_bl_mynn_mixqt },
									m_bl_mynn_edmf{ x.m_bl_mynn_edmf },
									m_bl_mynn_edmf_mom{ x.m_bl_mynn_edmf_mom },
									m_FLAG_QI{ x.m_FLAG_QI },
									m_FLAG_QNI{ x.m_FLAG_QNI },
									m_FLAG_QC{ x.m_FLAG_QC },
									m_FLAG_QNC{ x.m_FLAG_QNC },
									m_delt{ x.m_delt },
									m_ust{ x.m_ust },
									m_flt{ x.m_flt },
									m_flq{ x.m_flq },
									m_flqv{ x.m_flqv },
									m_flqc{ x.m_flqc },
									m_wspd{ x.m_wspd },
									m_uoce{ x.m_uoce },
									m_voce{ x.m_voce },
									m_qcg{ x.m_qcg },
									m_vdfg1{ x.m_vdfg1 } {

									for (int i{ 0 }; i != this->m_totArrays; ++i) {
										(&this->m_s_aw)[i] = (&x.m_s_aw)[i];
									}
									for (int i{ 0 }; i != x.m_totArrays; ++i) {
										(&x.m_s_aw)[i] = NULL;
									}
									x.m_kts = 0;
									x.m_kte = 0;
			}

					 /*
						@Purpose:
									Class Destructor.
					  */
					 ~Wrap_Mynn_Tendencies() {
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_s_aw)[i]) {
								 _mm_free((&this->m_s_aw)[i]);
							 }
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_s_aw)[i] = NULL;
						 }
						 m_kts = 0;
						 m_kte = 0;
			}

					 /*
						@Purpose:
								  Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Mynn_Tendencies & operator=(_In_ const Wrap_Mynn_Tendencies &x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 m_grav_settling = x.m_grav_settling;
						 m_levflag = x.m_levflag;
						 m_bl_mynn_cloudmix = x.m_bl_mynn_cloudmix;
						 m_bl_mynn_mixqt = x.m_bl_mynn_mixqt;
						 m_bl_mynn_edmf = x.m_bl_mynn_edmf;
						 m_bl_mynn_edmf_mom = x.m_bl_mynn_edmf_mom;
						 m_FLAG_QI = x.m_FLAG_QI;
						 m_FLAG_QNI = x.m_FLAG_QNI;
						 m_FLAG_QC = x.m_FLAG_QC;
						 m_FLAG_QNC = x.m_FLAG_QNC;
						 m_delt = x.m_delt;
						 m_ust = x.m_ust;
						 m_flt = x.m_flt;
						 m_flq = x.m_flq;
						 m_flqv = x.m_flqv;
						 m_flqc = x.m_flqc;
						 m_wspd = x.m_wspd;
						 m_uoce = x.m_uoce;
						 m_voce = x.m_voce;
						 m_qcg = x.m_qcg;
						 m_vdfg1 = x.m_vdfg1;
						 constexpr int ntPtrs1D{40};
						 R32  *tPtrs1D[ntPtrs1D] = {};
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 tPtrs1D[i] = reinterpret_cast<R32*>(_mm_malloc(((m_kte + 1)  * sizeof(R32)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if (tPtrs1D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mynn_Tendencies'!!\n";
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
								 tPtrs1D[idx][i] = (&x.m_s_aw)[idx][i];
							 }
						 }

						 const int top = m_kte + 1;
						 tPtrs1D[0][top] = x.m_s_aw[top];
						 tPtrs1D[1][top] = x.m_s_awthl[top];
						 tPtrs1D[2][top] = x.m_s_awqt[top];
						 tPtrs1D[3][top] = x.m_s_awqv[top];
						 tPtrs1D[4][top] = x.m_s_awqc[top];
						 tPtrs1D[5][top] = x.m_s_awu[top];
						 tPtrs1D[6][top] = x.m_s_awv[top];

						 for (int i {0}; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_s_aw)[i]);
						}

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_s_aw)[i] = tPtrs1D[i];
						 }

						 return (*this);
#else

#if defined (USE_AUTO_VECTORIZATION)

						 for (int idx = 0; idx != this->m_totArrays; ++idx) {
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
							 for (int i = m_kts; i != m_kte; ++i) {
								 tPtrs1D[idx][i] = (&x.m_s_aw)[idx][i];
							 }
						 }

						 const int top = m_kte + 1;
						 tPtrs1D[0][top] = x.m_s_aw[top];
						 tPtrs1D[1][top] = x.m_s_awthl[top];
						 tPtrs1D[2][top] = x.m_s_awqt[top];
						 tPtrs1D[3][top] = x.m_s_awqv[top];
						 tPtrs1D[4][top] = x.m_s_awqc[top];
						 tPtrs1D[5][top] = x.m_s_awu[top];
						 tPtrs1D[6][top] = x.m_s_awv[top];

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_s_aw)[i]);
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_s_aw)[i] = tPtrs1D[i];
						 }

						 return (*this);


#endif


#endif		
			}

					/*
						@Purpose:
									Move-assign Operator implements shallow copy semantics.
					*/
					 Wrap_Mynn_Tendencies & operator=(_In_ Wrap_Mynn_Tendencies &&x) {
						 if (this == &x) return (*this);

						 m_kts = x.m_kts;
						 m_kte = x.m_kte;
						 m_grav_settling = x.m_grav_settling;
						 m_levflag = x.m_levflag;
						 m_bl_mynn_cloudmix = x.m_bl_mynn_cloudmix;
						 m_bl_mynn_mixqt = x.m_bl_mynn_mixqt;
						 m_bl_mynn_edmf = x.m_bl_mynn_edmf;
						 m_bl_mynn_edmf_mom = x.m_bl_mynn_edmf_mom;
						 m_FLAG_QI = x.m_FLAG_QI;
						 m_FLAG_QNI = x.m_FLAG_QNI;
						 m_FLAG_QC = x.m_FLAG_QC;
						 m_FLAG_QNC = x.m_FLAG_QNC;
						 m_delt = x.m_delt;
						 m_ust = x.m_ust;
						 m_flt = x.m_flt;
						 m_flq = x.m_flq;
						 m_flqv = x.m_flqv;
						 m_flqc = x.m_flqc;
						 m_wspd = x.m_wspd;
						 m_uoce = x.m_uoce;
						 m_voce = x.m_voce;
						 m_qcg = x.m_qcg;
						 m_vdfg1 = x.m_vdfg1;

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_s_aw)[i]) {
								 _mm_free((&this->m_s_aw)[i]);
							 }
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_s_aw)[i] = (&x.m_s_aw)[i];
						 }

						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_s_aw)[i] = NULL;
						 }
						 x.m_kts = 0;
						 x.m_kte = 0;

						 return (*this);
			}

					 /*
						@Purpose:
									Call Fortran 90 'MYNN_TENDENCIES' subroutine.
					 */
					 void  Call_Mynn_Tendencies() {

						 MODULE_BL_MYNN_mp_MYNN_TENDENCIES(&this->m_kts, &this->m_kte,
															&this->m_levflag, &this->m_grav_settling,
															&this->m_delt, &this->m_dz[0],
															&this->m_u[0], &this->m_v[0], &this->m_th[0], &this->m_tk[0],
															&this->m_qv[0], &this->m_qc[0], &this->m_qi[0], &this->m_qni[0],
															&this->m_qnc[0], &this->m_p[0], &this->m_exner[0],
															&this->m_thl[0], &this->m_sqv[0], &this->m_sqc[0], &this->m_sqi[0],
															&this->m_sqw[0], &this->m_ust, &this->m_flt, &this->m_flq, &this->m_flqv,
															&this->m_flqc, &this->m_wspd, &this->m_qcg, &this->m_uoce, &this->m_voce,
															&this->m_tsq[0], &this->m_qsq[0], &this->m_cov[0],
															&this->m_tcd[0], &this->m_qcd[0], &this->m_dfm[0], &this->m_dfh[0],
															&this->m_dfq[0], &this->m_du[0], &this->m_dv[0], &this->m_dqv[0],
															&this->m_dqc[0], &this->m_dqi[0], &this->m_dqni[0], &this->m_vdfg1,
															&this->m_s_aw[0], &this->m_s_awthl[0], &this->m_s_awqt[0], &this->m_s_awqv[0],
															&this->m_s_awqc[0], &this->m_s_awu[0], &this->m_s_awv[0],
															&this->m_FLAG_QI, &this->m_FLAG_QNI, &this->m_FLAG_QC, &this->m_FLAG_QNC,
															&this->m_cldfra_bl1D[0], &this->m_bl_mynn_cloudmix,
															&this->m_bl_mynn_mixqt, &this->m_bl_mynn_edmf, &this->m_bl_mynn_edmf_mom);
					 }
					 /*
						@Purpose:
									Member variables:
					 */

					 // Scalar members!

					 I32 m_kts;

					 I32 m_kte;

					 I32 m_grav_settling;

					 I32 m_levflag;

					 I32 m_bl_mynn_cloudmix;

					 I32 m_bl_mynn_mixqt;

					 I32 m_bl_mynn_edmf;

					 I32 m_bl_mynn_edmf_mom;

					 I32 m_FLAG_QI;

					 I32 m_FLAG_QNI;

					 I32 m_FLAG_QC;

					 I32 m_FLAG_QNC;

					 R32 m_delt;

					 R32 m_ust;

					 R32 m_flt;

					 R32 m_flq;

					 R32 m_flqv;

					 R32 m_flqc;

					 R32 m_wspd;

					 R32 m_uoce;

					 R32 m_voce;

					 R32 m_qcg;

					 R32 m_vdfg1;

					 // Array 1D members!

					 // Input arrays1D

_Field_size_(m_kte + 1) R32* __restrict m_s_aw;

_Field_size_(m_kte + 1) R32* __restrict m_s_awthl;

_Field_size_(m_kte + 1) R32* __restrict m_s_awqt;

_Field_size_(m_kte + 1) R32* __restrict m_s_awqv;

_Field_size_(m_kte + 1) R32* __restrict m_s_awqc;

_Field_size_(m_kte + 1) R32* __restrict m_s_awu;

_Field_size_(m_kte + 1) R32* __restrict m_s_awv;

_Field_size_(m_kte)		R32* __restrict m_u;

_Field_size_(m_kte)     R32* __restrict m_v;

_Field_size_(m_kte)     R32* __restrict m_th;

_Field_size_(m_kte)     R32* __restrict m_tk;

_Field_size_(m_kte)		R32* __restrict m_qv;

_Field_size_(m_kte)		R32* __restrict m_qc;

_Field_size_(m_kte)		R32* __restrict m_qi;

_Field_size_(m_kte)		R32* __restrict m_qni;

_Field_size_(m_kte)		R32* __restrict m_qnc;

_Field_size_(m_kte)		R32* __restrict m_p;

_Field_size_(m_kte)		R32* __restrict m_exner;

_Field_size_(m_kte)		R32* __restrict m_dfq;

_Field_size_(m_kte)		R32* __restrict m_dz;

_Field_size_(m_kte)		R32* __restrict m_tsq;

_Field_size_(m_kte)		R32* __restrict m_qsq;

_Field_size_(m_kte)		R32* __restrict m_cov;

_Field_size_(m_kte)		R32* __restrict m_tcd;

_Field_size_(m_kte)		R32* __restrict m_qcd;

_Field_size_(m_kte)		R32* __restrict m_cldfra_bl1D;

					// Input/Output arrays 1D!

_Field_size_(m_kte)		R32* __restrict m_thl;

_Field_size_(m_kte)		R32* __restrict m_sqw;

_Field_size_(m_kte)		R32* __restrict m_sqv;

_Field_size_(m_kte)		R32* __restrict m_sqc;

_Field_size_(m_kte)		R32* __restrict m_sqi;

_Field_size_(m_kte)		R32* __restrict m_dfm;

_Field_size_(m_kte)		R32* __restrict m_dfh;

_Field_size_(m_kte)		R32* __restrict m_du;

_Field_size_(m_kte)		R32* __restrict m_dv;

_Field_size_(m_kte)		R32* __restrict m_dth;

_Field_size_(m_kte)		R32* __restrict m_dqv;

_Field_size_(m_kte)		R32* __restrict m_dqc;

_Field_size_(m_kte)		R32* __restrict m_dqi;

_Field_size_(m_kte)		R32* __restrict m_dqni;

				static const int m_totArrays = 40;
			};
















	}
}




#endif /*__MODULE_BL_MYNN_MYNN_TENDENCIES_IMPL_H__*/