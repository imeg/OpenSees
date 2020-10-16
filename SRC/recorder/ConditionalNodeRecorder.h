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
                                                                        

// $Revision: 1.11 $
// $Date: 1395-12-08 22:25:03 $
// $Source: /usr/local/cvs/OpenSees/SRC/recorder/ConditionalNodeRecorder.h,v $
                                                                        

                                                                        
#ifndef ConditionalNodeRecorder_h
#define ConditionalNodeRecorder_h

// Written: SAJalali 
//
// Description: This file contains the class definition for EnvelopeRecorder.
// A EnvelopeRecorder is used to record the envelop of specified dof responses 
// at a collection of nodes over an analysis. (between commitTag of 0 and
// last commitTag).
//
// What: "@(#) ConditionalNodeRecorder.h, revA"


#include <Recorder.h>
#include <ID.h>
#include <Vector.h>
#include <Matrix.h>
#include <TimeSeries.h>

class Domain;
class FE_Datastore;
class Node;

class ConditionalNodeRecorder: public Recorder
{
  public:
    ConditionalNodeRecorder();
    ConditionalNodeRecorder(const ID &theDof, 
			 const ID *theNodes, 
			 const char *dataToStore,
			 Domain &theDomain,
			 OPS_Stream &theOutputHandler,
			int rcrdrTag,
			int procMethod = 0,
			 bool echoTimeFlag = false,
			 TimeSeries **theTimeSeries =0); 
    
    ~ConditionalNodeRecorder();

    int record(int commitTag, double timeStamp);
    int restart(void);    

    int setDomain(Domain &theDomain);
    int sendSelf(int commitTag, Channel &theChannel);  
    int recvSelf(int commitTag, Channel &theChannel, 
		 FEM_ObjectBroker &theBroker);
    
  protected:
    
  private:	
	  int envRcrdrTag;
	  Recorder* envRcrdr;
      int numDOF;
      int procDataMethod;  //flag to indicate element group processing method:
                           //0: no processing, print separate results
                           //1: summate results
                           //2: maximize results
                           //3: minimize results
      int initialize(void);

    ID *theDofs;
    ID *theNodalTags;
    Node **theNodes;

    Matrix *data;

    Domain *theDomain;
    OPS_Stream *theHandler;

    int dataFlag; // flag indicating what it is to be stored in recorder

    bool initializationDone;
    int numValidNodes;

    bool echoTimeFlag;   // flag indicating whether time to be included in o/p

    int addColumnInfo;
    TimeSeries **theTimeSeries;
    double *timeSeriesValues;
};

#endif
