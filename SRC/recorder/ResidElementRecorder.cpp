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
// Description: This file contains the class implementatation of 
// ResidElementRecorder.
//
// What: "@(#) ResidElementRecorder.C, revA"

#include <OPS_Globals.h>
#ifdef _CSS


#include <ResidElementRecorder.h>
#include <Domain.h>
#include <Element.h>
#include <ElementIter.h>
#include <Matrix.h>
#include <Vector.h>
#include <ID.h>
#include <string.h>
#include <Response.h>
#include <FE_Datastore.h>
#include <Information.h>

#include <Message.h>
#include <FEM_ObjectBroker.h>
#include <math.h>
#include <stdlib.h>

ResidElementRecorder::ResidElementRecorder()
:Recorder(RECORDER_TAGS_ResidElementRecorder),
 numEle(0), numDOF(0), eleID(0), dof(0), theResponses(0), theDomain(0),
 theHandler(0), data(0), initializationDone(false), responseArgs(0), numArgs(0), echoTimeFlag(false), addColumnInfo(0)
{

}


ResidElementRecorder::ResidElementRecorder(const ID *ele, 
							 const char **argv, 
							 int argc,
							 Domain &theDom, 
							 OPS_Stream &theOutputHandler,
							 bool echoTime,
							 const ID *indexValues)
 :Recorder(RECORDER_TAGS_ResidElementRecorder),
  numEle(0), eleID(0), numDOF(0), dof(0), theResponses(0), theDomain(&theDom),
  theHandler(&theOutputHandler), data(0), 
  initializationDone(false), responseArgs(0), numArgs(0), echoTimeFlag(echoTime), addColumnInfo(0)
{

  if (ele != 0) {
    numEle = ele->Size();
    eleID = new ID(*ele);
    if (eleID == 0 || eleID->Size() != numEle)
      opserr << "ElementRecorder::ElementRecorder() - out of memory\n";
  }
  
  if (indexValues != 0) {
    dof = new ID(*indexValues);
    numDOF = dof->Size();
  }
  
  //
  // create a copy of the response request
  //

  responseArgs = new char *[argc];
  if (responseArgs == 0) {
    opserr << "ElementRecorder::ElementRecorder() - out of memory\n";
    numEle = 0;
  }
  
  for (int i=0; i<argc; i++) {
    responseArgs[i] = new char[strlen(argv[i])+1];
    if (responseArgs[i] == 0) {
      delete [] responseArgs;
      opserr << "ElementRecorder::ElementRecorder() - out of memory\n";
      numEle = 0;
    }
    strcpy(responseArgs[i], argv[i]);
  }
  
  numArgs = argc;
}

ResidElementRecorder::~ResidElementRecorder()
{
  //
  // write the data
  //

  if (eleID != 0)
    delete eleID;

  if (theHandler != 0 && data != 0) {

    theHandler->tag("Data"); // Data
	if (initializationDone)
	{
	int numResponse = data->noCols();
	Vector currentData(numResponse);
      
      for (int j=0; j<numResponse; j++)
		currentData(j) = (*data)(0,j);
      theHandler->write(currentData);
	}

    theHandler->endTag(); // Data
  }

  if (theHandler != 0)
    delete theHandler;

  if (data != 0)
    delete data;
  

  //
  // clean up the memory
  //

  if (theResponses != 0) {
    for (int i = 0; i < numEle; i++) 
      if (theResponses[i] != 0)
	delete theResponses[i];

    delete [] theResponses;
  }



  // 
  // invoke destructor on response args
  //

  for (int i=0; i<numArgs; i++)
    delete [] responseArgs[i];
  delete [] responseArgs;
}


int 
ResidElementRecorder::record(int commitTag, double timeStamp)
{
  // 
  // check that initialization has been done
  //

  if (initializationDone == false) {
    if (this->initialize() != 0) {
      opserr << "ElementRecorder::record() - failed to initialize\n";
      return -1;
    }
  }

  int result = 0;
int loc = 0;      
if (echoTimeFlag)
{
	loc = 1;
	(*data)(0,0) = timeStamp;
}
// for each element do a getResponse() & put the result in current data
for (int i=0; i< numEle; i++) {
	if (theResponses[i] == 0)
		continue;
	// ask the element for the reponse
	int res;
	if (( res = theResponses[i]->getResponse()) < 0)
	{
		result += res;
		continue;
	}
	// from the response determine no of cols for each
	Information &eleInfo = theResponses[i]->getInformation();
	const Vector &eleData = eleInfo.getData();
	if (numDOF == 0) {
		for (int j=0; j<eleData.Size(); j++)
			(*data)(0,loc++) = eleData(j);
	} else {
		int dataSize = eleData.Size();
		for (int j=0; j<numDOF; j++) {
			int index = (*dof)(j);
			if (index >= 0 && index < dataSize)
				(*data)(0,loc++) = eleData(index);		
			else
				(*data)(0,loc++) = 0.0;		
		}
	}
}
    
  // succesfull completion - return 0
  return result;
}

int
ResidElementRecorder::restart(void)
{
  data->Zero();
  return 0;
}

int 
ResidElementRecorder::setDomain(Domain &theDom)
{
  theDomain = &theDom;
  return 0;
}

int
ResidElementRecorder::sendSelf(int commitTag, Channel &theChannel)
{
  addColumnInfo = 1;

  if (theChannel.isDatastore() == 1) {
    opserr << "ResidElementRecorder::sendSelf() - does not send data to a datastore\n";
    return -1;
  }
  initializationDone = false;
  //
  // into an ID, place & send eleID size, numArgs and length of all responseArgs
  //

  static ID idData(7);
  if (eleID != 0)
    idData(0) = eleID->Size();
  else
    idData(0) = 0;

  idData(1) = numArgs;

  idData(5) = this->getTag();
  idData(6) = numDOF;

  int msgLength = 0;
  for (int i=0; i<numArgs; i++) 
    msgLength += strlen(responseArgs[i])+1;
  idData(2) = msgLength;


  if (theHandler != 0) {
    idData(3) = theHandler->getClassTag();
  } else 
    idData(3) = 0;

  if (echoTimeFlag == true)
    idData(4) = 1;
  else
    idData(4) = 0;

  if (theChannel.sendID(0, commitTag, idData) < 0) {
    opserr << "ResidElementRecorder::sendSelf() - failed to send idData\n";
    return -1;
  }




  //
  // send the eleID
  //

  if (eleID != 0)
    if (theChannel.sendID(0, commitTag, *eleID) < 0) {
      opserr << "ResidElementRecorder::sendSelf() - failed to send idData\n";
      return -1;
    }

  // send dof
  if (dof != 0)
    if (theChannel.sendID(0, commitTag, *dof) < 0) {
      opserr << "ElementRecorder::sendSelf() - failed to send dof\n";
      return -1;
    }

  //
  // create a single char array holding all strings
  //    will use string terminating character to differentiate strings on other side
  //

  if (msgLength ==  0) {
    opserr << "ResidElementRecorder::sendSelf() - no data to send!!\n";
    return -1;
  }

  char *allResponseArgs = new char[msgLength];
  if (allResponseArgs == 0) {
    opserr << "ResidElementRecorder::sendSelf() - out of memory\n";
    return -1;
  }

  char *currentLoc = allResponseArgs;
  for (int j=0; j<numArgs; j++) {
    strcpy(currentLoc, responseArgs[j]);
    currentLoc += strlen(responseArgs[j]);
    currentLoc++;
  }

  //
  // send this single char array
  //

  Message theMessage(allResponseArgs, msgLength);
  if (theChannel.sendMsg(0, commitTag, theMessage) < 0) {
    opserr << "ResidElementRecorder::sendSelf() - failed to send message\n";
    return -1;
  }

  //
  // invoke sendSelf() on the output handler
  //

  if (theHandler == 0 || theHandler->sendSelf(commitTag, theChannel) < 0) {
    opserr << "ResidElementRecorder::sendSelf() - failed to send the DataOutputHandler\n";
    return -1;
  }

  //
  // clean up & return success
  //

  delete [] allResponseArgs;
  return 0;
}


int 
ResidElementRecorder::recvSelf(int commitTag, Channel &theChannel, 
		 FEM_ObjectBroker &theBroker)
{
  addColumnInfo = 1;

  if (theChannel.isDatastore() == 1) {
    opserr << "ResidElementRecorder::recvSelf() - does not recv data to a datastore\n";
    return -1;
  }

  if (responseArgs != 0) {
    for (int i=0; i<numArgs; i++)
      delete [] responseArgs[i];
  
    delete [] responseArgs;
  }

  //
  // into an ID of size 2 recv eleID size and length of all responseArgs
  //

  static ID idData(7);
  if (theChannel.recvID(0, commitTag, idData) < 0) {
    opserr << "ResidElementRecorder::recvSelf() - failed to recv idData\n";
    return -1;
  }

  int eleSize = idData(0);
  numArgs = idData(1);
  int msgLength = idData(2);
  numDOF = idData(6);

  this->setTag(idData(5));

  if (idData(4) == 1)
    echoTimeFlag = true;
  else
    echoTimeFlag = false;    

  numEle = eleSize;



  //
  // resize & recv the eleID
  //

  if (eleSize != 0) {
    eleID = new ID(eleSize);
    if (eleID == 0) {
      opserr << "ElementRecorder::recvSelf() - failed to recv idData\n";
      return -1;
    }
    if (theChannel.recvID(0, commitTag, *eleID) < 0) {
      opserr << "ElementRecorder::recvSelf() - failed to recv idData\n";
      return -1;
    }
  }


  //
  // resize & recv the dof
  //

  if (numDOF != 0) {
    dof = new ID(numDOF);
    if (dof == 0) {
      opserr << "ElementRecorder::recvSelf() - failed to create dof\n";
      return -1;
    }
    if (theChannel.recvID(0, commitTag, *dof) < 0) {
      opserr << "ElementRecorder::recvSelf() - failed to recv dof\n";
      return -1;
    }
  }

  //
  // recv the single char array of element response args
  //

  if (msgLength == 0) {
    opserr << "ResidElementRecorder::recvSelf() - 0 sized string for responses\n";
    return -1;
  }

  char *allResponseArgs = new char[msgLength];
  if (allResponseArgs == 0) {
    opserr << "ResidElementRecorder::recvSelf() - out of memory\n";
    return -1;
  }

  Message theMessage(allResponseArgs, msgLength);
  if (theChannel.recvMsg(0, commitTag, theMessage) < 0) {
    opserr << "ResidElementRecorder::recvSelf() - failed to recv message\n";
    return -1;
  }

  //
  // now break this single array into many
  // 

  responseArgs = new char *[numArgs];
  if (responseArgs == 0) {
    opserr << "ResidElementRecorder::recvSelf() - out of memory\n";
    return -1;
  }

  char *currentLoc = allResponseArgs;
  for (int j=0; j<numArgs; j++) {

    int argLength = strlen(currentLoc)+1;

    responseArgs[j] = new char[argLength];
    if (responseArgs[j] == 0) {
      opserr << "ResidElementRecorder::recvSelf() - out of memory\n";
      return -1;
    }

    strcpy(responseArgs[j], currentLoc);
    currentLoc += argLength;
  }

  //
  // create a new handler object and invoke recvSelf() on it
  //

  if (theHandler != 0)
    delete theHandler;

  theHandler = theBroker.getPtrNewStream(idData(3));
  if (theHandler == 0) {
    opserr << "NodeRecorder::sendSelf() - failed to get a data output handler\n";
    return -1;
  }

  if (theHandler->recvSelf(commitTag, theChannel, theBroker) < 0) {
    opserr << "NodeRecorder::sendSelf() - failed to send the DataOutputHandler\n";
    return -1;
  }

  //
  // clean up & return success
  //

  delete [] allResponseArgs;
  return 0;

}

int 
ResidElementRecorder::initialize(void) 
{
  if (theDomain == 0)
    return 0;

  if (theResponses != 0) {
    for (int i = 0; i < numEle; i++)
      delete theResponses[i];
    delete [] theResponses;
  }

  int numDbColumns = 0;

  //
  // Set the response objects:
  //   1. create an array of pointers for them
  //   2. iterate over the elements invoking setResponse() to get the new objects & determine size of data
  //

  int i =0;
  ID xmlOrder(0,64);
  ID responseOrder(0,64);

  if (eleID != 0) {

    int eleCount = 0;
    int responseCount = 0;

    // loop over ele & set Reponses
    for (i=0; i<numEle; i++) {
      Element *theEle = theDomain->getElement((*eleID)(i));
      if (theEle != 0) {
		xmlOrder[eleCount++] = i+1;
      }
    }

    theHandler->setOrder(xmlOrder);

    //
    // if we have an eleID we know Reponse size so allocate Response holder & loop over & ask each element
    //

    // allocate memory for Reponses & set to 0
    theResponses = new Response *[numEle];
    if (theResponses == 0) {
      opserr << "ElementRecorder::initialize() - out of memory\n";
      return -1;
    }


    for (int ii=0; ii<numEle; ii++) {
      Element *theEle = theDomain->getElement((*eleID)(ii));
      if (theEle == 0) {
		theResponses[ii] = 0;
      } else {
		if (echoTimeFlag == true) 
			theHandler->tag("ResidualElementOutput");	  
	
		theResponses[ii] = theEle->setResponse((const char **)responseArgs, numArgs, *theHandler);
		if (theResponses[ii] != 0) {
			// from the response type determine no of cols for each      
			Information &eleInfo = theResponses[ii]->getInformation();
			const Vector &eleData = eleInfo.getData();
			int dataSize = eleData.Size();
			//	  numDbColumns += dataSize;
			if (numDOF == 0)
				numDbColumns += dataSize;
			else
				numDbColumns += numDOF;
	
			if (addColumnInfo == 1) {
				if (echoTimeFlag == true) {
					if (numDOF == 0) 
						for (int j=0; j<2*dataSize; j++)
							responseOrder[responseCount++] = i+1;
					else
						for (int j=0; j<2*numDOF; j++)
						responseOrder[responseCount++] = i+1;
				} else {
					if (numDOF == 0) 
					for (int j=0; j<dataSize; j++)
						responseOrder[responseCount++] = i+1;
					else
					for (int j=0; j<numDOF; j++)
						responseOrder[responseCount++] = i+1;	      
				}
			}
	  
			if (echoTimeFlag == true) {
			for (int i=0; i<eleData.Size(); i++) {
				theHandler->tag("TimeOutput");
				theHandler->tag("ResponseType", "time");
				theHandler->endTag();
			}
			theHandler->endTag();
			}
		}
      }
    }
    
    theHandler->setOrder(responseOrder);

  } else {

    //
    // if no eleID we don't know response size so make initial guess & loop over & ask ele
    // if guess to small, we enlarge
    //


    // initial size & allocation
    int numResponse = 0;
    numEle = 12;
    theResponses = new Response *[numEle];

    if (theResponses == 0) {
      opserr << "ElementRecorder::initialize() - out of memory\n";
      return -1;
    }

    for (int k=0; k<numEle; k++)
      theResponses[k] = 0;

    // loop over ele & set Reponses
    ElementIter &theElements = theDomain->getElements();
    Element *theEle;

    while ((theEle = theElements()) != 0) {
      Response *theResponse = theEle->setResponse((const char **)responseArgs, numArgs, *theHandler);
      if (theResponse != 0) {
	if (numResponse == numEle) {
	  Response **theNextResponses = new Response *[numEle*2];
	  if (theNextResponses != 0) {
	    for (int i=0; i<numEle; i++)
	      theNextResponses[i] = theResponses[i];
	    for (int j=numEle; j<2*numEle; j++)
	      theNextResponses[j] = 0;
	  }
	  numEle = 2*numEle;
	}
	theResponses[numResponse] = theResponse;

	// from the response type determine no of cols for each
	Information &eleInfo = theResponses[numResponse]->getInformation();
	const Vector &eleData = eleInfo.getData();
	if (numDOF == 0) {
	  numDbColumns += eleData.Size();
	} else {
	  numDbColumns += numDOF;
	}
	numResponse++;

	if (echoTimeFlag == true) {
	  for (int i=0; i<eleData.Size(); i++) {
	    theHandler->tag("TimeOutput");
	    theHandler->tag("ResponseType", "time");
	    theHandler->endTag(); // TimeOutput
	  }
	}
      }
    }
    numEle = numResponse;
  }

  //
  // create the matrix & vector that holds the data
  //

  if (echoTimeFlag == true) {
    numDbColumns += 1;
  }

  data = new Matrix(1, numDbColumns);
  if (data == 0) {
    opserr << "ResidElementRecorder::ResidElementRecorder() - out of memory\n";
    exit(-1);
  }

  initializationDone = true;  
  return 0;
}
//by SAJalali
int ResidElementRecorder::removeComponentResponse(int compTag)
{
	if (theResponses == 0)
		return -1;
	if (eleID == 0)
		return -1;
	int loc = eleID->getLocation(compTag);
	if (loc == -1)
		return -1;
	if (theResponses[loc] == 0)
		return -1;
	delete theResponses[loc];
	theResponses[loc] = 0;
	return 0;
}

#endif // _CSS
