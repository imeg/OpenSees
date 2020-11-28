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
                                                                        
// $Revision: 1.0 $                                                                     
// Written: S. A. Jalalli 11/2020
// A smooth version of the Ibarra-Medina-Krawinkler Model
// with Bilinear, Pinched and Peak-Oriented cyclic rules


#ifndef IMKJ_h
#define IMKJ_h

#include <UniaxialMaterial.h>

class IMKJ : public UniaxialMaterial
{
  public:
		IMKJ(int matTag, double E0, double bP, double bN, double FyP, double FyN,
          double gama, double c, double epspP, double epspN,
          double epspcP, double epspcN, double resFacP, double resFacN,
          double epsuP, double epsuN, int cyclicFlagP, int cyclicFlagN, double R0, double sigInit,
          double pinchxP, double pinchyP, double pinchxN, double pinchyN);
        
    IMKJ(void);
    virtual ~IMKJ();
    

    const char *getClassType(void) const {return "IMKJ";};

    double getInitialTangent(void);
    UniaxialMaterial *getCopy(void);

    int setTrialStrain(double strain, double strainRate = 0.0); 
    double getStrain(void);      
    double getStress(void);
    double getTangent(void);
    
    int commitState(void);
    int revertToLastCommit(void);    
    int revertToStart(void);        
    
    int sendSelf(int commitTag, Channel &theChannel);  
    int recvSelf(int commitTag, Channel &theChannel, 
		 FEM_ObjectBroker &theBroker);    
    
    void Print(OPS_Stream &s, int flag =0);

    int setParameter(const char **argv, int argc, Parameter &param);
    int updateParameter(int parameterID, Information &info);
    
    //by SAJalali
	virtual double getEnergy() { return EnergyP; };

#ifdef _CSS
	//by SAJalali
	double getInitYieldStrain() { return Fyp / E0; }
#endif // _CSS

protected:
    
 private:
	//by SAJalali
	double epspP, epspN, epspcP, epspcN, epsuP, epsuN, epsyP, epsyN;	
	double FailEnerg, c, gama;			//damage parameters
	double resFacP, resFacN;
	double FydP, FydN;		//Pos and Neg Fy's affected by damage
	double ExcurEnergy;
   int cyclicFlagP, cyclicFlagN;
   double pinchXP, pinchYP;
   double pinchXN, pinchYN;
   double FcP, FcN;
   double bcP, bcN;
	void updateDamage();
	 double EnergyP; //by SAJalali
    double Fyp;  //  = matpar(1)  : positive yield stress
    double Fyn;  //  = matpar(2)  : negative yield stress
    double E0;  //   = matpar(3)  : initial stiffness
    double bP, bN;   //   = matpar(4)  : hardening ratio (Esh/E0)
    double R0;  //   = matpar(5)  : exp transition elastic-plastic
    double sigini; // initial 
    // hstvP : STEEL HISTORY VARIABLES
    double epsminP; //  = hstvP(1) : max eps in compression
    double epsmaxP; //  = hstvP(2) : max eps in tension
    double sigminP;
    double sigmaxP;
    double epsplP;  //  = hstvP(3) : plastic excursion
    double epss0P;  //  = hstvP(4) : eps at asymptotes intersection
    double sigs0P;  //  = hstvP(5) : sig at asymptotes intersection
    double epssrP;  //  = hstvP(6) : eps at last inversion point
    double sigsrP;  //  = hstvP(7) : sig at last inversion point
    int    konP;    //  = hstvP(8) : index for loading/unloading
    double RP;      // transition curve
    // hstv : STEEL HISTORY VARIABLES   
    double epsP;  //  = strain at previous converged step
    double sigP;  //  = stress at previous converged step
    double eP;    //   stiffness modulus at last converged step;
    double b2P;    //   stiffness modulus at last converged step;

    double epsmin; 
    double epsmax; 
    double sigmin; 
    double sigmax; 
    double epspl;  
    double epss0;  
    double sigs0; 
    double epsr;  
    double sigr;  
    int    kon;    
    double sig;   
    double e;     
    double eps;   //  = strain at current step
    double b2;    // ratio of the second asymptote tangent to the first one
    double R;
    //double TrotPu, TrotNu; //reloading strain for positive and negative directions
    double posEnvlpStress(double strain);
    double negEnvlpStress(double strain);

    double posEnvlpTangent(double strain);
    double negEnvlpTangent(double strain);

    double posEnvlpRotlim(double strain);
    double negEnvlpRotlim(double strain);

};


#endif

