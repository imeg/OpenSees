/* ****************************************************************** **
**    OpenSees - Open System for Earthquake Engineering Simulation    **
**          Pacific Earthquake Engineering Research Center            **
**                                                                    **
**                                                                    **
** (C) Copyright 1999, The Regents of the University of California    **
** All Rights Reserved.                                               **
**                                                                    **
** Commercial use of this program without express permission of the   **
** University of California, Berkeley, is strictly prohibited.  See   **
** file 'COPYRIGHT'  in main directory for information on usage and   **
** redistribution,  and for a DISCLAIMER OF ALL WARRANTIES.           **
**                                                                    **
** Developed by:                                                      **
**   Frank McKenna (fmckenna@ce.berkeley.edu)                         **
**   Gregory L. Fenves (fenves@ce.berkeley.edu)                       **
**   Filip C. Filippou (filippou@ce.berkeley.edu)                     **
**                                                                    **
** ****************************************************************** */
                                                                        
// $Source: /usr/local/cvs/OpenSees/SRC/material/uniaxial/BucklingStrut.cpp,v $
//
//
// 
//
// Written: S. A. Jalali 03/2015
//
// Purpose: This file contains the implementation for the BucklingStrut class.
//
//////////////////////////////////////////////////////////////////////

#include <elementAPI.h>
#include "BucklingStrut.h"
#include <MaterialResponse.h>

#include <Vector.h>
#include <Channel.h>
#include <math.h>
#include <Information.h>


#ifdef _USRDLL
#define OPS_Export extern "C" _declspec(dllexport)
#elif _MACOSX
#define OPS_Export extern "C" __attribute__((visibility("default")))
#else
#define OPS_Export extern "C"
#endif

static int numThiscall = 0;

void*
OPS_BucklingStrut()
{
	if (numThiscall == 0) {
		opserr << "------ BucklingStrut unaxialMaterial, Written by Seyed Alireza Jalali:seyyed-jalali@aut.ac.ir, Tehran, 2016-------\n";
		opserr<<  "-------Syntax:\n\n";
		opserr<<  "-------UniaxialMaterial BucklingStrut tag fyt E0 b fc bc <R0 R1 R2>\n\n";
		opserr << "------------------------------------------------------------------------------------------------------------\n\n\n";
			numThiscall = 1;
	}
	int tag;
	double fpy, E0,  b, fc, bc, R0, R1, R2;
	UniaxialMaterial *theMaterial = 0;
	int argc = OPS_GetNumRemainingInputArgs();
	int numData = 1;
	int curArg = 2;
	if (OPS_GetIntInput(&numData, &tag) != 0) {
		opserr << "WARNING invalid -tag";
		opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
		return 0;
	}
	curArg ++;
	if (OPS_GetDoubleInput (&numData, &fpy) != 0) {
		opserr << "WARNING invalid -Fts";
		opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
		return 0;
	}
	curArg ++;

	if (OPS_GetDoubleInput (&numData, &E0) != 0) {
		opserr << "WARNING invalid -E0";
		opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
		return 0;
	}
	curArg ++;

	if (OPS_GetDoubleInput (&numData, &b) != 0) {
		opserr << "WARNING invalid -b";
		opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
		return 0;
	}
	curArg ++;

	if (OPS_GetDoubleInput (&numData, &fc) != 0) {
		opserr << "WARNING invalid -fc";
		opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
		return 0;
	}
	curArg ++;
	if (OPS_GetDoubleInput (&numData, &bc) != 0) {
		opserr << "WARNING invalid -bc";
		opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
		return 0;
	}
	curArg ++;

	R0 = 10;
	R1 = 0.925;
	R2 = 0.15;
	char * str = new char[10];
	if (argc >= curArg + 1)
	{
		if (OPS_GetDoubleInput (&numData, &R0) != 0) {
			opserr << "WARNING invalid R0";
			opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
			return 0;
		}
		curArg ++;
	}
	if (argc >= curArg + 1)
	{
		if (OPS_GetDoubleInput (&numData, &R1) != 0) {
			opserr << "WARNING invalid R1";
			opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
			return 0;
		}
		curArg ++;
	}
	if (argc >= curArg + 1)
	{
		if (OPS_GetDoubleInput (&numData, &R2) != 0) {
			opserr << "WARNING invalid R2";
			opserr << "uniaxialMaterial BucklingStrut: " << tag << endln;
			return 0;
		}
		curArg ++;
	}
	theMaterial = new BucklingStrut(tag, fpy, E0,  b, fc, bc, R0, R1, R2);
	//opserr<<"ok\n";

	return theMaterial;
}


BucklingStrut::BucklingStrut(int tag, double _fpy, double _E0, double _b, double _fc, double _bc, double r0, double r1, double r2):
	UniaxialMaterial(tag, 0), Fts(_fpy), E0(_E0), b(_b), Fcs(_fc), R0(r0), R1(r1), R2(r2), bc(_bc)
{
	FTS = Fts;
	FCS = Fcs;
	epsmaxP	=	Fts / E0	;
	sigmaxP	=	Fts	;
	epss0P	=	0.0	;
	sigs0P	=	0.0	;
	epssrP	=	0.0	;
	sigsrP	=	0.0	;
	epsTFP	=	0.0	;
	plstrP	=	0.0	;
	konP	=	0.0	;
	eP		=	0.0	;
	sigP	=	0.0	;
	epsP	=	0.0	;
	sig		=	0.0	;
	eps		=	0.0	;
	e		=	0.0	;
	EnergyP = 0;
}

BucklingStrut::BucklingStrut():
	UniaxialMaterial(0, 0)
{
	konP = 0;
	EnergyP = 0;
}

BucklingStrut::~BucklingStrut()
{

}

UniaxialMaterial* BucklingStrut::getCopy()
{
	BucklingStrut* theCopy = new BucklingStrut(this->getTag(), Fts, E0, b, Fcs, bc, R0, R1, R2);
	return theCopy;
}

double BucklingStrut::getInitialTangent()
{
	return E0;
}

int BucklingStrut::setTrialStrain(double trialStrain, double strainRate)
{
	double reloadFac = 0.075;
	double Esh = b * E0;
	double epsyn = FCS / E0;
	double epsyp = FTS / E0;
	eps = trialStrain;
	double deps = eps - epsP;
	epsmax = epsmaxP;
	sigmax = sigmaxP;
	epss0 = epss0P;
	sigs0 = sigs0P;
	epsr = epssrP;
	sigr = sigsrP;
	epsTF = epsTFP;
	plstr = plstrP;
	kon = konP;
	double sigTF = 0.01*FTS;			//sig at tension field redevelopment point
	//opserr<< "---------------epsilon= " << eps << "-----------------\n";
	//opserr<< "kon, epsTF= " << kon << " " <<epsTF<< "\n";
	//elastic branch
	if (kon == 0)
	{
		if (fabs(eps) <= epsyn)
		{
			sig = eps * E0;
			e = E0;
		}
		else if (eps < -epsyn)
		{
			if (deps > 0)
				kon = 11;
			else
			{
				sig = -Fcs;
				e = 1.0e-10;
			}
		}
		else if (eps > epsyn)
		{
			kon = 21;
			epsr = 0.0;
			sigr = 0.0;
			epss0 = epsyp;
			sigs0 = Fts;
		}
	}
	
	// plastic branch
	
	//	compression branch
	if (kon == 11)
	{
		if (deps > 0)
		{
			kon = 13;
			epsTF = 0.5*(plstr + epsP);
			//if (epsP > plstr - 4.*Fcs/(E0))
			//{
			//	//kon = 12;
			//	//opserr<< "kon= " << kon << "\n";
			//	//opserr<< "epsP, plstr, Fcs, reloadFac, E0, plstr - 2.*Fcs/(reloadFac*E0)= " << epsP <<" "<< plstr<< " "<<Fcs<< " "<< reloadFac << " "<< E0<< " "<<plstr - 2.*Fcs/(reloadFac*E0) <<"\n";
			//}
			//else
			//{
			//	kon = 13;
			//	epsTF = plstr - 0.5*(plstr - (epsP + Fcs / (reloadFac*E0))) + sigTF / E0;
			//	//opserr<< "kon= " << kon << "\n";
			//	//opserr<< "epsP, plstr, sigTF, epsTF= " << epsP <<" "<< plstr<< " "<< sigTF <<" " << epsTF<< "\n";
			//	//epsr = epsP;
			//	//sigr = sigP;
			//	//epss0 = epsr - (sigr - 0.5*Fcs) / (reloadFac*E0);
			//	//sigs0 = 0.5*Fcs;
			//}
		}
		else
		{
			sig = -Fcs;
			e = 1.0e-10;
		}
	}
	// compression reloading branch
	/*if (kon == 12)
	{
		sig = sigP + reloadFac*E0*deps;
		e = reloadFac*E0;
		double sigUnloading = E0 * (eps - plstr);
		if (sig <= -Fcs)
		{
			kon = 11;
			sig = -Fcs;
			e = 1.0e-10;
		}
		else if (sig <= sigUnloading)
		{
			kon = 21;
			sig = sigUnloading;
			e= E0;
		}
	}
	else*/ if (kon == 13)
	{
		if (eps > epsTF)
		{
			kon = 21;
			epsr = epsTF;
			sigr = sigP;
			//sigr = sigTF;
			double ET = (sigmax - sigr) / (epsmax - epsr);
			epss0 = (Fts - Esh * epsyp - sigr + ET * epsr) / (ET - Esh);
			//epss0 = (sigmax - Esh * epsyp - sigr + ET * epsr) / (ET - Esh);
			sigs0 = Fts + Esh * (epss0 - epsyp);
			//sigs0 = sigmax + Esh * (epss0 - epsyp);
			this->MenegottoPinto(eps, Esh, R0, sig, bc, e);
		}
		else
		{
			//double bT = (sigTF - sigs0) / (epsTF - epss0)/*/(reloadFac*E0)*/;
			//double sigEnvlp, eEnvlp;
			//this->MenegottoPinto(eps, bT, R, sigEnvlp, eEnvlp);
			sig = sigP + reloadFac*E0*deps;
			e = reloadFac*E0;
			if (sig <= -Fcs)
			{
				kon = 11;
				sig = -Fcs;
				e = 1.e-10;
			}
			//commented to handle non-convergence:
			/*else /*if (sig >= sigEnvlp)
			{
				sig = sigEnvlp;
				e = eEnvlp;
			}*/
		}
	}
	// tension branch
	else if (kon == 21)
	{
		if (epsP > epsmax)
		{
			sigmax = sigP;
			epsmax = epsP;
		}
		double sigEnvlp, eEnvlp;
		this->MenegottoPinto(eps, Esh, R0, sigEnvlp, bc, eEnvlp);
		sig = sigP + E0 * deps;
		e = E0;
		if (sig <= -Fcs)
		{
			kon = 11;
			sig = -Fcs;
			e = 1.0e-10;
			plstr = epsP - sigP/E0;
		}
		else if (sig >= sigEnvlp)
		{
			sig = sigEnvlp;
			e = eEnvlp;
		}
	}
	
	return 0;
}

//void BucklingStrut::updateDamage()
//{
//	if ( (sig < 0.0 && sigP >= 0) || (sig == 0 && sigP > 0))
//	{
//		//submit damage and reset for new excursion
//		double zeroSigEps = epsP - sigP/E0;
//		double dE = 0.5 * sigP * (zeroSigEps - epsP);
//		totalEnerg += dE;
//		if (totalEnerg < 0) totalEnerg = 0.;
//		if (gama > 9999)
//		{
//			return;
//		}
//		excurEnerg += dE;
//		if (excurEnerg < 0) excurEnerg = 0.;
//		beta = pow( excurEnerg / ( FailEnerg - totalEnerg) , c );
//		if (beta > 0.999 || beta < 0)
//		{
//			opserr<< "\nBucklingStrut:"<< this->getTag()<< " WARNING! Maximum Energy Absorbance Capacity Reached\n"<< endln;
//			beta = 0.999;
//
//		}
//		sigmaxP = (1. - beta)*sigmaxP + beta * resFac*FTS;
//		Fts = (1. - beta)*Fts + beta * resFac*FTS;
//		if (Fcs > Fts)
//			Fcs = Fts;
//		excurEnerg = 0.0;
//	} 
//	else if ( sig > 0.0 )
//	{
//		double dE = 0.5 * (sig + sigP) * (eps - epsP);
//		excurEnerg += dE;
//		totalEnerg += dE;
//    }
//}

double BucklingStrut::getStrain()
{
	return eps;
}

double BucklingStrut::getStress()
{
	return sig;
}

double BucklingStrut::getTangent()
{
	return e;
}

int BucklingStrut::commitState()
{
	epsmaxP = epsmax;
	sigmaxP = sigmax;
	epss0P = epss0;
	sigs0P = sigs0;
	epssrP = epsr;
	sigsrP = sigr;
	epsTFP = epsTF;
	plstrP = plstr;
	konP = kon;

	//this->updateDamage();
	EnergyP += 0.5*(sigP+sig)*(eps-epsP);
	eP = e;
	sigP = sig;
	epsP = eps;

	/*totalEnergP = totalEnerg;
	excurEnergP = excurEnerg;*/
	
	return 0;
}

int BucklingStrut::revertToLastCommit()
{
	epsmax	=	epsmaxP	;
	sigmax	=	sigmaxP	;
	epss0	=	epss0P	;
	sigs0	=	sigs0P	;
	epsr	=	epssrP	;
	sigr	=	sigsrP	;
	epsTF	=	epsTFP	;
	plstr	=	plstrP	;
	kon		=	konP	;
	e		=	eP		;
	sig		=	sigP	;
	eps		=	epsP	;
	/*excurEnerg = excurEnergP;
	totalEnerg = totalEnergP;
	beta = betaP;*/
	
	return 0;
}

int BucklingStrut::revertToStart()
{
	//opserr <<"revert called\n";
	/*excurEnerg = totalEnerg = beta = 0;
	excurEnergP = totalEnergP = betaP = 0;*/

	//this->Calc_sigcr(/*Fts, Fcs*/);
	FTS = Fts;
	FCS = Fcs;
	//FailEnerg = gama * Fts * Fts/E0;
	epsmaxP	=	Fts / E0	;
	sigmaxP	=	Fts	;
	epss0P	=	0.0	;
	sigs0P	=	0.0	;
	epssrP	=	0.0	;
	sigsrP	=	0.0	;
	epsTFP	=	0.0	;
	plstrP	=	0.0	;
	konP	=	0.0	;
	eP		=	0.0	;
	sigP	=	0.0	;
	epsP	=	0.0	;
	sig		=	0.0	;
	eps		=	0.0	;
	e		=	0.0	;
	return 0;
}

int BucklingStrut::sendSelf(int commitTag, Channel & theChannel)
{
	return -1;
}

int BucklingStrut::recvSelf(int commitTag, Channel & theChannel, FEM_ObjectBroker & theBroker)
{
	return -1;
}

void BucklingStrut::Print(OPS_Stream & s, int flag)
{
	s << "BucklingStrut:(strain, stress, tangent)" << eps << " " << sig << " " << e << endln;
}

//void BucklingStrut::Calc_sigcr(/*double & _Fts, double &_Fcs*/)
//{
//	// calculate plate buckling strengthh, sigcr
//	double hsToL = hs/l;
//	double ks = 5.6 + 8.98 / hsToL / hsToL;
//	if (hsToL > 1.0)
//		ks = 8.98 + 5.6 / hsToL / hsToL;
//	
//	double pi = 2 * asin (1.0);
//	double nu = 0.3;
//	double lToT = l/t;
//	//double sigcr = ks * pi * pi * E0 / (12 * (1.0 - nu * nu) * lToT * lToT); 
//	Fcs = ks * pi * pi * E0 / (12 * (1.0 - nu * nu) * lToT * lToT); 
//	// plate clamped on four edges
//	//_Fcs = sigcr * sin(2*alpha/180.0 * pi);									//buckling strength of compression strip
//	Fts = pow( Fts * Fts - 0.75 * Fcs * Fcs, 0.5) - 0.5 * Fcs;		//yield strength of tensional strip acording to Von-Mises rule
//
//	/*Fcs = t;
//	_Fts = Fts;*/
//	return;
//}

void BucklingStrut::MenegottoPinto(double epsc, double E2, double R, double & sigc, double bc, double& ec)
{
	double E1 = (sigs0 - sigr) / (epss0 - epsr);
	double bT = E2/E1;
	// double bT = E2;
	double epsrat = (epsc-epsr) / (epss0 - epsr);
	double dum1 = 1.0 + pow (fabs(epsrat),R);
	double dum2 = pow(dum1, 1.0/R);
	sigc = bT * epsrat + (1.0 - bT) * epsrat / dum2;
	sigc = sigc * (sigs0 - sigr) + sigr;
	ec = bT + (1.0 - bT) / (dum1 * dum2);
	ec *= (sigs0 - sigr) / (epss0 - epsr);
}

double BucklingStrut::getEnergy()
{
	return EnergyP;
}

//Response* 
//BucklingStrut::setResponse(const char **argv, int argc,
//			      OPS_Stream &theOutput)
//{
//	Response *theResponse = UniaxialMaterial::setResponse(argv, argc, theOutput);
//	if (theResponse != 0)
//		return theResponse;
//
//	if ( (strcmp(argv[0],"energy") == 0) ||
//		(strcmp(argv[0],"Energy") == 0) ) {
//    
//		theOutput.tag("UniaxialMaterialOutput");
//		theOutput.attr("matType", this->getClassType());
//		theOutput.attr("matTag", this->getTag());
//    
//		theOutput.tag("ResponseType", "energy");
//		theResponse =  new MaterialResponse(this, 6, totalEnergP);
//		theOutput.endTag();
//  }
//  
//  return theResponse;
//
//}
// 
//int 
//BucklingStrut::getResponse(int responseID, Information &matInfo)
//{
//	if (UniaxialMaterial::getResponse(responseID, matInfo) == 0)
//		return 0;
//	//opserr << "getResponse-2\n";
//	switch (responseID) {
//	case 6:
//		matInfo.setDouble(totalEnergP);
//		return 0;
//	default:      
//		return -1;
//	}
//}
//
