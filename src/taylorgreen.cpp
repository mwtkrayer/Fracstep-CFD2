//Functions used for Taylor-Green calculations
//file: taylorgreen.cpp
//author: Michael Stumpf

#include <iostream>
#include <cmath>
#include <taylorgreen.hpp>
#include <settings.hpp>

using namespace std;
using namespace Eigen;

void calcTaylorGreen(VectorXd &velocity,char comp,double t){
	double nu = (LREF*UREF)/RE;
	//u-component
	if(comp=='u'){
		for(int j=0;j<NGP;j++){
			double y=((double)j)/NGP; //y-coordinate
			for(int i=0;i<NGP;i++){
				double x=((double)i)/NGP + DX/2; //x-coordinate
				velocity(i+j*NGP) =
					sin(2*M_PI*x)*cos(2*M_PI*y)*exp(-8*M_PI*M_PI*nu*t);
			}
		}
	}
	else if(comp=='v'){
		for(int j=0;j<NGP;j++){
			double y=((double)j)/NGP + DX/2; //y-coordinate (shifted grid)
			for(int i=0;i<NGP;i++){
				double x=((double)i)/NGP; //x-coordinate
				velocity(i+j*NGP) =
					-sin(2*M_PI*y)*cos(2*M_PI*x)*exp(-8*M_PI*M_PI*nu*t);
			}
		}
	}
}

void calcTaylorError(VectorXd &u, VectorXd &v){
	VectorXd *u_tg = new VectorXd(NGP*NGP),
			*v_tg = new VectorXd(NGP*NGP);
	calcTaylorGreen(*u_tg,'u',TSMAX*DT);
	calcTaylorGreen(*v_tg,'v',TSMAX*DT);
	//u.norm() -> sqrt(u*u)
	double u_tmp=0, v_tmp=0;
	for(int i=0; i<NGP-1; i++){
		for(int j=0; j<NGP-1; j++){
			u_tmp += pow(u(i+j*NGP) - (*u_tg)(i+j*NGP),2);
			v_tmp += pow(v(i+j*NGP) - (*v_tg)(i+j*NGP),2);
		}
	}
	u_tmp = sqrt(u_tmp)/(NGP*NGP);
	v_tmp = sqrt(v_tmp)/(NGP*NGP);
	cout << "Relative error at time step #" << TSMAX << endl
		 << "velocity u: " << u_tmp << endl
		 << "velocity v: " << v_tmp << endl;
	delete u_tg;
	delete v_tg;
}
