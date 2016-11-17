
#ifndef __MODULE_CU_MESOSAS_F90_IFACE_H__
#define __MODULE_CU_MESOSAS_F90_IFACE_H__

// File granularity version.
#ifndef MODULE_CU_MESOSAS_F90_IFACE_VERSION_MAJOR
#define MODULE_CU_MESOSAS_F90_IFACE_VERSION_MAJOR 1
#endif

#ifndef MODULE_CU_MESOSAS_F90_IFACE_VERSION_MINOR
#define MODULE_CU_MESOSAS_F90_IFACE_VERSION_MINOR 0
#endif

#ifndef MODULE_CU_MESOSAS_F90_IFACE_PATCH_VERSION
#define MODULE_CU_MESOSAS_F90_IFACE_PATCH_VERSION 0
#endif

#ifndef MODULE_CU_MESOSAS_F90_IFACE_CREATE_DATE
#define MODULE_CU_MESOSAS_F90_IFACE_CREATE_DATE "Date: 15-11-2016 , Time: 15:06 PM GMT+2"
#endif

// Set this value to successful build date/time.
#ifndef MODULE_CU_MESOSAS_F90_IFACE_BUILD_DATE
#define MODULE_CU_MESOSAS_F90_IFACE_BUILD_DATE ""
#endif

#ifndef MODULE_CU_MESOSAS_F90_IFACE_AUTHOR
#define MODULE_CU_MESOSAS_F90_IFACE_AUTHOR "Name: Bernard Gingold , e-mail: beniekg@gmail.com"
#endif


/*********************************************************
	C-interface to Fortran 90 module 'module_cu_mesosas'.
**********************************************************/

#if defined (__cplusplus)

extern "C" {

			
	/*
	@Purpose:
	          Module subroutine declarations.
	*/


	/*
!-------------------------------------------------------------------
!-- U3D         3D u-velocity interpolated to theta points (m/s)
!-- V3D         3D v-velocity interpolated to theta points (m/s)
!-- TH3D	3D potential temperature (K)
!-- T3D         temperature (K)
!-- QV3D        3D water vapor mixing ratio (Kg/Kg)
!-- QC3D        3D cloud mixing ratio (Kg/Kg)
!-- QI3D        3D ice mixing ratio (Kg/Kg)
!-- P8w         3D pressure at full levels (Pa)
!-- Pcps        3D pressure (Pa)
!-- PI3D	3D exner function (dimensionless)
!-- rr3D	3D dry air density (kg/m^3)
!-- RUBLTEN     U tendency due to
!               PBL parameterization (m/s^2)
!-- RVBLTEN     V tendency due to
!               PBL parameterization (m/s^2)
!-- RTHBLTEN    Theta tendency due to
!               PBL parameterization (K/s)
!-- RQVBLTEN    Qv tendency due to
!               PBL parameterization (kg/kg/s)
!-- RQCBLTEN    Qc tendency due to
!               PBL parameterization (kg/kg/s)
!-- RQIBLTEN    Qi tendency due to
!               PBL parameterization (kg/kg/s)
!
!-- MOMMIX      MOMENTUM MIXING COEFFICIENT (can be set in the namelist)
!-- RUCUTEN     U tendency due to Cumulus Momentum Mixing (gopal's doing for SAS)
!-- RVCUTEN     V tendency due to Cumulus Momentum Mixing (gopal's doing for SAS)
!
!-- CP          heat capacity at constant pressure for dry air (J/kg/K)
!-- GRAV        acceleration due to gravity (m/s^2)
!-- ROVCP       R/CP
!-- RD          gas constant for dry air (J/kg/K)
!-- ROVG 	R/G
!-- P_QI	species index for cloud ice
!-- dz8w	dz between full levels (m)
!-- z		height above sea level (m)
!-- PSFC        pressure at the surface (Pa)
!-- UST		u* in similarity theory (m/s)
!-- PBL		PBL height (m)
!-- PSIM        similarity stability function for momentum
!-- PSIH        similarity stability function for heat
!-- HFX		upward heat flux at the surface (W/m^2)
!-- QFX		upward moisture flux at the surface (kg/m^2/s)
!-- TSK		surface temperature (K)
!-- GZ1OZ0      log(z/z0) where z0 is roughness length
!-- WSPD        wind speed at lowest model level (m/s)
!-- BR          bulk Richardson number in surface layer
!-- DT		time step (s)
!-- rvovrd      R_v divided by R_d (dimensionless)
!-- EP1         constant for virtual temperature (R_v/R_d - 1) (dimensionless)
!-- KARMAN      Von Karman constant
!-- ids         start index for i in domain
!-- ide         end index for i in domain
!-- jds         start index for j in domain
!-- jde         end index for j in domain
!-- kds         start index for k in domain
!-- kde         end index for k in domain
!-- ims         start index for i in memory
!-- ime         end index for i in memory
!-- jms         start index for j in memory
!-- jme         end index for j in memory
!-- kms         start index for k in memory
!-- kme         end index for k in memory
!-- its         start index for i in tile
!-- ite         end index for i in tile
!-- jts         start index for j in tile
!-- jte         end index for j in tile
!-- kts         start index for k in tile
!-- kte         end index for k in tile
!-------------------------------------------------------------------

	*/

	void	MODULE_CU_MESOSAS_mp_CU_MESO_SAS(float *, int *, int *,
											 float *, float *, float *, float *,
											 float *, float *, 
											 float *, float *, float *, float *,
											 float *, float *, float *, float *, float *, float *, float *, float *, float *,
											 float *, float *, float *, float *, int *, 
											 int *, 
											 float *,
											 float *, float *,
											 int *, float *,
											 float *, float *, float *,
											 int *, int *, 
											 int *, int *, int *, int *, int *, int *,
											 int *, int *, int *, int *, int *, int *,
											 int *, int *, int *, int *, int *, int * );


	
	void	MODULE_CU_MESOSAS_mp_MSASINIT(float *, float *, float *, float *,
										  float *, float *,
										  int *, int *, int *, int *,
										  int *,
										  int *, int *, int *, int *, int *, int *,
										  int *, int *, int *, int *, int *, int *,
										  int *, int *, int *, int *, int *, int *);


	void    MODULE_CU_MESOSAS_mp_SASCNV(int *, int *, int *, int *, float *, float *, float *, float *, float *, float,
									    float *, float *, float *, float *, float, float *, float *, int *, int *, int *,
										float *, float *, float *, int * );


	void    MODULE_CU_MESOSAS_mp_OLD_ARW_SHALCV(int *, int *, int *, float *, float *, float *, float *, float *, int *, float *,
												float *, float *);


	void    MODULE_CU_MESOSAS_mp_TRIDI2T3(int *, int *, float *, float *, float *, float *, float *, float *, float *, float);


	void    MODULE_CU_MESOSAS_mp_MSTADBT3(int *, int *, int *, int *, float *, float *, float *, float *,
										  int *, int *, int *, float *, float * );


	void    MODULE_CU_MESOSAS_mp_SASCNVN(int *, int *, int *, int *, float *, float *, float *, float *, float *, float *,
										 float *, float *, float *, float *, float *, float *, float *, int *, int *, int *, float *,
										 float *, int *, float *, float * );


	void    MODULE_CU_MESOSAS_mp_SHALCNV(int *, int *, int *, int *, float *, float *, float *, float *, float *, float *,
										 float *, float *, float *, float *, float *, float *, int *, int *, int *, float *,
										 float *, int *, float *, float *, float *, float *);


	void    MODULE_CU_MESOSAS_mp_SASCNVN_H(int *, int *, int *, int *, float *, float *, float *, float *, float *, float *,
										   float *, float *, float *, float *, float *, float *, float *, int *, int *, int *, float *,
										   float *, int *, float *, float * );






}








#endif











#endif /*__MODULE_CU_MESOSAS_F90_IFACE_H__*/