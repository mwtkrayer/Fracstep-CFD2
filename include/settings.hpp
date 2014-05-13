//General settings
//file: settings.hpp
//author: Michael Stumpf

#ifndef _SETTINGS_ 
#define _SETTINGS_
	const int NGP=300;			//number of grid points in one dimension 
	const double RE=10;			//Reynolds number
	const double LREF=1;		//characteristic length (=lenght of domain)
	const double UREF=1;		//characteristic speed
	const int TSMAX=100;		//number of time steps
	const double DT=0.001; 			//time step size
	const double DX=LREF/NGP;	//grid width (grid is uniform)
#endif
