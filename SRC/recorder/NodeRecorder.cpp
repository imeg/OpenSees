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
                                                                        
// Written: fmk 
//
// Description: This file contains the class definition for NodeRecorder.
// A NodeRecorder is used to record the specified dof responses 
// at a collection of nodes over an analysis. (between commitTag of 0 and
// last commitTag).
//
// What: "@(#) NodeRecorder.C, revA"

#include <NodeRecorder.h>
#include <Domain.h>
#include <Parameter.h>
#include <Node.h>
#include <NodeIter.h>
#include <Vector.h>
#include <ID.h>
#include <Matrix.h>
#include <FE_Datastore.h>
#include <FEM_ObjectBroker.h>
#include <Pressure_Constraint.h>
#include <MeshRegion.h>
#include <TimeSeries.h>

#include <StandardStream.h>
#include <DataFileStream.h>
#include <DataFileStreamAdd.h>
#include <XmlFileStream.h>
#include <BinaryFileStream.h>
#include <DatabaseStream.h>
#include <TCP_Stream.h>

#include <elementAPI.h>

#include <string.h>
#include <stdlib.h>
#include <math.h>

void*
OPS_NodeRecorder()
{
    if (OPS_GetNumRemainingInputArgs() < 5) {
        opserr << "WARING: recorder Node ";
        opserr << "-node <list nodes> -dof <doflist> -file <fileName> -dT <dT> reponse";
        return 0;
    }
    
    const char* responseID = 0;
    OPS_Stream *theOutputStream = 0;
    const char* filename = 0;
    
    const int STANDARD_STREAM = 0;
    const int DATA_STREAM = 1;
    const int XML_STREAM = 2;
    const int DATABASE_STREAM = 3;
    const int BINARY_STREAM = 4;
    const int DATA_STREAM_CSV = 5;
    const int TCP_STREAM = 6;
    const int DATA_STREAM_ADD = 7;
    
    int eMode = STANDARD_STREAM;
#ifdef _CSS
    int procDataMethod = 0;
#endif // _CSS

    bool echoTimeFlag = false;
    double dT = 0.0;
    bool doScientific = false;
    
    int precision = 6;
    
    bool closeOnWrite = false;
    
    const char *inetAddr = 0;
    int inetPort;
    
    int gradIndex = -1;
    
    TimeSeries **theTimeSeries = 0;
    
    ID nodes(0, 6);
    ID dofs(0, 6);
    ID timeseries(0, 6);
    
    while (OPS_GetNumRemainingInputArgs() > 0) {
        
        const char* option = OPS_GetString();
        responseID = option;
        
        if (strcmp(option, "-time") == 0) {
            echoTimeFlag = true;
        }
        else if (strcmp(option, "-load") == 0) {
            echoTimeFlag = true;
        }
        else if (strcmp(option, "-scientific") == 0) {
            doScientific = true;
        }
        else if (strcmp(option, "-file") == 0) {
            if (OPS_GetNumRemainingInputArgs() > 0) {
                filename = OPS_GetString();
            }
            eMode = DATA_STREAM;
        }
        else if (strcmp(option, "-fileAdd") == 0) {
            if (OPS_GetNumRemainingInputArgs() > 0) {
                filename = OPS_GetString();
            }
            eMode = DATA_STREAM_ADD;
        }
        else if (strcmp(option, "-closeOnWrite") == 0) {
            closeOnWrite = true;
        }
        else if (strcmp(option, "-csv") == 0) {
            if (OPS_GetNumRemainingInputArgs() > 0) {
                filename = OPS_GetString();
            }
            eMode = DATA_STREAM_CSV;
        }
        else if (strcmp(option, "-tcp") == 0) {
            if (OPS_GetNumRemainingInputArgs() > 0) {
                inetAddr = OPS_GetString();
            }
            if (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                if (OPS_GetIntInput(&num, &inetPort) < 0) {
                    opserr << "WARNING: failed to read inetPort\n";
                    return 0;
                }
            }
            eMode = TCP_STREAM;
        }
        else if (strcmp(option, "-xml") == 0) {
            if (OPS_GetNumRemainingInputArgs() > 0) {
                filename = OPS_GetString();
            }
            eMode = XML_STREAM;
        }
        else if (strcmp(option, "-binary") == 0) {
            if (OPS_GetNumRemainingInputArgs() > 0) {
                filename = OPS_GetString();
            }
            eMode = BINARY_STREAM;
        }
        else if (strcmp(option, "-dT") == 0) {
            if (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                if (OPS_GetDoubleInput(&num, &dT) < 0) {
                    opserr << "WARNING: failed to read dT\n";
                    return 0;
                }
            }
        }
        else if (strcmp(option, "-timeSeries") == 0) {
            int numTimeSeries = 0;
            while (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                int ts;
                if (OPS_GetIntInput(&num, &ts) < 0) {
                    OPS_ResetCurrentInputArg(-1);
                    break;
                }
                timeseries[numTimeSeries++] = ts;
            }
            theTimeSeries = new TimeSeries *[numTimeSeries];
            for (int j = 0; j<numTimeSeries; j++) {
                if (timeseries(j) != 0 && timeseries(j) != -1)
                    theTimeSeries[j] = OPS_getTimeSeries(timeseries(j));
                else
                    theTimeSeries[j] = 0;
            }
        }
        else if (strcmp(option, "-precision") == 0) {
            if (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                if (OPS_GetIntInput(&num, &precision) < 0) {
                    opserr << "WARNING: failed to read precision\n";
                    return 0;
                }
            }
        }
        else if (strcmp(option, "-node") == 0) {
            int numNodes = 0;
            while (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                int nd;
                if (OPS_GetIntInput(&num, &nd) < 0) {
                    OPS_ResetCurrentInputArg(-1);
                    break;
                }
                nodes[numNodes++] = nd;
            }
        }
        else if (strcmp(option, "-nodeRange") == 0) {
            int start, end;
            if (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                if (OPS_GetIntInput(&num, &start) < 0) {
                    opserr << "WARNING: failed to read start node\n";
                    return 0;
                }
            }
            if (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                if (OPS_GetIntInput(&num, &end) < 0) {
                    opserr << "WARNING: failed to read end node\n";
                    return 0;
                }
            }
            if (start > end) {
                int swap = end;
                end = start;
                start = swap;
            }
            int numNodes = 0;
            for (int i = start; i <= end; i++)
                nodes[numNodes++] = i;
        }
        else if (strcmp(option, "-region") == 0) {
            int tag;
            if (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                if (OPS_GetIntInput(&num, &tag) < 0) {
                    opserr << "WARNING: failed to read region tag\n";
                    return 0;
                }
            }
            Domain *domain = OPS_GetDomain();
            MeshRegion *theRegion = domain->getRegion(tag);
            if (theRegion == 0) {
                opserr << "WARNING: region does not exist\n";
                return 0;
            }
            const ID &nodeRegion = theRegion->getNodes();
            int numNodes = 0;
            for (int i = 0; i < nodeRegion.Size(); i++)
                nodes[numNodes++] = nodeRegion(i);
        }
        else if (strcmp(option, "-dof") == 0) {
            int numDOF = 0;
            while (OPS_GetNumRemainingInputArgs() > 0) {
                int num = 1;
                int dof;
                if (OPS_GetIntInput(&num, &dof) < 0) {
                    OPS_ResetCurrentInputArg(-1);
                    break;
                }
                dofs[numDOF++] = dof - 1;
            }
        }
#ifdef _CSS
        else if (strcmp(option, "-process") == 0) {
        const char* procType = OPS_GetString();
        if (strcmp(procType, "sum") == 0)
            procDataMethod = 1;
        else if (strcmp(procType, "max") == 0)
            procDataMethod = 2;
        else if (strcmp(procType, "min") == 0)
            procDataMethod = 3;
        else
            opserr << "unrecognized element result process method: " << procType << endln;
        }
#endif // _CSS
    }
    
    // data handler
    if (eMode == DATA_STREAM && filename != 0)
        theOutputStream = new DataFileStream(filename, OVERWRITE, 2, 0, closeOnWrite, precision, doScientific);
    else if (eMode == DATA_STREAM_ADD && filename != 0)
        theOutputStream = new DataFileStreamAdd(filename, OVERWRITE, 2, 0, closeOnWrite, precision, doScientific);
    else if (eMode == DATA_STREAM_CSV && filename != 0)
        theOutputStream = new DataFileStream(filename, OVERWRITE, 2, 1, closeOnWrite, precision, doScientific);
    else if (eMode == XML_STREAM && filename != 0)
        theOutputStream = new XmlFileStream(filename);
    //else if (eMode == DATABASE_STREAM && tableName != 0)
    //    theOutputStream = new DatabaseStream(theDatabase, tableName);
    else if (eMode == BINARY_STREAM && filename != 0)
        theOutputStream = new BinaryFileStream(filename);
    else if (eMode == TCP_STREAM && inetAddr != 0)
        theOutputStream = new TCP_Stream(inetPort, inetAddr);
    else
        theOutputStream = new StandardStream();
    
    theOutputStream->setPrecision(precision);
    
    Domain* domain = OPS_GetDomain();
    if (domain == 0)
        return 0;
    NodeRecorder* recorder = new NodeRecorder(dofs, &nodes, gradIndex,
        responseID, *domain, *theOutputStream,
#ifdef _CSS
        procDataMethod,
#endif // _CSS
        dT, echoTimeFlag, theTimeSeries);
    
    return recorder;
}


NodeRecorder::NodeRecorder()
:Recorder(RECORDER_TAGS_NodeRecorder),
 theDofs(0), theNodalTags(0), theNodes(0), response(0), 
 theDomain(0), theOutputHandler(0),
 echoTimeFlag(true), dataFlag(0), 
 deltaT(0), nextTimeStampToRecord(0.0), 
 gradIndex(-1),
 initializationDone(false), numValidNodes(0), addColumnInfo(0), theTimeSeries(0), timeSeriesValues(0)
{

}


NodeRecorder::NodeRecorder(const ID &dofs, 
			   const ID *nodes, 
			   int pgradIndex,
			   const char *dataToStore,
			   Domain &theDom,
			   OPS_Stream &theOutput,
#ifdef _CSS
            int procMethod,
#endif // _CSS
    double dT,
			   bool timeFlag,
			   TimeSeries **theSeries)
:Recorder(RECORDER_TAGS_NodeRecorder),
 theDofs(0), theNodalTags(0), theNodes(0), response(0), 
 theDomain(&theDom), theOutputHandler(&theOutput),
 echoTimeFlag(timeFlag), dataFlag(0), 
 deltaT(dT), nextTimeStampToRecord(0.0), 
 initializationDone(false), numValidNodes(0), addColumnInfo(0), 
	gradIndex(pgradIndex),
	theTimeSeries(theSeries), timeSeriesValues(0)
#ifdef _CSS
	, procDataMethod(procMethod)
#endif // _CSS

{
  //
  // store copy of dof's to be recorder, verifying dof are valid, i.e. >= 0
  //

#ifndef _CSS
    int numDOF = dofs.Size();
#else
  numDOF = dofs.Size();
#endif // !_CSS

  if (numDOF != 0) {

      theDofs = new ID(numDOF);

      int count = 0;
      int i;
      for (i = 0; i < numDOF; i++) {
          int dof = dofs(i);
          if (dof >= 0) {
              (*theDofs)[count] = dof;
              count++;
          }
          else {
              opserr << "NodeRecorder::NodeRecorder - invalid dof  " << dof;
              opserr << " will be ignored\n";
          }
      }
  }

  // 
  // create memory to hold nodal ID's
  //

  if (nodes != 0) {
    int numNode = nodes->Size();
    if (numNode != 0) {
      theNodalTags = new ID(*nodes);
      if (theNodalTags == 0 || theNodalTags->Size() != nodes->Size()) {
	opserr << "NodeRecorder::NodeRecorder - out of memory\n";
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

  } else if (((strcmp(dataToStore, "nodalRayleighForces") == 0))) {
    dataFlag = 10001;

  } else if (((strcmp(dataToStore, "pressure") == 0))) {
    dataFlag = 10002;

  } else if ((strcmp(dataToStore, "dispNorm") == 0)) {
    dataFlag = 10000;

  } else if ((strncmp(dataToStore, "eigen",5) == 0)) {
    int mode = atoi(&(dataToStore[5]));
    if (mode > 0)
      dataFlag = 10 + mode;
    else
      dataFlag = 10;
  } else if ((strncmp(dataToStore, "sensitivity",11) == 0)) {
	  int paramTag = atoi(&(dataToStore[11]));
	  Parameter* theParameter = theDomain->getParameter(paramTag);
	  int grad = -1;
	  if (theParameter != 0)
		  grad = theParameter->getGradIndex();

	  if (grad > 0)
		  dataFlag = 1000 + grad;
	  else
		  dataFlag = 10;
  } else if ((strncmp(dataToStore, "velSensitivity",14) == 0)) {
	  int paramTag = atoi(&(dataToStore[14]));
	  Parameter* theParameter = theDomain->getParameter(paramTag);
	  int grad = -1;
	  if (theParameter != 0)
		  grad = theParameter->getGradIndex();

	  if (grad > 0)
		  dataFlag = 2000 + grad;
	  else
		  dataFlag = 10;
  }
  else if ((strncmp(dataToStore, "accSensitivity", 14) == 0)) {
	  int paramTag = atoi(&(dataToStore[14]));
	  Parameter* theParameter = theDomain->getParameter(paramTag);
	  int grad = -1;
	  if (theParameter != 0)
		  grad = theParameter->getGradIndex();

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
  }
#endif _CSS
  else {
    dataFlag = 10;
    opserr << "NodeRecorder::NodeRecorder - dataToStore " << dataToStore;
    opserr << "not recognized (disp, vel, accel, incrDisp, incrDeltaDisp)\n";
  }

  if (dataFlag == 7 || dataFlag == 8 || dataFlag == 9) {
    if (timeFlag == true)
      theOutputHandler->setAddCommon(2);
    else
      theOutputHandler->setAddCommon(1);
  }

#ifdef _CSS
  if (theTimeSeries != 0) {
      timeSeriesValues = new double[numDOF];
      for (int i = 0; i < numDOF; i++)
          timeSeriesValues[i] = 0.0;
  }
#endif // !_CSS

}


NodeRecorder::~NodeRecorder()
{
  if (theOutputHandler != 0) {
    theOutputHandler->endTag(); // Data
    delete theOutputHandler;
  }

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
  
  if (timeSeriesValues != 0) 
    delete [] timeSeriesValues;

  if (theNodalTags != 0)
    delete theNodalTags;

  if (theNodes != 0)
    delete [] theNodes;

  if (theTimeSeries != 0) {
    for (int i=0; i<numDOF; i++)
      delete theTimeSeries[i];
    delete [] theTimeSeries;
  }
}


int 
NodeRecorder::record(int commitTag, double timeStamp)
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

    if (theOutputHandler == 0) {
        opserr << "NodeRecorder::record() - no DataOutputHandler has been set\n";
        return -1;
    }

    if (initializationDone == false) {
        if (this->initialize() != 0) {
            opserr << "NodeRecorder::record() - failed in initialize()\n";
            return -1;
        }
    }

#ifndef _CSS
    int numDOF = theDofs->Size();
#endif // !_CSS

    if (deltaT == 0.0 || timeStamp >= nextTimeStampToRecord) {

        if (deltaT != 0.0)
            nextTimeStampToRecord = timeStamp + deltaT;

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

        //
        // add time information if requested
        //

        int timeOffset = 0;
        if (echoTimeFlag == true) {
            timeOffset = 1;
            response(0) = timeStamp;
        }

        double timeSeriesTerm = 0.0;

        if (theTimeSeries != 0) {
            for (int i = 0; i < numDOF; i++) {

                if (theTimeSeries[i] != 0)
                    timeSeriesValues[i] = theTimeSeries[i]->getFactor(timeStamp);
            }

        }

        //
        // now we go get the responses from the nodes & place them in disp vector
        //

        if (dataFlag != 10) {
#ifdef _CSS
            if (procDataMethod != 0)
            {
                double val = 0, val1 = 0;
                for (int j = 0; j < numDOF; j++) {
                    int dof = 0;
                    if (theDofs != 0)
                        dof = (*theDofs)(j);
                    int cnt = j + timeOffset;
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
                            val1 = theNode->getKineticEnergy();
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
                    response(cnt) = val;
                }
            }
            else
#endif //_CSS
            for (int i = 0; i < numValidNodes; i++) {

                int cnt = i * numDOF + timeOffset;
                if (dataFlag == 10000 || dataFlag == 10002)
                    cnt = i + timeOffset;

                Node* theNode = theNodes[i];
                if (dataFlag == 0) {

                    // AddingSensitivity:BEGIN ///////////////////////////////////
                    if (gradIndex < 0) {
                        const Vector& theResponse = theNode->getTrialDisp();
                        for (int j = 0; j < numDOF; j++) {

                            if (theTimeSeries != 0) {
                                timeSeriesTerm = timeSeriesValues[j];
                            }

                            int dof = (*theDofs)(j);
                            if (theResponse.Size() > dof) {
                                response(cnt) = theResponse(dof) + timeSeriesTerm;
                            }
                            else {
                                response(cnt) = 0.0 + timeSeriesTerm;
                            }
                            cnt++;
                        }
                    }
                    else {
                        for (int j = 0; j < numDOF; j++) {
                            int dof = (*theDofs)(j);

                            response(cnt) = theNode->getDispSensitivity(dof + 1, gradIndex);
                            cnt++;
                        }
                    }

                    // AddingSensitivity:END /////////////////////////////////////
                }
                else if (dataFlag == 1) {

                    const Vector& theResponse = theNode->getTrialVel();
                    for (int j = 0; j < numDOF; j++) {

                        if (theTimeSeries != 0) {
                            timeSeriesTerm = timeSeriesValues[j];
                        }

                        int dof = (*theDofs)(j);
                        if (theResponse.Size() > dof) {
                            response(cnt) = theResponse(dof) + timeSeriesTerm;
                        }
                        else
                            response(cnt) = 0.0 + timeSeriesTerm;

                        cnt++;
                    }


                }
                else if (dataFlag == 10000) {
                    const Vector& theResponse = theNode->getTrialDisp();
                    double sum = 0.0;

                    for (int j = 0; j < numDOF; j++) {

                        if (theTimeSeries != 0) {
                            timeSeriesTerm = timeSeriesValues[j];
                        }

                        int dof = (*theDofs)(j);
                        if (theResponse.Size() > dof) {
                            sum += (theResponse(dof) + timeSeriesTerm) * (theResponse(dof) + timeSeriesTerm);
                        }
                        else
                            sum += timeSeriesTerm * timeSeriesTerm;
                    }

                    response(cnt) = sqrt(sum);
                    cnt++;

                }
                else if (dataFlag == 10002) {

                    if (theTimeSeries != 0) {
                        timeSeriesTerm = timeSeriesValues[0];
                    }

                    // get node pressure
                    double pressure = timeSeriesTerm;
                    Pressure_Constraint* pc = theDomain->getPressure_Constraint(theNode->getTag());
                    if (pc != 0) {
                        pressure += pc->getPressure();
                    }

                    response(cnt) = pressure;
                    cnt++;

                }
                else if (dataFlag == 2) {

                    const Vector& theResponse = theNode->getTrialAccel();
                    for (int j = 0; j < numDOF; j++) {

                        if (theTimeSeries != 0) {
                            timeSeriesTerm = timeSeriesValues[j];
                        }

                        int dof = (*theDofs)(j);
                        if (theResponse.Size() > dof) {
                            response(cnt) = theResponse(dof) + timeSeriesTerm;
                        }
                        else
                            response(cnt) = 0.0 + timeSeriesTerm;

                        cnt++;
                    }

                }
                else if (dataFlag == 3) {
                    const Vector& theResponse = theNode->getIncrDisp();
                    for (int j = 0; j < numDOF; j++) {

                        if (theTimeSeries != 0) {
                            timeSeriesTerm = timeSeriesValues[j];
                        }

                        int dof = (*theDofs)(j);
                        if (theResponse.Size() > dof) {
                            response(cnt) = theResponse(dof);
                        }
                        else
                            response(cnt) = 0.0;

                        cnt++;
                    }
                }
                else if (dataFlag == 4) {
                    const Vector& theResponse = theNode->getIncrDeltaDisp();
                    for (int j = 0; j < numDOF; j++) {
                        int dof = (*theDofs)(j);
                        if (theResponse.Size() > dof) {
                            response(cnt) = theResponse(dof);
                        }
                        else
                            response(cnt) = 0.0;

                        cnt++;
                    }
                }
                else if (dataFlag == 5) {
                    const Vector& theResponse = theNode->getUnbalancedLoad();
                    for (int j = 0; j < numDOF; j++) {
                        int dof = (*theDofs)(j);
                        if (theResponse.Size() > dof) {
                            response(cnt) = theResponse(dof);
                        }
                        else
                            response(cnt) = 0.0;

                        cnt++;
                    }

                }
                else if (dataFlag == 6) {
                    const Vector& theResponse = theNode->getUnbalancedLoadIncInertia();
                    for (int j = 0; j < numDOF; j++) {
                        int dof = (*theDofs)(j);
                        if (theResponse.Size() > dof) {
                            response(cnt) = theResponse(dof);
                        }
                        else
                            response(cnt) = 0.0;

                        cnt++;
                    }

                }
                else if (dataFlag == 10001) {
                    const Vector* theResponse = theNode->getResponse(RayleighForces);
                    for (int j = 0; j < numDOF; j++) {
                        int dof = (*theDofs)(j);
                        if (theResponse->Size() > dof) {
                            response(cnt) = (*theResponse)(dof);
                        }
                        else
                            response(cnt) = 0.0;
                        cnt++;
                    }

                }
                else if (dataFlag == 7 || dataFlag == 8 || dataFlag == 9) {
                    const Vector& theResponse = theNode->getReaction();
                    for (int j = 0; j < numDOF; j++) {
                        int dof = (*theDofs)(j);
                        if (theResponse.Size() > dof) {
                            response(cnt) = theResponse(dof);
                        }
                        else
                            response(cnt) = 0.0;
                        cnt++;
                    }

                }
                else if (10 <= dataFlag && dataFlag < 1000) {
                    int mode = dataFlag - 10;
                    int column = mode - 1;

                    const Matrix& theEigenvectors = theNode->getEigenvectors();
                    if (theEigenvectors.noCols() > column) {
                        int noRows = theEigenvectors.noRows();
                        for (int j = 0; j < numDOF; j++) {
                            int dof = (*theDofs)(j);
                            if (noRows > dof) {
                                response(cnt) = theEigenvectors(dof, column);
                            }
                            else
                                response(cnt) = 0.0;
                            cnt++;
                        }
                    }

                }
                else if (dataFlag >= 1000 && dataFlag < 2000) {
                    int grad = dataFlag - 1000;

                    for (int j = 0; j < numDOF; j++) {
                        int dof = (*theDofs)(j);
                        dof += 1; // Terje uses 1 through DOF for the dof indexing; the fool then subtracts 1 
                        // his code!!
                        response(cnt) = theNode->getDispSensitivity(dof, grad - 1);  // Quan May 2009, the one above is not my comment! 
                        cnt++;
                    }

                }
                else if (dataFlag >= 2000 && dataFlag < 3000) {
                    int grad = dataFlag - 2000;

                    for (int j = 0; j < numDOF; j++) {
                        int dof = (*theDofs)(j);
                        dof += 1; // Terje uses 1 through DOF for the dof indexing; the fool then subtracts 1 
                        // his code!!
                        response(cnt) = theNode->getVelSensitivity(dof, grad - 1); // Quan May 2009
                        cnt++;
                    }


                }
#ifdef _CSS
                else if (dataFlag == 999997) {
                    if (theTimeSeries == 0)
                    {
                        opserr << "WARNING! NodeRecorder::motionEnergy: the timeSeries tag is missing. Please use the -TimeSeries option\n";
                    }
                    response(cnt++) = theNode->getMotionEnergy(theTimeSeries);
                }
                else if (dataFlag == 999998)
                    response(cnt++) = theNode->getKineticEnergy();
                else if (dataFlag == 999999)
                    response(cnt++) = theNode->getDampEnergy();
#endif // _CSS

                else if (dataFlag >= 3000) {
                    int grad = dataFlag - 3000;

                    for (int j = 0; j < numDOF; j++) {
                        int dof = (*theDofs)(j);
                        dof += 1; // Terje uses 1 through DOF for the dof indexing; the fool then subtracts 1 
                        // his code!!
                        response(cnt) = theNode->getAccSensitivity(dof, grad - 1);// Quan May 2009
                        cnt++;
                    }
                }

                else {
                    // unknown response
                    for (int j = 0; j < numDOF; j++) {
                        response(cnt) = 0.0;
                    }
                }
            }

            // insert the data into the database
            theOutputHandler->write(response);

        }
        else { // output all eigenvalues

            Node* theNode = theNodes[0];
            const Matrix& theEigenvectors = theNode->getEigenvectors();
            int numValidModes = theEigenvectors.noCols();

            for (int mode = 0; mode < numValidModes; mode++) {

                for (int i = 0; i < numValidNodes; i++) {
                    int cnt = i * numDOF + timeOffset;
                    theNode = theNodes[i];
                    int column = mode;

                    const Matrix& theEigenvectors = theNode->getEigenvectors();
                    if (theEigenvectors.noCols() > column) {
                        int noRows = theEigenvectors.noRows();
                        for (int j = 0; j < numDOF; j++) {
                            int dof = (*theDofs)(j);
                            if (noRows > dof) {
                                response(cnt) = theEigenvectors(dof, column);
                            }
                            else
                                response(cnt) = 0.0;
                            cnt++;
                        }
                    }
                }
                theOutputHandler->write(response);
            }
        }
    }
    return 0;
}


int 
NodeRecorder::setDomain(Domain &theDom)
{
  theDomain = &theDom;
  return 0;
}


int 
NodeRecorder::sendSelf(int commitTag, Channel &theChannel)
{
  addColumnInfo = 1;

  if (theChannel.isDatastore() == 1) {
    opserr << "NodeRecorder::sendSelf() - does not send data to a datastore\n";
    return -1;
  }

  initializationDone = false;

  int numDOF = theDofs->Size();

  static ID idData(8); 
  idData.Zero();
  if (theDofs != 0)
    idData(0) = numDOF;
  if (theNodalTags != 0)
    idData(1) = theNodalTags->Size();
  if (theOutputHandler != 0) {
    idData(2) = theOutputHandler->getClassTag();
  }
  
  if (echoTimeFlag == true)
    idData(3) = 1;
  else
    idData(3) = 0;

  idData(4) = dataFlag;
  idData(5) = gradIndex;

  idData(6) = this->getTag();
  if (theTimeSeries == 0)
    idData[7] = 0;
  else
    idData[7] = 1;


  if (theChannel.sendID(0, commitTag, idData) < 0) {
    opserr << "NodeRecorder::sendSelf() - failed to send idData\n";
    return -1;
  }

  if (theDofs != 0) 
    if (theChannel.sendID(0, commitTag, *theDofs) < 0) {
      opserr << "NodeRecorder::sendSelf() - failed to send dof id's\n";
      return -1;
    }

  if (theNodalTags != 0)
    if (theChannel.sendID(0, commitTag, *theNodalTags) < 0) {
      opserr << "NodeRecorder::sendSelf() - failed to send nodal tags\n";
      return -1;
    }

  static Vector data(2);
  data(0) = deltaT;
  data(1) = nextTimeStampToRecord;
  if (theChannel.sendVector(0, commitTag, data) < 0) {
    opserr << "NodeRecorder::sendSelf() - failed to send data\n";
    return -1;
  }

  if (theOutputHandler->sendSelf(commitTag, theChannel) < 0) {
    opserr << "NodeRecorder::sendSelf() - failed to send the DataOutputHandler\n";
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
      opserr << "EnvelopeNodeRecorder::sendSelf() - failed to send time series tags\n";
      return -1;
    }    
    for (int i=0; i<numDOF; i++) {
      if (theTimeSeries[i] != 0) {	
	if (theTimeSeries[i]->sendSelf(commitTag, theChannel) < 0) {
	  opserr << "EnvelopeNodeRecorder::sendSelf() - time series failed in send\n";
	  return -1;

	}
      }
    }
  }


  return 0;
}


int 
NodeRecorder::recvSelf(int commitTag, Channel &theChannel, 
		       FEM_ObjectBroker &theBroker)
{
  addColumnInfo = 1;

  if (theChannel.isDatastore() == 1) {
    opserr << "NodeRecorder::sendSelf() - does not send data to a datastore\n";
    return -1;
  }

  static ID idData(8); 
  if (theChannel.recvID(0, commitTag, idData) < 0) {
    opserr << "NodeRecorder::recvSelf() - failed to send idData\n";
    return -1;
  }


  int numDOFs = idData(0);
  int numNodes = idData(1);

  this->setTag(idData(6));

  if (idData(3) == 1)
    echoTimeFlag = true;
  else
    echoTimeFlag = false;    

  dataFlag = idData(4);
  gradIndex = idData(5);

  //
  // get the DOF ID data
  //

  if (theDofs == 0 || theDofs->Size() != numDOFs) {
    if (theDofs != 0)
      delete theDofs;

    if (numDOFs != 0) {
      theDofs = new ID(numDOFs);
      if (theDofs == 0 || theDofs->Size() != numDOFs) {
	opserr << "NodeRecorder::recvSelf() - out of memory\n";
	return -1;
      }	
    }
  }
  if (theDofs != 0)
    if (theChannel.recvID(0, commitTag, *theDofs) < 0) {
      opserr << "NodeRecorder::recvSelf() - failed to recv dof data\n";
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
	opserr << "NodeRecorder::recvSelf() - out of memory\n";
	return -1;
      }	
    }
  }
  if (theNodalTags != 0)
    if (theChannel.recvID(0, commitTag, *theNodalTags) < 0) {
      opserr << "NodeRecorder::recvSelf() - failed to recv dof data\n";
      return -1;
    } 


  static Vector data(2);
  if (theChannel.recvVector(0, commitTag, data) < 0) {
    opserr << "NodeRecorder::sendSelf() - failed to receive data\n";
    return -1;
  }
  deltaT = data(0);
  nextTimeStampToRecord = data(1);


  if (theOutputHandler != 0)
    delete theOutputHandler;

  theOutputHandler = theBroker.getPtrNewStream(idData(2));
  if (theOutputHandler == 0) {
    opserr << "NodeRecorder::sendSelf() - failed to get a data output handler\n";
    return -1;
  }

  if (theOutputHandler->recvSelf(commitTag, theChannel, theBroker) < 0) {
    opserr << "NodeRecorder::sendSelf() - failed to send the DataOutputHandler\n";
    return -1;
  }

  if (idData[7] == 1) {

    timeSeriesValues = new double [numDOFs];
    for (int i=0; i<numDOFs; i++)
      timeSeriesValues[i] = 0.0;

    theTimeSeries = new TimeSeries *[numDOFs];
    ID timeSeriesTags(numDOFs);
    if (theChannel.recvID(0, commitTag, timeSeriesTags) < 0) {
      opserr << "EnvelopeNodeRecorder::recvSelf() - failed to recv time series tags\n";
      return -1;
    }    
    for (int i=0; i<numDOFs; i++) {
      if (timeSeriesTags[i] == -1)
	theTimeSeries[i] = 0;
      else {
	theTimeSeries[i] = theBroker.getNewTimeSeries(timeSeriesTags(i));
	if (theTimeSeries[i]->recvSelf(commitTag, theChannel, theBroker) < 0) {
	  opserr << "EnvelopeNodeRecorder::recvSelf() - time series failed in recv\n";
	  return -1;
	} 
	  }
	}
  }
  
  return 0;
}


int
NodeRecorder::domainChanged(void)
{
  return 0;
}


int
NodeRecorder::initialize(void)
{
#ifdef _CSS
    if (theDomain == 0) {
        opserr << "NodeRecorder::initialize() - either nodes or domain has not been set\n";
        return -1;
    }
#else
  if (theDofs == 0 || theDomain == 0) {
    opserr << "NodeRecorder::initialize() - either nodes, dofs or domain has not been set\n";
    return -1;
  }
#endif // _CSS


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
      opserr << "NodeRecorder::domainChanged - out of memory\n";
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
    theNodes = new Node *[numNodes];

    if (theNodes == 0) {
      opserr << "NodeRecorder::domainChanged - out of memory\n";
      return -1;
    }

    NodeIter &theDomainNodes = theDomain->getNodes();
    Node *theNode;
    numValidNodes = 0;
    while (((theNode = theDomainNodes()) != 0) && (numValidNodes < numNodes)) {
      theNodes[numValidNodes] = theNode;
      numValidNodes++;
    }
  }

  //
  // resize the response vector
  //

  int timeOffset = 0;
  if (echoTimeFlag == true)
    timeOffset = 1;
#ifdef _CSS
  int numValidResponse = numValidNodes * numDOF + timeOffset;
  if (procDataMethod)
      numValidResponse = numDOF + timeOffset;
#else
  int numDOF = theDofs->Size();
  int numValidResponse = numValidNodes * numDOF + timeOffset;
#endif // _CSS
  if (dataFlag == 10000 || dataFlag == 10002) {
      numValidResponse = numValidNodes + timeOffset;
  }

  response.resize(numValidResponse);
  response.Zero();

  ID orderResponse(numValidResponse);

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

  /************************************************************
  } else if ((strncmp(dataToStore, "sensitivity",11) == 0)) {
    int grad = atoi(&(dataToStore[11]));
    if (grad > 0)
      dataFlag = 1000 + grad;
    else
      dataFlag = 6;
  } else if ((strncmp(dataToStore, "velSensitivity",14) == 0)) {
    int grad = atoi(&(dataToStore[14]));
    if (grad > 0)
      dataFlag = 2000 + grad;
    else
      dataFlag = 6;
  } else if ((strncmp(dataToStore, "accSensitivity",14) == 0)) {
    int grad = atoi(&(dataToStore[14]));
    if (grad > 0)
      dataFlag = 3000 + grad;
    else
      dataFlag = 6;

  ***********************************************************/
  
  // write out info to handler if parallel execution
  //  

  ID xmlOrder(numValidNodes);

  if (echoTimeFlag == true)  
    xmlOrder.resize(numValidNodes+1);

  if (theNodalTags != 0 && addColumnInfo == 1) {

    int numNode = theNodalTags->Size();
    int count = 0;
    int nodeCount = 0;

    if (echoTimeFlag == true)  {
      orderResponse(count++) = 0;
      xmlOrder(nodeCount++) = 0;
    }
    
    for (int i=0; i<numNode; i++) {
      int nodeTag = (*theNodalTags)(i);
      Node *theNode = theDomain->getNode(nodeTag);
      if (theNode != 0) {
	xmlOrder(nodeCount++) = i+1;
	for (int j=0; j<numDOF; j++)
	  orderResponse(count++) = i+1;
      }
    }

    theOutputHandler->setOrder(xmlOrder);
  }

  char nodeCrdData[20];
  sprintf(nodeCrdData,"coord");

  // fixing TimeOutput for node recorder
#if _DLL
  if (echoTimeFlag == true) {
	  if (theNodalTags != 0) {
		  theOutputHandler->tag("TimeOutput");
		  theOutputHandler->tag("ResponseType", "time");
		  theOutputHandler->endTag();
	  }
  }
#else 
  if (echoTimeFlag == true) {
	  if (theNodalTags != 0 && addColumnInfo == 1) {
		  theOutputHandler->tag("TimeOutput");
		  theOutputHandler->tag("ResponseType", "time");
		  theOutputHandler->endTag();
	  }
  }
#endif

  for (int i=0; i<numValidNodes; i++) {
    int nodeTag = theNodes[i]->getTag();
    const Vector &nodeCrd = theNodes[i]->getCrds();
    int numCoord = nodeCrd.Size();


    theOutputHandler->tag("NodeOutput");
    theOutputHandler->attr("nodeTag", nodeTag);

    for (int j=0; j<3; j++) {
      sprintf(nodeCrdData,"coord%d",j+1);
      if (j < numCoord)
	theOutputHandler->attr(nodeCrdData, nodeCrd(j));      
      else
	theOutputHandler->attr(nodeCrdData, 0.0);      
    }

    for (int k=0; k<numDOF; k++) {
      sprintf(outputData, "%s%d", dataType, k+1);
      theOutputHandler->tag("ResponseType",outputData);
    }

    theOutputHandler->endTag();
  }

  if (theNodalTags != 0 && addColumnInfo == 1) {
    theOutputHandler->setOrder(orderResponse);
  }

  theOutputHandler->tag("Data");
  initializationDone = true;

  return 0;
}
//added by SAJalali
double NodeRecorder::getRecordedValue(int clmnId, int rowOffset, bool reset)
{
	double res = 0;
	if (!initializationDone)
		return res;
	if (clmnId >= response.Size())
		return res;
	res = response(clmnId);
	return res;
}