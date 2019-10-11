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
                                                                        
// $Revision: 1.10 $
// $Date: 1395-12-08 22:25:03 $
// $Source: /usr/local/cvs/OpenSees/SRC/recorder/ResidElementRecorder.h,v $
                                                                        
#ifndef ResidElementRecorder_h
#define ResidElementRecorder_h

// Written: SAJalali 
//
// What: "@(#) ResidElementRecorder.h, revA"

#include <Recorder.h>
#include <Information.h>
#include <OPS_Globals.h>
#include <ID.h>


class Domain;
class Vector;
class Matrix;
class Element;
class Response;
class FE_Datastore;

class ResidElementRecorder: public Recorder
{
  public:
    ResidElementRecorder();
    ResidElementRecorder(const ID *eleID, 
			    const char **argv, 
			    int argc,
			    Domain &theDomain, 
			    OPS_Stream &theOutputHandler,
			    bool echoTimeFlag = true,
			    const ID *dof =0); 


    ~ResidElementRecorder();

    int record(int commitTag, double timeStamp);
    int restart(void);    

    int setDomain(Domain &theDomain);
    int sendSelf(int commitTag, Channel &theChannel);  
    int recvSelf(int commitTag, Channel &theChannel, 
		 FEM_ObjectBroker &theBroker);
    
  protected:
    
  private:	
    int initialize(void);

    int numEle;
    int numDOF;
    
    ID *eleID;
    ID *dof;

    Response **theResponses;

    Domain *theDomain;
    OPS_Stream *theHandler;

    Matrix *data;

    bool initializationDone;
    char **responseArgs;
    int numArgs;

    bool echoTimeFlag; 

    int addColumnInfo;
};


#endif
