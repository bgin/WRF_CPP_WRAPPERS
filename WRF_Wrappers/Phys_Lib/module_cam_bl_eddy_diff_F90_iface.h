
#ifndef __MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_H__
#define __MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_H__

#ifndef MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_VERSION_MAJOR
#define MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_VERSION_MAJOR 1
#endif

#ifndef MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_VERSION_MINOR
#define MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_VERSION_MINOR 0
#endif

#ifndef MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_PATCH_VERSION 
#define MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_PATCH_VERSION 0
#endif

#ifndef MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_CREATE_DATE
#define MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_CREATE_DATE "Date: 12-10-2016 , Time: 15:15 PM GMT+2"
#endif

#ifndef MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_BUILD_DATE
#define MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_BUILD_DATE " "
#endif

#ifndef MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_AUTHOR
#define MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


/**********************************************
   C-Interface to Fortran 90 Module eddy_diff.
***********************************************/

#if defined (__cplusplus)


extern "C" {

	/************************************************
	Module eddy_diff variables and its subroutines
	declarations.
	*************************************************/

	/*
	Module parameters declarations.
	*/

	// 8-byte real.
	int EDDY_DIFF_mp_r8;

	//!-------------------------------- - !
	// !PBL Parameters used in the UW PBL !
	//!-------------------------------- - !

	// Method for calculating saturation fraction
	unsigned char EDDY_DIFF_mp_sftype;

	// 'orig',   'ramp',   'maxi'   : recommended to be used with choice_radf 
	unsigned char EDDY_DIFF_mp_choice_evhc[4];

	// 'orig',   'ramp',   'maxi'   : recommended to be used with choice_evhc
	unsigned char EDDY_DIFF_mp_choice_radf[6];

	// 'origin', 'remove', 'nonamb'
	unsigned char EDDY_DIFF_mp_choice_SRCL[6];

	// 'origin', 'rampsl'(Sungsu), 'rampcl'(Chris)
	unsigned char EDDY_DIFF_mp_choice_tunl[6];

	//  Maximum asympt leng = ctunl*tunl when choice_tunl = 'rampsl(cl)' [ no unit ]
	double EDDY_DIFF_mp_ctunl;

	// 'origin', 'takemn'
	unsigned char EDDY_DIFF_mp_choice_leng[6];

	// Order of 'leng' when choice_leng = 'origin' [ no unit ]
	double EDDY_DIFF_mp_cleng;

	// 'ibprod' (include tkes in computing bprod), 'ebprod'(exclude)
	unsigned char EDDY_DIFF_mp_choice_tkes[6];

	/*
	! Parameters for 'sedimenttaion-entrainment feedback' for liquid stratus
	! If .false.,  no sedimentation entrainment feedback ( i.e., use default evhc )
	*/

	int EDDY_DIFF_mp_id_sedfact;

	// Valid only when id_sedfact = .true.
	double EDDY_DIFF_mp_ased;

	/*
	! --------------------------------------------------------------------------------------------------- !
	! Parameters governing entrainment efficiency A = a1l(i)*evhc, evhc = 1 + a2l * a3l * L * ql / jt2slv !
	! Here, 'ql' is cloud-top LWC and 'jt2slv' is the jump in 'slv' across                                !
	! the cloud-top entrainment zone ( across two grid layers to consider full mixture )                  !
	! --------------------------------------------------------------------------------------------------- !
	*/

	//  Dry entrainment efficiency for TKE closure
	//  a1l = 0.2*tunl*erat^-1.5, where erat = <e> / wstar ^ 2 for dry CBL = 0.3.
	double EDDY_DIFF_mp_a1l;

	//  Dry entrainment efficiency for wstar closure
	double  EDDY_DIFF_mp_a1i;

	//  Minimum allowable sqrt(tke)/wstar. Used in solving cubic equation for 'ebrk'
	double  EDDY_DIFF_mp_ccrit;

	//  1/wstar3factcrit is the maximally allowed enhancement of 'wstar3' due to entrainment.
	double  EDDY_DIFF_mp_wstar3factcrit;

	//  Moist entrainment enhancement param (recommended range : 10~30 )
	double  EDDY_DIFF_mp_a2l;

	//  Approximation to a complicated thermodynamic parameters
	double  EDDY_DIFF_mp_a3l;

	//  Minimum buoyancy jump at an entrainment jump, [m/s2]
	double  EDDY_DIFF_mp_jbumin;

	//  Upper limit of evaporative enhancement factor
	double  EDDY_DIFF_mp_evhcmax;

	//  Minimum permitted value of ustar [ m/s ] 
	double  EDDY_DIFF_mp_ustar_min;

	//  1/3 power in wind gradient expression [ no unit ]
	double  EDDY_DIFF_mp_onet;

	//
	int    EDDY_DIFF_mp_ncvmax;

	//  Minimum grid-mean LWC counted as clouds [kg/kg]
	double EDDY_DIFF_mp_qmin;

	//   Not zero (small positive number used in 's2')
	double EDDY_DIFF_mp_ntzero;

	//   TKE dissipation D = e^3/(b1*leng), e = b1*W.
	double EDDY_DIFF_mp_b1;

	//   b1**(2/3)
	double EDDY_DIFF_mp_b123;

	//   Asympt leng = tunl*(turb lay depth)
	double EDDY_DIFF_mp_tunl;

	//   alph1~alph5 : Galperin instability function parameters
	double EDDY_DIFF_mp_alph1;

	//    These coefficients are used to calculate 
	//    'sh' and 'sm' from 'gh'.
	double EDDY_DIFF_mp_alph2;

	double EDDY_DIFF_mp_alph3;

	double EDDY_DIFF_mp_alph4;

	double EDDY_DIFF_mp_alph5;

	//  Critical Richardson number for turbulence. Can be any value >= 0.19.
	double EDDY_DIFF_mp_ricrit;

	//  TKE transport efficiency [no unit].
	double EDDY_DIFF_mp_ae;

	//   Minimum W/<W> used for CL merging test 
	double EDDY_DIFF_mp_rinc;

	//   Minimum PBL eddy vertical velocity perturbation
	double EDDY_DIFF_mp_wpertmin;

	//   Ratio of 'wpert' to sqrt(tke) for CL.
	double EDDY_DIFF_mp_wfac;

	//   Ratio of 'tpert' to (w't')/wpert for CL. Same ratio also used for q
	double EDDY_DIFF_mp_tfac;

	//   Constant in surface temperature excess for stable STL. [ no unit ]  
	double EDDY_DIFF_mp_fak;

	//   Minimum allowable e/<e> in a CL
	double EDDY_DIFF_mp_rcapmin;

	//   Maximum allowable e/<e> in a CL
	double EDDY_DIFF_mp_rcapmax;

	//   TKE is capped at tkemax [m2/s2]
	double EDDY_DIFF_mp_tkemax;

	//   Under-relaxation factor ( 0 < lambda =< 1 )
	double EDDY_DIFF_mp_lambda;

	//   .true. (.false.) : initialize kvh/kvm =  kvf ( 0. )
	int  EDDY_DIFF_mp_use_kvf;

	//    Used in 'zisocl'. Default is 'true'
	int  EDDY_DIFF_mp_use_dw_surf;
	/*
	! If 'true', surface interfacial energy does not contribute to the CL mean
	!            stbility functions after finishing merging.     For this case,
	!           'dl2n2_surf' is only used for a merging test based on 'l2n2'
	! If 'false',surface interfacial enery explicitly contribute to    CL mean
	!            stability functions after finishing merging.    For this case,
	!           'dl2n2_surf' and 'dl2s2_surf' are directly used for calculating
	!            surface interfacial layer energetics
	*/

	//   .true. ( .false.) : turning-off ( on) radiative-turbulence interaction by setting qrl = 0.
	int  EDDY_DIFF_mp_set_qrlzero;


	/*
	! ------------------------------------- !
	! PBL Parameters not used in the UW PBL !
	! ------------------------------------- !
	*/
	//  PBL max depth in pressure units. 
	double EDDY_DIFF_mp_pblmaxp;

	//  Minimum kneutral*f(ri). 
	double EDDY_DIFF_mp_zkmin;

	//  Constant in wind gradient expression.
	double EDDY_DIFF_mp_betam;

	//   Constant in surface layer gradient expression.
	double EDDY_DIFF_mp_betas;

	//   Constant in temperature gradient expression.
	double EDDY_DIFF_mp_betah;

	//   Constant in turbulent prandtl number.
	double EDDY_DIFF_mp_fakn;

	//   Critical richardson number.
	double EDDY_DIFF_mp_ricr;

	//   Surface layer fraction of boundary layer
	double EDDY_DIFF_mp_sffrac;

	//   betam * sffrac
	double EDDY_DIFF_mp_binm;

	//   betah * sffrac
	double EDDY_DIFF_mp_binh;


	/*

	! ------------------------------------------------------- !
	! PBL constants set using values from other parts of code !
	! ------------------------------------------------------- !
	*/

	//  Specific heat of dry air
	double EDDY_DIFF_mp_cpair;

	//  Gas const for dry air
	double EDDY_DIFF_mp_rair;

	//  rh2o/rair - 1
	double EDDY_DIFF_mp_zvir;

	//  Latent heat of vaporization
	double EDDY_DIFF_mp_latvap;

	//  Latent heat of fusion
	double EDDY_DIFF_mp_latice;

	//   Latent heat of sublimation
	double EDDY_DIFF_mp_latsub;

	//   Gravitational acceleration
	double EDDY_DIFF_mp_g;

	//   Von Karman's constant
	double EDDY_DIFF_mp_vk;

	//   fak * sffrac * vk
	double EDDY_DIFF_mp_ccon;

	//   Top interface level to which turbulent vertical diffusion is applied ( = 1 )
	int  EDDY_DIFF_mp_ntop_turb;

	//   Bottom interface level to which turbulent vertical diff is applied ( = pver )
	int  EDDY_DIFF_mp_nbot_turb;

	//   Mixing lengths squared. Not used in the UW PBL. Used for computing free air diffusivity.
	double * EDDY_DIFF_mp_ml2;

	/*
	Module subroutine declarations.
	*/


	/*
	!---------------------------------------------------------------- !
	! Purpose:                                                        !
	! Initialize time independent constants/variables of PBL package. !
	!---------------------------------------------------------------- !
	*/
	void  EDDY_DIFF_mp_INIT_EDDY_DIFF(int *, int *,
		                              int *, int *,
		                              double *, double *,
		                              double *, double *,
		                              double *, double *,
		                              double *, double *);


	/*
	!-------------------------------------------------------------------- !
	! Purpose: Interface to compute eddy diffusivities.                   !
	!          Eddy diffusivities are calculated in a fully implicit way  !
	!          through iteration process.                                 !
	! Author:  Sungsu Park. August. 2006.                                 !
	!                       May.    2008.                                 !
	!-------------------------------------------------------------------- !

	*/
	void  EDDY_DIFF_mp_COMPUTE_EDDY_DIFF(int *, int *, int *, int *, double *, double *, double *, double *,
		                                double *, double *, double *, double *, double *, double *, double *,
		                                double *, double *, double *, double *, double *, double *, double *,
		                                double *, double *, int *, int *, double *, double *, double *,
		                                double *, double *, double *, double *, double *, double *, double *,
		                                double *, double *, double *, double *, double *, double *, int *,
		                                int *, double *, double *, double *, double *, double *, double *,
		                                 double *, double *  );


	/*
	!----------------------------------------------------------------------- !
	!                                                                        !
	! Purpose: Interface for calculating saturation fractions  at upper and  !
	!          lower-half layers, & interfaces for use by turbulence scheme  !
	!                                                                        !
	! Method : Various but 'l' should be chosen for consistency.             !
	!                                                                        !
	! Author : B. Stevens and C. Bretherton (August 2000)                    !
	!          Sungsu Park. August 2006.                                     !
	!                       May.   2008.                                     !
	!                                                                        !
	! S.Park : The computed saturation fractions are repeatedly              !
	!          used to compute buoyancy coefficients in'trbintd' & 'caleddy'.!
	!----------------------------------------------------------------------- !
	*/
	void  EDDY_DIFF_mp_SFDIAG(int *, int *, int *, double *, double *, double *,
		                       double *, double *, double *, double *, double *,
		                          double *, double *, double *, double *, int *);


	/*
	!----------------------------------------------------------------------- !
	! Purpose: Calculate buoyancy coefficients at all interfaces including   !
	!          surface. Also, computes the profiles of ( sl,qt,n2,s2,ri ).   !
	!          Note that (n2,s2,ri) are defined at each interfaces except    !
	!          surface.                                                      !
	!                                                                        !
	! Author: B. Stevens  ( Extracted from pbldiff, August, 2000 )           !
	!         Sungsu Park ( August 2006, May. 2008 )                         !
	!----------------------------------------------------------------------- !
	*/
	void  EDDY_DIFF_mp_TRBINTD(int *, int *, int *, double *, double *, double *,
		                        double *, double *, double *, double *, double *,
		                        double *, double *, double *, double *, double *,
		                        double *, double *, double *, double *, double *,
		                        double *, double *, double *, double *, double *,
		                        double *, double *, double *, double *, double *,
		                        double *, double *, double *, int *);


	/*
	!---------------------------------------------------------------------- !
	!                                                                       !
	! Purpose: Computes exchange coefficients for free turbulent flows.     !
	!          This is not used in the UW moist turbulence scheme.          !
	!                                                                       !
	! Method:                                                               !
	!                                                                       !
	! The free atmosphere diffusivities are based on standard mixing length !
	! forms for the neutral diffusivity multiplied by functns of Richardson !
	! number. K = l^2 * |dV/dz| * f(Ri). The same functions are used for    !
	! momentum, potential temperature, and constitutents.                   !
	!                                                                       !
	! The stable Richardson num function (Ri>0) is taken from Holtslag and  !
	! Beljaars (1989), ECMWF proceedings. f = 1 / (1 + 10*Ri*(1 + 8*Ri))    !
	! The unstable Richardson number function (Ri<0) is taken from  CCM1.   !
	! f = sqrt(1 - 18*Ri)                                                   !
	!                                                                       !
	! Author: B. Stevens (rewrite, August 2000)                             !
	!                                                                       !
	!---------------------------------------------------------------------- !
	*/
	void  EDDY_DIFF_mp_AUSTAUSCH_ATM(int *, int *, int *, double *, double *, double *);


	/*
	! ---------------------------------------------------------------------------- !
	!                                                                              !
	! The University of Washington Moist Turbulence Scheme                         !
	!                                                                              !
	! Authors : Chris Bretherton at the University of Washington, Seattle, WA      !
	!           Sungsu Park at the CGD/NCAR, Boulder, CO                           !
	!                                                                              !
	! ---------------------------------------------------------------------------- !
	*/

	/*
	!--------------------------------------------------------------------------------- !
	!                                                                                  !
	! Purpose : This is a driver routine to compute eddy diffusion coefficients        !
	!           for heat (sl), momentum (u, v), moisture (qt), and other  trace        !
	!           constituents.   This scheme uses first order closure for stable        !
	!           turbulent layers (STL). For convective layers (CL), entrainment        !
	!           closure is used at the CL external interfaces, which is coupled        !
	!           to the diagnosis of a CL regime mean TKE from the instantaneous        !
	!           thermodynamic and velocity profiles.   The CLs are diagnosed by        !
	!           extending original CL layers of moist static instability   into        !
	!           adjacent weakly stably stratified interfaces,   stopping if the        !
	!           stability is too strong.   This allows a realistic depiction of        !
	!           dry convective boundary layers with a downgradient approach.           !
	!                                                                                  !
	! NOTE:     This routine currently assumes ntop_turb = 1, nbot_turb = pver         !
	!           ( turbulent diffusivities computed at all interior interfaces )        !
	!           and will require modification to handle a different ntop_turb.         !
	!                                                                                  !
	! Authors:  Sungsu Park and Chris Bretherton. 08/2006, 05/2008.                    !
	!                                                                                  !
	! For details, see                                                                 !
	!                                                                                  !
	! 1. 'A new moist turbulence parametrization in the Community Atmosphere Model'    !
	!     by Christopher S. Bretherton & Sungsu Park. J. Climate. 22. 3422-3448. 2009. !
	!                                                                                  !
	! 2. 'The University of Washington shallow convection and moist turbulence schemes !
	!     and their impact on climate simulations with the Community Atmosphere Model' !
	!     by Sungsu Park & Christopher S. Bretherton. J. Climate. 22. 3449-3469. 2009. !
	!                                                                                  !
	! For questions on the scheme and code, send an email to                           !
	!     sungsup@ucar.edu or breth@washington.edu                                     !
	!                                                                                  !
	!--------------------------------------------------------------------------------- !
	*/
	void  EDDY_DIFF_mp_CALEDDY(int *, int *, int *,
		                       double *, double *, double *, double *, double *,
		                       double *, double *, double *, double *,
		                       double *, double *, double *, double *,
		                       double *, double *, double *, double *, double *,
		                       double *, double *, double *, double *, double *,
		                       double *, double *,
		                       double *, double *, double *, double *,
		                       double *, double *, double *, double *, double *,
		                       int *, double *, double *, double *, double *,
		                       double *, double *, double *,
		                       double *, double *, double *,
		                       double *, double *, double *,
		                       double *, double *, double *,
		                       double *, double *, double *, double *,
		                       double *, double *, double *, double *, double *,
		                       double *, double *, double *, double *, double *,
		                       double *, double *, double *, double *, double *,
		                       double *, double *,
		                       double *, double *, double *, double *, double *,
		                       double *, double *, double *, double *, double *,
		                       double *);



	/*
	! ---------------------------------------------------------------------------- !
	! Object : Find unstable CL regimes and determine the indices                  !
	!          kbase, ktop which delimit these unstable layers :                   !
	!          ri(kbase) > 0 and ri(ktop) > 0, but ri(k) < 0 for ktop < k < kbase. !
	! Author : Chris  Bretherton 08/2000,                                          !
	!          Sungsu Park       08/2006, 11/2008                                  !
	!----------------------------------------------------------------------------- !
	*/
	void  EDDY_DIFF_mp_EXACOL(int *, int *, int *, double *, double *, double *,
		                      double *, int *, int *, int *);

	/*
	!------------------------------------------------------------------------ !
	! Object : This 'zisocl' vertically extends original CLs identified from  !
	!          'exacol' using a merging test based on either 'wint' or 'l2n2' !
	!          and identify new CL regimes. Similar to the case of 'exacol',  !
	!          CL regime index increases with height.  After identifying new  !
	!          CL regimes ( kbase, ktop, ncvfin ),calculate CL internal mean  !
	!          energetics (lbrk : energetic thickness integral, wbrk, ebrk )  !
	!          and stability functions (ricl, ghcl, shcl, smcl) by including  !
	!          surface interfacial layer contribution when bflxs > 0.   Note  !
	!          that there are two options in the treatment of the energetics  !
	!          of surface interfacial layer (use_dw_surf= 'true' or 'false')  !
	! Author : Sungsu Park 08/2006, 11/2008                                   !
	!------------------------------------------------------------------------ !
	*/
	void  EDDY_DIFF_mp_ZISCOL(int *, int *, int *,
		                      double *, double *, double *, double *,
		                      double *, double *, double *, double *,
		                      int *, int *, int *, int *,
		                      double *, double *, double *, double *,
		                      double *, double *, double *, int *, int *, int *);




}

#endif

#endif /*__MODULE_CAM_BL_EDDY_DIFF_F90_IFACE_H__*/