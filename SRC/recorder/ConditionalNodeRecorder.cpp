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

// Written: SAJalali 
//
// Description: This file contains the class definition for ConditionalNodeRecorder.
// A ConditionalNodeRecorder is used to record the envelop of specified dof responses 
// at a collection of nodes over an analysis. (between commitTag of 0 and
// last commitTag).
//
// What: "@(#) ConditionalNodeRecorder.C, revA"

#include <OPS_Globals.h>
#ifdef _CSS


#include <math.h>
#include <stdlib.h>

#include <ConditionalNodeRecorder.h>
#include <Domain.h>
#include <Node.h>
#include <NodeIter.h>
#include <Vector.h>
#include <ID.h>
#include <Matrix.h>
#include <FE_Datastore.h>
#include <FEM_ObjectBroker.h>
#include <TimeSeries.h>

#include <string.h>

ConditionalNodeRecorder::ConditionalNodeRecorder()
:Recorder(RECORDER_TAGS_ConditionalNodeRecorder),
 theDofs(0), theNodalTags(0), theNodes(0),
 data(0), 
 theDomain(0), theHandler(0),
 initializationDone(false), 
 numValidNodes(0), addColumnInfo(0), theTimeSeries(0), timeSeriesValues(0)
{

}

ConditionalNodeRecorder::ConditionalNodeRecorder(const ID &dofs, 
					   const ID *nodes, 
					   const char *dataToStore,
					   Domain &theDom,
					   OPS_Stream &theOutputHandler,
						int rcrdrTag,
						int procMethod,
					   bool echoTime,
					   TimeSeries **theSeries)
:Recorder(RECORDER_TAGS_ConditionalNodeRecorder),
 theDofs(0), theNodalTags(0), theNodes(0),
 data(0), 
 theDomain(&theDom), theHandler(&theOutputHandler),
 initializationDone(false), numValidNodes(0), echoTimeFlag(echoTime), 
 addColumnInfo(0), theTimeSeries(theSeries), timeSeriesValues(0)
    , procDataMethod(procMethod), envRcrdrTag(rcrdrTag)
{
  // verify dof are valid 
#ifndef _CSS
    int numDOF = dofs.Size();
#else
    numDOF = dofs.Size();
#endif // !_CSS
    theDofs = new ID(0, numDOF);

  int count = 0;
  int i;
  for (i=0; i<numDOF; i++) {
    int dof = dofs(i);
    if (dof >= 0) {
      (*theDofs)[count] = dof;
      count++;
    } else {
      opserr << "ConditionalNodeRecorder::ConditionalNodeRecorder - invalid dof  " << dof;
      opserr << " will be ignored\n";
    }
  }


  // 
  // create memory to hold nodal ID's (neeed parallel)
  //

  if (nodes != 0) {
    int numNode = nodes->Size();
    if (numNode != 0) {
      theNodalTags = new ID(*nodes);
      if (theNodalTags == 0 || theNodalTags->Size() != nodes->Size()) {
	opserr << "ConditionalNodeRecorder::ConditionalNodeRecorder - out of memory\n";
      }
    }
  } 

#ifndef _CSS
  if (theTimeSeries != 0) {
    timeSeriesValues = new double [numDOF];
    for (int i=0; i<numDOF; i++)
      timeSeriesValues[i] = 0.0;
  }
#endif // !_CSS

  //
  // set the data flag used as a switch to get the response in a record
  //

  if (dataToStore == 0 || (strcmp(dataToStore, "disp") == 0)) {
    dataFlag = 0;
  } else if ((strcmp(dataToStore, "vel") == 0)) {
    dataFlag = 1;
  } else if ((strcmp(dataToStore, "accel") == 0)) {
    dataFlag = 2;
  } else if ((strcmp(dataToStore, "incrDisp") == 0)) {
    dataFlag = 3;
  } else if ((strcmp(dataToStore, "incrDeltaDisp") == 0)) {
    dataFlag = 4;
  } else if ((strcmp(dataToStore, "unbalance") == 0)) {
    dataFlag = 5;
  } else if ((strcmp(dataToStore, "unbalanceInclInertia") == 0) ||
	     (strcmp(dataToStore, "unbalanceIncInertia") == 0) ||
	     (strcmp(dataToStore, "unbalanceIncludingInertia") == 0))  {
    dataFlag = 6;
  } else if ((strcmp(dataToStore, "reaction") == 0)) {
    dataFlag = 7;
  } else if (((strcmp(dataToStore, "reactionIncInertia") == 0))
	     || ((strcmp(dataToStore, "reactionInclInertia") == 0))
	     || ((strcmp(dataToStore, "reactionIncludingInertia") == 0))) {
    dataFlag = 8;
  } else if (((strcmp(dataToStore, "rayleighForces") == 0))
	     || ((strcmp(dataToStore, "rayleighDampingForces") == 0))) {
    dataFlag = 9;

  } else if ((strcmp(dataToStore, "dispNorm") == 0)) {
    dataFlag = 10000;

  } else if ((strncmp(dataToStore, "eigen",5) == 0)) {
    int mode = atoi(&(dataToStore[5]));
    if (mode > 0)
      dataFlag = 10 + mode;
    else
      dataFlag = 10;
  } else if ((strncmp(dataToStore, "sensitivity",11) == 0)) {
    int grad = atoi(&(dataToStore[11]));
    if (grad > 0)
      dataFlag = 1000 + grad;
    else
      dataFlag = 10;
  } else if ((strncmp(dataToStore, "velSensitivity",14) == 0)) {
    int grad = atoi(&(dataToStore[14]));
    if (grad > 0)
      dataFlag = 2000 + grad;
    else
      dataFlag = 10;
  } else if ((strncmp(dataToStore, "accSensitivity",14) == 0)) {
    int grad = atoi(&(dataToStore[14]));
    if (grad > 0)
      dataFlag = 3000 + grad;
    else
      dataFlag = 10;
  }
#ifdef _CSS
  else if ((strcmp(dataToStore, "motionEnergy") == 0) || (strcmp(dataToStore, "MotionEnergy") == 0)) {
      dataFlag = 999997;
      numDOF = 1;
  }
  else if ((strcmp(dataToStore, "kineticEnergy") == 0) || (strcmp(dataToStore, "KineticEnergy") == 0)) {
      dataFlag = 999998;
      numDOF = 1;
  }
  else if ((strcmp(dataToStore, "dampingEnergy") == 0) || (strcmp(dataToStore, "DampingEnergy") == 0)) {
      dataFlag = 999999;
      numDOF = 1;
#endif _CSS

  } else {
    dataFlag = 10;
    opserr << "ConditionalNodeRecorder::ConditionalNodeRecorder - dataToStore " << dataToStore;
    opserr << "not recognized (disp, vel, accel, incrDisp, incrDeltaDisp)\n";
  }
#ifdef _CSS
  if (theTimeSeries != 0) {
      timeSeriesValues = new double[numDOF];
      for (int i = 0; i < numDOF; i++)
          timeSeriesValues[i] = 0.0;
  }
#endif // !_CSS
}


ConditionalNodeRecorder::~ConditionalNodeRecorder()
{
  //
  // write the data
  //

  if (theHandler != 0 && data != 0) {
    
    theHandler->tag("Data"); // Data
    
    int numResponse = data->noCols();
    Vector currentData(numResponse);
      for (int j=0; j<numResponse; j++)
	currentData(j) = (*data)(0,j);
      theHandler->write(currentData);
    
      
    theHandler->endTag(); // Data
  }

  //
  // clean up the memory
  //

#ifdef _CSS
  if (theDofs != 0) {
      delete theDofs;
  }
#else
  int numDOF;
  if (theDofs != 0) {
      numDOF = theDofs->Size();
      delete theDofs;
  }
#endif // _CSS

  if (theNodalTags != 0)
    delete theNodalTags;

  if (theHandler != 0)
    delete theHandler;

  if (data != 0)
    delete data;

  if (theNodes != 0)
    delete [] theNodes;

  if (theTimeSeries != 0) {
    for (int i=0; i<numDOF; i++)
      delete theTimeSeries[i];
    delete [] theTimeSeries;
  }
}

int 
ConditionalNodeRecorder::record(int commitTag, double timeStamp)
{
#ifdef _CSS
    if (theDomain == 0) {
        return 0;
    }
#else
    if (theDomain == 0 || theDofs == 0) {
        return 0;
    }
#endif // _CSS


  if (theHandler == 0) {
    opserr << "ConditionalNodeRecorder::record() - no DataOutputHandler has been set\n";
    return -1;
  }

  // 
  // check that initialization has been done
  //

  if (initializationDone == false) {
    if (this->initialize() != 0) {
      opserr << "ElementRecorder::record() - failed to initialize\n";
      return -1;
    }
  }

  if (envRcrdr->getModified() == 0)
	return 0;

  int iCnt = 0;
  if (echoTimeFlag)
  {
	  iCnt = 1;
	  (*data)(0,0) = timeStamp;
  }
  if (initializationDone != true) 
    if (this->initialize() != 0) {
      opserr << "ConditionalNodeRecorder::record() - failed in initialize()\n";
      return -1;
    }


#ifndef _CSS
  int numDOF = theDofs->Size();
#endif // !_CSS

double timeSeriesTerm = 0.0;

if (theTimeSeries != 0) {
    for (int i=0; i<numDOF; i++) {
if (theTimeSeries[i] != 0) 
	timeSeriesValues[i] = theTimeSeries[i]->getFactor(timeStamp);
    }
}

//
// if need nodal reactions get the domain to calculate them
// before we iterate over the nodes
//

if (dataFlag == 7)
    theDomain->calculateNodalReactions(0);
else if (dataFlag == 8)
    theDomain->calculateNodalReactions(1);
if (dataFlag == 9)
    theDomain->calculateNodalReactions(2);

#ifdef _CSS
if (procDataMethod != 0)
{
    double val = 0, val1 = 0;
    for (int j = 0; j < numDOF; j++) {
        int dof = (*theDofs)(j);
        int cnt = j + iCnt;
        for (int i = 0; i < numValidNodes; i++) {
            Node* theNode = theNodes[i];
            if (dataFlag == 7 || dataFlag == 8 || dataFlag == 9) {
                const Vector& theResponse = theNode->getReaction();
                if (theResponse.Size() > dof) {
                    val1 = theResponse(dof);
                }
                else
                    val1 = 0.0;
            }
            else if (dataFlag == 999997) {
                if (theTimeSeries == 0)
                {
                    opserr << "WARNING! NodeRecorder::motionEnergy: the timeSeries tag is missing. Please use the -TimeSeries option\n";
                }
                val1 = theNode->getMotionEnergy(theTimeSeries);
            }
            else if (dataFlag == 999998)
                val1 = theNode->getKineticEnergy(theTimeSeries);
            else if (dataFlag == 999999)
                val1 = theNode->getDampEnergy();

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
        (*data)(0, cnt) = val;
    }
}
else
#endif //_CSS

for (int i=0; i<numValidNodes; i++) {
    int cnt = i*numDOF + iCnt;

    if (dataFlag == 10000)
		cnt = i+ iCnt;

    Node *theNode = theNodes[i];
    if (dataFlag == 0) {
		const Vector &response = theNode->getTrialDisp();
		for (int j=0; j<numDOF; j++) {
			int dof = (*theDofs)(j);

			if (theTimeSeries != 0) {
				timeSeriesTerm = timeSeriesValues[j];
			}

			if (response.Size() > dof) {
				(*data)(0,cnt) = response(dof) + timeSeriesTerm;
			} else 
				(*data)(0,cnt) = 0.0 + timeSeriesTerm;
	  
			cnt++;
		}

    } else if (dataFlag == 10000) {
		const Vector &response = theNode->getTrialDisp();
		double sum = 0.0;
		for (int j=0; j<numDOF; j++) {
			int dof = (*theDofs)(j);

			if (theTimeSeries != 0) {
			timeSeriesTerm = timeSeriesValues[j];
			}

			if (response.Size() > dof) {
			sum += (response(dof) + timeSeriesTerm) * (response(dof) + timeSeriesTerm);    
			} else 
			sum += timeSeriesTerm * timeSeriesTerm;    
		}

		(*data)(0,cnt) = sqrt(sum);
		cnt++;

    } else if (dataFlag == 1) {
		const Vector &response = theNode->getTrialVel();
		for (int j=0; j<numDOF; j++) {

		if (theTimeSeries != 0) {
		timeSeriesTerm = timeSeriesValues[j];
		}

		int dof = (*theDofs)(j);
		if (response.Size() > dof) {
		(*data)(0,cnt) = response(dof) + timeSeriesTerm;
		} else 
		(*data)(0,cnt) = 0.0 + timeSeriesTerm;
	  
		cnt++;
	}
    } else if (dataFlag == 2) {
		const Vector &response = theNode->getTrialAccel();
		for (int j=0; j<numDOF; j++) {

			if (theTimeSeries != 0) {
			timeSeriesTerm = timeSeriesValues[j];
			}

			int dof = (*theDofs)(j);
			if (response.Size() > dof) {
			(*data)(0,cnt) = response(dof) + timeSeriesTerm;
			} else 
			(*data)(0,cnt) = 0.0 + timeSeriesTerm;
	  
			cnt++;
		}
    } else if (dataFlag == 3) {
		const Vector &response = theNode->getIncrDisp();
		for (int j=0; j<numDOF; j++) {
			int dof = (*theDofs)(j);
			if (response.Size() > dof) {
			(*data)(0,cnt) = response(dof);
			} else 
			(*data)(0,cnt) = 0.0;
	  
			cnt++;
		}
    } else if (dataFlag == 4) {
		const Vector &response = theNode->getIncrDeltaDisp();
		for (int j=0; j<numDOF; j++) {
			int dof = (*theDofs)(j);
			if (response.Size() > dof) {
			(*data)(0,cnt) = response(dof);
			} else 
			(*data)(0,cnt) = 0.0;
	  
			cnt++;
		}
    } else if (dataFlag == 5) {
		const Vector &theResponse = theNode->getUnbalancedLoad();
		for (int j=0; j<numDOF; j++) {
			int dof = (*theDofs)(j);
			if (theResponse.Size() > dof) {
			(*data)(0,cnt) = theResponse(dof);
			} else 
			(*data)(0,cnt) = 0.0;
	  
			cnt++;
		}

    } else if (dataFlag == 6) {
		const Vector &theResponse = theNode->getUnbalancedLoadIncInertia();
		for (int j=0; j<numDOF; j++) {
			int dof = (*theDofs)(j);
			if (theResponse.Size() > dof) {
			(*data)(0,cnt) = theResponse(dof);
			} else 
			(*data)(0,cnt) = 0.0;
	  
			cnt++;
		}

    } else if (dataFlag == 7 || dataFlag == 8 || dataFlag == 9) {
		const Vector &theResponse = theNode->getReaction();
		for (int j=0; j<numDOF; j++) {
			int dof = (*theDofs)(j);
			if (theResponse.Size() > dof) {
			(*data)(0,cnt) = theResponse(dof);
			} else 
			(*data)(0,cnt) = 0.0;
	  
			cnt++;
		}
#ifdef _CSS
    } else if (dataFlag == 999997) {
    if (theTimeSeries == 0)
    {
        opserr << "WARNING! ConditionalNodeRecorder::motionEnergy: the timeSeries tag is missing. Please use the -TimeSeries option\n";
    }
    (*data)(0, cnt++) = theNode->getMotionEnergy(theTimeSeries);
                }
    else if (dataFlag == 999998)
    (*data)(0, cnt++) = theNode->getKineticEnergy(theTimeSeries);
    else if (dataFlag == 999999)
    (*data)(0, cnt++) = theNode->getDampEnergy();
#endif // _CSS
    else if (dataFlag > 10) {
		int mode = dataFlag - 10;
		int column = mode - 1;
		const Matrix &theEigenvectors = theNode->getEigenvectors();
		if (theEigenvectors.noCols() > column) {
			int noRows = theEigenvectors.noRows();
			for (int j=0; j<numDOF; j++) {
				int dof = (*theDofs)(j);
				if (noRows > dof) {
					(*data)(0,cnt) = theEigenvectors(dof,column);
				} else 
					(*data)(0,cnt) = 0.0;
				cnt++;		
			}
		} else {
			for (int j=0; j<numDOF; j++) {
				(*data)(0,cnt) = 0.0;
				cnt++;		
			}
		}
    }
}

return 0;
}


int
ConditionalNodeRecorder::restart(void)
{
  data->Zero();
  return 0;
}


int 
ConditionalNodeRecorder::setDomain(Domain &theDom)
{
  theDomain = &theDom;
  initializationDone = false;  
  return 0;
}


int
ConditionalNodeRecorder::sendSelf(int commitTag, Channel &theChannel)
{
  addColumnInfo = 1;

  int numDOF = theDofs->Size();

  if (theChannel.isDatastore() == 1) {
    opserr << "ConditionalNodeRecorder::sendSelf() - does not send data to a datastore\n";
    return -1;
  }

  initializationDone = false;
  static ID idData(7); 
  idData.Zero();

  if (theDofs != 0)
    idData(0) = numDOF;
  if (theNodalTags != 0)
    idData(1) = theNodalTags->Size();
  if (theHandler != 0) {
    idData(2) = theHandler->getClassTag();
  }

  idData(3) = dataFlag;

  if (echoTimeFlag == true)
    idData(4) = 1;
  else
    idData(4) = 0;

  idData(5) = this->getTag();

  if (theTimeSeries == 0)
    idData[6] = 0;
  else
    idData[6] = 1;

  if (theChannel.sendID(0, commitTag, idData) < 0) {
    opserr << "ConditionalNodeRecorder::sendSelf() - failed to send idData\n";
    return -1;
  }

  if (theDofs != 0) 
    if (theChannel.sendID(0, commitTag, *theDofs) < 0) {
      opserr << "ConditionalNodeRecorder::sendSelf() - failed to send dof id's\n";
      return -1;
    }

  if (theNodalTags != 0)
    if (theChannel.sendID(0, commitTag, *theNodalTags) < 0) {
      opserr << "ConditionalNodeRecorder::sendSelf() - failed to send nodal tags\n";
      return -1;
    }


  if (theHandler->sendSelf(commitTag, theChannel) < 0) {
    opserr << "ConditionalNodeRecorder::sendSelf() - failed to send the DataOutputHandler\n";
    return -1;
  }

  if (theTimeSeries != 0) {
    ID timeSeriesTags(numDOF);
    for (int i=0; i<numDOF; i++) {
      if (theTimeSeries[i] != 0) {
	timeSeriesTags[i] = theTimeSeries[i]->getClassTag();
      } else
	timeSeriesTags[i] = -1;
    }
    if (theChannel.sendID(0, commitTag, timeSeriesTags) < 0) {
      opserr << "ConditionalNodeRecorder::sendSelf() - failed to send time series tags\n";
      return -1;
    }    
    for (int i=0; i<numDOF; i++) {
      if (theTimeSeries[i] != 0) {	
	if (theTimeSeries[i]->sendSelf(commitTag, theChannel) < 0) {
	  opserr << "ConditionalNodeRecorder::sendSelf() - time series failed in send\n";
	  return -1;

	}
      }
    }
  }

  return 0;
}

int 
ConditionalNodeRecorder::recvSelf(int commitTag, Channel &theChannel, 
		 FEM_ObjectBroker &theBroker)
{
  addColumnInfo = 1;

  if (theChannel.isDatastore() == 1) {
    opserr << "ConditionalNodeRecorder::sendSelf() - does not send data to a datastore\n";
    return -1;
  }

  static ID idData(7); 
  if (theChannel.recvID(0, commitTag, idData) < 0) {
    opserr << "ConditionalNodeRecorder::recvSelf() - failed to send idData\n";
    return -1;
  }

  int numDOFs = idData(0);
  int numNodes = idData(1);

  dataFlag = idData(3);

  this->setTag(idData(5));

  if (idData(4) == 1)
    echoTimeFlag = true;
  else
    echoTimeFlag = false;    


  //
  // get the DOF ID data
  //

  if (theDofs == 0 || theDofs->Size() != numDOFs) {
    if (theDofs != 0)
      delete theDofs;

    if (numDOFs != 0) {
      theDofs = new ID(numDOFs);
      if (theDofs == 0 || theDofs->Size() != numDOFs) {
	opserr << "ConditionalNodeRecorder::recvSelf() - out of memory\n";
	return -1;
      }	
    }
  }
  if (theDofs != 0)
    if (theChannel.recvID(0, commitTag, *theDofs) < 0) {
      opserr << "ConditionalNodeRecorder::recvSelf() - failed to recv dof data\n";
      return -1;
    } 

  //
  // get the NODAL tag data
  //

  if (theNodalTags == 0 || theNodalTags->Size() != numNodes) {
    if (theNodalTags != 0)
      delete theNodalTags;

    if (numNodes != 0) {
      theNodalTags = new ID(numNodes);
      if (theNodalTags == 0 || theNodalTags->Size() != numNodes) {
	opserr << "ConditionalNodeRecorder::recvSelf() - out of memory\n";
	return -1;
      }	
    }
  }
  if (theNodalTags != 0)
    if (theChannel.recvID(0, commitTag, *theNodalTags) < 0) {
      opserr << "ConditionalNodeRecorder::recvSelf() - failed to recv dof data\n";
      return -1;
    } 

 
  if (theHandler != 0)
    delete theHandler;

  theHandler = theBroker.getPtrNewStream(idData(2));
  if (theHandler == 0) {
    opserr << "ConditionalNodeRecorder::sendSelf() - failed to get a data output handler\n";
    return -1;
  }

  if (theHandler->recvSelf(commitTag, theChannel, theBroker) < 0) {
    opserr << "ConditionalNodeRecorder::sendSelf() - failed to send the DataOutputHandler\n";
    return -1;
  }


  if (idData[6] == 1) {
    theTimeSeries = new TimeSeries *[numDOFs];
    ID timeSeriesTags(numDOFs);
    if (theChannel.recvID(0, commitTag, timeSeriesTags) < 0) {
      opserr << "ConditionalNodeRecorder::recvSelf() - failed to recv time series tags\n";
      return -1;
    }    
    for (int i=0; i<numDOFs; i++) {
      if (timeSeriesTags[i] == -1)
	theTimeSeries[i] = 0;
      else {
	theTimeSeries[i] = theBroker.getNewTimeSeries(timeSeriesTags(i));
	if (theTimeSeries[i]->recvSelf(commitTag, theChannel, theBroker) < 0) {
	  opserr << "ConditionalNodeRecorder::recvSelf() - time series failed in recv\n";
	  return -1;
	}
      }
    }
  }

  return 0;
}


int
ConditionalNodeRecorder::initialize(void)
{
    if (theDomain == 0) {
        opserr << "ConditionalNodeRecorder::initialize() - either nodes or domain has not been set\n";
        return -1;
    }

  //
  // create & set nodal array pointer
  //

  if (theNodes != 0) 
    delete [] theNodes;
  
  numValidNodes = 0;

  if (theNodalTags != 0) {
    int numNode = theNodalTags->Size();
    theNodes = new Node *[numNode];
    if (theNodes == 0) {
      opserr << "ConditionalNodeRecorder::domainChanged - out of memory\n";
      return -1;
    }

    for (int i=0; i<numNode; i++) {
      int nodeTag = (*theNodalTags)(i);
      Node *theNode = theDomain->getNode(nodeTag);
      if (theNode != 0) {
	theNodes[numValidNodes] = theNode;
	numValidNodes++;
      } 
    }
  } else {

    int numNodes = theDomain->getNumNodes();
    if (numNodes != 0) {
      theNodes = new Node *[numNodes];
      
      if (theNodes == 0) {
	opserr << "ConditionalNodeRecorder::domainChanged - out of memory\n";
	return -1;
      }
      NodeIter &theDomainNodes = theDomain->getNodes();
      Node *theNode;
      numValidNodes = 0;
      while (((theNode = theDomainNodes()) != 0) && (numValidNodes < numNodes)) {
	theNodes[numValidNodes] = theNode;
	numValidNodes++;
      }
    } else
      numValidNodes = 0;
  }

  //
  // need to create the data description, i.e. what each column of data is
  //

  //
  // need to create the data description, i.e. what each column of data is
  //

  char outputData[32];
  char dataType[10];

  if (dataFlag == 0) {
    strcpy(dataType,"D");
  } else if (dataFlag == 1) {
    strcpy(dataType,"V");
  } else if (dataFlag == 2) {
    strcpy(dataType,"A");
  } else if (dataFlag == 3) {
    strcpy(dataType,"dD");
  } else if (dataFlag == 4) {
    strcpy(dataType,"ddD");
  } else if (dataFlag == 5) {
    strcpy(dataType,"U");
  } else if (dataFlag == 6) {
    strcpy(dataType,"U");
  } else if (dataFlag == 7) {
    strcpy(dataType,"R");
  } else if (dataFlag == 8) {
    strcpy(dataType,"R");
  } else if (dataFlag == 10000) {
    strcpy(dataType,"|D|");
  } else if (dataFlag > 10) {
    sprintf(dataType,"E%d", dataFlag-10);
  } else
    strcpy(dataType,"Unknown");


  //
  // resize the output matrix
  //

#ifdef _CSS
  int numValidResponse = numValidNodes * numDOF;
  if (procDataMethod)
      numValidResponse = numDOF;
#else
  int numDOF = theDofs->Size();
  int numValidResponse = numValidNodes*numDOF;
#endif // _CSS

  if (dataFlag == 10000)
    numValidResponse = numValidNodes;  

  if (echoTimeFlag == true) {
    numValidResponse += 1;
  }

 
  data = new Matrix(1, numValidResponse);
  data->Zero();

  ID dataOrder(numValidResponse);
  ID xmlOrder(numValidNodes);

  if (theNodalTags != 0 && addColumnInfo == 1) {

    int count = 0;
    int nodeCount = 0;

    int numNode = theNodalTags->Size();
    for (int i=0; i<numNode; i++) {
      int nodeTag = (*theNodalTags)(i);
      Node *theNode = theDomain->getNode(nodeTag);
      if (theNode != 0) {
	xmlOrder(nodeCount++) = i+1;
	for (int j=0; j<numDOF; j++)
	  dataOrder(count++) = i+1;
	if (echoTimeFlag == true) {
	  for (int j=0; j<numDOF; j++)
	    dataOrder(count++) = i+1;
	}
      }
    }

    theHandler->setOrder(xmlOrder);
  }

  for (int i=0; i<numValidNodes; i++) {
    int nodeTag = theNodes[i]->getTag();

    theHandler->tag("NodeOutput");
    theHandler->attr("nodeTag", nodeTag);

    for (int j=0; j<theDofs->Size(); j++) {
      
      if (echoTimeFlag == true) {
	theHandler->tag("TimeOutput");
	theHandler->tag("ResponseType", "time");
	theHandler->endTag();
      }

      sprintf(outputData, "%s%d", dataType, j+1);
      theHandler->tag("ResponseType",outputData);
    }

    theHandler->endTag();
  }

  if (theNodalTags != 0 && addColumnInfo == 1) {
    theHandler->setOrder(dataOrder);
  }

	envRcrdr = theDomain->getRecorder(envRcrdrTag);
  if (envRcrdr == 0) {
    opserr << "ConditionalNodeRecorder::initialize() - could not retrieve base recorder object with tag: " << envRcrdrTag <<"\n";
    return -3;
  }
  initializationDone = true;

  return 0;
}
#endif // _CSS
