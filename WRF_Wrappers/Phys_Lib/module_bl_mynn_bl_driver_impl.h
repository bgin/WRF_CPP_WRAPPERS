
#ifndef __MODULE_BL_MYNN_BL_DRIVER_IMPL_H__
#define __MODULE_BL_MYNN_BL_DRIVER_IMPL_H__

// File granularity version.
#ifndef MODULE_BL_MYNN_BL_DRIVER_IMPL_VERSION_MAJOR
#define MODULE_BL_MYNN_BL_DRIVER_IMPL_VERSION_MAJOR 1
#endif

#ifndef MODULE_BL_MYNN_BL_DRIVER_IMPL_VERSION_MINOR
#define MODULE_BL_MYNN_BL_DRIVER_IMPL_VERSION_MINOR 0
#endif

#ifndef MODULE_BL_MYNN_BL_DRIVER_IMPL_PATCH_VERSION
#define MODULE_BL_MYNN_BL_DRIVER_IMPL_PATCH_VERSION 0
#endif

#ifndef MODULE_BL_MYNN_BL_DRIVER_IMPL_CREATE_DATE
#define MODULE_BL_MYNN_BL_DRIVER_IMPL_CREATE_DATE "Date: 02-11-2016 , Time: 11:20 AM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_BL_MYNN_BL_DRIVER_IMPL_BUILD_DATE
#define MODULE_BL_MYNN_BL_DRIVER_IMPL_BUILD_DATE ""
#endif

#ifndef MODULE_BL_MYNN_BL_DRIVER_IMPL_AUTHOR
#define MODULE_BL_MYNN_BL_DRIVER_IMPL_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif

#include "module_bl_mynn_F90_iface.h"
#include "PhysLib_Config.h"
#include "std_headers.h"

// In accordance to F90 source where this macro is set to 1
#define WRF_CHEM 1

namespace  phys_lib_wrappers {
	namespace    module_bl_mynn {


		template<typename R32 = float,
			typename I32 = int   >   struct Wrap_Mynn_Bl_Driver {


				/**************************************
					  Constructors and Destructor.
				***************************************/

				/*
					@Purpose:
								Default Constructor - explicitly default.
				*/

				     Wrap_Mynn_Bl_Driver() = default;


			    /*
					@Purpose:
									1st 'main' Constructor which purpose
								    is to allocate and initialize scalar
								    and array members. Array members are
								    zero-filled. Caller must later initialize
								    input arrays to correct physical state.
				*/
					 Wrap_Mynn_Bl_Driver(_In_ const I32 initflag,
										 _In_ const I32 grav_settling,
										 _In_ const I32 bl_mynn_tkebudget,
										 _In_ const I32 bl_mynn_cloudpdf,
										 _In_ const I32 bl_mynn_mixlength,
										 _In_ const I32 bl_mynn_edmf,
										 _In_ const I32 bl_mynn_tkeadvect,
										 _In_ const I32 bl_mynn_edmf_mom,
										 _In_ const I32 bl_mynn_edmf_tke,
										 _In_ const I32 bl_mynn_edmf_part,
										 _In_ const I32 bl_mynn_cloudmix,
										 _In_ const I32 bl_mynn_mixqt,
										 _In_ const I32 icloud_bl,
										 _In_ const I32 FLAG_QI,
										 _In_ const I32 FLAG_QNI,
										 _In_ const I32 FLAG_QC,
										 _In_ const I32 FLAG_QNC,
										 _In_ const I32 IDS,
										 _In_ const I32 IDE,
										 _In_ const I32 JDS,
										 _In_ const I32 JDE,
										 _In_ const I32 KDS,
										 _In_ const I32 KDE,
										 _In_ const I32 IMS,
										 _In_ const I32 IME,
										 _In_ const I32 JMS,
										 _In_ const I32 JME,
										 _In_ const I32 KMS,
										 _In_ const I32 KME,
										 _In_ const I32 ITS,
										 _In_ const I32 ITE,
										 _In_ const I32 JTS,
										 _In_ const I32 JTE,
										 _In_ const I32 KTS,
										 _In_ const I32 KTE,
#if WRF_CHEM == 1										 
										 _In_ const I32 nchem,
										 _In_ const I32 kdvel,
										 _In_ const I32 ndvel,
										 _In_ const I32 num_vert_mix,
										
#endif                                                           
										 _In_ const R32 delt,
										 _In_ const R32 dx
																)
												:
					                  m_initflag{ initflag },
									  m_grav_settling{ grav_settling },
									  m_bl_mynn_tkebudget{ bl_mynn_tkebudget },
									  m_bl_mynn_cloudpdf{ bl_mynn_cloudpdf },
									  m_bl_mynn_mixlength{ bl_mynn_mixlength },
									  m_bl_mynn_edmf{ bl_mynn_edmf },
									  m_bl_mynn_tkeadvect{ bl_mynn_tkeadvect },
									  m_bl_mynn_edmf_mon{ bl_mynn_edmf_mom },
									  m_bl_mynn_edmf_tke{ bl_mynn_edmf_tke },
									  m_bl_mynn_edmf_part{ bl_mynn_edmf_part },
									  m_bl_mynn_cloudmix{ bl_mynn_cloudmix },
									  m_bl_mynn_mixqt{ bl_mynn_mixqt },
									  m_icloud_bl{ icloud_bl },
									  m_FLAG_QI{ FLAG_QI },
									  m_FLAG_QNI{ FLAG_QNI },
									  m_FLAG_QC{ FLAG_QC },
									  m_FLAG_QNC{FLAG_QNC},
									  m_IDS{ IDS },
									  m_IDE{ IDE },
									  m_JDS{ JDS },
									  m_JDE{ JDE },
									  m_KDS{ KDS },
									  m_KDE{ KDE },
									  m_IMS{ IMS },
									  m_IME{ IME },
									  m_JMS{ JMS },
									  m_JME{ JME },
									  m_KMS{ KMS },
									  m_KME{ KME },
									  m_ITS{ ITS },
									  m_ITE{ ITE },
									  m_JTS{ JTS },
									  m_JTE{ JTE },
									  m_KTS{ KTS },
									  m_KTE{ KTE },
#if WRF_CHEM == 1
									  m_nchem{ nchem },
									  m_kdvel{ kdvel },
									  m_ndvel{ ndvel },
									  m_num_vert_mix{ num_vert_mix },
									 
#endif
									  m_delt{ delt },
									  m_dx{ dx },
									  m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_u{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_v{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_w{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_th{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qv{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_p{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_rho{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_T3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qi{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qni{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qnc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_xland{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_ust{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_ch{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_rmol{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_ts{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_qsfc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_qcg{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_ps{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_hfx{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_qfx{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_wspd{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_uoce{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_voce{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_vdfg{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_znt{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_Qke{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_Tsq{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_Qsq{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_Cov{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_tke_pbl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qke_adv{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_RUBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_RVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_RTHBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_RQVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_RQCBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_RQIBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_RQNBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_exch_h{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_exch_m{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_edmf_a{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_edmf_w{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_edmf_qt{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_edmf_thl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_emdf_ent{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_edmf_qc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_Pblh{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_wstar{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_delta{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  
									  m_KPBL{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
									  m_el_pbl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qWT{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qSHEAR{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qBUOY{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qDISS{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_dqke{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									 
									  
									  m_Sh3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_qc_bl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									  m_cldfra_bl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
									 
#if WRF_CHEM == 1
									  m_chem3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KTE * m_JME * m_nchem * sizeof(R32)), align32B)) },
									  m_vd3d{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_kdvel * m_JME * m_ndvel * sizeof(R32)), align32B)) }
									  
#endif
									  {

										  // Check for memory allocation errors i.e. (malloc failures).
										  for (int i{ 0 }; i != this->m_totArrays; ++i) {
											  if ((&this->m_dz)[i] == NULL) {
												  std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 1st Ctor: 'Wrap_Mynn_Bl_Driver'!!\n";
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
										  // Zero-initialization of Arrays 3D.
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_IME * m_KME * m_JME) > (1 << 20))
										  for (int i = m_IMS; i != m_IME; ++i) {
											  for (int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
												  for (int j = m_JMS; j != m_JME; ++j) {
													  this->m_dz[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_u[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_v[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_w[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_th[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qv[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_p[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_exner[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_rho[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_T3D[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qc[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qi[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qni[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qnc[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_Qke[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_Tsq[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_Qsq[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_Cov[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_tke_pbl[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qke_adv[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_RUBLTEN[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_RVBLTEN[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_RTHBLTEN[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_RQVBLTEN[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_RQCBLTEN[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_RQIBLTEN[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_RQNBLTEN[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_exch_h[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_exch_m[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_edmf_a[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_edmf_w[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_edmf_qt[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_edmf_thl[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_edmf_ent[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_edmf_qc[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_el_pbl[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qWT[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qSHEAR[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qBUOY[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qDISS[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_dqke[i + m_IME * k + m_KME * j] = 0.0;
													 
													  this->m_Sh3D[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_qc_bl[i + m_IME * k + m_KME * j] = 0.0;
													  this->m_cldfra_bl[i + m_IME * k + m_KME * j] = 0.0;
												  }
											  }
										  }
#if WRF_CHEM == 1
										  for (int i = m_IMS; i != m_IME; ++i) {
											  for (int k = m_KMS; k != m_KME; ++k) {
												  for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
													  for (int n = 0; n != m_nchem; ++n) {
														  this->m_chem3D[i + m_IME * k + m_KME * j + m_JME * n] = 0.0;
													  }
												  }
											  }
										  }
										  for (int i = m_IMS; i != m_IME; ++i) {
											  for (int k = 0; k != m_kdvel; ++k) {
												  for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
													  for (int n = 0; n != m_ndvel; ++n) {
														  this->m_vd3d[i + m_IME * k + m_kdvel * j + m_JME * n] = 0.0;
													  }
												  }
											  }
										  }
										  
#endif
											// Zero-initialization of Arrays 2D.
#pragma omp parallel for if((m_IME * m_JME) >= (1 << 20))
										  for (int i = m_IMS; i != m_IME; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
											  for (int j = m_JMS; j != m_JME; ++j) {
												  this->m_xland[i + m_IME * j] = 0.0;
												  this->m_ust[i + m_IME * j] = 0.0;
												  this->m_ch[i + m_IME  * j] = 0.0;
												  this->m_rmol[i + m_IME * j] = 0.0;
												  this->m_ts[i + m_IME * j] = 0.0;
												  this->m_qsfc[i + m_IME * j] = 0.0;
												  this->m_qcg[i + m_IME * j] = 0.0;
												  this->m_ps[i + m_IME * j] = 0.0;
												  this->m_hfx[i + m_IME * j] = 0.0;
												  this->m_qfx[i + m_IME * j] = 0.0;
												  this->m_wspd[i + m_IME * j] = 0.0;
												  this->m_uoce[i + m_IME * j] = 0.0;
												  this->m_voce[i + m_IME * j] = 0.0;
												  this->m_vdfg[i + m_IME * j] = 0.0;
												  this->m_znt[i + m_IME * j] = 0.0;
												  this->m_Pblh[i + m_IME * j] = 0.0;
												  this->m_wstar[i + m_IME * j] = 0.0;
												  this->m_delta[i + m_IME * j] = 0.0;
												  
												  this->m_KPBL[i + m_IME * j] = 0.0;

											  }
										  }
										  
#else
#if defined (USE_LOOP_BLOCKING)
// Use loop blocking.
// Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
									for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
										 for (int k = m_KMS; k != m_KME; k += DEFAULT_BLOCK_SIZE) {
		                                      for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
			                                       for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
				                                        for (int kk = k; kk < DEFAULT_BLOCK_SIZE; ++kk) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
					                                         for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
																  this->m_dz[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_u[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_v[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_w[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_th[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qv[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_p[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_exner[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_rho[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_T3D[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qc[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qi[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qni[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qnc[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_Qke[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_Tsq[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_Qsq[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_Cov[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_tke_pbl[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qke_adv[ii + m_IME * kk + m_KME * jj] = 0.0;
						                                          this->m_RUBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
						                                          this->m_RVBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
						                                          this->m_RTHBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
						                                          this->m_RQVBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
						                                          this->m_RQCBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
						                                          this->m_RQIBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_RQNBLTEN[ii + m_IME * kk + m_KME * jj] = 0.0;
						                                          this->m_exch_h[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_exch_m[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_edmf_a[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_edmf_w[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_edmf_qt[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_edmf_thl[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_edmf_ent[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_edmf_qc[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_el_pbl[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qWT[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qSHEAR[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qBUOY[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qDISS[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_dqke[ii + m_IME * kk + m_KME * jj] = 0.0;
																 
																  this->m_Sh3D[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_qc_bl[ii + m_IME * kk + m_KME * jj] = 0.0;
																  this->m_cldfra_bl[ii + m_IME * kk + m_KME * jj] = 0.0;
																}
															}
														}
													}
												}
											}




#endif
#if WRF_CHEM == 1
									for (int i = m_IMS; i != m_IME; ++i) {
										for (int k = m_KMS; k != m_KME; ++k) {
											for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
												for (int n = 0; n != m_nchem; ++n) {
													this->m_chem3D[i + m_IME * k + m_KME * j + m_JME * n] = 0.0;
												}
											}
										}
									}
									for (int i = m_IMS; i != m_IME; ++i) {
										for (int k = 0; k != m_kdvel; ++k) {
											for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
												for (int n = 0; n != m_ndvel; ++n) {
													this->m_vd3d[i + m_IME * k + m_kdvel * j + m_JME * n] = 0.0;
												}
											}
										}
									}
									
#endif
									// Zero-initialization of Arrays 2D.
#if defined (USE_LOOP_BLOCKING)

									for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
										for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
											for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
												for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
													this->m_xland[ii + m_IME * jj] = 0.0;
													this->m_ust[ii + m_IME * jj] = 0.0;
													this->m_ch[ii + m_IME  * jj] = 0.0;
													this->m_rmol[ii + m_IME * jj] = 0.0;
													this->m_ts[ii + m_IME * jj] = 0.0;
													this->m_qsfc[ii + m_IME * jj] = 0.0;
													this->m_qcg[ii + m_IME * jj] = 0.0;
													this->m_ps[ii + m_IME * jj] = 0.0;
													this->m_hfx[ii + m_IME * jj] = 0.0;
													this->m_qfx[ii + m_IME * jj] = 0.0;
													this->m_wspd[ii + m_IME * jj] = 0.0;
													this->m_uoce[ii + m_IME * jj] = 0.0;
													this->m_voce[ii + m_IME * jj] = 0.0;
													this->m_vdfg[ii + m_IME * jj] = 0.0;
													this->m_znt[ii + m_IME * jj] = 0.0;
													this->m_Pblh[ii + m_IME * jj] = 0.0;
													this->m_wstar[ii + m_IME * jj] = 0.0;
													this->m_delta[ii + m_IME * jj] = 0.0;
													
													this->m_KPBL[ii + m_IME * jj] = 0.0;
												}
											}
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
			         Wrap_Mynn_Bl_Driver(_In_ const I32 initflag,
				                         _In_ const I32 grav_settling,
				                         _In_ const I32 bl_mynn_tkebudget,
				                         _In_ const I32 bl_mynn_cloudpdf,
				                         _In_ const I32 bl_mynn_mixlength,
				                         _In_ const I32 bl_mynn_edmf,
				                         _In_ const I32 bl_mynn_tkeadvect,
				                         _In_ const I32 bl_mynn_edmf_mom,
				                         _In_ const I32 bl_mynn_edmf_tke,
				                         _In_ const I32 bl_mynn_edmf_part,
				                         _In_ const I32 bl_mynn_cloudmix,
				                         _In_ const I32 bl_mynn_mixqt,
				                         _In_ const I32 icloud_bl,
				                         _In_ const I32 FLAG_QI,
				                         _In_ const I32 FLAG_QNI,
				                         _In_ const I32 FLAG_QC,
				                         _In_ const I32 FLAG_QNC,
				                         _In_ const I32 IDS,
				                         _In_ const I32 IDE,
				                         _In_ const I32 JDS,
				                         _In_ const I32 JDE,
				                         _In_ const I32 KDS,
				                         _In_ const I32 KDE,
				                         _In_ const I32 IMS,
				                         _In_ const I32 IME,
				                         _In_ const I32 JMS,
				                         _In_ const I32 JME,
				                         _In_ const I32 KMS,
				                         _In_ const I32 KME,
				                         _In_ const I32 ITS,
				                         _In_ const I32 ITE,
				                         _In_ const I32 JTS,
				                         _In_ const I32 JTE,
				                         _In_ const I32 KTS,
				                         _In_ const I32 KTE,
#if WRF_CHEM == 1										 
				                         _In_ const I32 nchem,
				                         _In_ const I32 kdvel,
				                         _In_ const I32 ndvel,
				                         _In_ const I32 num_vert_mix,
				                         _In_ const R32 vd1,
				                         _In_ const I32 ic,
#endif                                                           
				                         _In_ const R32 delt,
				                         _In_ const R32 dx, 
										 _In_ R32* __restrict const dz,
										 _In_ R32* __restrict const u,
										 _In_ R32* __restrict const v,
										 _In_ R32* __restrict const w,
										 _In_ R32* __restrict const th,
										 _In_ R32* __restrict const qv,
										 _In_ R32* __restrict const p,
										 _In_ R32* __restrict const exner,
										 _In_ R32* __restrict const rho,
										 _In_ R32* __restrict const T3D,
										 _In_ R32* __restrict const qc,
										 _In_ R32* __restrict const qi,
										 _In_ R32* __restrict const qni,
										 _In_ R32* __restrict const qnc,
										 _In_ R32* __restrict const xland,
										 _In_ R32* __restrict const ust,
										 _In_ R32* __restrict const ch,
										 _In_ R32* __restrict const rmol,
										 _In_ R32* __restrict const ts,
										 _In_ R32* __restrict const qsfc,
										 _In_ R32* __restrict const qcg,
										 _In_ R32* __restrict const ps,
										 _In_ R32* __restrict const hfx,
										 _In_ R32* __restrict const qfx,
										 _In_ R32* __restrict const wspd,
										 _In_ R32* __restrict const uoce,
										 _In_ R32* __restrict const voce,
										 _In_ R32* __restrict const vdfg,
										 _In_ R32* __restrict const znt,
										 _In_ R32* __restrict const Qke,
										 _In_ R32* __restrict const Tsq,
										 _In_ R32* __restrict const Qsq,
										 _In_ R32* __restrict const Cov,
										 _In_ R32* __restrict const tke_pbl,
										 _In_ R32* __restrict const qke_adv,
										 _In_ R32* __restrict const RUBLTEN,
										 _In_ R32* __restrict const RVBLTEN,
										 _In_ R32* __restrict const RTHBLTEN,
										 _In_ R32* __restrict const RQVBLTEN,
										 _In_ R32* __restrict const RQCBLTEN,
										 _In_ R32* __restrict const RQIBLTEN,
										 _In_ R32* __restrict const RQNIBLTEN,
										 _In_ R32* __restrict const edmf_a,
										 _In_ R32* __restrict const edmf_w,
										 _In_ R32* __restrict const edmf_qt,
										 _In_ R32* __restrict const edmf_thl,
										 _In_ R32* __restrict const edmf_ent,
										 _In_ R32* __restrict const edmf_qc,
										 _In_ R32* __restrict const Pblh,
										 _In_ R32* __restrict const wstar,
										 _In_ R32* __restrict const delta,
										 _In_ R32* __restrict const KPBL,
										 _In_ R32* __restrict const el_pbl,
										 _In_ R32* __restrict const qWT,
										 _In_ R32* __restrict const qSHEAR,
										 _In_ R32* __restrict const qBUOY,
										 _In_ R32* __restrict const qDISS,
										 _In_ R32* __restrict const dqke,
										 _In_ R32* __restrict const Sh3D,
										 _In_ R32* __restrict const qc_bl,
										 _In_ R32* __restrict const cldfra_bl,
#if WRF_CHEM == 1
										 _In_ R32* __restrict const chem3D,
										 _In_ R32* __restrict const vd3D
#endif
										                               )
													:
										     m_initflag{ initflag },
											 m_grav_settling{ grav_settling },
											 m_bl_mynn_tkebudget{ bl_mynn_tkebudget },
											 m_bl_mynn_cloudpdf{ bl_mynn_cloudpdf },
											 m_bl_mynn_mixlength{ bl_mynn_mixlength },
											 m_bl_mynn_edmf{ bl_mynn_edmf },
											 m_bl_mynn_tkeadvect{ bl_mynn_tkeadvect },
											 m_bl_mynn_edmf_mon{ bl_mynn_edmf_mom },
											 m_bl_mynn_edmf_tke{ bl_mynn_edmf_tke },
											 m_bl_mynn_edmf_part{ bl_mynn_edmf_part },
											 m_bl_mynn_cloudmix{ bl_mynn_cloudmix },
											 m_bl_mynn_mixqt{ bl_mynn_mixqt },
											 m_icloud_bl{ icloud_bl },
											 m_FLAG_QI{ FLAG_QI },
											 m_FLAG_QNI{ FLAG_QNI },
											 m_FLAG_QC{ FLAG_QC },
											 m_FLAG_QNC{ FLAG_QNC },
											 m_IDS{ IDS },
											 m_IDE{ IDE },
											 m_JDS{ JDS },
											 m_JDE{ JDE },
											 m_KDS{ KDS },
											 m_KDE{ KDE },
											 m_IMS{ IMS },
											 m_IME{ IME },
											 m_JMS{ JMS },
											 m_JME{ JME },
											 m_KMS{ KMS },
											 m_KME{ KME },
											 m_ITS{ ITS },
											 m_ITE{ ITE },
											 m_JTS{ JTS },
											 m_JTE{ JTE },
											 m_KTS{ KTS },
											 m_KTE{ KTE },
#if WRF_CHEM == 1
											 m_nchem{ nchem },
											 m_kdvel{ kdvel },
											 m_ndvel{ ndvel },
											 m_num_vert_mix{ num_vert_mix },

#endif
											 m_delt{ delt },
											 m_dx{ dx },
											 m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_u{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_v{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_w{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_th{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qv{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_p{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_rho{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_T3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qi{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qni{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qnc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_xland{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_ust{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_ch{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_rmol{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_ts{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_qsfc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_qcg{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_ps{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_hfx{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_qfx{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_wspd{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_uoce{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_voce{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_vdfg{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_znt{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_Qke{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_Tsq{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_Qsq{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_Cov{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_tke_pbl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qke_adv{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_RUBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_RVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_RTHBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_RQVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_RQCBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_RQIBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_RQNBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_exch_h{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_exch_m{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_edmf_a{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_edmf_w{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_edmf_qt{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_edmf_thl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_emdf_ent{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_edmf_qc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_Pblh{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_wstar{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_delta{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											
											 m_KPBL{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											 m_el_pbl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qWT{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qSHEAR{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qBUOY{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qDISS{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_dqke{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },

											
											 m_Sh3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_qc_bl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											 m_cldfra_bl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },

#if WRF_CHEM == 1
											 m_chem3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KTE * m_JME * m_nchem * sizeof(R32)), align32B)) },
											 m_vd3d{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_kdvel * m_JME * m_ndvel * sizeof(R32)), align32B)) }

#endif

											 {
												 // Check for memory allocation errors i.e. (malloc failures).
												 for (int i{ 0 }; i != this->m_totArrays; ++i) {
													 if ((&this->m_dz)[i] == NULL) {
														 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mynn_Bl_Driver'!!\n";
														 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
														 std::cerr << "***** ERROR-DETAILS ***** \n";
														 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
														 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
														 std::exit(-1);
													 }
												 }
											     // Check for null pointer occurrence.
												 if (dz        == NULL ||
													 u         == NULL ||
													 v         == NULL ||
													 w         == NULL ||
													 th        == NULL ||
													 qv        == NULL ||
													 p         == NULL ||
													 exner     == NULL ||
													 rho       == NULL ||
													 T3D       == NULL ||
													 qc        == NULL ||
													 qi        == NULL ||
													 qni       == NULL ||
													 qnc       == NULL ||
													 xland     == NULL ||
													 ust       == NULL ||
													 ch        == NULL ||
													 rmol      == NULL ||
													 ts        == NULL ||
													 qsfc      == NULL ||
													 qcg       == NULL ||
													 ps        == NULL ||
													 hfx       == NULL ||
													 qfx       == NULL ||
													 wspd      == NULL ||
													 uoce      == NULL ||
													 voce      == NULL ||
													 vdfg      == NULL ||
													 znt       == NULL ||
													 Qke       == NULL ||
													 Tsq       == NULL ||
													 Qsq       == NULL ||
													 Cov       == NULL ||
													 tke_pbl   == NULL ||
													 qke_adv   == NULL ||
													 RUBLTEN   == NULL ||
													 RVBLTEN   == NULL ||
													 RTHBLTEN  == NULL ||
													 RQVBLTEN  == NULL ||
													 RQCBLTEN  == NULL ||
													 RQIBLTEN  == NULL ||
													 RQNIBLTEN == NULL ||
													 edmf_a    == NULL ||
													 edmf_w    == NULL ||
													 edmf_qt   == NULL ||
													 edmf_thl  == NULL ||
													 edmf_ent  == NULL ||
													 edmf_qc   == NULL ||
													 Pblh      == NULL ||
													 wstar     == NULL ||
													 delta     == NULL ||
													 KPBL      == NULL ||
													 el_pbl    == NULL ||
													 qWT       == NULL ||
													 qSHEAR    == NULL ||
													 qBUOY     == NULL ||
													 qDISS     == NULL ||
													 dqke      == NULL ||
													 Sh3D      == NULL ||
													 qc_bl     == NULL ||
													 cldfra_bl == NULL   )  {

													 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in 2nd Ctor: 'Wrap_Mynn_Bl_Driver'!!\n";
													 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
													 std::cerr << "***** ERROR-DETAILS ***** \n";
													 std::cerr << "One or more caller's arrays contains invalid pointer!!\n";
													 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
													 std::exit(-1);
									}
												 // Copy caller's input arrays.
												 // Using OpenMP for outermost loop 
												 // and vectorization for innermost loop.
												 // Arrays 3D first.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_IME * m_KME * m_JME) >= (1 << 20))
												 for (int i = m_IMS; i != m_IME; ++i) {
													 for (int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
														 for (int j = m_JMS; j != m_JME; ++j) {
															 this->m_dz[i + m_IME * k + m_KME * j] = dz[i + m_IME * k + m_KME * j];
															 this->m_u[i + m_IME * k + m_KME * j]  =  u[i + m_IME * k + m_KME * j];
															 this->m_v[i + m_IME * k + m_KME * j]  =  v[i + m_IME * k + m_KME * j];
															 this->m_w[i + m_IME * k + m_KME * j]  =  w[i + m_IME * k + m_KME * j];
															 this->m_th[i + m_IME * k + m_KME * j] = th[i + m_IME * k + m_KME * j];
															 this->m_qv[i + m_IME * k + m_KME * j] = qv[i + m_IME * k + m_KME * j];
															 this->m_p[i + m_IME * k + m_KME * j] =   p[i + m_IME * k + m_KME * j];
															 this->m_exner[i + m_IME * k + m_KME * j] = exner[i + m_IME * k + m_KME * j];
															 this->m_rho[i + m_IME * k + m_KME * j] = rho[i + m_IME * k + m_KME * j];
															 this->m_T3D[i + m_IME * k + m_KME * j] = T3D[i + m_IME * k + m_KME * j];
															 this->m_qc[i + m_IME * k + m_KME * j] =   qc[i + m_IME * k + m_KME * j];
															 this->m_qi[i + m_IME * k + m_KME * j] =   qi[i + m_IME * k + m_KME * j];
															 this->m_qni[i + m_IME * k + m_KME * j] = qni[i + m_IME * k + m_KME * j];
															 this->m_qnc[i + m_IME * k + m_KME * j] = qnc[i + m_IME * k + m_KME * j];
															 this->m_Qke[i + m_IME * k + m_KME * j] = Qke[i + m_IME * k + m_KME * j];
															 this->m_Tsq[i + m_IME * k + m_KME * j] = Tsq[i + m_IME * k + m_KME * j];
															 this->m_Qsq[i + m_IME * k + m_KME * j] = Qsq[i + m_IME * k + m_KME * j];
															 this->m_Cov[i + m_IME * k + m_KME * j] = Cov[i + m_IME * k + m_KME * j];
															 this->m_tke_pbl[i + m_IME * k + m_KME * j] = tke_pbl[i + m_IME * k + m_KME * j];
															 this->m_qke_adv[i + m_IME * k + m_KME * j] = qke_adv[i + m_IME * k + m_KME * j];
															 this->m_RUBLTEN[i + m_IME * k + m_KME * j] = RUBLTEN[i + m_IME * k + m_KME * j];
															 this->m_RVBLTEN[i + m_IME * k + m_KME * j] = RVBLTEN[i + m_IME * k + m_KME * j];
															 this->m_RTHBLTEN[i + m_IME * k + m_KME * j] = RTHBLTEN[i + m_IME * k + m_KME * j];
															 this->m_RQVBLTEN[i + m_IME * k + m_KME * j] = RQVBLTEN[i + m_IME * k + m_KME * j];
															 this->m_RQCBLTEN[i + m_IME * k + m_KME * j] = RQCBLTEN[i + m_IME * k + m_KME * j];
															 this->m_RQIBLTEN[i + m_IME * k + m_KME * j] = RQIBLTEN[i + m_IME * k + m_KME * j];
															 this->m_RQNBLTEN[i + m_IME * k + m_KME * j] = RQNIBLTEN[i + m_IME * k + m_KME * j];
															 this->m_exch_h[i + m_IME * k + m_KME * j] = 0.0;
															 this->m_exch_m[i + m_IME * k + m_KME * j] = 0.0;
															 this->m_edmf_a[i + m_IME * k + m_KME * j] =  edmf_a[i + m_IME * k + m_KME * j];
															 this->m_edmf_w[i + m_IME * k + m_KME * j] =  edmf_w[i + m_IME * k + m_KME * j];
															 this->m_edmf_qt[i + m_IME * k + m_KME * j] = edmf_qt[i + m_IME * k + m_KME * j];
															 this->m_edmf_thl[i + m_IME * k + m_KME * j] = edmf_thl[i + m_IME * k + m_KME * j];
															 this->m_edmf_ent[i + m_IME * k + m_KME * j] = edmf_ent[i + m_IME * k + m_KME * j];
															 this->m_edmf_qc[i + m_IME * k + m_KME * j] = edmf_qc[i + m_IME * k + m_KME * j];
															 this->m_el_pbl[i + m_IME * k + m_KME * j] = el_pbl[i + m_IME * k + m_KME * j];
															 this->m_qWT[i + m_IME * k + m_KME * j] = qWT[i + m_IME * k + m_KME * j];
															 this->m_qSHEAR[i + m_IME * k + m_KME * j] = qSHEAR[i + m_IME * k + m_KME * j];
															 this->m_qBUOY[i + m_IME * k + m_KME * j] = qBUOY[i + m_IME * k + m_KME * j];
															 this->m_qDISS[i + m_IME * k + m_KME * j] = qDISS[i + m_IME * k + m_KME * j];
															 this->m_dqke[i + m_IME * k + m_KME * j] = dqke[i + m_IME * k + m_KME * j];

															 this->m_Sh3D[i + m_IME * k + m_KME * j] = Sh3D[i + m_IME * k + m_KME * j];
															 this->m_qc_bl[i + m_IME * k + m_KME * j] = qc_bl[i + m_IME * k + m_KME * j];
															 this->m_cldfra_bl[i + m_IME * k + m_KME * j] = cldfra_bl[i + m_IME * k + m_KME * j];

														 }
													 }
												 }
												 // Copy caller's Arrays 2D.
												 // Using OpenMP multithreading for outer loop
												 // and vectorization for inner loop.
#pragma omp parallel for if((m_IME * m_JME) >= (1 << 20))
												 for (int i = m_IMS; i != m_IME; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
													 for (int j = m_JMS; j != m_JME; ++j) {
														 this->m_xland[i + m_IME * j] = xland[i + m_IME * j];
														 this->m_ust[i + m_IME * j] = ust[i + m_IME * j];
														 this->m_ch[i + m_IME  * j] =  ch[i + m_IME * j];
														 this->m_rmol[i + m_IME * j] = rmol[i + m_IME * j];
														 this->m_ts[i + m_IME * j] = ts[i + m_IME * j];
														 this->m_qsfc[i + m_IME * j] = qsfc[i + m_IME * j];
														 this->m_qcg[i + m_IME * j] = qcg[i + m_IME * j];
														 this->m_ps[i + m_IME * j] = ps[i + m_IME * j];
														 this->m_hfx[i + m_IME * j] = hfx[i + m_IME * j];
														 this->m_qfx[i + m_IME * j] = qfx[i + m_IME * j];
														 this->m_wspd[i + m_IME * j] = wspd[i + m_IME * j];
														 this->m_uoce[i + m_IME * j] = uoce[i + m_IME * j];
														 this->m_voce[i + m_IME * j] = voce[i + m_IME * j];
														 this->m_vdfg[i + m_IME * j] = vdfg[i + m_IME * j];
														 this->m_znt[i + m_IME * j] = znt[i + m_IME * j];
														 this->m_Pblh[i + m_IME * j] = Pblh[i + m_IME * j];
														 this->m_wstar[i + m_IME * j] = wstar[i + m_IME * j];
														 this->m_delta[i + m_IME * j] = delta[i + m_IME * j];

														 this->m_KPBL[i + m_IME * j] = 0.0;
													 }
												 }
#if WRF_CHEM == 1
												 for (int i = m_IMS; i != m_IME; ++i) {
													 for (int k = m_KMS; k != m_KME; ++k) {
														 for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
															 for (int n = 0; n != m_nchem; ++n) {
																 this->m_chem3D[i + m_IME * k + m_KME * j + m_JME * n] = chem3D[i + m_IME * k + m_KME * j + m_JME * n];
															 }
														 }
													 }
												 }
												 for (int i = m_IMS; i != m_IME; ++i) {
													 for (int k = 0; k != m_kdvel; ++k) {
														 for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
															 for (int n = 0; n != m_ndvel; ++n) {
																 this->m_vd3d[i + m_IME * k + m_kdvel * j + m_JME * n] = vd3D[i + m_IME * k + m_KME * j + m_JME * n];
															 }
														 }
													 }
												 }


#endif

#else

#if defined (USE_LOOP_BLOCKING)

					// Use loop blocking.
					// Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
									for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
										 for (int k = m_KMS; k != m_KME; k += DEFAULT_BLOCK_SIZE) {
		                                      for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
			                                       for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
				                                       for (int kk = k; kk < DEFAULT_BLOCK_SIZE; ++kk) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
					                                         for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
																 this->m_dz[ii + m_IME * kk + m_KME * jj] = dz[ii + m_IME * kk + m_KME * jj];
																 this->m_u[ii + m_IME * kk + m_KME * jj]  =  u[ii + m_IME * kk + m_KME * jj];
																 this->m_v[ii + m_IME * kk + m_KME * jj]  =  v[ii + m_IME * kk + m_KME * jj];
																 this->m_w[ii + m_IME * kk + m_KME * jj]  =  w[ii + m_IME * kk + m_KME * jj];
																 this->m_th[ii + m_IME * kk + m_KME * jj] = th[ii + m_IME * kk + m_KME * jj];
																 this->m_qv[ii + m_IME * kk + m_KME * jj] = qv[ii + m_IME * kk + m_KME * jj];
																 this->m_p[ii + m_IME * kk + m_KME * jj] =   p[ii + m_IME * kk + m_KME * jj];
																 this->m_exner[ii + m_IME * kk + m_KME * jj] = exner[ii + m_IME * kk + m_KME * jj];
																 this->m_rho[ii + m_IME * kk + m_KME * jj] = rho[ii + m_IME * kk + m_KME * jj];
																 this->m_T3D[ii + m_IME * kk + m_KME * jj] = T3D[ii + m_IME * kk + m_KME * jj];
																 this->m_qc[ii + m_IME * kk + m_KME * jj] =   qc[ii + m_IME * kk + m_KME * jj];
																 this->m_qi[ii + m_IME * kk + m_KME * jj] =   qi[ii + m_IME * kk + m_KME * jj];
																 this->m_qni[ii + m_IME * kk + m_KME * jj] = qni[ii + m_IME * kk + m_KME * jj];
																 this->m_qnc[ii + m_IME * kk + m_KME * jj] = qnc[ii + m_IME * kk + m_KME * jj];
																 this->m_Qke[ii + m_IME * kk + m_KME * jj] = Qke[ii + m_IME * kk + m_KME * jj];
																 this->m_Tsq[ii + m_IME * kk + m_KME * jj] = Tsq[ii + m_IME * kk + m_KME * jj];
																 this->m_Qsq[ii + m_IME * kk + m_KME * jj] = Qsq[ii + m_IME * kk + m_KME * jj];
																 this->m_Cov[ii + m_IME * kk + m_KME * jj] = Cov[ii + m_IME * kk + m_KME * jj];
																 this->m_tke_pbl[ii + m_IME * kk + m_KME * jj] = tke_pbl[ii + m_IME * kk + m_KME * jj];
																 this->m_qke_adv[ii + m_IME * kk + m_KME * jj] = qkv_adv[ii + m_IME * kk + m_KME * jj];
																 this->m_RUBLTEN[ii + m_IME * kk + m_KME * jj] = RUBLTEN[ii + m_IME * kk + m_KME * jj];
																 this->m_RVBLTEN[ii + m_IME * kk + m_KME * jj] = RVBLTEN[ii + m_IME * kk + m_KME * jj];
																 this->m_RTHBLTEN[ii + m_IME * kk + m_KME * jj] = RTHBLTEN[ii + m_IME * kk + m_KME * jj];
																 this->m_RQVBLTEN[ii + m_IME * kk + m_KME * jj] = RQVBLTEN[ii + m_IME * kk + m_KME * jj];
																 this->m_RQCBLTEN[ii + m_IME * kk + m_KME * jj] = RQCBLTEN[ii + m_IME * kk + m_KME * jj];
																 this->m_RQIBLTEN[ii + m_IME * kk + m_KME * jj] = RQIBLTEN[ii + m_IME * kk + m_KME * jj];
																 this->m_RQNBLTEN[ii + m_IME * kk + m_KME * jj] = RQNIBLTEN[ii + m_IME * kk + m_KME * jj];
																 this->m_exch_h[ii + m_IME * kk + m_KME * jj] = 0.0;
																 this->m_exch_m[ii + m_IME * kk + m_KME * jj] = 0.0;
																 this->m_edmf_a[ii+ m_IME * kk + m_KME * jj] =  edmf_a[ii + m_IME * kk + m_KME * jj];
																 this->m_edmf_w[ii + m_IME * kk + m_KME * jj] =  edmf_w[ii + m_IME * kk + m_KME * jj];
																 this->m_edmf_qt[ii + m_IME * kk + m_KME * jj] = edmf_qt[ii + m_IME * kk + m_KME * jj];
																 this->m_edmf_thl[ii + m_IME * kk + m_KME * jj] = edmf_thl[ii + m_IME * kk + m_KME * jj];
																 this->m_edmf_ent[ii + m_IME * kk + m_KME * jj] = edmf_ent[ii + m_IME * kk + m_KME * jj];
																 this->m_edmf_qc[ii + m_IME * kk + m_KME * jj] = edmf_qc[ii + m_IME * kk + m_KME * jj];
																 this->m_el_pbl[ii + m_IME * kk + m_KME * jj] = el_pbl[ii + m_IME * kk + m_KME * jj];
																 this->m_qWT[ii + m_IME * kk + m_KME * jj] = qWT[ii + m_IME * kk + m_KME * jj];
																 this->m_qSHEAR[ii + m_IME * kk + m_KME * jj] = qSHEAR[ii + m_IME * kk + m_KME * jj];
																 this->m_qBUOY[ii + m_IME * kk + m_KME * jj] = qBUOY[ii + m_IME * kk + m_KME * jj];
																 this->m_qDISS[ii + m_IME * kk + m_KME * jj] = qDISS[ii + m_IME * kk + m_KME * jj];
																 this->m_dqke[ii + m_IME * kk + m_KME * jj] = dqke[ii + m_IME * kk + m_KME * jj];

																 this->m_Sh3D[ii + m_IME * kk + m_KME * jj] = Sh3D[ii + m_IME * kk + m_KME * jj];
																 this->m_qc_bl[ii + m_IME * kk + m_KME * jj] = qc_bl[ii + m_IME * kk + m_KME * jj];
																 this->m_cldfra_bl[ii + m_IME * kk + m_KME * jj] = cldfra_bl[ii + m_IME * kk + m_KME * jj];
					}
				}
			}
		}
	}
}

									


#endif
									// Copy caller's Arrays 2D.
									// Using loop blocking.
									// and vectorization for inner loop.
									// You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)
									for(int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
										for(int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
											for(int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
												for(int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
													this->m_xland[ii + m_IME * jj] = xland[ii + m_IME * jj];
													this->m_ust[ii + m_IME * jj] = ust[ii + m_IME * jj];
													this->m_ch[ii + m_IME  * jj] =  ch[ii + m_IME * jj];
													this->m_rmol[ii + m_IME * jj] = rmol[ii + m_IME * jj];
													this->m_ts[ii + m_IME * jj] = ts[ii + m_IME * jj];
													this->m_qsfc[ii + m_IME * jj] = qsfc[ii + m_IME * jj];
													this->m_qcg[ii + m_IME * jj] = qcg[ii + m_IME * jj];
													this->m_ps[ii + m_IME * jj] = ps[ii + m_IME * jj];
													this->m_hfx[ii + m_IME * jj] = hfx[ii + m_IME * jj];
													this->m_qfx[ii + m_IME * jj] = qfx[ii + m_IME * jj];
													this->m_wspd[ii + m_IME * jj] = wspd[ii + m_IME * jj];
													this->m_uoce[ii + m_IME * jj] = uoce[ii + m_IME * jj];
													this->m_voce[ii + m_IME * jj] = voce[ii + m_IME * jj];
													this->m_vdfg[ii + m_IME * jj] = vdfg[ii + m_IME * jj];
													this->m_znt[ii + m_IME * jj] = znt[ii + m_IME * jj];
													this->m_Pblh[ii + m_IME * jj] = Pblh[ii + m_IME * jj];
													this->m_wstar[ii + m_IME * jj] = wstar[ii + m_IME * jj];
													this->m_delta[ii + m_IME * jj] = delta[ii + m_IME * jj];

													this->m_KPBL[ii + m_IME * jj] = 0.0;
												}
											}
										}
									}

#endif
#if WRF_CHEM == 1
									for (int i = m_IMS; i != m_IME; ++i) {
										for (int k = m_KMS; k != m_KME; ++k) {
											for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
												for (int n = 0; n != m_nchem; ++n) {
													this->m_chem3D[i + m_IME * k + m_KME * j + m_JME * n] = chem3D[i + m_IME * k + m_KME * j + m_JME * n];
												}
											}
										}
									}
									for (int i = m_IMS; i != m_IME; ++i) {
										for (int k = 0; k != m_kdvel; ++k) {
											for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
												for (int n = 0; n != m_ndvel; ++n) {
													this->m_vd3d[i + m_IME * k + m_kdvel * j + m_JME * n] = vd3D[i + m_IME * k + m_KME * j + m_JME * n];
												}
											}
										}
									}


#endif

#endif
			}
			   

			      /*
					@Purpose:
							  Copy Constructor implements deep copy semantics.
			     */
			         Wrap_Mynn_Bl_Driver(_In_ const Wrap_Mynn_Bl_Driver &x)
											:
											m_initflag{ x.m_initflag },
											m_grav_settling{ x.m_grav_settling },
											m_bl_mynn_tkebudget{ x.m_bl_mynn_tkebudget },
											m_bl_mynn_cloudpdf{ x.m_bl_mynn_cloudpdf },
											m_bl_mynn_mixlength{ x.m_bl_mynn_mixlength },
											m_bl_mynn_edmf{ x.m_bl_mynn_edmf },
											m_bl_mynn_tkeadvect{ x.m_bl_mynn_tkeadvect },
											m_bl_mynn_edmf_mon{ x.m_bl_mynn_edmf_mom },
											m_bl_mynn_edmf_tke{ x.m_bl_mynn_edmf_tke },
											m_bl_mynn_edmf_part{ x.m_bl_mynn_edmf_part },
											m_bl_mynn_cloudmix{ x.m_bl_mynn_cloudmix },
											m_bl_mynn_mixqt{ x.m_bl_mynn_mixqt },
											m_icloud_bl{ x.m_icloud_bl },
											m_FLAG_QI{ x.m_FLAG_QI },
											m_FLAG_QNI{ x.m_FLAG_QNI },
											m_FLAG_QC{ x.m_FLAG_QC },
											m_FLAG_QNC{ x.m_FLAG_QNC },
											m_IDS{ x.m_IDS },
											m_IDE{ x.m_IDE },
											m_JDS{ x.m_JDS },
											m_JDE{ x.m_JDE },
											m_KDS{ x.m_KDS },
											m_KDE{ x.m_KDE },
											m_IMS{ x.m_IMS },
											m_IME{ x.m_IME },
											m_JMS{ x.m_JMS },
											m_JME{ x.m_JME },
											m_KMS{ x.m_KMS },
											m_KME{ x.m_KME },
											m_ITS{ x.m_ITS },
											m_ITE{ x.m_ITE },
											m_JTS{ x.m_JTS },
											m_JTE{ x.m_JTE },
											m_KTS{ x.m_KTS },
											m_KTE{ x.m_KTE },
#if WRF_CHEM == 1
											m_nchem{ x.m_nchem },
											m_kdvel{ x.m_kdvel },
											m_ndvel{ x.m_ndvel },
											m_num_vert_mix{ x.m_num_vert_mix },

#endif
											m_delt{ x.m_delt },
											m_dx{ x.m_dx },
											m_dz{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_u{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_v{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_w{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_th{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qv{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_p{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_exner{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_rho{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_T3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qi{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qni{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qnc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_xland{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_ust{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_ch{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_rmol{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_ts{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_qsfc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_qcg{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_ps{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_hfx{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_qfx{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_wspd{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_uoce{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_voce{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_vdfg{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_znt{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_Qke{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_Tsq{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_Qsq{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_Cov{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_tke_pbl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qke_adv{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_RUBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_RVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_RTHBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_RQVBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_RQCBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_RQIBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_RQNBLTEN{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_exch_h{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_exch_m{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_edmf_a{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_edmf_w{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_edmf_qt{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_edmf_thl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_emdf_ent{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_edmf_qc{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_Pblh{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_wstar{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_delta{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },

											m_KPBL{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)), align32B)) },
											m_el_pbl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qWT{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qSHEAR{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qBUOY{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qDISS{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_dqke{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },


											m_Sh3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_qc_bl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },
											m_cldfra_bl{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)), align32B)) },

#if WRF_CHEM == 1
											m_chem3D{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KTE * m_JME * m_nchem * sizeof(R32)), align32B)) },
											m_vd3d{ reinterpret_cast<R32*>(_mm_malloc((m_IME * m_kdvel * m_JME * m_ndvel * sizeof(R32)), align32B)) }

#endif
											{
												//Check for memory allocation errors i.e. (malloc failures).
												for (int i{ 0 }; i != this->m_totArrays; ++i) {
													if ((&this->m_dz)[i] == NULL) {
														std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Ctor: 'Wrap_Mynn_Bl_Driver'!!\n";
														std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
														std::cerr << "***** ERROR-DETAILS ***** \n";
														std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << (&this->m_dz)[i] << "\n";
														std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
														std::exit(-1);
													}
												}
												// Copy x's input arrays.
												// Using OpenMP for outermost loop 
												// and vectorization for innermost loop.
												// Arrays 3D first.
#if defined (USE_ICL_OPENMP) && \
	OPENMP_CURR_VER >= 40
#pragma omp parallel for if((m_IME * m_KME * m_JME) >= (1 << 20))
												for (int i = m_IMS; i != m_IME; ++i) {
													for (int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
														for (int j = m_JMS; m != m_JME; ++j) {
															this->m_dz[i + m_IME * k + m_KME * j] = x.m_dz[i + m_IME * k + m_KME * j];
															this->m_u[i + m_IME * k + m_KME * j] = x.m_u[i + m_IME * k + m_KME * j];
															this->m_v[i + m_IME * k + m_KME * j] = x.m_v[i + m_IME * k + m_KME * j];
															this->m_w[i + m_IME * k + m_KME * j] = x.m_w[i + m_IME * k + m_KME * j];
															this->m_th[i + m_IME * k + m_KME * j] = x.m_th[i + m_IME * k + m_KME * j];
															this->m_qv[i + m_IME * k + m_KME * j] = x.m_qv[i + m_IME * k + m_KME * j];
															this->m_p[i + m_IME * k + m_KME * j] = x.m_p[i + m_IME * k + m_KME * j];
															this->m_exner[i + m_IME * k + m_KME * j] = x.m_exner[i + m_IME * k + m_KME * j];
															this->m_rho[i + m_IME * k + m_KME * j] = x.m_rho[i + m_IME * k + m_KME * j];
															this->m_T3D[i + m_IME * k + m_KME * j] = x.m_T3D[i + m_IME * k + m_KME * j];
															this->m_qc[i + m_IME * k + m_KME * j] = x.m_qc[i + m_IME * k + m_KME * j];
															this->m_qi[i + m_IME * k + m_KME * j] = x.m_qi[i + m_IME * k + m_KME * j];
															this->m_qni[i + m_IME * k + m_KME * j] = x.m_qni[i + m_IME * k + m_KME * j];
															this->m_qnc[i + m_IME * k + m_KME * j] = x.m_qnc[i + m_IME * k + m_KME * j];
															this->m_Qke[i + m_IME * k + m_KME * j] = x.m_Qke[i + m_IME * k + m_KME * j];
															this->m_Tsq[i + m_IME * k + m_KME * j] = x.m_Tsq[i + m_IME * k + m_KME * j];
															this->m_Qsq[i + m_IME * k + m_KME * j] = x.m_Qsq[i + m_IME * k + m_KME * j];
															this->m_Cov[i + m_IME * k + m_KME * j] = x.m_Cov[i + m_IME * k + m_KME * j];
															this->m_tke_pbl[i + m_IME * k + m_KME * j] = x.m_tke_pbl[i + m_IME * k + m_KME * j];
															this->m_qke_adv[i + m_IME * k + m_KME * j] = x.m_qke_adv[i + m_IME * k + m_KME * j];
															this->m_RUBLTEN[i + m_IME * k + m_KME * j] = x.m_RUBLTEN[i + m_IME * k + m_KME * j];
															this->m_RVBLTEN[i + m_IME * k + m_KME * j] = x.m_RVBLTEN[i + m_IME * k + m_KME * j];
															this->m_RTHBLTEN[i + m_IME * k + m_KME * j] = x.m_RTHBLTEN[i + m_IME * k + m_KME * j];
															this->m_RQVBLTEN[i + m_IME * k + m_KME * j] = x.m_RQVBLTEN[i + m_IME * k + m_KME * j];
															this->m_RQCBLTEN[i + m_IME * k + m_KME * j] = x.m_RQCBLTEN[i + m_IME * k + m_KME * j];
															this->m_RQIBLTEN[i + m_IME * k + m_KME * j] = x.m_RQIBLTEN[i + m_IME * k + m_KME * j];
															this->m_RQNBLTEN[i + m_IME * k + m_KME * j] = x.m_RQNIBLTEN[i + m_IME * k + m_KME * j];
															this->m_exch_h[i + m_IME * k + m_KME * j] = x.m_exch_h[i + m_IME * k + m_KME * j];
															this->m_exch_m[i + m_IME * k + m_KME * j] = x.m_exch_m[i + m_IME * k + m_KME * j];
															this->m_edmf_a[i + m_IME * k + m_KME * j] = x.m_edmf_a[i + m_IME * k + m_KME * j];
															this->m_edmf_w[i + m_IME * k + m_KME * j] = x.m_edmf_w[i + m_IME * k + m_KME * j];
															this->m_edmf_qt[i + m_IME * k + m_KME * j] = x.m_edmf_qt[i + m_IME * k + m_KME * j];
															this->m_edmf_thl[i + m_IME * k + m_KME * j] = x.m_edmf_thl[i + m_IME * k + m_KME * j];
															this->m_edmf_ent[i + m_IME * k + m_KME * j] = x.m_edmf_ent[i + m_IME * k + m_KME * j];
															this->m_edmf_qc[i + m_IME * k + m_KME * j] = x.m_edmf_qc[i + m_IME * k + m_KME * j];
															this->m_el_pbl[i + m_IME * k + m_KME * j] = x.m_el_pbl[i + m_IME * k + m_KME * j];
															this->m_qWT[i + m_IME * k + m_KME * j] = x.m_qWT[i + m_IME * k + m_KME * j];
															this->m_qSHEAR[i + m_IME * k + m_KME * j] = x.m_qSHEAR[i + m_IME * k + m_KME * j];
															this->m_qBUOY[i + m_IME * k + m_KME * j] = x.m_qBUOY[i + m_IME * k + m_KME * j];
															this->m_qDISS[i + m_IME * k + m_KME * j] = x.m_qDISS[i + m_IME * k + m_KME * j];
															this->m_dqke[i + m_IME * k + m_KME * j] = x.m_dqke[i + m_IME * k + m_KME * j];

															this->m_Sh3D[i + m_IME * k + m_KME * j] = x.m_Sh3D[i + m_IME * k + m_KME * j];
															this->m_qc_bl[i + m_IME * k + m_KME * j] = x.m_qc_bl[i + m_IME * k + m_KME * j];
															this->m_cldfra_bl[i + m_IME * k + m_KME * j] = x.m_cldfra_bl[i + m_IME * k + m_KME * j];

														}
													}
												}
												// Copy x's Arrays 2D.
												// Using OpenMP multithreading for outer loop
												// and vectorization for inner loop.
#pragma omp parallel for if((m_IME * m_JME) >= (1 << 20))
												for (int i = m_IMS; i != m_IME; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
													for (int j = m_JMS; j != m_JME; ++j) {
														this->m_xland[i + m_IME * j] = x.m_xland[i + m_IME * j];
														this->m_ust[i + m_IME * j] = x.m_ust[i + m_IME * j];
														this->m_ch[i + m_IME  * j] = x.m_ch[i + m_IME * j];
														this->m_rmol[i + m_IME * j] = x.m_rmol[i + m_IME * j];
														this->m_ts[i + m_IME * j] = x.m_ts[i + m_IME * j];
														this->m_qsfc[i + m_IME * j] = x.m_qsfc[i + m_IME * j];
														this->m_qcg[i + m_IME * j] = x.m_qcg[i + m_IME * j];
														this->m_ps[i + m_IME * j] = x.m_ps[i + m_IME * j];
														this->m_hfx[i + m_IME * j] = x.m_hfx[i + m_IME * j];
														this->m_qfx[i + m_IME * j] = x.m_qfx[i + m_IME * j];
														this->m_wspd[i + m_IME * j] = x.m_wspd[i + m_IME * j];
														this->m_uoce[i + m_IME * j] = x.m_uoce[i + m_IME * j];
														this->m_voce[i + m_IME * j] = x.m_voce[i + m_IME * j];
														this->m_vdfg[i + m_IME * j] = x.m_vdfg[i + m_IME * j];
														this->m_znt[i + m_IME * j] = x.m_znt[i + m_IME * j];
														this->m_Pblh[i + m_IME * j] = x.m_Pblh[i + m_IME * j];
														this->m_wstar[i + m_IME * j] = x.m_wstar[i + m_IME * j];
														this->m_delta[i + m_IME * j] = x.m_delta[i + m_IME * j];

														this->m_KPBL[i + m_IME * j] = x.m_KPBL[i + m_IME * j];
													}
												}

#if WRF_CHEM == 1
												for (int i = m_IMS; i != m_IME; ++i) {
													for (int k = m_KMS; k != m_KME; ++k) {
														for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
															for (int n = 0; n != m_nchem; ++n) {
																this->m_chem3D[i + m_IME * k + m_KME * j + m_JME * n] = x.m_chem3D[i + m_IME * k + m_KME * j + m_JME * n];
															}
														}
													}
												}
												for (int i = m_IMS; i != m_IME; ++i) {
													for (int k = 0; k != m_kdvel; ++k) {
														for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
															for (int n = 0; n != m_ndvel; ++n) {
																this->m_vd3d[i + m_IME * k + m_kdvel * j + m_JME * n] = x.m_vd3d[i + m_IME * k + m_KME * j + m_JME * n];
															}
														}
													}
												}


#endif






#else

#if defined (USE_LOOP_BLOCKING)

// Use loop blocking.
// Warning: You must not #undef 'USE_LOOP_BLOCKING' macro!!
                     for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
	                     for (int k = m_KMS; k != m_KME; k += DEFAULT_BLOCK_SIZE) {
		                     for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
			                     for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
				                      for (int kk = k; kk < DEFAULT_BLOCK_SIZE; ++kk) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
					                       for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
											   this->m_dz[ii + m_IME * kk + m_KME * jj] = x.m_dz[ii + m_IME * kk + m_KME * jj];
											   this->m_u[ii + m_IME * kk + m_KME * jj] = x.m_u[ii + m_IME * kk + m_KME * jj];
											   this->m_v[ii + m_IME * kk + m_KME * jj] = x.m_v[ii + m_IME * kk + m_KME * jj];
											   this->m_w[ii + m_IME * kk + m_KME * jj] = x.m_w[ii + m_IME * kk + m_KME * jj];
											   this->m_th[ii + m_IME * kk + m_KME * jj] = x.m_th[ii + m_IME * kk + m_KME * jj];
											   this->m_qv[ii + m_IME * kk + m_KME * jj] = x.m_qv[ii + m_IME * kk + m_KME * jj];
											   this->m_p[ii + m_IME * kk + m_KME * jj] = x.m_p[ii + m_IME * kk + m_KME * jj];
											   this->m_exner[ii + m_IME * kk + m_KME * jj] = x.m_exner[ii + m_IME * kk + m_KME * jj];
											   this->m_rho[ii + m_IME * kk + m_KME * jj] = x.m_rho[ii + m_IME * kk + m_KME * jj];
											   this->m_T3D[ii + m_IME * kk + m_KME * jj] = x.m_T3D[ii + m_IME * kk + m_KME * jj];
											   this->m_qc[ii + m_IME * kk + m_KME * jj] = x.m_qc[ii + m_IME * kk + m_KME * jj];
											   this->m_qi[ii + m_IME * kk + m_KME * jj] = x.m_qi[ii + m_IME * kk + m_KME * jj];
											   this->m_qni[ii + m_IME * kk + m_KME * jj] = x.m_qni[ii + m_IME * kk + m_KME * jj];
											   this->m_qnc[ii + m_IME * kk + m_KME * jj] = x.m_qnc[ii + m_IME * kk + m_KME * jj];
											   this->m_Qke[ii + m_IME * kk + m_KME * jj] = x.m_Qke[ii + m_IME * kk + m_KME * jj];
											   this->m_Tsq[ii + m_IME * kk + m_KME * jj] = x.m_Tsq[ii + m_IME * kk + m_KME * jj];
											   this->m_Qsq[ii + m_IME * kk + m_KME * jj] = x.m_Qsq[ii + m_IME * kk + m_KME * jj];
											   this->m_Cov[ii + m_IME * kk + m_KME * jj] = x.m_Cov[ii + m_IME * kk + m_KME * jj];
											   this->m_tke_pbl[ii + m_IME * kk + m_KME * jj] = x.m_tke_pbl[ii + m_IME * kk + m_KME * jj];
											   this->m_qke_adv[ii + m_IME * kk + m_KME * jj] = x.m_qke_adv[ii + m_IME * kk + m_KME * jj];
											   this->m_RUBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RUBLTEN[ii + m_IME * kk + m_KME * jj];
											   this->m_RVBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RVBLTEN[ii + m_IME * kk + m_KME * jj];
											   this->m_RTHBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RTHBLTEN[ii + m_IME * kk + m_KME * jj];
											   this->m_RQVBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RQVBLTEN[ii + m_IME * kk + m_KME * jj];
											   this->m_RQCBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RQCBLTEN[ii + m_IME * kk + m_KME * jj];
											   this->m_RQIBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RQIBLTEN[ii + m_IME * kk + m_KME * jj];
											   this->m_RQNBLTEN[ii + m_IME * kk + m_KME * jj] = x.m_RQNIBLTEN[ii + m_IME * kk + m_KME * jj];
											   this->m_exch_h[ii + m_IME * kk + m_KME * jj] = x.m_exch_h[ii + m_IME * kk + m_KME * jj];
											   this->m_exch_m[ii + m_IME * kk + m_KME * jj] = x.m_exch_m[ii + m_IME * kk + m_KME * jj];
											   this->m_edmf_a[ii + m_IME * kk + m_KME * jj] = x.m_edmf_a[ii + m_IME * kk + m_KME * jj];
											   this->m_edmf_w[ii + m_IME * kk + m_KME * jj] = x.m_edmf_w[ii + m_IME * kk + m_KME * jj];
											   this->m_edmf_qt[ii + m_IME * kk + m_KME * jj] = x.m_edmf_qt[ii + m_IME * kk + m_KME * jj];
											   this->m_edmf_thl[ii + m_IME * kk + m_KME * jj] = x.m_edmf_thl[ii + m_IME * kk + m_KME * jj];
											   this->m_edmf_ent[ii + m_IME * kk + m_KME * jj] = x.m_edmf_ent[ii + m_IME * kk + m_KME * jj];
											   this->m_edmf_qc[ii + m_IME * kk + m_KME * jj] = x.m_edmf_qc[ii + m_IME * kk + m_KME * jj];
											   this->m_el_pbl[ii + m_IME * kk + m_KME * jj] = x.m_el_pbl[ii + m_IME * kk + m_KME * jj];
											   this->m_qWT[ii + m_IME * kk + m_KME * jj] = x.m_qWT[ii + m_IME * kk + m_KME * jj];
											   this->m_qSHEAR[ii + m_IME * kk + m_KME * jj] = x.m_qSHEAR[ii + m_IME * kk + m_KME * jj];
											   this->m_qBUOY[ii + m_IME * kk + m_KME * jj] = x.m_qBUOY[ii + m_IME * kk + m_KME * jj];
											   this->m_qDISS[ii + m_IME * kk + m_KME * jj] = x.m_qDISS[ii + m_IME * kk + m_KME * jj];
											   this->m_dqke[ii + m_IME * kk + m_KME * jj] = x.m_dqke[ii + m_IME * kk + m_KME * jj];

											   this->m_Sh3D[ii + m_IME * kk + m_KME * jj] = x.m_Sh3D[ii + m_IME * kk + m_KME * jj];
											   this->m_qc_bl[ii + m_IME * kk + m_KME * jj] = x.m_qc_bl[ii + m_IME * kk + m_KME * jj];
											   this->m_cldfra_bl[ii + m_IME * kk + m_KME * jj] = x.m_cldfra_bl[ii + m_IME * kk + m_KME * jj];
					}
				}
			}
		}
	}
}




#endif

					 // Copy caller's Arrays 2D.
					 // Using loop blocking.
					 // and vectorization for inner loop.
					 // You must not #undef 'USE_LOOP_BLOCKING' macro!!
#if defined (USE_LOOP_BLOCKING)
					 for (int i = m_IMS; i != m_IME; i += DEFAULT_BLOCK_SIZE) {
						 for (int j = m_JMS; j != m_JME; j += DEFAULT_BLOCK_SIZE) {
							 for (int ii = i; ii < DEFAULT_BLOCK_SIZE; ++ii) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#endif
								 for (int jj = j; jj < DEFAULT_BLOCK_SIZE; ++jj) {
									 this->m_xland[ii + m_IME * jj] = x.m_xland[ii + m_IME * jj];
									 this->m_ust[ii + m_IME * jj] = x.m_ust[ii + m_IME * jj];
									 this->m_ch[ii + m_IME  * jj] = x.m_ch[ii + m_IME * jj];
									 this->m_rmol[ii + m_IME * jj] = x.m_rmol[ii + m_IME * jj];
									 this->m_ts[ii + m_IME * jj] = x.m_ts[ii + m_IME * jj];
									 this->m_qsfc[ii + m_IME * jj] = x.m_qsfc[ii + m_IME * jj];
									 this->m_qcg[ii + m_IME * jj] = x.m_qcg[ii + m_IME * jj];
									 this->m_ps[ii + m_IME * jj] = x.m_ps[ii + m_IME * jj];
									 this->m_hfx[ii + m_IME * jj] = x.m_hfx[ii + m_IME * jj];
									 this->m_qfx[ii + m_IME * jj] = x.m_qfx[ii + m_IME * jj];
									 this->m_wspd[ii + m_IME * jj] = x.m_wspd[ii + m_IME * jj];
									 this->m_uoce[ii + m_IME * jj] = x.m_uoce[ii + m_IME * jj];
									 this->m_voce[ii + m_IME * jj] = x.m_voce[ii + m_IME * jj];
									 this->m_vdfg[ii + m_IME * jj] = x.m_vdfg[ii + m_IME * jj];
									 this->m_znt[ii + m_IME * jj] = x.m_znt[ii + m_IME * jj];
									 this->m_Pblh[ii + m_IME * jj] = x.m_Pblh[ii + m_IME * jj];
									 this->m_wstar[ii + m_IME * jj] = x.m_wstar[ii + m_IME * jj];
									 this->m_delta[ii + m_IME * jj] = x.m_delta[ii + m_IME * jj];

									 this->m_KPBL[ii + m_IME * jj] = x.m_KPBL[ii + m_IME * jj];
								 }
							 }
						 }
					 }

#endif

#if WRF_CHEM == 1
					 for (int i = m_IMS; i != m_IME; ++i) {
						 for (int k = m_KMS; k != m_KME; ++k) {
							 for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for (int n = 0; n != m_nchem; ++n) {
									 this->m_chem3D[i + m_IME * k + m_KME * j + m_JME * n] = x.m_chem3D[i + m_IME * k + m_KME * j + m_JME * n];
								 }
							 }
						 }
					 }
					 for (int i = m_IMS; i != m_IME; ++i) {
						 for (int k = 0; k != m_kdvel; ++k) {
							 for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for (int n = 0; n != m_ndvel; ++n) {
									 this->m_vd3d[i + m_IME * k + m_kdvel * j + m_JME * n] = x.m_vd3d[i + m_IME * k + m_KME * j + m_JME * n];
								 }
							 }
						 }
					 }


#endif


#endif

			}

			    /*
					@Purpose:
							 Move Constructor implements shallow copy semantics.
			     */
					 Wrap_Mynn_Bl_Driver(_In_ Wrap_Mynn_Bl_Driver &&x)
				                         :
				                 m_initflag{ x.m_initflag },
				                 m_grav_settling{ x.m_grav_settling },
				                 m_bl_mynn_tkebudget{ x.m_bl_mynn_tkebudget },
				                 m_bl_mynn_cloudpdf{ x.m_bl_mynn_cloudpdf },
				                 m_bl_mynn_mixlength{ x.m_bl_mynn_mixlength },
				                 m_bl_mynn_edmf{ x.m_bl_mynn_edmf },
				                 m_bl_mynn_tkeadvect{ x.m_bl_mynn_tkeadvect },
				                 m_bl_mynn_edmf_mon{ x.m_bl_mynn_edmf_mom },
				                 m_bl_mynn_edmf_tke{ x.m_bl_mynn_edmf_tke },
				                 m_bl_mynn_edmf_part{ x.m_bl_mynn_edmf_part },
				                 m_bl_mynn_cloudmix{ x.m_bl_mynn_cloudmix },
				                 m_bl_mynn_mixqt{ x.m_bl_mynn_mixqt },
				                 m_icloud_bl{ x.m_icloud_bl },
				                 m_FLAG_QI{ x.m_FLAG_QI },
				                 m_FLAG_QNI{ x.m_FLAG_QNI },
				                 m_FLAG_QC{ x.m_FLAG_QC },
				                 m_FLAG_QNC{ x.m_FLAG_QNC },
				                 m_IDS{ x.m_IDS },
				                 m_IDE{ x.m_IDE },
				                 m_JDS{ x.m_JDS },
				                 m_JDE{ x.m_JDE },
				                 m_KDS{ x.m_KDS },
				                 m_KDE{ x.m_KDE },
				                 m_IMS{ x.m_IMS },
				                 m_IME{ x.m_IME },
				                 m_JMS{ x.m_JMS },
				                 m_JME{ x.m_JME },
				                 m_KMS{ x.m_KMS },
				                 m_KME{ x.m_KME },
				                 m_ITS{ x.m_ITS },
				                 m_ITE{ x.m_ITE },
				                 m_JTS{ x.m_JTS },
				                 m_JTE{ x.m_JTE },
				                 m_KTS{ x.m_KTS },
				                 m_KTE{ x.m_KTE },
#if WRF_CHEM == 1
				                 m_nchem{ x.m_nchem },
				                 m_kdvel{ x.m_kdvel },
				                 m_ndvel{ x.m_ndvel },
				                 m_num_vert_mix{ x.m_num_vert_mix },

#endif
				                 m_delt{ x.m_delt },
				                 m_dx{ x.m_dx }
					 {

						 // Reassign x's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&x.m_dz)[i]) {
								 (&this->m_dz)[i] = (&x.m_dz)[i];
							 }
						 }
#if WRF_CHEM == 1
						 this->m_chem3D = x.m_chem3D;
						 this->m_vd3d = x.m_vd3d;
#endif
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
#if defined WRF_CHEM == 1

						 x.m_chem3D = NULL;
						 x.m_vd3d = NULL;
#endif
						 x.m_IMS = 0;
						 x.m_IME = 0;
						 x.m_KMS = 0;
						 x.m_KME = 0;
						 x.m_JMS = 0;
						 x.m_JME = 0;
						 
			}

					 /*
						@Purpose:
									Class Destructor.
					 */
					 ~Wrap_Mynn_Bl_Driver() {
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i]) {
								 _mm_free((&this->m_dz)[i]);
							 }
						 }
#if WRF_CHEM == 1
						 _mm_free(this->m_chem3D);
						 _mm_free(this->m_vd3d);
						 this->m_chem3D = NULL;
						 this->m_vd3d = NULL;
#endif
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = NULL;
						 }
						 this->m_IMS = 0;
						 this->m_IME = 0;
						 this->m_KMS = 0;
						 this->m_KME = 0;
						 this->m_JMS = 0;
						 this->m_JME = 0;
			 }

					 /*
						@Purpose:
								  Copy-assign Operator implements deep copy semantics.
					 */
					 Wrap_Mynn_Bl_Driver & operator=(_In_ const Wrap_Mynn_Bl_Driver &x) {
						 if (this == &x) return (*this);

						 this->m_initflag = x.m_initflag;
						 this->m_grav_settling = x.m_grav_settling;
						 this->m_bl_mynn_tkebudget = x.m_bl_mynn_tkebudget;
						 this->m_bl_mynn_cloudpdf = x.m_bl_mynn_cloudpdf;
						 this->m_bl_mixlength = x.m_bl_mixlength;
						 this->m_bl_mynn_edmf = x.m_bl_mynn_edmf;
						 this->m_bl_mynn_tkeadvect = x.m_bl_mynn_tkeadvect;
						 this->m_bl_mynn_edmf_mom = x.m_bl_mynn_edmf_mom;
						 this->m_bl_mynn_edmf_tke = x.m_bl_mynn_edmf_tke;
						 this->m_bl_mynn_edmf_part = x.m_bl_mynn_edmf_part;
						 this->m_bl_mynn_cloudmix = x.m_bl_mynn_cloudmix;
						 this->m_bl_mynn_mixqt = x.m_bl_mynn_mixqt;
						 this->m_icloud_bl = x.m_icloud_bl;
						 this->m_FLAG_QI = x.m_FLAG_QI;
						 this->m_FLAG_QNI = x.m_FLAG_QNI;
						 this->m_FLAG_QC = x.m_FLAG_QC;
						 this->m_FLAG_QNC = x.m_FLAG_QNC;
						 this->m_IDS = x.m_IDS;
						 this->m_IDE = x.m_IDE;
						 this->m_JDS = x.m_JDS;
						 this->m_JDE = x.m_JDE;
						 this->m_KDS = x.m_KDS;
						 this->m_KDE = x.m_KDE;
						 this->m_IMS = x.m_IMS;
						 this->m_IME = x.m_IME;
						 this->m_JMS = x.m_JMS;
						 this->m_JME = x.m_JME;
						 this->m_KMS = x.m_KMS;
						 this->m_KME = x.m_KME;
						 this->m_ITS = x.m_ITS;
						 this->m_ITE = x.m_ITE;
						 this->m_JTS = x.m_JTS;
						 this->m_JTE = x.m_JTE;
						 this->m_KTS = x.m_KTS;
						 this->m_KTE = x.m_KTE;
#if WRF_CHEM == 1
						 this->m_nchem = x.m_nchem;
						 this->m_kdvel = x.m_kdvel;
						 this->m_ndvel = x.m_ndvel;
						 this->m_num_vert_mix = x.m_num_vert_mix;
#endif
						 this->m_delt = x.m_delt;
						 this->m_dx = x.m_dx;
						 constexpr int ntPtrs3D{44};
						 R32 *tPtrs3D[ntPtrs3D] = {};
						 for (int i{ 0 }; i != this->m_totArrays3D; ++i) {
							 tPtrs3D[i] = reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KME * m_JME * sizeof(R32)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_totArrays3D; ++i) {
							 if (tPtrs3D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mynn_Bl_Driver'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 3D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs3D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 }
						 }
						 constexpr int ntPtrs2D{19};
						 R32  *tPtrs2D[ntPtrs2D] = {};
						 for (int i{ 0 }; i != this->m_totArrays2D; ++i) {
							 tPtrs2D[i] = reinterpret_cast<R32*>(_mm_malloc((m_IME * m_JME * sizeof(R32)),align32B));
						 }
						 for (int i{ 0 }; i != this->m_totArrays2D; ++i) {
							 if (tPtrs2D[i] == NULL) {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mynn_Bl_Driver'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at index: " << i << " heap address: " << std::hex << "0x" << tPtrs2D[i] << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 }
						 }
						 // Copy caller's input arrays.
						 // Using OpenMP for outermost loop 
						 // and vectorization for innermost loop.
						 // Arrays 3D first to be copied.
#if defined (USE_ICL_OPENMP) && \
OPENMP_CURR_VER >= 40

#pragma omp parallel for if((m_IME * m_KME * m_JME) >= (1 << 20))					
						 for (int i = m_IMS; i != m_IME; ++i) {
							 for (int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for(int j = m_JMS; j != m_JME; ++j) {
									 tPtrs3D[0][i + m_IME * k + m_KME * j] = x.m_dz[i + m_IME * k + m_KME * j];
									 tPtrs3D[1][i + m_IME * k + m_KME * j] = x.m_u[i + m_IME * k + m_KME * j];
									 tPtrs3D[2][i + m_IME * k + m_KME * j] = x.m_v[i + m_IME * k + m_KME * j];
									 tPtrs3D[3][i + m_IME * k + m_KME * j] = x.m_w[i + m_IME * k + m_KME * j];
									 tPtrs3D[4][i + m_IME * k + m_KME * j] = x.m_th[i + m_IME * k + m_KME * j];
									 tPtrs3D[5][i + m_IME * k + m_KME * j] = x.m_qv[i + m_IME * k + m_KME * j];
									 tPtrs3D[6][i + m_IME * k + m_KME * j] =  x.m_p[i + m_IME * k + m_KME * j];
									 tPtrs3D[7][i + m_IME * k + m_KME * j] = x.m_exner[i + m_IME * k + m_KME * j];
									 tPtrs3D[8][i + m_IME * k + m_KME * j] = x.m_rho[i + m_IME * k + m_KME * j];
									 tPtrs3D[9][i + m_IME * k + m_KME * j] = x.m_T3D[i + m_IME * k + m_KME * j];
									 tPtrs3D[10][i + m_IME * k + m_KME * j] = x.m_qc[i + m_IME * k + m_KME * j];
									 tPtrs3D[11][i + m_IME * k + m_KME * j] = x.m_qi[i + m_IME * k + m_KME * j];
									 tPtrs3D[12][i + m_IME * k + m_KME * j] = x.m_qni[i + m_IME * k + m_KME * j];
									 tPtrs3D[13][i + m_IME * k + m_KME * j] = x.m_qnc[i + m_IME * k + m_KME * j];
									 tPtrs3D[14][i + m_IME * k + m_KME * j] = x.m_Qke[i + m_IME * k + m_KME * j];
									 tPtrs3D[15][i + m_IME * k + m_KME * j] = x.m_Tsq[i + m_IME * k + m_KME * j];
									 tPtrs3D[16][i + m_IME * k + m_KME * j] = x.m_Qsq[i + m_IME * k + m_KME * j];
									 tPtrs3D[17][i + m_IME * k + m_KME * j] = x.m_Cov[i + m_IME * k + m_KME * j];
									 tPtrs3D[18][i + m_IME * k + m_KME * j] = x.m_tke_pbl[i + m_IME * k + m_KME * j];
									 tPtrs3D[19][i + m_IME * k + m_KME * j] = x.m_qke_adv[i + m_IME * k + m_KME * j];
									 tPtrs3D[20][i + m_IME * k + m_KME * j] = x.m_RUBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[21][i + m_IME * k + m_KME * j] = x.m_RVBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[22][i + m_IME * k + m_KME * j] = x.m_RTHBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[23][i + m_IME * k + m_KME * j] = x.m_RQVBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[24][i + m_IME * k + m_KME * j] = x.m_RQCBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[25][i + m_IME * k + m_KME * j] = x.m_RQIBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[26][i + m_IME * k + m_KME * j] = x.m_RQNBLTEN[i + m_IME * k + m_KME * j];
									 tPtrs3D[27][i + m_IME * k + m_KME * j] = x.m_exch_h[i + m_IME * k + m_KME * j];
									 tPtrs3D[28][i + m_IME * k + m_KME * j] = x.m_exch_m[i + m_IME * k + m_KME * j];
									 tPtrs3D[29][i + m_IME * k + m_KME * j] = x.m_edmf_a[i + m_IME * k + m_KME * j];
									 tPtrs3D[30][i + m_IME * k + m_KME * j] = x.m_edmf_w[i + m_IME * k + m_KME * j];
									 tPtrs3D[31][i + m_IME * k + m_KME * j] = x.m_edmf_qt[i + m_IME * k + m_KME * j];
									 tPtrs3D[32][i + m_IME * k + m_KME * j] = x.m_edmf_thl[i + m_IME * k + m_KME * j];
									 tPtrs3D[33][i + m_IME * k + m_KME * j] = x.m_edmf_ent[i + m_IME * k + m_KME * j];
									 tPtrs3D[34][i + m_IME * k + m_KME * j] = x.m_edmf_qc[i + m_IME * k + m_KME * j];
									 tPtrs3D[35][i + m_IME * k + m_KME * j] = x.m_el_pbl[i + m_IME * k + m_KME * j];
									 tPtrs3D[36][i + m_IME * k + m_KME * j] = x.m_qWT[i + m_IME * k + m_KME * j];
									 tPtrs3D[37][i + m_IME * k + m_KME * j] = x.m_qSHEAR[i + m_IME * k + m_KME * j];
									 tPtrs3D[38][i + m_IME * k + m_KME * j] = x.m_qBUOY[i + m_IME * k + m_KME * j];
									 tPtrs3D[39][i + m_IME * k + m_KME * j] = x.m_qDISS[i + m_IME * k + m_KME * j];
									 tPtrs3D[40][i + m_IME * k + m_KME * j] = x.m_dqke[i + m_IME * k + m_KME * j];
									 tPtrs3D[41][i + m_IME * k + m_KME * j] = x.m_qc_bl[i + m_IME * k + m_KME * j];
									 tPtrs3D[42][i + m_IME * k + m_KME * j] = x.m_cldfra_bl[i + m_IME * k + m_KME * j];
									 tPtrs3D[43][i + m_IME * k + m_KME * j] = x.m_Sh3D[i + m_IME * k + m_KME * j];
								 }
							 }
						 }

#if WRF_CHEM == 1

						 R32* __restrict tchem3D = reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KTE * m_JME * m_nchem * sizeof(R32)),align32B));
						 if (tchem3D) {
							 for (int i = m_IMS; i != m_IME; ++i) {
								 for (int k = m_KTS; k != m_KTE; ++k) {
									 for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
										 for (int n = 0; n != m_nchem; ++n) {
											 tchem3D[i + m_IME * k + m_KME * j + m_JME * n] = x.m_chem3D[i + m_IME * k + m_KME * j + m_JME * n];
										 }
									 }
								 }
							 }
							 _mm_free(this->m_chem3D);
							 this->m_chem3D = tchem3D;
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mynn_Bl_Driver'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Checking allocation of temporary arrays 2D\.n";
							 std::cerr << "Failure detected at heap address: " << std::hex << "0x" << tchem3D << "\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
						 }
						 R32* __restrict tvd3D = reinterpret_cast<R32*>(_mm_malloc((m_IME * m_kdvel * m_JME * m_ndvel * sizeof(R32)),align32B));
						 if (tvd3D) {
							 for (int i = m_IMS; i != m_IME; ++i) {
								 for (int k = 0; k != m_kdvel; ++k) {
									 for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
										 for (int n = 0; n != m_ndvel; ++n) {
											 tvd3D[i + m_IME * k + m_kdvel * j + m_JME * n] = x.m_vd3d[i + m_IME * k + m_kdvel * j + m_JME * n];
										 }
									 }
								 }
							 }
							 _mm_free(this->m_vd3d);
							 this->m_vd3d = tvd3D;
						 }
						 else {
							 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mynn_Bl_Driver'!!\n";
							 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
							 std::cerr << "***** ERROR-DETAILS ***** \n";
							 std::cerr << "Checking allocation of temporary arrays 2D\.n";
							 std::cerr << "Failure detected at heap address: " << std::hex << "0x" << tvd3D << "\n";
							 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
						 }

#endif
						 // Copy caller's input arrays.
						 // Using OpenMP for outermost loop 
						 // and vectorization for innermost loop.
						 // Arrays 2D first to be copied.
#pragma omp parallel for if((m_IME * m_JME) >= (1 << 20))
						 for (int i = m_IMS; i != m_IME; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
							 for (int j = m_JMS; j != m_JME; ++j) {
								 tPtrs2D[0][i + m_IME * j] = x.m_xland[i + m_IME * j];
								 tPtrs2D[1][i + m_IME * j] = x.m_ust[i + m_IME * j];
								 tPtrs2D[2][i + m_IME * j] = x.m_ch[i + m_IME * j];
								 tPtrs2D[3][i + m_IME * j] = x.m_rmol[i + m_IME * j];
								 tPtrs2D[4][i + m_IME * j] = x.m_ts[i + m_IME * j];
								 tPtrs2D[5][i + m_IME * j] = x.m_qsfc[i + m_IME * j];
								 tPtrs2D[6][i + m_IME * j] = x.m_qcg[i + m_IME * j];
								 tPtrs2D[7][i + m_IME * j] = x.m_ps[i + m_IME * j];
								 tPtrs2D[8][i + m_IME * j] = x.m_hfx[i + m_IME * j];
								 tPtrs2D[9][i + m_IME * j] = x.m_qfx[i + m_IME * j];
								 tPtrs2D[10][i + m_IME * j] = x.m_wspd[i + m_IME * j];
								 tPtrs2D[11][i + m_IME * j] = x.m_uoce[i + m_IME * j];
								 tPtrs2D[12][i + m_IME * j] = x.m_voce[i + m_IME * j];
								 tPtrs2D[13][i + m_IME * j] = x.m_vdfg[i + m_IME * j];
								 tPtrs2D[14][i + m_IME * j] = x.m_znt[i + m_IME * j];
								 tPtrs2D[15][i + m_IME * j] = x.m_Pblh[i + m_IME * j];
								 tPtrs2D[16][i + m_IME * j] = x.m_wstar[i + m_IME * j];
								 tPtrs2D[17][i + m_IME * j] = x.m_delta[i + m_IME * j];
								 tPtrs2D[18][i + m_IME * j] = x.m_KPBL[i + m_IME * j];
							 }
						 }
						 // Deallocate current context of *this.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 _mm_free((&this->m_dz)[i]);
						 }
						 // Reassign temporay pointers to member pointers.
						 this->m_dz = tPtrs3D[0];
						 this->m_u = tPtrs3D[1];
						 this->m_v = tPtrs3D[2];
						 this->m_w = tPtrs3D[3];
						 this->m_th = tPtrs3D[4];
						 this->m_qv = tPtrs3D[5];
						 this->m_p = tPtrs3D[6];
						 this->m_exner = tPtrs3D[7];
						 this->m_rho = tPtrs3D[8];
						 this->m_T3D = tPtrs3D[9];
						 this->m_qc = tPtrs3D[10];
						 this->m_qi = tPtrs3D[11];
						 this->m_qni = tPtrs3D[12];
						 this->m_qnc = tPtrs3D[13];
						 this->m_xland = tPtrs2D[0];
						 this->m_ust = tPtrs2D[1];
						 this->m_ch = tPtrs2D[2];
						 this->m_rmol = tPtrs2D[3];
						 this->m_ts = tPtrs2D[4];
						 this->m_qsfc = tPtrs2D[5];
						 this->m_qcg = tPtrs2D[6];
						 this->m_ps = tPtrs2D[7];
						 this->m_hfx = tPtrs2D[8];
						 this->m_qfx = tPtrs2D[9];
						 this->m_wspd = tPtrs2D[10];
						 this->m_uoce = tPtrs2D[11];
						 this->m_voce = tPtrs2D[12];
						 this->m_vdfg = tPtrs2D[13];
						 this->m_znt = tPtrs2D[14];
						 this->m_Qke = tPtrs3D[14];
						 this->m_Tsq = tPtrs3D[15];
						 this->m_Qsq = tPtrs3D[16];
						 this->m_Cov = tPtrs3D[17];
						 this->m_tke_pbl = tPtrs3D[18];
						 this->m_qke_adv = tPtrs3D[19];
						 this->m_RUBLTEN = tPtrs3D[20];
						 this->m_RVBLTEN = tPtrs3D[21];
						 this->m_RTHBLTEN = tPtrs3D[22];
						 this->m_RQVBLTEN = tPtrs3D[23];
						 this->m_RQCBLTEN = tPtrs3D[24];
						 this->m_RQIBLTEN = tPtrs3D[25];
						 this->m_RQNBLTEN = tPtrs3D[26];
						 this->m_exch_h = tPtrs3D[27];
						 this->m_exch_m = tPtrs3D[28];
						 this->m_edmf_a = tPtrs3D[29];
						 this->m_edmf_w = tPtrs3D[30];
						 this->m_edmf_qt = tPtrs3D[31];
						 this->m_edmf_thl = tPtrs3D[32];
						 this->m_edmf_ent = tPtrs3D[33];
						 this->m_edmf_qc = tPtrs3D[34];
						 this->m_Pblh = tPtrs2D[15];
						 this->m_wstar = tPtrs2D[16];
						 this->m_delta = tPtrs2D[17];
						 this->m_KPBL = tPtrs2D[18];
						 
						 this->m_el_pbl = tPtrs3D[35];
						 this->m_qWT = tPtrs3D[36];
						 this->m_qSHEAR = tPtrs3D[37];
						 this->m_qBUOY = tPtrs3D[38];
						 this->m_qDISS = tPtrs3D[39];
						 this->m_dqke = tPtrs3D[40];
						 this->m_qc_bl = tPtrs3D[41];
						 this->m_cldfra_bl = tPtrs3D[42];
						 this->m_Sh3D = tPtrs3D[43];

						 return (*this);
#else

                             for (int i = m_IMS; i != m_IME; ++i) {
	                             for (int k = m_KMS; k != m_KME; ++k) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
		                               for (int j = m_JMS; j != m_JME; ++j) {
			                                tPtrs3D[0][i + m_IME * k + m_KME * j] = x.m_dz[i + m_IME * k + m_KME * j];
			                                tPtrs3D[1][i + m_IME * k + m_KME * j] = x.m_u[i + m_IME * k + m_KME * j];
			                                tPtrs3D[2][i + m_IME * k + m_KME * j] = x.m_v[i + m_IME * k + m_KME * j];
			                                tPtrs3D[3][i + m_IME * k + m_KME * j] = x.m_w[i + m_IME * k + m_KME * j];
			                                tPtrs3D[4][i + m_IME * k + m_KME * j] = x.m_th[i + m_IME * k + m_KME * j];
			                                tPtrs3D[5][i + m_IME * k + m_KME * j] = x.m_qv[i + m_IME * k + m_KME * j];
			                                tPtrs3D[6][i + m_IME * k + m_KME * j] = x.m_p[i + m_IME * k + m_KME * j];
			                                tPtrs3D[7][i + m_IME * k + m_KME * j] = x.m_exner[i + m_IME * k + m_KME * j];
			                                tPtrs3D[8][i + m_IME * k + m_KME * j] = x.m_rho[i + m_IME * k + m_KME * j];
			                                tPtrs3D[9][i + m_IME * k + m_KME * j] = x.m_T3D[i + m_IME * k + m_KME * j];
			                                tPtrs3D[10][i + m_IME * k + m_KME * j] = x.m_qc[i + m_IME * k + m_KME * j];
			                                tPtrs3D[11][i + m_IME * k + m_KME * j] = x.m_qi[i + m_IME * k + m_KME * j];
			                                tPtrs3D[12][i + m_IME * k + m_KME * j] = x.m_qni[i + m_IME * k + m_KME * j];
			                                tPtrs3D[13][i + m_IME * k + m_KME * j] = x.m_qnc[i + m_IME * k + m_KME * j];
			                                tPtrs3D[14][i + m_IME * k + m_KME * j] = x.m_Qke[i + m_IME * k + m_KME * j];
			                                tPtrs3D[15][i + m_IME * k + m_KME * j] = x.m_Tsq[i + m_IME * k + m_KME * j];
			                                tPtrs3D[16][i + m_IME * k + m_KME * j] = x.m_Qsq[i + m_IME * k + m_KME * j];
			                                tPtrs3D[17][i + m_IME * k + m_KME * j] = x.m_Cov[i + m_IME * k + m_KME * j];
			                                tPtrs3D[18][i + m_IME * k + m_KME * j] = x.m_tke_pbl[i + m_IME * k + m_KME * j];
			                                tPtrs3D[19][i + m_IME * k + m_KME * j] = x.m_qke_adv[i + m_IME * k + m_KME * j];
			                                tPtrs3D[20][i + m_IME * k + m_KME * j] = x.m_RUBLTEN[i + m_IME * k + m_KME * j];
			                                tPtrs3D[21][i + m_IME * k + m_KME * j] = x.m_RVBLTEN[i + m_IME * k + m_KME * j];
			                                tPtrs3D[22][i + m_IME * k + m_KME * j] = x.m_RTHBLTEN[i + m_IME * k + m_KME * j];
			                                tPtrs3D[23][i + m_IME * k + m_KME * j] = x.m_RQVBLTEN[i + m_IME * k + m_KME * j];
			                                tPtrs3D[24][i + m_IME * k + m_KME * j] = x.m_RQCBLTEN[i + m_IME * k + m_KME * j];
			                                tPtrs3D[25][i + m_IME * k + m_KME * j] = x.m_RQIBLTEN[i + m_IME * k + m_KME * j];
			                                tPtrs3D[26][i + m_IME * k + m_KME * j] = x.m_RQNBLTEN[i + m_IME * k + m_KME * j];
			                                tPtrs3D[27][i + m_IME * k + m_KME * j] = x.m_exch_h[i + m_IME * k + m_KME * j];
			                                tPtrs3D[28][i + m_IME * k + m_KME * j] = x.m_exch_m[i + m_IME * k + m_KME * j];
			                                tPtrs3D[29][i + m_IME * k + m_KME * j] = x.m_edmf_a[i + m_IME * k + m_KME * j];
			                                tPtrs3D[30][i + m_IME * k + m_KME * j] = x.m_edmf_w[i + m_IME * k + m_KME * j];
			                                tPtrs3D[31][i + m_IME * k + m_KME * j] = x.m_edmf_qt[i + m_IME * k + m_KME * j];
			                                tPtrs3D[32][i + m_IME * k + m_KME * j] = x.m_edmf_thl[i + m_IME * k + m_KME * j];
			                                tPtrs3D[33][i + m_IME * k + m_KME * j] = x.m_edmf_ent[i + m_IME * k + m_KME * j];
			                                tPtrs3D[34][i + m_IME * k + m_KME * j] = x.m_edmf_qc[i + m_IME * k + m_KME * j];
			                                tPtrs3D[35][i + m_IME * k + m_KME * j] = x.m_el_pbl[i + m_IME * k + m_KME * j];
			                                tPtrs3D[36][i + m_IME * k + m_KME * j] = x.m_qWT[i + m_IME * k + m_KME * j];
			                                tPtrs3D[37][i + m_IME * k + m_KME * j] = x.m_qSHEAR[i + m_IME * k + m_KME * j];
			                                tPtrs3D[38][i + m_IME * k + m_KME * j] = x.m_qBUOY[i + m_IME * k + m_KME * j];
			                                tPtrs3D[39][i + m_IME * k + m_KME * j] = x.m_qDISS[i + m_IME * k + m_KME * j];
			                                tPtrs3D[40][i + m_IME * k + m_KME * j] = x.m_dqke[i + m_IME * k + m_KME * j];
			                                tPtrs3D[41][i + m_IME * k + m_KME * j] = x.m_qc_bl[i + m_IME * k + m_KME * j];
			                                tPtrs3D[42][i + m_IME * k + m_KME * j] = x.m_cldfra_bl[i + m_IME * k + m_KME * j];
			                                tPtrs3D[43][i + m_IME * k + m_KME * j] = x.m_Sh3D[i + m_IME * k + m_KME * j];
		                                  }
	                                  }
                                  }

#if WRF_CHEM == 1

							 R32* __restrict tchem3D = reinterpret_cast<R32*>(_mm_malloc((m_IME * m_KTE * m_JME * m_nchem * sizeof(R32)), align32B));
							 if (tchem3D) {
								 for (int i = m_IMS; i != m_IME; ++i) {
									 for (int k = m_KTS; k != m_KTE; ++k) {
										 for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
											 for (int n = 0; n != m_nchem; ++n) {
												 tchem3D[i + m_IME * k + m_KME * j + m_JME * n] = x.m_chem3D[i + m_IME * k + m_KME * j + m_JME * n];
											 }
										 }
									 }
								 }
								 _mm_free(this->m_chem3D);
								 this->m_chem3D = tchem3D;
							 }
							 else {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mynn_Bl_Driver'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at heap address: " << std::hex << "0x" << tchem3D << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 }
							 R32* __restrict tvd3D = reinterpret_cast<R32*>(_mm_malloc((m_IME * m_kdvel * m_JME * m_ndvel * sizeof(R32)), align32B));
							 if (tvd3D) {
								 for (int i = m_IMS; i != m_IME; ++i) {
									 for (int k = 0; k != m_kdvel; ++k) {
										 for (int j = m_JMS; j != m_JME; ++j) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
											 for (int n = 0; n != m_ndvel; ++n) {
												 tvd3D[i + m_IME * k + m_kdvel * j + m_JME * n] = x.m_vd3d[i + m_IME * k + m_kdvel * j + m_JME * n];
											 }
										 }
									 }
								 }
								 _mm_free(this->m_vd3d);
								 this->m_vd3d = tvd3D;
							 }
							 else {
								 std::cerr << "[" << __DATE__ << ":" << __TIME__ << "]" << "FATAL ERROR: Memory allocation failure in Copy Operator: 'Wrap_Mynn_Bl_Driver'!!\n";
								 std::cerr << "at " << __FILE__ << ":" << __LINE__ << "(" << std::hex << "0x" << __FUNCTIONW__ << ")" << "\n";
								 std::cerr << "***** ERROR-DETAILS ***** \n";
								 std::cerr << "Checking allocation of temporary arrays 2D\.n";
								 std::cerr << "Failure detected at heap address: " << std::hex << "0x" << tvd3D << "\n";
								 std::cerr << "Cannot recover, hence on first failure occurrence --> calling exit(-1)!!\n";
							 }

#endif

							 for (int i = m_IMS; i != m_IME; ++i) {
#if defined (USE_AUTO_VECTORIZATION)
#pragma ivdep
#pragma simd
#pragma unroll(UNROLL_4X)
#endif
								 for (int j = m_JMS; j != m_JME; ++j) {
									 tPtrs2D[0][i + m_IME * j] = x.m_xland[i + m_IME * j];
									 tPtrs2D[1][i + m_IME * j] = x.m_ust[i + m_IME * j];
									 tPtrs2D[2][i + m_IME * j] = x.m_ch[i + m_IME * j];
									 tPtrs2D[3][i + m_IME * j] = x.m_rmol[i + m_IME * j];
									 tPtrs2D[4][i + m_IME * j] = x.m_ts[i + m_IME * j];
									 tPtrs2D[5][i + m_IME * j] = x.m_qsfc[i + m_IME * j];
									 tPtrs2D[6][i + m_IME * j] = x.m_qcg[i + m_IME * j];
									 tPtrs2D[7][i + m_IME * j] = x.m_ps[i + m_IME * j];
									 tPtrs2D[8][i + m_IME * j] = x.m_hfx[i + m_IME * j];
									 tPtrs2D[9][i + m_IME * j] = x.m_qfx[i + m_IME * j];
									 tPtrs2D[10][i + m_IME * j] = x.m_wspd[i + m_IME * j];
									 tPtrs2D[11][i + m_IME * j] = x.m_uoce[i + m_IME * j];
									 tPtrs2D[12][i + m_IME * j] = x.m_voce[i + m_IME * j];
									 tPtrs2D[13][i + m_IME * j] = x.m_vdfg[i + m_IME * j];
									 tPtrs2D[14][i + m_IME * j] = x.m_znt[i + m_IME * j];
									 tPtrs2D[15][i + m_IME * j] = x.m_Pblh[i + m_IME * j];
									 tPtrs2D[16][i + m_IME * j] = x.m_wstar[i + m_IME * j];
									 tPtrs2D[17][i + m_IME * j] = x.m_delta[i + m_IME * j];
									 tPtrs2D[18][i + m_IME * j] = x.m_KPBL[i + m_IME * j];
								 }
							 }


							 // Deallocate current context of *this.
							 for (int i{ 0 }; i != this->m_totArrays; ++i) {
								 _mm_free((&this->m_dz)[i]);
							 }
							 // Reassign temporay pointers to member pointers.
							 this->m_dz = tPtrs3D[0];
							 this->m_u = tPtrs3D[1];
							 this->m_v = tPtrs3D[2];
							 this->m_w = tPtrs3D[3];
							 this->m_th = tPtrs3D[4];
							 this->m_qv = tPtrs3D[5];
							 this->m_p = tPtrs3D[6];
							 this->m_exner = tPtrs3D[7];
							 this->m_rho = tPtrs3D[8];
							 this->m_T3D = tPtrs3D[9];
							 this->m_qc = tPtrs3D[10];
							 this->m_qi = tPtrs3D[11];
							 this->m_qni = tPtrs3D[12];
							 this->m_qnc = tPtrs3D[13];
							 this->m_xland = tPtrs2D[0];
							 this->m_ust = tPtrs2D[1];
							 this->m_ch = tPtrs2D[2];
							 this->m_rmol = tPtrs2D[3];
							 this->m_ts = tPtrs2D[4];
							 this->m_qsfc = tPtrs2D[5];
							 this->m_qcg = tPtrs2D[6];
							 this->m_ps = tPtrs2D[7];
							 this->m_hfx = tPtrs2D[8];
							 this->m_qfx = tPtrs2D[9];
							 this->m_wspd = tPtrs2D[10];
							 this->m_uoce = tPtrs2D[11];
							 this->m_voce = tPtrs2D[12];
							 this->m_vdfg = tPtrs2D[13];
							 this->m_znt = tPtrs2D[14];
							 this->m_Qke = tPtrs3D[14];
							 this->m_Tsq = tPtrs3D[15];
							 this->m_Qsq = tPtrs3D[16];
							 this->m_Cov = tPtrs3D[17];
							 this->m_tke_pbl = tPtrs3D[18];
							 this->m_qke_adv = tPtrs3D[19];
							 this->m_RUBLTEN = tPtrs3D[20];
							 this->m_RVBLTEN = tPtrs3D[21];
							 this->m_RTHBLTEN = tPtrs3D[22];
							 this->m_RQVBLTEN = tPtrs3D[23];
							 this->m_RQCBLTEN = tPtrs3D[24];
							 this->m_RQIBLTEN = tPtrs3D[25];
							 this->m_RQNBLTEN = tPtrs3D[26];
							 this->m_exch_h = tPtrs3D[27];
							 this->m_exch_m = tPtrs3D[28];
							 this->m_edmf_a = tPtrs3D[29];
							 this->m_edmf_w = tPtrs3D[30];
							 this->m_edmf_qt = tPtrs3D[31];
							 this->m_edmf_thl = tPtrs3D[32];
							 this->m_edmf_ent = tPtrs3D[33];
							 this->m_edmf_qc = tPtrs3D[34];
							 this->m_Pblh = tPtrs2D[15];
							 this->m_wstar = tPtrs2D[16];
							 this->m_delta = tPtrs2D[17];
							 this->m_KPBL = tPtrs2D[18];

							 this->m_el_pbl = tPtrs3D[35];
							 this->m_qWT = tPtrs3D[36];
							 this->m_qSHEAR = tPtrs3D[37];
							 this->m_qBUOY = tPtrs3D[38];
							 this->m_qDISS = tPtrs3D[39];
							 this->m_dqke = tPtrs3D[40];
							 this->m_qc_bl = tPtrs3D[41];
							 this->m_cldfra_bl = tPtrs3D[42];
							 this->m_Sh3D = tPtrs3D[43];

							 return (*this);
#endif




			}

			       /*
					  @Purpose:
						        Move-assign Operator implements shallow copy semantics.
			       */
					 Wrap_Mynn_Bl_Driver & operator=(_In_ Wrap_Mynn_Bl_Driver &&x) {
						 if (this == &x) return (*this);

						 this->m_initflag = x.m_initflag;
						 this->m_grav_settling = x.m_grav_settling;
						 this->m_bl_mynn_tkebudget = x.m_bl_mynn_tkebudget;
						 this->m_bl_mynn_cloudpdf = x.m_bl_mynn_cloudpdf;
						 this->m_bl_mixlength = x.m_bl_mixlength;
						 this->m_bl_mynn_edmf = x.m_bl_mynn_edmf;
						 this->m_bl_mynn_tkeadvect = x.m_bl_mynn_tkeadvect;
						 this->m_bl_mynn_edmf_mom = x.m_bl_mynn_edmf_mom;
						 this->m_bl_mynn_edmf_tke = x.m_bl_mynn_edmf_tke;
						 this->m_bl_mynn_edmf_part = x.m_bl_mynn_edmf_part;
						 this->m_bl_mynn_cloudmix = x.m_bl_mynn_cloudmix;
						 this->m_bl_mynn_mixqt = x.m_bl_mynn_mixqt;
						 this->m_icloud_bl = x.m_icloud_bl;
						 this->m_FLAG_QI = x.m_FLAG_QI;
						 this->m_FLAG_QNI = x.m_FLAG_QNI;
						 this->m_FLAG_QC = x.m_FLAG_QC;
						 this->m_FLAG_QNC = x.m_FLAG_QNC;
						 this->m_IDS = x.m_IDS;
						 this->m_IDE = x.m_IDE;
						 this->m_JDS = x.m_JDS;
						 this->m_JDE = x.m_JDE;
						 this->m_KDS = x.m_KDS;
						 this->m_KDE = x.m_KDE;
						 this->m_IMS = x.m_IMS;
						 this->m_IME = x.m_IME;
						 this->m_JMS = x.m_JMS;
						 this->m_JME = x.m_JME;
						 this->m_KMS = x.m_KMS;
						 this->m_KME = x.m_KME;
						 this->m_ITS = x.m_ITS;
						 this->m_ITE = x.m_ITE;
						 this->m_JTS = x.m_JTS;
						 this->m_JTE = x.m_JTE;
						 this->m_KTS = x.m_KTS;
						 this->m_KTE = x.m_KTE;
#if WRF_CHEM == 1
						 this->m_nchem = x.m_nchem;
						 this->m_kdvel = x.m_kdvel;
						 this->m_ndvel = x.m_ndvel;
						 this->m_num_vert_mix = x.m_num_vert_mix;
#endif
						 this->m_delt = x.m_delt;
						 this->m_dx = x.m_dx;
						 // Deallocate current context.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 if ((&this->m_dz)[i]) {
								 _mm_free((&this->m_dz)[i]);
							 }
						 }
#if WRF_CHEM == 1
						 _mm_free(this->m_chem3D);
						 _mm_free(this->m_vd3d);
						 this->m_chem3D = x.m_chem3D;
						 this->m_vd3d = x.m_vd3d;
						 x.m_chem3D = NULL;
						 x.m_vd3d = NULL;
#endif
						 // Reassign x's pointers to *this's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&this->m_dz)[i] = (&x.m_dz)[i];
						 }
						 // Nullify x's pointers.
						 for (int i{ 0 }; i != this->m_totArrays; ++i) {
							 (&x.m_dz)[i] = NULL;
						 }
						 x.m_IMS = 0;
						 x.m_IME = 0;
						 x.m_KMS = 0;
						 x.m_KME = 0;
						 x.m_JMS = 0;
						 x.m_JME = 0;

						 return (*this);
			}

				/*
					@Purpose:
							  Call Fortran 90 MYNN_BL_DRIVER subroutine.
				*/
					 void  Call_Mynn_Bl_Driver() {

						 MODULE_BL_MYNN_mp_MYNN_BL_DRIVER(&this->m_bl_mixlength, &this->m_grav_settling,
							 &this->m_delt, &this->m_dz[0], &this->m_dx, &this->m_znt[0],
							 &this->m_u[0], &this->m_v[0], &this->m_w[0], &this->m_th[0], &this->m_qv[0], &this->m_qc[0],
							 &this->m_qi[0], &this->m_qni[0], &this->m_qnc[0], &this->m_p[0], &this->m_exner[0], &this->m_rho[0],
							 &this->m_T3D[0], &this->m_xland[0], &this->m_ts[0], &this->m_qsfc[0], &this->m_qcg[0], &this->m_ps[0],
							 &this->m_ust[0], &this->m_ch[0], &this->m_hfx[0], &this->m_qfx[0], &this->m_rmol[0], &this->m_wspd[0],
							 &this->m_uoce[0], &this->m_voce[0], &this->m_vdfg[0], &this->m_Qke[0], &this->m_tke_pbl[0],
							 &this->m_qke_adv[0], &this->m_bl_mynn_tkeadvect,
#if WRF_CHEM == 1
							 &this->m_chem3D[0], &this->m_vd3d[0], &this->m_nchem,
							 &this->m_kdvel, &this->m_ndvel, &this->m_num_vert_mix,
#endif							
							 &this->m_Tsq[0], &this->m_Qsq[0], &this->m_Cov[0],
							 &this->m_RUBLTEN[0], &this->m_RVBLTEN[0], &this->m_RTHBLTEN[0],
							 &this->m_RQVBLTEN[0], &this->m_RQCBLTEN[0], &this->m_RQIBLTEN[0],
							 &this->m_RQNBLTEN[0], &this->m_exch_h[0], &this->m_exch_m[0],
							 &this->m_Pblh[0], &this->m_KPBL[0],
							 &this->m_el_pbl[0], 
							 &this->m_dqke[0], &this->m_qWT[0], &this->m_qSHEAR[0], &this->m_qBUOY[0], &this->m_qDISS[0],
							 &this->m_wstar[0], &this->m_delta[0],
							 &this->m_bl_mynn_tkebudget, &this->m_bl_mynn_cloudpdf, &this->m_Sh3D[0],
							 &this->m_bl_mixlength, &this->m_icloud_bl, &this->m_qc_bl[0], &this->m_cldfra_bl[0],
							 &this->m_bl_mynn_edmf, &this->m_bl_mynn_edmf_mom, &this->m_bl_mynn_edmf_tke,
							 &this->m_bl_mynn_edmf_part, &this->m_bl_mynn_cloudmix, &this->m_bl_mynn_mixqt,
							 &this->m_edmf_a[0], &this->m_edmf_w[0], &this->m_edmf_qt[0],
							 &this->m_edmf_thl[0], &this->m_edmf_ent[0], &this->m_edmf_qc[0],
							 &this->m_FLAG_QI, &this->m_FLAG_QNI, &this->m_FLAG_QC, &this->m_FLAG_QNC,
							 &this->m_IDS, &this->m_IDE, &this->m_JDS, &this->m_JDE, &this->m_KDS, &this->m_KDE,
							 &this->m_IMS, &this->m_IME, &this->m_JMS, &this->m_JME, &this->m_KMS, &this->m_KME,
							 &this->m_ITS, &this->m_ITE, &this->m_JTS, &this->m_JTE, &this->m_KTS, &this->m_KTE)
							 
					 }
				/*
				  @Purpose:
						    Member variables:
				*/

				// Scalar integral variables.

				I32 m_initflag;

				I32 m_grav_settling;

				I32 m_bl_mynn_tkebudget;

				I32 m_bl_mynn_cloudpdf;

				I32 m_bl_mixlength;

				I32 m_bl_mynn_edmf;

				I32 m_bl_mynn_tkeadvect;

				I32 m_bl_mynn_edmf_mom;

				I32 m_bl_mynn_edmf_tke;

				I32 m_bl_mynn_edmf_part;

				I32 m_bl_mynn_cloudmix;

				I32 m_bl_mynn_mixqt;

				I32 m_icloud_bl;

				I32 m_FLAG_QI;

				I32 m_FLAG_QNI;

				I32 m_FLAG_QC;

				I32 m_FLAG_QNC;

				I32 m_IDS;

				I32 m_IDE;

				I32 m_JDS;

				I32 m_JDE;

				I32 m_KDS;

				I32 m_KDE;

				I32 m_IMS;

				I32 m_IME;

				I32 m_JMS;

				I32 m_JME;

				I32 m_KMS;

				I32 m_KME;

				I32 m_ITS;

				I32 m_ITE;

				I32 m_JTS;

				I32 m_JTE;

				I32 m_KTS;

				I32 m_KTE;

#if WRF_CHEM == 1

				I32 m_nchem;

				I32 m_kdvel;

				I32 m_ndvel;

				I32 m_num_vert_mix;

				
#endif

				// Scalar real variables.

				R32 m_delt;

				R32 m_dx;

				// Array real variables.
				// Arrays 3D - Input.

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_dz;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_u;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_v;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_w;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_th;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qv;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_p;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_exner;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_rho;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_T3D;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qc;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qi;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qni;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qnc;

					// Arrays 2D - Input.

_Field_size_(m_IME * m_JME) R32* __restrict m_xland;

_Field_size_(m_IME * m_JME) R32* __restrict m_ust;

_Field_size_(m_IME * m_JME) R32* __restrict m_ch;

_Field_size_(m_IME * m_JME) R32* __restrict m_rmol;

_Field_size_(m_IME * m_JME) R32* __restrict m_ts;

_Field_size_(m_IME * m_JME) R32* __restrict m_qsfc;

_Field_size_(m_IME * m_JME) R32* __restrict m_qcg;

_Field_size_(m_IME * m_JME) R32* __restrict m_ps;

_Field_size_(m_IME * m_JME) R32* __restrict m_hfx;

_Field_size_(m_IME * m_JME) R32* __restrict m_qfx;

_Field_size_(m_IME * m_JME) R32* __restrict m_wspd;

_Field_size_(m_IME * m_JME) R32* __restrict m_uoce;

_Field_size_(m_IME * m_JME) R32* __restrict m_voce;

_Field_size_(m_IME * m_JME) R32* __restrict m_vdfg;

_Field_size_(m_IME * m_JME) R32* __restrict m_znt;

				// Arrays 3D - Input/Output.

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_Qke;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_Tsq;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_Qsq;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_Cov;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_tke_pbl;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qke_adv;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RUBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RVBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RTHBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RQVBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RQCBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RQIBLTEN;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_RQNBLTEN;

					// Arrays 3D - Output.

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_exch_h;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_exch_m;

					// Arrays 3D - Input/Output , [optional]

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_edmf_a;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_edmf_w;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_edmf_qt;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_edmf_thl;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_edmf_ent;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_edmf_qc;

					// Arrays 2D - Input/Output.

_Field_size_(m_IME * m_JME) R32* __restrict m_Pblh;

_Field_size_(m_IME * m_JME) R32* __restrict m_wstar;

_Field_size_(m_IME * m_JME) R32* __restrict m_delta;





_Field_size_(m_IME * m_JME) R32* __restrict m_KPBL;

                     // Arrays 3D - Input/Output and Output.

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_el_pbl;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qWT;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qSHEAR;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qBUOY;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qDISS;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_dqke;

				    // Arrays  3D.





_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_Sh3D;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_qc_bl;

_Field_size_(m_IME * m_KME * m_JME) R32* __restrict m_cldfra_bl;



			// defined if WRF_CHEM == 1 (F90 source)
#if WRF_CHEM == 1

_Field_size_(m_IME * m_KME * m_JME * nchem) R32* __restrict m_chem3D;

_Field_size_(m_IME * m_kdvel * m_JME * ndvel) R32* __restrict m_vd3d;



						

#endif

						static const int m_totArrays = 63;

						

						static const int m_totArrays2D = 19;

						static const int m_totArrays3D = 44;
			};












	}
}



#endif /*__MODULE_BL_MYNN_BL_DRIVER_IMPL_H__*/