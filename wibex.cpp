//-------------------------------------------------------------------------
/* File: wibex.cpp
 * Description: "Work around IBEX" Project (Interval Based EXplorer)
 *                https://github.com/ibex-team/ibex-lib
 * Authors: Bagad Sigwal
 * Copyright: 2020 Sigwal.info/github
 * Last modification: 04/04/2020
 * Version: 20.04
 *
 * Change records:
 * SWL - 04/04/2020 - creation, added main()                             */
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//[>DEFINITIONS]
//-------------------------------------------------------------------------
//[>STANDARD DEFINITIONS]
#include <iostream>
//[>EXTERN DEFINITIONS]
#include "ibex.h"
//[>PROJECT DEFINITIONS]
//[>LOCAL DEFINITIONS]
#define WIBEX_VERSION "20.04"
//-------------------------------------------------------------------------
//[<DEFINITIONS]
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

	std::cout<<"---------------------------------------------------------------------------"<<std::endl;
	std::cout<<"[<WIBEX]"<<std::endl;
	std::cout<<"---------------------------------------------------------------------------"<<std::endl;

	return 0;
}
//-------------------------------------------------------------------------
//[<MAIN]
//-------------------------------------------------------------------------

