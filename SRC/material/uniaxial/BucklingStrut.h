#ifndef BucklingStrut_h
#define BucklingStrut_h
#include <UniaxialMaterial.h>
class BucklingStrut:public UniaxialMaterial
{
public:
	BucklingStrut(int tag, double fpy, double E0, double b, double fc, double _bc, double r0, double r1, double r2);
	
	BucklingStrut(void);
	virtual ~BucklingStrut();
	const char* getClassType(void) const override {return "BucklingStrut";};
	double getInitialTangent() override;
	UniaxialMaterial* getCopy();
	virtual int setTrialStrain(double strain, double strainRate = 0.0);
	virtual double getStrain();
	virtual double getStress();
	virtual double getTangent();
	virtual int commitState();
	virtual int revertToLastCommit();
	virtual int revertToStart();
	virtual int sendSelf(int commitTag, Channel& theChannel);
	virtual int recvSelf(int commitTag, Channel& theChannel, FEM_ObjectBroker & theBroker);
	virtual void Print(OPS_Stream & s, int flag = 0);
    //virtual Response *setResponse (const char **argv, int argc, 
				//   OPS_Stream &theOutputStream);
    //virtual int getResponse (int responseID, Information &matInformation);
	virtual double getEnergy();
	double getInitYieldStrain() {return Fts/E0;}

private:
	//void updateDamage();
private:
	void MenegottoPinto (double epsc, double bT, double R, double& sigc, double _bc, double& ec);
	//void MenegottoPinto (double epsc, double bT, double R, double& sigc, double& ec, double er, double sr, double e0, double s0);
	//matpar : PLATE PROPERTIES
	double Fts	;			//yield stress
	double E0	;			//initial stiffness
	double b	;			//hardening ratio
	double bc	;			//hardening ratio in compression
	double R0;
	double R1;
	double R2;
	double Fcs	;			//yield stress of a compression strip
	double FTS, FCS;		//yield stresses before damage
	//Commit HISTORY VARIABLES
	double epsmaxP	;		//max eps in tension
	double sigmaxP	;		//max sig in tension
	double epss0P	;		//eps at asymptotes intersection
	double sigs0P	;		//sig at ...
	double epssrP	;		//eps at last inversion point
	double sigsrP	;		//sig at ...
	double epsTFP	;		//eps at tension field redevelopment point
	double plstrP	;		//plastic strain
	int konP	;			//index for loading-unloading
	double epsP	;			//eps at previous converged step
	double sigP	;			//stress at ...
	double eP	;			//stiffness modulus at ...

	//trial history variables
	double epsmax	;		//
	double sigmax	;		//
	double epss0	;		//
	double sigs0	;		//
	double epsr		;		//
	double sigr		;		//
	double epsTF	;		//
	double plstr	;		//
	int kon			;		//
	double sig		;		//
	double e		;		//
	double eps		;		//
	//bool capStrFlg;		//flag to indicate whether capping strain has been passed or not

	//by SAJalali
	double EnergyP;

};
#endif