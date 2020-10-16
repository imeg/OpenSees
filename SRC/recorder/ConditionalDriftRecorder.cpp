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

// $Revision: 1.1 $
// $Date: 1395-12-08 22:25:03 $
// $Source: /usr/local/cvs/OpenSees/SRC/recorder/ConditionalDriftRecorder.cpp,v $

// Written: SAJalali
// Created: 08/06
//
// Description: This file contains the class definition for ConditionalDriftRecorder.
#include <OPS_Globals.h>
#ifdef _CSS


#include <math.h>

#include <ConditionalDriftRecorder.h>
#include <Domain.h>
#include <Node.h>
#include <Vector.h>
#include <ID.h>
#include <Matrix.h>
#include <string.h>
#include <Channel.h>
#include <FEM_ObjectBroker.h>

ConditionalDriftRecorder::ConditionalDriftRecorder()
  :Recorder(RECORDER_TAGS_ResidDriftRecorder),
   ndI(0), ndJ(0), dof(0), perpDirn(0), oneOverL(0),
   theDomain(0), theOutputHandler(0), data(0),
   initializationDone(false), numNodes(0), echoTimeFlag(false)
{
  
}


ConditionalDriftRecorder::ConditionalDriftRecorder(int ni, 
					     int nj, 
					     int df, 
					     int dirn,
					     Domain &theDom, 
					     OPS_Stream &theCurrentDataOutputHandler,
						 int rcrdrTag, int dataProcMethod,
					     bool timeFlag)
  :Recorder(RECORDER_TAGS_ResidDriftRecorder),
   ndI(0), ndJ(0), theNodes(0), dof(df), perpDirn(dirn), oneOverL(0),
   theDomain(&theDom), theOutputHandler(&theCurrentDataOutputHandler), data(0),
   initializationDone(false), numNodes(0), echoTimeFlag(timeFlag), envRcrdrTag(rcrdrTag), procDataMethod(dataProcMethod)
{
  ndI = new ID(1);
  ndJ = new ID (1);
  
  if (ndI != 0 && ndJ != 0) {
    (*ndI)(0) = ni;
    (*ndJ)(0) = nj;
  }
}


ConditionalDriftRecorder::ConditionalDriftRecorder(const ID &nI, 
					     const ID &nJ, 
					     int df, 
					     int dirn,
					     Domain &theDom, 
					     OPS_Stream &theDataOutputHandler,
						 int rcrdrTag, int dataProcMethod,
					     bool timeFlag)
  :Recorder(RECORDER_TAGS_ResidDriftRecorder),
   ndI(0), ndJ(0), theNodes(0), dof(df), perpDirn(dirn), oneOverL(0),
   theDomain(&theDom), theOutputHandler(&theDataOutputHandler), data(0),
   initializationDone(false), numNodes(0), echoTimeFlag(timeFlag), envRcrdrTag(rcrdrTag), procDataMethod(dataProcMethod)
{
  ndI = new ID(nI);
  ndJ = new ID (nJ);
}

ConditionalDriftRecorder::~ConditionalDriftRecorder()
{
  //
  // write the data
  //
  if (theOutputHandler != 0 && data != 0) {
	  int size = data->noCols();
	  Vector currentData(size);
    theOutputHandler->tag("Data"); // Data
		
    for (int j=0; j<size; j++)
		currentData(j) = (*data)(0,j);
    theOutputHandler->write(currentData);
    theOutputHandler->endTag(); // Data
    theOutputHandler->endTag(); // OpenSeesOutput
  }



  if (ndI != 0)
    delete ndI;
  
  if (ndJ != 0)
    delete ndJ;
  
  if (oneOverL != 0)
    delete oneOverL;
  
  if (theNodes != 0)
    delete [] theNodes;
  
  if (theOutputHandler != 0)
    delete theOutputHandler;
}

int 
ConditionalDriftRecorder::record(int commitTag, double timeStamp)
{
  
  if (theDomain == 0 || ndI == 0 || ndJ == 0) {
    return 0;
  }
  
  if (theOutputHandler == 0) {
    opserr << "ConditionalDriftRecorder::record() - no DataOutputHandler has been set\n";
    return -1;
  }
  
  if (initializationDone != true) 
    if (this->initialize() != 0) {
      opserr << "ConditionalDriftRecorder::record() - failed in initialize()\n";
      return -1;
    }
  
  if (numNodes == 0)
    return 0;
  if (envRcrdr->getModified() == 0)
	return 0;
  int  iStart = 0;
  if (echoTimeFlag)
  {
	  iStart = 1;
	  (*data)(0,0) = timeStamp;
  }

  if (procDataMethod)
  {
      double val = 0, val1 = 0;
      for (int i = 0; i < numNodes; i++) {
          Node* nodeI = theNodes[2 * i];
          Node* nodeJ = theNodes[2 * i + 1];

          if ((*oneOverL)(i) != 0.0) {
              const Vector& dispI = nodeI->getTrialDisp();
              const Vector& dispJ = nodeJ->getTrialDisp();

              double dx = dispJ(dof) - dispI(dof);

              val1 = dx * (*oneOverL)(i);

          }
          else
              val1 = 0.0;

          if (i == 0 && procDataMethod != 1)
              val = fabs(val1);
          if (procDataMethod == 1)
              val += val1;
          else if (procDataMethod == 2 && val1 > val)
              val = val1;
          else if (procDataMethod == 3 && val1 < val)
              val = val1;
          else if (procDataMethod == 4 && fabs(val1) > val)
              val = fabs(val1);
          else if (procDataMethod == 5 && fabs(val1) < val)
              val = fabs(val1);
      }
      (*data)(0,iStart) = val;
  }
  else

  for (int i=0; i<numNodes; i++) {
    Node *nodeI = theNodes[2*i];
    Node *nodeJ = theNodes[2*i+1];
    
    if ((*oneOverL)(i) != 0.0) {
      const Vector &dispI = nodeI->getTrialDisp();
      const Vector &dispJ = nodeJ->getTrialDisp();
      
      double dx = dispJ(dof)-dispI(dof);
      
      (*data)(0,i+iStart) =  dx* (*oneOverL)(i);
      
    }
    else
      (*data)(0,iStart) = 0.0;
  }
  
  return 0;
}

int
ConditionalDriftRecorder::restart(void)
{
  data->Zero();
  return 0;
}

int 
ConditionalDriftRecorder::setDomain(Domain &theDom)
{
  theDomain = &theDom;
  initializationDone = false;
  return 0;
}

int
ConditionalDriftRecorder::sendSelf(int commitTag, Channel &theChannel)
{
  static ID idData(6); 
  idData.Zero();
  if (ndI != 0 && ndI->Size() != 0)
    idData(0) = ndI->Size();
  if (ndJ != 0 && ndJ->Size() != 0)
    idData(1) = ndJ->Size();
  idData(2) = dof;
  idData(3) = perpDirn;
  if (theOutputHandler != 0) {
    idData(4) = theOutputHandler->getClassTag();
  }
  if (echoTimeFlag == true)
    idData(5) = 0;
  else
    idData(5) = 1;    

  if (theChannel.sendID(0, commitTag, idData) < 0) {
    opserr << "ConditionalDriftRecorder::sendSelf() - failed to send idData\n";
    return -1;
  }

  if (ndI != 0) 
    if (theChannel.sendID(0, commitTag, *ndI) < 0) {
      opserr << "ConditionalDriftRecorder::sendSelf() - failed to send dof id's\n";
      return -1;
    }

  if (ndJ != 0) 
    if (theChannel.sendID(0, commitTag, *ndJ) < 0) {
      opserr << "ConditionalDriftRecorder::sendSelf() - failed to send dof id's\n";
      return -1;
    }


  if (theOutputHandler->sendSelf(commitTag, theChannel) < 0) {
    opserr << "ConditionalDriftRecorder::sendSelf() - failed to send the DataOutputHandler\n";
    return -1;
  }

  return 0;
}

int 
ConditionalDriftRecorder::recvSelf(int commitTag, Channel &theChannel, 
			FEM_ObjectBroker &theBroker)
{
  static ID idData(5); 
  if (theChannel.recvID(0, commitTag, idData) < 0) {
    opserr << "ConditionalDriftRecorder::sendSelf() - failed to send idData\n";
    return -1;
  }
  
  if (idData(0) != 0) {
    ndI = new ID(idData(0));
    if (ndI == 0) {
      opserr << "ConditionalDriftRecorder::sendSelf() - out of memory\n";
      return -1;
    }
    if (theChannel.recvID(0, commitTag, *ndI) < 0) {
      opserr << "ConditionalDriftRecorder::sendSelf() - failed to recv dof id's\n";
      return -1;
    } 
  }

  if (idData(1) != 0) {

    ndJ = new ID(idData(1));
    if (ndJ == 0) {
      opserr << "ConditionalDriftRecorder::sendSelf() - out of memory\n";
      return -1;
    }
    if (theChannel.recvID(0, commitTag, *ndJ) < 0) {
      opserr << "ConditionalDriftRecorder::sendSelf() - failed to recv dof id's\n";
      return -1;
    } 
  }

  dof = idData(2);
  perpDirn = idData(3);

  if (idData(5) == 0)
    echoTimeFlag = true;
  else
    echoTimeFlag = false;

  if (theOutputHandler != 0)
    delete theOutputHandler;

  theOutputHandler = theBroker.getPtrNewStream(idData(4));
  if (theOutputHandler == 0) {
    opserr << "ConditionalDriftRecorder::sendSelf() - failed to get a data output handler\n";
    return -1;
  }

  if (theOutputHandler->recvSelf(commitTag, theChannel, theBroker) < 0) {
    opserr << "ConditionalDriftRecorder::sendSelf() - failed to send the DataOutputHandler\n";
    return -1;
  }

  return 0;
}


int
ConditionalDriftRecorder::initialize(void)
{
  theOutputHandler->tag("OpenSeesOutput");

  initializationDone = true; // still might fail but don't want back in again

  //
  // clean up old memory
  //

  if (theNodes != 0) {
    delete [] theNodes;
    theNodes = 0;
  }
  if (oneOverL != 0) {
    delete oneOverL;
    oneOverL = 0;
  }

  //
  // check valid node ID's
  //

  if (ndI == 0 || ndJ == 0) {
    opserr << "ConditionalDriftRecorder::initialize() - no nodal id's set\n";
    return -1;
  }

  int ndIsize = ndI->Size();
  int ndJsize = ndJ->Size();

  if (ndIsize == 0) {
    opserr << "ConditionalDriftRecorder::initialize() - no nodal id's set\n";
    return -1;
  }

  if (ndIsize != ndJsize) {
    opserr << "ConditionalDriftRecorder::initialize() - error node arrays differ in size\n";
    return -2;
  }

  //
  // lets loop through & determine number of valid nodes
  //


  numNodes = 0;

  for (int i=0; i<ndIsize; i++) {
    int ni = (*ndI)(i);
    int nj = (*ndJ)(i);
    
    Node *nodeI = theDomain->getNode(ni);
    Node *nodeJ = theDomain->getNode(nj);

    if (nodeI != 0 && nodeJ != 0) {
     const Vector &crdI = nodeI->getCrds();
     const Vector &crdJ = nodeJ->getCrds();

     if (crdI.Size() > perpDirn  && crdJ.Size() > perpDirn) 
       if (crdI(perpDirn) != crdJ(perpDirn)) 
	 numNodes++;
    }  
  }

  if (numNodes == 0) {
    opserr << "ConditionalDriftRecorder::initialize() - no valid nodes or perpendicular direction\n";
    return 0;
  }

  //
  // allocate memory
  //

  if (echoTimeFlag == true) {
    data = new Matrix(1, numNodes+1);
  } else {
    data = new Matrix(1, numNodes);
  }
  data->Zero();
  theNodes = new Node *[2*numNodes];
  oneOverL = new Vector(numNodes);
  if (theNodes == 0  || oneOverL == 0 ) {
    opserr << "ConditionalDriftRecorder::initialize() - out of memory\n";
    return -3;
  }

  //
  // set node pointers and determine one over L
  //

  int counter = 0;
  int counterI = 0;
  int counterJ = 1;
  for (int j=0; j<ndIsize; j++) {
    int ni = (*ndI)(j);
    int nj = (*ndJ)(j);
    
    Node *nodeI = theDomain->getNode(ni);
    Node *nodeJ = theDomain->getNode(nj);

    if (nodeI != 0 && nodeJ != 0) {
     const Vector &crdI = nodeI->getCrds();
     const Vector &crdJ = nodeJ->getCrds();

     if (crdI.Size() > perpDirn  && crdJ.Size() > perpDirn) 
       if (crdI(perpDirn) != crdJ(perpDirn)) {

	 theOutputHandler->tag("DriftOutput");	 
	 theOutputHandler->attr("node1", ni);	 
	 theOutputHandler->attr("node2", ni);	 
	 theOutputHandler->attr("perpDirn", perpDirn);	 
	 theOutputHandler->attr("lengthPerpDirn", fabs(crdJ(perpDirn) - crdI(perpDirn)));

	 if (echoTimeFlag == true) {
	   theOutputHandler->tag("TimeOutput");
	   theOutputHandler->tag("ResponseType", "time");
	   theOutputHandler->endTag(); // TimeOutput
	 }

	 theOutputHandler->tag("ResponseType", "drift");
	 theOutputHandler->endTag(); // DriftOutput


	 (*oneOverL)(counter) = 1.0/fabs(crdJ(perpDirn) - crdI(perpDirn));
	 theNodes[counterI] = nodeI;
	 theNodes[counterJ] = nodeJ;
	 counterI+=2;
	 counterJ+=2;
	 counter++;
       }  
    }
  }

	envRcrdr = theDomain->getRecorder(envRcrdrTag);
  if (envRcrdr == 0) {
    opserr << "ConditionalDriftRecorder::initialize() - could not retrieve base recorder object with tag: " << envRcrdrTag <<"\n";
    return -3;
  }
  //
  // mark as having been done & return
  //

  return 0;
}

#endif // _CSS
