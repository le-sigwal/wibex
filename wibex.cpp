//-------------------------------------------------------------------------
/* File: wibex.cpp
 * Description: "Work around IBEX" Project (Interval Based EXplorer)
 *                https://github.com/ibex-team/ibex-lib
 * Authors: Bagad Sigwal
 * Copyright: 2020 Sigwal.info/github - All Rights Reserved
 * Last modification: 05/04/2020
 * Version: 20.04
 *
 * Change records:
 * SWL - 04/04/2020 - creation, added main()
 * SWL - 05/04/2020 - added "SEND+MORE=MONEY" problem computation
 *                    send_more_money_ibx()                        */
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//[>DEFINITIONS]
//-------------------------------------------------------------------------
//[>STANDARD DEFINITIONS]
#include <iostream>
#include <set>
//[>EXTERN DEFINITIONS]
#include "ibex.h"
//[>PROJECT DEFINITIONS]
//[>LOCAL DEFINITIONS]
#define WIBEX_VERSION "20.04"
//-------------------------------------------------------------------------
//[<DEFINITIONS]
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//[>SEND_MORE_MONEY_IBX]
//-------------------------------------------------------------------------
int send_more_money_ibx() {

	int vi;
	ibex::Variable R1, R2, R3, S, E, N, D, M, O, R, Y;

	//---------------------------------------------------------------------
	// Contrainte principale
	ibex::Function f0(S, E, N, D, M, O, R, Y,
			/*     */ 10E3*S + 100.0*E + 10.0*N + D +
			/*     */ 10E3*M + 100.0*O + 10.0*R + E -
			(10E4*M + 10E3*O + 100.0*N + 10.0*E + Y));
	// Contracteur principal
	ibex::CtcFwdBwd c0(f0);
	// Intervalles
	ibex::IntervalVector I0(8);
	//---------------------------------------------------------------------
	ibex::Function f1(R3, S, M, O,
			R3+S-9.0*M-O);
	ibex::CtcFwdBwd c1(f1);
	ibex::IntervalVector I1(4);
	I1[1]=ibex::Interval(1.0, 9.0); // S
	I1[2]=ibex::Interval(1.0, 9.0); // M
	//---------------------------------------------------------------------
	ibex::Function f2(R2, E, O, R3, N,
			R2+E+O-10.0*R3-N);
	ibex::CtcFwdBwd c2(f2);
	ibex::IntervalVector I2(5);
	I2[2]=ibex::Interval(0.0, 9.0); // O init
	I2[3]=ibex::Interval(0.0, 1.0); // R3 init
	//---------------------------------------------------------------------
	ibex::Function f3(R1, N, R, R2, E,
			R1+N+R-10.0*R2-E);
	ibex::CtcFwdBwd c3(f3);
	ibex::IntervalVector I3(5);
	I3[1]=ibex::Interval(0.0, 9.0); // N init
	I3[2]=ibex::Interval(0.0, 9.0); // R init
	I3[3]=ibex::Interval(0.0, 1.0); // R2 init
	//---------------------------------------------------------------------
	ibex::Function f4(D, E, R1, Y,
			D+E-10.0*R1-Y);
	ibex::CtcFwdBwd c4(f4);
	ibex::IntervalVector I4(4);
	I4[0]=ibex::Interval(0.0, 9.0); // D init
	I4[1]=ibex::Interval(0.0, 9.0); // E init
	I4[2]=ibex::Interval(0.0, 1.0); // R1 init
	I4[3]=ibex::Interval(0.0, 9.0); // Y init

	// Valeurs restantes
	std::set<int> VR;
	VR.insert(0); VR.insert(1); VR.insert(2); VR.insert(3); VR.insert(4);
	VR.insert(5); VR.insert(6); VR.insert(7); VR.insert(8); VR.insert(9);

	int in=0, ic; double ia, ie, va, ve;

	std::cout<<"  SEND+MORE=MONEY"<<std::endl;
	do{
		//-----------------------------------------------------------------
		I0[0] = I1[1]; // S
		I0[1] = I4[1]; // E
		I0[2] = I3[1]; // N
		I0[3] = I4[0]; // D
		I0[4] = I1[2]; // M
		I0[5] = I2[2]; // O
		I0[6] = I3[2]; // R
		I0[7] = I4[3]; // Y

		/*std::cout<<"    avant contraction 0"<<std::endl;
		std::cout<<"      - S : "<<I0[0]<<std::endl;
		std::cout<<"      - E : "<<I0[1]<<std::endl;
		std::cout<<"      - N : "<<I0[2]<<std::endl;
		std::cout<<"      - D : "<<I0[3]<<std::endl;
		std::cout<<"      - M : "<<I0[4]<<std::endl;
		std::cout<<"      - O : "<<I0[5]<<std::endl;
		std::cout<<"      - R : "<<I0[6]<<std::endl;
		std::cout<<"      - Y : "<<I0[7]<<std::endl;*/
		c0.contract(I0);
		/*std::cout<<"    apres contraction 0"<<std::endl;
		std::cout<<"      - S : "<<I0[0]<<std::endl;
		std::cout<<"      - E : "<<I0[1]<<std::endl;
		std::cout<<"      - N : "<<I0[2]<<std::endl;
		std::cout<<"      - D : "<<I0[3]<<std::endl;
		std::cout<<"      - M : "<<I0[4]<<std::endl;
		std::cout<<"      - O : "<<I0[5]<<std::endl;
		std::cout<<"      - R : "<<I0[6]<<std::endl;
		std::cout<<"      - Y : "<<I0[7]<<std::endl;*/

		for(vi=0;vi<8;vi++){
			ia=ceil(I0[vi].lb()); ie=floor(I0[vi].ub());
			if((ie-ia)==0.0){
				ic=(int)ia;
				if(VR.find(ic)!=VR.end()){
					VR.erase(ic);
				}
			}
			else{
				va = (double)(*(VR.begin()));
				if(ia<va){ ia=va;}
				ve = (double)(*(VR.rbegin()));
				if(ie>ve){ ie=ve;}
			}
			I0[vi]=ibex::Interval(ia, ie);
		}
		/*std::cout<<"    avant partie entiere 0"<<std::endl;
		std::cout<<"      - S : "<<I0[0]<<std::endl;
		std::cout<<"      - E : "<<I0[1]<<std::endl;
		std::cout<<"      - N : "<<I0[2]<<std::endl;
		std::cout<<"      - D : "<<I0[3]<<std::endl;
		std::cout<<"      - M : "<<I0[4]<<std::endl;
		std::cout<<"      - O : "<<I0[5]<<std::endl;
		std::cout<<"      - R : "<<I0[6]<<std::endl;
		std::cout<<"      - Y : "<<I0[7]<<std::endl;*/

		//-----------------------------------------------------------------
		I1[0] = I2[3]; // R3
		I1[1] = I0[0]; // S
		I1[2] = I0[4]; // M
		I1[3] = I0[5]; // O
		c1.contract(I1);

		for(vi=0;vi<4;vi++){
			ia=ceil(I1[vi].lb()); ie=floor(I1[vi].ub());
			I1[vi]=ibex::Interval(ia, ie);
		}
		//-----------------------------------------------------------------
		I2[0] = I3[3]; // R2
		I2[1] = I0[1]; // E
		I2[2] = I1[3]; // O
		I2[3] = I1[0]; // R3
		I2[4] = I0[2]; // N
		/*std::cout<<"    avant contraction 2"<<std::endl;
		std::cout<<"      - R2: "<<I2[0]<<std::endl;
		std::cout<<"      - E : "<<I2[1]<<std::endl;
		std::cout<<"      - O : "<<I2[2]<<std::endl;
		std::cout<<"      - R3: "<<I2[3]<<std::endl;
		std::cout<<"      - N : "<<I2[4]<<std::endl;*/
		c2.contract(I2);
		/*std::cout<<"    apres contraction 2"<<std::endl;
		std::cout<<"      - R2: "<<I2[0]<<std::endl;
		std::cout<<"      - E : "<<I2[1]<<std::endl;
		std::cout<<"      - O : "<<I2[2]<<std::endl;
		std::cout<<"      - R3: "<<I2[3]<<std::endl;
		std::cout<<"      - N : "<<I2[4]<<std::endl;*/

		for(vi=0;vi<5;vi++){
			ia=ceil(I2[vi].lb()); ie=floor(I2[vi].ub());
			I2[vi]=ibex::Interval(ia, ie);
		}
		//-----------------------------------------------------------------
		I3[0] = I4[2]; // R1
		I3[1] = I2[4]; // N
		I3[2] = I0[6]; // R
		I3[3] = I2[0]; // R2
		I3[4] = I2[1]; // E
		/*std::cout<<"      - R1: "<<I3[0]<<std::endl;
		std::cout<<"      - N : "<<I3[1]<<std::endl;
		std::cout<<"      - R : "<<I3[2]<<std::endl;
		std::cout<<"      - R2: "<<I3[3]<<std::endl;
		std::cout<<"      - E : "<<I3[4]<<std::endl;*/
		c3.contract(I3);
		/*std::cout<<"      - R1: "<<I3[0]<<std::endl;
		std::cout<<"      - N : "<<I3[1]<<std::endl;
		std::cout<<"      - R : "<<I3[2]<<std::endl;
		std::cout<<"      - R2: "<<I3[3]<<std::endl;
		std::cout<<"      - E : "<<I3[4]<<std::endl;*/

		for(vi=0;vi<5;vi++){
			ia=ceil(I3[vi].lb()); ie=floor(I3[vi].ub());
			I3[vi]=ibex::Interval(ia, ie);
		}
		//-----------------------------------------------------------------
		I4[0] = I0[3]; // D
		I4[1] = I3[4]; // E
		I4[2] = I3[0]; // R1
		I4[3] = I0[7]; // Y
		/*std::cout<<"      - D : "<<I4[0]<<std::endl;
		std::cout<<"      - E : "<<I4[1]<<std::endl;
		std::cout<<"      - R1: "<<I4[2]<<std::endl;
		std::cout<<"      - Y : "<<I4[3]<<std::endl;*/
		c4.contract(I4);
		/*std::cout<<"      - D : "<<I4[0]<<std::endl;
		std::cout<<"      - E : "<<I4[1]<<std::endl;
		std::cout<<"      - R1: "<<I4[2]<<std::endl;
		std::cout<<"      - Y : "<<I4[3]<<std::endl;*/

		for(vi=0;vi<4;vi++){
			ia=ceil(I4[vi].lb()); ie=floor(I4[vi].ub());
			I4[vi]=ibex::Interval(ia, ie);
		}

		std::cout<<"    - Iteration n°"<<in<<std::endl;
		std::cout<<"      - R1: "<<I3[0]<<std::endl;
		std::cout<<"      - R2: "<<I2[0]<<std::endl;
		std::cout<<"      - R3: "<<I1[0]<<std::endl;
		std::cout<<"      - S : "<<I0[0]<<std::endl;
		std::cout<<"      - E : "<<I0[1]<<std::endl;
		std::cout<<"      - N : "<<I0[2]<<std::endl;
		std::cout<<"      - D : "<<I0[3]<<std::endl;
		std::cout<<"      - M : "<<I0[4]<<std::endl;
		std::cout<<"      - O : "<<I0[5]<<std::endl;
		std::cout<<"      - R : "<<I0[6]<<std::endl;
		std::cout<<"      - Y : "<<I0[7]<<std::endl;

		in++; if(in>=10){ break; }
	} while(VR.size()>0);


	return 0;
}
//-------------------------------------------------------------------------
//[<SEND_MORE_MONEY_IBX]
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//[>MAIN]
//-------------------------------------------------------------------------
int main(int argc, char *argv[]) {

	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	std::cout<<"[>WIBEX] version "<<WIBEX_VERSION<<std::endl;
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;

	ibex::Interval X(0,1);
	std::cout << "  My first interval X: " << X << std::endl;
	std::cout << "    - exp(X): " << ibex::exp(X) << std::endl;

	send_more_money_ibx();

	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	std::cout<<"[<WIBEX]"<<std::endl;
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;

	return 0;
}
//-------------------------------------------------------------------------
//[<MAIN]
//-------------------------------------------------------------------------
