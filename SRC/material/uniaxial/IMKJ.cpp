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
                                                                        
// $Source: /usr/local/cvs/OpenSees/SRC/material/uniaxial/IMKJ.cpp,v $
                                                                      
// Written: S. A. Jalali 11/2020
// A smooth version of the Ibarra-Medina-Krawinkler Model
// with Bilinear, Pinched and Peak-Oriented cyclic rules

#include <math.h>

#include <stdlib.h>
#include <IMKJ.h>
#include <float.h>
#include <Channel.h>
#include <Information.h>
#include <Parameter.h>

#include <elementAPI.h>
#include <OPS_Globals.h>
#include "classTags.h"

static int numThisCall = 0;

void *
OPS_IMKJ()
{
	if (numThisCall == 0) {
		opserr << "------ IMKJ unaxialMaterial, Written by SAJalali @ Civil Soft Science, Iran, 2020-------\n";
		opserr << "------------------------------ Please Send Comments to: seyedalirezajalali@gmail.com-----------------------------\n";
		opserr<<  "-------Syntax:\n";
		opserr << "-------uniaxialMaterial IMKJ $matTag $K0 $as_Plus $as_Neg $My_Plus $My_Neg gama c $theta_p_Plus $theta_p_Neg $theta_pc_Plus $theta_pc_Neg $Res_Pos $Res_Neg $theta_u_Plus $theta_u_Neg  cyclicFlagP cyclicFlagN[: 1=Bilinear, 2=Pinched] $R0  $sigInit pinchxP pinchyP pinchxN pinchyN";
			 opserr << "\n\n";
		opserr << "------------------------------------------------------------------------------------------------------------\n\n\n";
			numThisCall = 1;
	}
  // Pointer to a uniaxial material that will be returned
  UniaxialMaterial *theMaterial = 0;

  int    iData[1];
  double dData[23];
  int numData = 1;

  if (OPS_GetIntInput(&numData, iData) != 0) {
    opserr << "WARNING invalid uniaxialMaterial IMKJ tag" << endln;
    return 0;
  }

  numData = OPS_GetNumRemainingInputArgs();

  if (numData < 23) {
    opserr << "Invalid IMKJ #args for: " << iData[0] << " see the syntax" << endln;
    return 0;
  }
    if (OPS_GetDoubleInput(&numData, dData) != 0) {
    opserr << "Invalid IMKJ #args for: " << iData[0] << " see the syntax" << endln;
    return 0;
    }

    // Parsing was successful, allocate the material
    theMaterial = new IMKJ(iData[0], dData[0], dData[1], dData[2], 
			      dData[3], dData[4], dData[5], dData[6], 
			      dData[7], dData[8], dData[9], dData[10],    
			      dData[11], dData[12], dData[13], dData[14], dData[15],
					 dData[16], dData[17], dData[18], dData[19], dData[20], dData[21], dData[22]);   


  if (theMaterial == 0) {
    opserr << "WARNING could not create uniaxialMaterial of type IMKJ Material\n";
    return 0;
  }

  return theMaterial;
}


IMKJ::IMKJ(int matTag, double K0, double as_Plus, double as_Neg, double My_Plus, double My_Neg,
	 double _gama, double _c, double theta_p_Plus, double theta_p_Neg,
	 double theta_pc_Plus, double theta_pc_Neg, double Res_Pos, double Res_Neg,
	 double theta_u_Plus, double theta_u_Neg, int flagP, int flagN, double _R0, double sigInit,
	 double pinchxP, double pinchyP, double pinchxN, double pinchyN) :
UniaxialMaterial(matTag, MAT_TAG_IMKJ),
	 Fyp(My_Plus), Fyn(My_Neg), E0(K0), bP(as_Plus), bN(as_Neg), epspP(theta_p_Plus), epspN(fabs(theta_p_Neg)),
	 epspcP(theta_pc_Plus), epspcN(fabs(theta_pc_Neg)), epsuP (theta_u_Plus), epsuN (fabs(theta_u_Neg)),
	 gama(_gama), c(_c), resFacP(Res_Pos), resFacN(Res_Neg),
	 R0(_R0), sigini(sigInit), cyclicFlagP(flagP), cyclicFlagN(flagN), pinchXP(pinchxP), pinchYP(pinchyP), pinchXN(pinchxN),  pinchYN(pinchyN)
{
	 EnergyP = 0;
	 eP = E0;
	 epsP = sigini / E0;
	 sigP = sigini;
	 sig = 0.0;
	 eps = 0.0;
	 e = E0;

	 konP = 0;
	 epsmaxP = Fyp / E0;
	 epsminP = -epsmaxP;
	 epsplP = 0.0;
	 epss0P = 0.0;
	 sigs0P = 0.0;
	 epssrP = 0.0;
	 sigsrP = 0.0;
	 FailEnerg = gama * Fyp * Fyp / E0;
	 ExcurEnergy = 0;
	 FydP = Fyp;
	 FydN = Fyn;

	 epsyP = Fyp / E0;
	 epsyN = Fyn / E0;
	 FcP = Fyp + bP *E0* (epspP - epsyP);
	 FcN = Fyn + bN *E0* (epspN - epsyN);
	 bcP = (resFacP * Fyp - FcP) / (epspcP - epspP)/E0;
	 bcN = (resFacN * Fyn - FcN) / (epspcN - epspN)/E0;
	 sigmin = -Fyn;
	 sigmax = Fyp;
	 b2 = 0;
	 RP = R0;

	 //double epsp = epspP + (resFacP * Fyp - FcP) / bcP / E0;
}

IMKJ::IMKJ(void):
  UniaxialMaterial(0, MAT_TAG_IMKJ)
{
	 EnergyP = 0;
	 eP = E0;
	 epsP = 0;
	 sigP = 0;
	 sig = 0.0;
	 eps = 0.0;
	 e = 0;

	 konP = 0;
	 epsmaxP = 0;
	 epsminP = 0;
	 epsplP = 0.0;
	 epss0P = 0.0;
	 sigs0P = 0.0;
	 epssrP = 0.0;
	 sigsrP = 0.0;

	 FailEnerg = gama = 0;
	 ExcurEnergy = 0;
	 FydP = FydN = 0;
}

IMKJ::~IMKJ(void)
{
  // Does nothing
}

UniaxialMaterial*
IMKJ::getCopy(void)
{
  IMKJ *theCopy = new IMKJ(this->getTag(), E0, bP, bN, Fyp, Fyn,
		gama, c, epspP, epspN,
		epspcP, epspcN, resFacP, resFacN,
		epsuP, epsuN, cyclicFlagP, cyclicFlagN, R0, sigini, pinchXP, pinchYP, pinchXN, pinchYN);
  
  return theCopy;
}

double
IMKJ::getInitialTangent(void)
{
  return E0;
}

int
IMKJ::setTrialStrain(double trialStrain, double strainRate)
{
	 double EshP = bP * E0;
	 double EshN = bN * E0;
	 eps = trialStrain + sigini / E0;
	 const double deps = eps - epsP;
	 if (fabs(deps) < 1.e-20)
		  return 0;

	 R = RP;
	 epsmax = epsmaxP;
	 epsmin = epsminP;
	 sigmax = sigmaxP;
	 sigmin = sigminP;
	 epspl = epsplP;
	 epss0 = epss0P;
	 sigs0 = sigs0P;
	 epsr = epssrP;
	 sigr = sigsrP;
	 kon = konP;
	 b2 = b2P;
	 if (kon == 0) {
		  epsmax = epsyP;
		  epsmin = -epsyN;
		  if (deps < 0.0) {
				kon = 2;
				epss0 = epsmin;
				sigs0 = -FydN;
				double e1 = (sigs0 - sigr) / (epss0 - epsr);
				b2 = bN * E0 / e1;
		  }
		  else
		  {
				kon = 1;
				epss0 = epsmax;
				sigs0 = FydP;
				double e1 = (sigs0 - sigr) / (epss0 - epsr);
				b2 = bP*E0/e1;
		  }
	 }
	 if (((kon == 1 || kon == 3 || kon == 5 || kon == 7 || kon == 9) && deps < 0) || ((kon == 2 || kon == 4 || kon == 6 || kon == 8) && deps > 0) )
	 {
		  epsr = epsP;
		  sigr = sigP;
		  epspl = epsP - sigP / E0;
		  R = R0;
		  if (kon == 2 || kon == 4 || kon == 6 || kon == 8)
		  {
				if (epsP < epsmin)
				{
					 epsmin = epsP;
					 sigmin = sigP;
				}
				if (cyclicFlagP == 1)
				{
					 kon = 1;
					 epss0 = (FydP - EshP * epsyP - sigr + E0 * epsr) / (E0 - EshP);
					 sigs0 = FydP + EshP * (epss0 - epsyP - epspl);
					 double e1 = (sigs0 - sigr) / (epss0 - epsr);
					 b2 = bP * E0 / e1;
				}
				else {
					 sigmax = posEnvlpStress(epsmax);
					 //double rotlim = negEnvlpRotlim(epsmin);
					 //double rotrel = (rotlim > epspl) ? rotlim : epspl;
					 double rotrel = epspl;
					 double rotmp2 = epsmax - (1.0 - pinchYP) * sigmax / E0;
					 double rotch = rotrel + (rotmp2 - rotrel) * pinchXP;
					 epss0 = rotch;
					 sigs0 = pinchYP * sigmax;
					 double e1 = (sigs0 - sigr) / (epss0 - epsr);
					 double e2 = (1 - pinchYP) * sigmax / (epsmax - epss0);
					 b2 = e2 / e1;
					 kon = 5;
				}
		  }
		  else {
				if (epsP > epsmax)
				{
					 epsmax = epsP;
					 sigmax = sigP;
				}
				if (cyclicFlagN == 1)
				{
					 kon = 2;
					 epss0 = (-FydN + EshN * epsyN - sigr + E0 * epsr) / (E0 - EshN);
					 sigs0 = -FydN + EshN * (epss0 + epsyN - epspl);
					 double e1 = (sigs0 - sigr) / (epss0 - epsr);
					 b2 = bN * E0 / e1;
					 R = R0 * 2;
				}
				else {
					 kon = 6;
				}

		  }

	 }
	 if (kon == 2) {
		  if (eps < -(epspN + epsyN) / 2 + epspl)
		  {
				epss0 = -epspN + epspl;
				sigs0 = -FcN;
				epsr = epsP;
				sigr = sigP;
				double e1 = (sigs0 - sigr) / (epss0 - epsr);
				b2 = bcN * E0 / e1;
				kon = 4;
		  }
	 }
	 if (kon == 1) {
		  if (eps > (epspP + epsyP) / 2)
		  {
				epss0 = epspP;
				sigs0 = FcP;
				epsr = epsP;
				sigr = sigP;
				double e1 = (sigs0 - sigr) / (epss0 - epsr);
				b2 = bcP * E0/ e1;
				kon = 3;
		  }
	 }
	 if (kon == 3)
	 {
		  if (eps > (epspP + epspcP)/2.)
		  {
				epss0 = epspcP;
				sigs0 = resFacP*Fyp;
				epsr = epsP;
				sigr = sigP;
				double e1 = (sigs0 - sigr) / (epss0 - epsr);
				b2 = 1.e-12 * E0 / e1;
				R = R0 / 4;
				kon = 9;
		  }
	 }
	 if (kon == 4)
	 {
		  
		  if (eps < -(epspN + epspcN)/2. + epspl)
		  {
				epss0 = -epspcN + epspl;
				sigs0 = -resFacN*Fyn;
				epsr = epsP;
				sigr = sigP;
				double e1 = (sigs0 - sigr) / (epss0 - epsr);
				//double e1 = bcN*E0;
				b2 = 1.e-12 * E0 / e1;
				R = R0 / 2;
				kon = 8;
		  }
	 }
	 if (kon == 5) {
		  if (eps > (epsmax + epss0) / 2)
		  {
				epss0 = epsmax;
				sigs0 = sigmax;
				epsr = epsP;
				sigr = sigP;
				double e1 = (sigs0 - sigr) / (epss0 - epsr);
				b2 = bP * E0 / e1;
				kon = 7;
				if (epsmax  > epspcP )
				{
					 b2 = 1.e-12 * E0 / e1;//
					 kon = 9;
				}
				else if (epsmax  > epspP )
				{
					 b2 = bcP * E0 / e1;//
					 kon = 3;
				}
		  }
	 }
	 if (kon == 6) {
		  opserr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	 }
	 if (kon == 7) {
		  if (epsmax > (epsyP+epspP)/2.)
		  if ((eps - epsr) / (epss0 - epsr) > 1.2)
		  {
				epss0 = epspP;
				sigs0 = FcP;
				epsr = epsP;
				sigr = sigP;
				double e1 = (sigs0 - sigr) / (epss0 - epsr);
				b2 = bcP * E0 / e1;
				kon = 3;
		  }
		  
	 }
	 // calculate current stress sig and tangent modulus E 
	 const double epsrat = (eps - epsr) / (epss0 - epsr);
	 const double dum1 = 1.0 + pow(fabs(epsrat), R);
	 const double dum2 = pow(dum1, (1 / R));

	 sig = b2 * epsrat + (1.0 - b2) * epsrat / dum2;
	 sig = sig * (sigs0 - sigr) + sigr;

	 e = b2 + (1.0 - b2) / (dum1 * dum2);
	 e *= (sigs0 - sigr) / (epss0 - epsr);
	 //if (kon == 4 && sig > -resFacN * Fyn)
	 //{
		//  sig = -resFacN * Fyn;
		//  e = 1.e-12 * E0;
	 //}
	 return 0;
}

double 
IMKJ::getStrain(void)
{
  return eps;
}

double 
IMKJ::getStress(void)
{
  return sig;
}

double 
IMKJ::getTangent(void)
{
  return e;
}

int 
IMKJ::commitState(void)
{
  epsminP = epsmin;
  epsmaxP = epsmax;
  sigminP = sigmin;
  sigmaxP = sigmax;
  b2P = b2;
  epsplP = epspl;
  epss0P = epss0;
  sigs0P = sigs0;
  epssrP = epsr;
  sigsrP = sigr;

  updateDamage();
  konP = kon;
  eP = e;
  sigP = sig;
  epsP = eps;
  RP = R;
  return 0;
}

int 
IMKJ::revertToLastCommit(void)
{
  epsmin = epsminP;
  epsmax = epsmaxP;
  sigmin = sigminP;
  sigmax = sigmaxP;
  epspl = epsplP;
  epss0 = epss0P;
  sigs0 = sigs0P;
  epsr = epssrP;
  sigr = sigsrP;
  kon = konP;
  b2 = b2P;
  e = eP;
  sig = sigP;
  eps = epsP;
  R = RP;
  return 0;
}

int 
IMKJ::revertToStart(void)
{
	 EnergyP = 0;	//by SAJalali
	 eP = E0;
	 epsP = sigini / E0;
	 sigP = sigini;
	 sig = 0.0;
	 eps = 0.0;
	 e = E0;
	 
	 konP = 0;
	 epsmaxP = Fyp / E0;
	 epsminP = -epsmaxP;
	 sigmaxP = Fyp;
	 sigminP = -Fyn;
	 epsplP = 0.0;
	 epss0P = 0.0;
	 sigs0P = 0.0;
	 epssrP = 0.0;
	 sigsrP = 0.0;


	 ExcurEnergy = 0;
	 FydP = Fyp;
	 FydN = Fyn;
	 return 0;
}

int 
IMKJ::sendSelf(int commitTag, Channel &theChannel)
{
  static Vector data(42);
  int i = 0;
  data(i++) = Fyp;
  data(i++) = Fyn;
  data(i++) = E0;
  data(i++) = bP;
  data(i++) = bN;
  data(i++) = R0;
  data(i++) = epsminP;
  data(i++) = epsmaxP;
  data(i++) = epsplP;
  data(i++) = epss0P;
  data(i++) = sigs0P;
  data(i++) = epssrP;
  data(i++) = sigsrP;
  data(i++) = konP;
  data(i++) = epsP;
  data(i++) = sigP;
  data(i++) = eP;
  data(i++) = this->getTag();
  data(i++) = sigini;
  data(i++) = EnergyP;
  data(i++) = gama;
  data(i++) = c;
  data(i++) = resFacP;
  data(i++) = resFacN;
  data(i++) = FydP;
  data(i++) = FydN;
  data(i++) = ExcurEnergy;
  data(i++) = gama;
  data(i++) = cyclicFlagP;
  data(i++) = cyclicFlagN;
  data(i++) = sigmaxP;
  data(i++) = sigminP;
  if (theChannel.sendVector(this->getDbTag(), commitTag, data) < 0) {
    opserr << "IMKJ::sendSelf() - failed to sendSelf\n";
    return -1;
  }
  return 0;
}

int 
IMKJ::recvSelf(int commitTag, Channel& theChannel,
	 FEM_ObjectBroker& theBroker)
{
	 static Vector data(42);	//editted by SAJalali for energy

	 if (theChannel.recvVector(this->getDbTag(), commitTag, data) < 0) {
		  opserr << "IMKJ::recvSelf() - failed to recvSelf\n";
		  return -1;
	 }
	 int i = 0;
	 Fyp = data(i++);
	 Fyn = data(i++);
	 E0 = data(i++);
	 bP = data(i++);
	 bN = data(i++);
	 R0 = data(i++);
	 epsminP = data(i++);
	 epsmaxP = data(i++);
	 epsplP = data(i++);
	 epss0P = data(i++);
	 sigs0P = data(i++);
	 epssrP = data(i++);
	 sigsrP = data(i++);
	 konP = int(data(i++));
	 epsP = data(i++);
	 sigP = data(i++);
	 eP = data(i++);
	 this->setTag(int(data(i++)));
	 sigini = data(i++);
	 EnergyP = data(i++);
	 gama = data(i++);
	 c = data(i++);
	 resFacP = data(i++);
	 resFacN = data(i++);
	 FydP = data(i++);
	 FydN = data(i++);
	 ExcurEnergy = data(i++);
	 gama = data(i++);
	 cyclicFlagP = int(data(i++));
	 cyclicFlagN = int(data(i++));
	 sigmaxP = data(i++);
	 sigminP = data(i++);
	 FailEnerg = gama * Fyp * Fyp / E0;

	 e = eP;
	 sig = sigP;
	 eps = epsP;

	 return 0;
}

void 
IMKJ::Print(OPS_Stream &s, int flag)
{
}

// AddingSensitivity:BEGIN ///////////////////////////////////
int
IMKJ::setParameter(const char **argv, int argc, Parameter &param)
{
  return -1;
}

int
IMKJ::updateParameter(int parameterID, Information &info)
{
  
  return -1;
}


void IMKJ::updateDamage()
{
	if (((konP == 1 || konP == 3) && sig < 0) || ((konP == 2 || konP == 4) && sig > 0))
	{
		//submit Pos damage and reset for new excursion
		double zeroSigEps = epsP - sigP/E0;
		double dE = 0.5 * sigP * (zeroSigEps - epsP);
		EnergyP += dE;
		if (EnergyP < 0) EnergyP = 0.;
		if (gama > 9999)
		{
			return;
		}
		double& Fyd = (konP == 2 || konP == 4) ? FydP : FydN;
		double& resFac = (konP == 2 || konP == 4) ? resFacP : resFacN;
		//double& Fyd = FydP;
		ExcurEnergy += dE;
		if (ExcurEnergy < 0) ExcurEnergy = 0.;
		double beta = pow( ExcurEnergy / ( FailEnerg - EnergyP) , c );
		if (beta > 0.999 || beta < 0)
		{
			opserr<< "\nIMKJ:"<< this->getTag()<< " WARNING! Maximum Energy Absorbance Capacity Reached\n"<< endln;
			beta = 0.999;
		}
		Fyd = (1. - beta)*Fyd + beta * resFac*Fyd;
		//FydN = Fyd;
		ExcurEnergy = 0.0;
	} 
	else
	{
		double dE = 0.5 * (sig + sigP) * (eps - epsP);
		ExcurEnergy += dE;
		EnergyP += dE;
    }
}

double
IMKJ::posEnvlpStress(double strain)
{
	 double epsr = (resFacP * Fyp - FcP) / bcP/E0 + epspP;
	 if (strain <= 0.0)
		  return 0.0;
	 else if (strain <= epsyP)
		  return E0 * strain;
	 else if (strain <= epspP)
		  return Fyp + bP *E0* (strain - epsyP);
	 else if (strain <= epsr)
		  return FcP + bcP *E0* (strain - epspP);
	 else if (strain <= epsuP)
		  return resFacP * Fyp;
	 else
		  return 0;
}

double
IMKJ::negEnvlpStress(double strain)
{
	 double epsr = (resFacN * Fyn - FcN) / bcN/E0 + epspN;
	 if (strain >= 0)
		  return 0.0;
	 else if (strain >= -epsyN)
		  return E0 * strain;
	 else if (strain >= -epspN)
		  return -Fyn + bN*E0 * (strain - (-epsyN));
	 else if (strain >= -epsr)
		  return -FcN + bcN*E0 * (strain - (-epspN));
	 else if (strain >= -epsuN)
		  return -resFacN * Fyn;
	 else
		  return 0;
}

double
IMKJ::posEnvlpTangent(double strain)
{
	 double epsr = (resFacN * Fyn - FcN) / bcN / E0 + epspN;
	 if (strain < 0.0)
		  return E0 * 1.0e-12;
	 else if (strain <= epsyP)
		  return E0;
	 else if (strain <= epspP)
		  return bP*E0;
	 else if (strain <= epsr)
		  return bcP*E0;
	 else
		  return E0 * 1.0e-12;
}

double
IMKJ::negEnvlpTangent(double strain)
{
	 if (strain > 0)
		  return E0 * 1.0e-12;
	 else if (strain >= -epsyN)
		  return E0;
	 else if (strain >= -epspN)
		  return bN * E0;
	 else if (strain >= -epsr)
		  return bcN * E0;
	 else
		  return 1.e-12*E0;
}

double
IMKJ::posEnvlpRotlim(double strain)
{
	 double epsr = (resFacN * Fyn - FcN) / bcN / E0 + epspN;
	 double strainLimit = POS_INF_STRAIN;

	 if (strain <= epsyP)
		  return POS_INF_STRAIN;
	 if (strain > epsyP && strain <= epspP && bP < 0.0)
		  strainLimit = epsyP - Fyp / bP/E0;
	 if (strain > epspP && bcP < 0.0)
		  strainLimit = epspP - FcP / bcP/E0;

	 if (strainLimit == POS_INF_STRAIN)
		  return POS_INF_STRAIN;
	 else if (posEnvlpStress(strainLimit) > 0)
		  return POS_INF_STRAIN;
	 else
		  return strainLimit;
}

double
IMKJ::negEnvlpRotlim(double strain)
{
	 double strainLimit = NEG_INF_STRAIN;

	 if (strain >= -epsyN)
		  return NEG_INF_STRAIN;
	 if (strain < -epsyN && strain >= -epspN && bN < 0.0)
		  strainLimit = -epsyN + Fyn / bN/E0;
	 if (strain < -epspN && bcN < 0.0)
		  strainLimit = -epspN + FcN / bcN/E0;

	 if (strainLimit == NEG_INF_STRAIN)
		  return NEG_INF_STRAIN;
	 else if (negEnvlpStress(strainLimit) < 0)
		  return NEG_INF_STRAIN;
	 else
		  return strainLimit;
}

