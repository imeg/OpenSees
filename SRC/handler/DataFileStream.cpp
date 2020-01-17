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
// $Date: 2009-10-13 21:17:42 $
// $Source: /usr/local/cvs/OpenSees/SRC/handler/DataFileStream.cpp,v $


#include <DataFileStream.h>
#include <Vector.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <ID.h>
#include <Channel.h>
#include <Message.h>
#include <Matrix.h>

using std::cerr;
using std::ios;
using std::setiosflags;
using std::ifstream;
using std::string;
using std::getline;
#if _DLL
using std::to_string;
#endif

DataFileStream::DataFileStream(int indent)
	:OPS_Stream(OPS_STREAM_TAGS_DataFileStream),
	fileOpen(0), fileName(0), indentSize(indent), sendSelfCount(0), theChannels(0), numDataRows(0),
	mapping(0), maxCount(0), sizeColumns(0), theColumns(0), theData(0), theRemoteData(0), doCSV(0), commonColumns(0)
#if _DLL
	, xmlOrderProcessed(0), xmlString(0), xmlStringLength(0), numXMLTags(0), xmlColumns(0), attributeMode(false), numTag(0), sizeTags(0), tags(0)
#endif
{
	if (indentSize < 1) indentSize = 1;
	indentString = new char[indentSize + 5];
	for (int i = 0; i < indentSize; i++)
		strcpy(indentString, " ");
}


DataFileStream::DataFileStream(const char* file, openMode mode, int indent, int csv, bool closeWrite, int prec, bool scientific)
	:OPS_Stream(OPS_STREAM_TAGS_DataFileStream),
	fileOpen(0), fileName(0), indentSize(indent), sendSelfCount(0),
	theChannels(0), numDataRows(0),
	mapping(0), maxCount(0), sizeColumns(0),
	theColumns(0), theData(0), theRemoteData(0),
	doCSV(csv), closeOnWrite(closeWrite), commonColumns(0)
#if _DLL
	, xmlOrderProcessed(0), xmlString(0), xmlStringLength(0), numXMLTags(0), xmlColumns(0), attributeMode(false), numTag(0), sizeTags(0), tags(0)
#endif
{
	thePrecision = prec;
	doScientific = scientific;

	if (indentSize < 1) indentSize = 1;
	indentString = new char[indentSize + 1];
	for (int i = 0; i < indentSize; i++)
		strcpy(indentString, " ");

	this->setFile(file, mode);
}


DataFileStream::~DataFileStream()
{
	if (fileOpen == 1)
		theFile.close();

	if (theChannels != 0) {
		delete[] theChannels;
	}

	if (indentString != 0)
		delete[] indentString;

	if (fileName != 0)
		delete[] fileName;

	if (sendSelfCount > 0) {
		for (int i = 0; i <= sendSelfCount; i++) {
			if (theColumns != 0)
				if (theColumns[i] != 0)
					delete theColumns[i];

			if (theData != 0)
				if (theData[i] != 0)
					delete[] theData[i];

			if (theRemoteData != 0)
				if (theRemoteData[i] != 0)
					delete theRemoteData[i];

		}

		if (theData != 0) delete[] theData;
		if (theRemoteData != 0) delete[] theRemoteData;
		if (theColumns != 0) delete[] theColumns;
		if (sizeColumns != 0) delete sizeColumns;
		if (commonColumns != 0) delete commonColumns;

#if _DLL
		if (xmlColumns != 0)
			delete xmlColumns;
#endif
	}
}

int
DataFileStream::setFile(const char* name, openMode mode)
{
	if (name == 0) {
		std::cerr << "DataFileStream::setFile() - no name passed\n";
		return -1;
	}

	// first create a copy of the file name
	if (fileName != 0) {
		if (strcmp(fileName, name) != 0)
			delete[] fileName;
		fileName = 0;
	}
	if (fileName == 0) {
		fileName = new char[strlen(name) + 5];
		if (fileName == 0) {
			std::cerr << "DataFileStream::setFile() - out of memory copying name: " << name << std::endl;
			return -1;
		}

		// copy the strings
		strcpy(fileName, name);
	}

	// if file already open, close it
	if (fileOpen == 1) {
		theFile.close();
		fileOpen = 0;
	}

	if (mode == 0)
		theOpenMode = OVERWRITE;
	else
		theOpenMode = APPEND;

	return 0;
}

int
DataFileStream::open(void)
{
	// check setFile has been called
	if (fileName == 0) {
		std::cerr << "DataFileStream::open(void) - no file name has been set\n";
		return -1;
	}

	// if file already open, return
	if (fileOpen == 1) {
		return 0;
	}

	if (theOpenMode == OVERWRITE)
		theFile.open(fileName, ios::out);
	else
		theFile.open(fileName, ios::out | ios::app);

	theOpenMode = APPEND;
#ifdef _CSS
	if (theFile.bad() || !theFile.is_open()) {
#else
	if (theFile.bad()) {
#endif
		std::cerr << "WARNING - DataFileStream::setFile()";
		std::cerr << " - could not open file " << fileName << std::endl;
		fileOpen = 0;
		return -1;
	}
	else
		fileOpen = 1;
	if (doScientific == true)
		theFile << std::scientific;
#if _DLL
	if (sendSelfCount >= 0) {
		headers = "";
		//theFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		headers.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		//theFile << " <OpenSees\n";
		headers.append("<OpenSees\n");
		//theFile << "  xmlns:xsi = \"http://www.w3.org/2001/XMLSchema-instance\"\n";
		headers.append("  xmlns:xsi = \"http://www.w3.org/2001/XMLSchema-instance\"\n");
		//theFile << "  xsi:noNamespaceSchemaLocation = \"http://OpenSees.berkeley.edu/xml-schema/xmlns/OpenSees.xsd\">\n";
		headers.append("  xsi:noNamespaceSchemaLocation = \"http://OpenSees.berkeley.edu/xml-schema/xmlns/OpenSees.xsd\">\n");
		numIndent++;
	}
#endif
	theFile << std::setprecision(thePrecision);

	return 0;
}

int
DataFileStream::close(void)
{
#if _DLL
	if (fileOpen == 1) {
		for (int i = 0; i < numTag; i++) {
			this->endTag();
		}

		//theFile << "</OpenSees>\n";
		headers.append("</OpenSees>\n");
		theFile.close();
	}

	fileOpen = 0;
	return 0;
#else 
	if (fileOpen != 0)
		theFile.close();
	fileOpen = 0;

	return 0;
#endif
}


int
DataFileStream::setPrecision(int prec)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << std::setprecision(prec);

	return 0;
}

int
DataFileStream::setFloatField(floatField field)
{
	if (fileOpen == 0)
		this->open();

	if (field == FIXEDD) {
		if (fileOpen != 0)
			theFile << setiosflags(ios::fixed);
	}
	else if (field == SCIENTIFIC) {
		if (fileOpen != 0)
			theFile << setiosflags(ios::scientific);
	}

	return 0;
}


int
DataFileStream::tag(const char* tagName)
{
#if !_DLL
	return 0;
#else 
	if (numTag == sizeTags) {
		int nextSize = 2 * sizeTags;

		if (nextSize == 0) nextSize = 32;
		char** nextTags = new char* [nextSize];
		if (nextTags != 0) {
			for (int i = 0; i < sizeTags; i++)
				nextTags[i] = tags[i];
			for (int j = sizeTags + 1; j < nextSize; j++)
				nextTags[j] = 0;
			sizeTags = nextSize;
		}
		else {
			sizeTags = 0;
			delete[] tags;
			tags = 0;
			return -1;
		}

		if (tags != 0)
			delete[] tags;

		tags = nextTags;
	}


	// copy string and assign to end of array
	char* newTag = new char[strlen(tagName) + 1];
	strcpy(newTag, tagName);

	if (sendSelfCount != 0 && numTag != 0) {
		if (attributeMode == true)
			(*xmlColumns)(numXMLTags) += 2;
		else
			(*xmlColumns)(numXMLTags) += 1;
	}

	tags[numTag++] = newTag;

	//  if (sendSelfCount == 0 || (strstr(tagName,"Data") != 0)) {
	if (attributeMode == true) {
		headers.append(">\n");
	}

	// output the xml for it to the file

	numIndent++;
	this->indent();
	headers.append("<");
	headers.append(tagName);

	attributeMode = true;
	return 0;
#endif
}

int
DataFileStream::tag(const char* tagName, const char* value)
{
#if !_DLL
	return 0;
#else 
	//  if (sendSelfCount == 0) {
	if (attributeMode == true) {
		//theFile << ">\n";
		headers.append(">\n");
	}
	// output the xml for it to the file
	numIndent++;
	this->indent();

	//theFile << "<" << tagName << ">" << value << "</" << tagName << ">" << endln;
	headers.append("<");
	headers.append(tagName);
	headers.append(">");
	headers.append(value);
	headers.append("</");
	headers.append(tagName);
	headers.append(">");
	headers.append(endln);
	numIndent--;

	if (sendSelfCount != 0 && numTag != 0)
		(*xmlColumns)(numXMLTags) += 1;

	attributeMode = false;
	return 0;
#endif

}

int
DataFileStream::endTag()
{
#if !_DLL
	return 0;
#else 
	if (numTag != 0) {
		if (attributeMode == true) {
			//theFile << "/>\n";
			headers.append("/>\n");
			delete[] tags[numTag - 1];
			numTag--;
		}
		else {
			this->indent();
			//theFile << "</" << tags[numTag - 1] << ">\n";
			headers.append("</");
			headers.append(tags[numTag - 1]);
			headers.append(">\n");
			delete[] tags[numTag - 1];
			numTag--;
		}

		attributeMode = false;
		numIndent--;

		if (sendSelfCount != 0)
			(*xmlColumns)[numXMLTags] += 1;

		if (numIndent == -1)
			numXMLTags++;

		return 0;
	}

	return -1;
#endif
}

int
DataFileStream::attr(const char* name, int value)
{
#if _DLL
//	theFile << " " << name << "=\"" << value << "\"";
	headers.append(" ");
	headers.append(name);
	headers.append("=\"");
	headers.append(to_string(value));
	headers.append("\"");
#endif
	return 0;
}

int
DataFileStream::attr(const char* name, double value)
{
#if _DLL
	//	theFile << " " << name << "=\"" << value << "\"";
	headers.append(" ");
	headers.append(name);
	headers.append("=\"");
	headers.append(to_string(value));
	headers.append("\"");
#endif
	return 0;
}

int
DataFileStream::attr(const char* name, const char* value)
{
#if _DLL
	//	theFile << " " << name << "=\"" << value << "\"";
	headers.append(" ");
	headers.append(name);
	headers.append("=\"");
	headers.append(value);
	headers.append("\"");
#endif
	return 0;
}

int
DataFileStream::write(Vector& data)
{
	if (fileOpen == 0 && sendSelfCount >= 0)
		this->open();

	//
	// if not parallel, just write the data
	//

	if (sendSelfCount == 0) {
		(*this) << data;
		if (closeOnWrite == true)
			this->close();
		return 0;
	}

	//
	// otherwise parallel, send the data if not p0
	//

	if (sendSelfCount < 0) {
		if (data.Size() != 0) {
			if (theChannels[0]->sendVector(0, 0, data) < 0) {
				return -1;
			}
			return 0;
		}
		else
			return 0;
	}

	//
	// if p0 recv the data & write it out sorted
	//

	// recv data
	for (int i = 0; i <= sendSelfCount; i++) {

		int numColumns = (*sizeColumns)(i);
		double* dataI = theData[i];
		if (i == 0) {
			for (int j = 0; j < numColumns; j++) {
				dataI[j] = data(j);
			}
		}
		else {
			if (numColumns != 0) {
				Vector* theV = theRemoteData[i];
				if (theChannels[i - 1]->recvVector(0, 0, *theV) < 0) {
					opserr << "DataFileStream::write - failed to recv data\n";
				}
			}
		}
	}

	Matrix& printMapping = *mapping;

	// write data
	if (doCSV == 0) {

		for (int i = 0; i < maxCount + 1; i++) {
			int fileID = (int)printMapping(0, i);
			int numData = (int)printMapping(2, i);

			if (fileID == -2)
				;

			else if (fileID != -1) {
				int startLoc = (int)printMapping(1, i);
				double* data = theData[fileID];
				for (int j = 0; j < numData; j++) {
					theFile << data[startLoc++] << " ";
				}
			}

			else {
				int numProc = (int)printMapping(4, i);
				int colAddLoc = (int)printMapping(3, i);

				for (int j = 0; j < numData; j++) {
					double value = 0.0;
					for (int k = 0; k < numProc; k++) {
						int fileID = (*commonColumns)(colAddLoc + k * 2);
						int startLoc = (*commonColumns)(colAddLoc + k * 2 + 1);
						double* data = theData[fileID];
						if (i == 0 && addCommonFlag == 2)
							value = data[startLoc + j];
						else
							value += data[startLoc + j];
					}
					theFile << value << " ";
				}
			}
		}
		theFile << "\n";
	}
	else {

		for (int i = 0; i < maxCount + 1; i++) {
			int fileID = (int)printMapping(0, i);
			int numData = (int)printMapping(2, i);

			if (fileID == -2)
				;

			else if (fileID != -1) {
				int startLoc = (int)printMapping(1, i);
				double* data = theData[fileID];
				int nM1 = numData - 1;

				for (int j = 0; j < numData; j++)
					if ((i == maxCount) && (j == nM1))
						theFile << data[startLoc++] << "\n";
					else
						theFile << data[startLoc++] << ",";
			}

			else {
				int numProc = (int)printMapping(4, i);
				int colAddLoc = (int)printMapping(3, i);
				int nM1 = numData - 1;

				for (int j = 0; j < numData; j++) {
					double value = 0.0;
					for (int k = 0; k < numProc; k++) {
						int fileID = (*commonColumns)(colAddLoc + k * 2);
						int startLoc = (*commonColumns)(colAddLoc + k * 2 + 1);
						double* data = theData[fileID];
						if (i == 0 && addCommonFlag == 2)
							value = data[startLoc + j];
						else
							value += data[startLoc + j];
					}
					if ((i == maxCount) && (j == nM1))
						theFile << value << "\n";
					else
						theFile << value << ",";
				}
			}
		}
	}

	if (closeOnWrite == true)
		this->close();

	return 0;
}

OPS_Stream&
DataFileStream::write(const char* s, int n)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile.write(s, n);

	return *this;
}

OPS_Stream&
DataFileStream::write(const unsigned char* s, int n)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile.write((const char*)s, n);

	return *this;
}
OPS_Stream&
DataFileStream::write(const signed char* s, int n)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile.write((const char*)s, n);

	return *this;
}
OPS_Stream&
DataFileStream::write(const void* s, int n)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile.write((const char*)s, n);

	return *this;
}

OPS_Stream&
DataFileStream::write(const double* s, int n)
{
	numDataRows++;

	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0) {
		if (n > 0) {
			if (doCSV == 0) {
				int nm1 = n - 1;
				for (int i = 0; i < nm1; i++) {
					theFile << s[i] << " ";
				}
				theFile << s[nm1] << "\n";
			}
			else {
				int nm1 = n - 1;
				for (int i = 0; i < nm1; i++) {
					theFile << s[i] << ",";
				}
				theFile << s[nm1] << "\n";
			}
		}
	}
	return *this;
}


OPS_Stream&
DataFileStream::operator<<(char c)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << c;

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(unsigned char c)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << c;

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(signed char c)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << c;

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(const char* s)
{
	if (fileOpen == 0)
		this->open();

	// note that we do the flush so that a "/n" before
	// a crash will cause a flush() - similar to what 
	if (fileOpen != 0) {
		theFile << s;
		theFile.flush();
	}

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(const unsigned char* s)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << s;

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(const signed char* s)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << s;

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(const void* p)
{
	if (fileOpen == 0)
		this->open();

	/*
	  if (fileOpen != 0)
		theFile << p;
	*/
	return *this;
}
OPS_Stream&
DataFileStream::operator<<(int n)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << 1.0 * n;

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(unsigned int n)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << 1.0 * n;

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(long n)
{
	if (fileOpen == 0)
		this->open();

	/*
	  if (fileOpen != 0)
		theFile << n;
	*/
	return *this;
}
OPS_Stream&
DataFileStream::operator<<(unsigned long n)
{
	if (fileOpen == 0)
		this->open();

	/*
	  if (fileOpen != 0)
		theFile << n;
	*/
	return *this;
}
OPS_Stream&
DataFileStream::operator<<(short n)
{
	if (fileOpen == 0)
		this->open();

	/*
	  if (fileOpen != 0)
		theFile << n;
	*/
	return *this;
}
OPS_Stream&
DataFileStream::operator<<(unsigned short n)
{
	if (fileOpen == 0)
		this->open();

	/*
	  if (fileOpen != 0)
		theFile << n;
	*/
	return *this;
}
OPS_Stream&
DataFileStream::operator<<(bool b)
{
	if (fileOpen == 0)
		this->open();

	/*
	  if (fileOpen != 0)
		theFile << b;
	*/
	return *this;
}
OPS_Stream&
DataFileStream::operator<<(double n)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << n;

	return *this;
}
OPS_Stream&
DataFileStream::operator<<(float n)
{
	if (fileOpen == 0)
		this->open();

	if (fileOpen != 0)
		theFile << n;

	return *this;
}


int
DataFileStream::sendSelf(int commitTag, Channel& theChannel)
{
	sendSelfCount++;

	Channel** theNextChannels = new Channel * [sendSelfCount];
	for (int i = 0; i < sendSelfCount - 1; i++)
		theNextChannels[i] = theChannels[i];
	theNextChannels[sendSelfCount - 1] = &theChannel;
	if (theChannels != 0)
		delete[] theChannels;
	theChannels = theNextChannels;

	static ID idData(3);
	int fileNameLength = 0;
	if (fileName != 0)
		fileNameLength = int(strlen(fileName));

	idData(0) = fileNameLength;

	if (theOpenMode == OVERWRITE)
		idData(1) = 0;
	else
		idData(1) = 1;

	idData(2) = sendSelfCount;

	if (theChannel.sendID(0, commitTag, idData) < 0) {
		opserr << "DataFileStream::sendSelf() - failed to send id data\n";
		return -1;
	}

	if (fileNameLength != 0) {
		Message theMessage(fileName, fileNameLength);
		if (theChannel.sendMsg(0, commitTag, theMessage) < 0) {
			opserr << "DataFileStream::sendSelf() - failed to send message\n";
			return -1;
		}
	}

	return 0;
}

int
DataFileStream::recvSelf(int commitTag, Channel& theChannel, FEM_ObjectBroker& theBroker)
{
	static ID idData(3);

	sendSelfCount = -1;
	theChannels = new Channel * [1];
	theChannels[0] = &theChannel;

	if (theChannel.recvID(0, commitTag, idData) < 0) {
		opserr << "DataFileStream::recvSelf() - failed to recv id data\n";
		return -1;
	}

	int fileNameLength = idData(0);
	if (idData(1) == 0)
		theOpenMode = OVERWRITE;
	else
		theOpenMode = APPEND;

	if (fileNameLength != 0) {
		if (fileName != 0)
			delete[] fileName;
		fileName = new char[fileNameLength + 10];
		if (fileName == 0) {
			opserr << "DataFileStream::recvSelf() - out of memory\n";
			return -1;
		}

		Message theMessage(fileName, fileNameLength);
		if (theChannel.recvMsg(0, commitTag, theMessage) < 0) {
			opserr << "DataFileStream::recvSelf() - failed to recv message\n";
			return -1;
		}

		int tag = idData(2);

		sprintf(&fileName[fileNameLength], ".%d", tag);

		/* don't write anymore .. so don't need to open file

		if (this->setFile(fileName, theOpenMode) < 0) {
		  opserr << "DataFileStream::DataFileStream() - setFile() failed\n";
		  if (fileName != 0) {
		delete [] fileName;
		fileName = 0;
		  }
		}
		*/
	}

	return 0;
}


void
DataFileStream::indent(void)
{
	if (fileOpen != 0)
		for (int i = 0; i < numIndent; i++)
			theFile << indentString;
}


int
DataFileStream::setOrder(const ID& orderData)
{
	if (sendSelfCount == 0)
		return 0;

	if (sendSelfCount < 0) {
		static ID numColumnID(1);
		int numColumn = orderData.Size();
		numColumnID(0) = numColumn;
		theChannels[0]->sendID(0, 0, numColumnID);
		if (numColumn != 0)
			theChannels[0]->sendID(0, 0, orderData);
	}

	if (sendSelfCount > 0) {

		sizeColumns = new ID(sendSelfCount + 1);
		theColumns = new ID * [sendSelfCount + 1];
		theData = new double* [sendSelfCount + 1];
		theRemoteData = new Vector * [sendSelfCount + 1];

		for (int i = 0; i <= sendSelfCount; i++) {
			(*sizeColumns)(i) = 0;
			theColumns[i] = 0;
			theData[i] = 0;
			theRemoteData[i] = 0;
		}

		int numColumns = orderData.Size();
		(*sizeColumns)(0) = numColumns;
		if (numColumns != 0) {
			theColumns[0] = new ID(orderData);
			theData[0] = new double[numColumns];
		}
		else {
			theColumns[0] = 0;
			theData[0] = 0;
		}
		theRemoteData[0] = 0;

		maxCount = 0;
		if (numColumns != 0)
			maxCount = orderData(numColumns - 1);

		// now receive orderData from the other channels
		for (int i = 0; i < sendSelfCount; i++) {
			static ID numColumnID(1);
			if (theChannels[i]->recvID(0, 0, numColumnID) < 0) {
				opserr << "DataFileStream::setOrder - failed to recv column size for process: " << i + 1 << endln;
				return -1;
			}

			int numColumns = numColumnID(0);

			(*sizeColumns)(i + 1) = numColumns;
			if (numColumns != 0) {
				theColumns[i + 1] = new ID(numColumns);
				if (theChannels[i]->recvID(0, 0, *theColumns[i + 1]) < 0) {
					opserr << "DataFileStream::setOrder - failed to recv column data for process: " << i + 1 << endln;
					return -1;
				}

				if (numColumns != 0 && (*theColumns[i + 1])[numColumns - 1] > maxCount)
					maxCount = (*theColumns[i + 1])[numColumns - 1];

				theData[i + 1] = new double[numColumns];
				theRemoteData[i + 1] = new Vector(theData[i + 1], numColumns);
			}
			else {
				theColumns[i + 1] = 0;
				theData[i + 1] = 0;
				theRemoteData[i + 1] = 0;
			}
		}

		ID currentLoc(sendSelfCount + 1);
		ID currentCount(sendSelfCount + 1);

		if (mapping != 0)
			delete mapping;

		mapping = new Matrix(5, maxCount + 1);
		commonColumns = new ID(0, 64);

		Matrix& printMapping = *mapping;

		// set all values equal -1
		printMapping.Zero();
		for (int i = 0; i < maxCount + 1; i++)
			printMapping(0, i) = -2;

		/*
		for (int i=0; i<=sendSelfCount; i++) {
		  opserr << "COLUMN: " << i << " ";
		  if (theColumns[i] != 0) {
		opserr << *(theColumns[i]);
		  } else opserr << "\n";
		}
		*/

		for (int i = 0; i <= sendSelfCount; i++) {
			currentLoc(i) = 0;
			if (theColumns[i] != 0)
				currentCount(i) = (*theColumns[i])[0];
			else
				currentCount(i) = -1;
		}

		int colAddCount = 0;
		int count = 0;
		while (count <= maxCount) {

			printMapping(3, count) = colAddCount; // set index for start of data entry in commonColumns
			for (int i = 0; i <= sendSelfCount; i++) {

				if (currentCount(i) == count) {

					if (addCommonFlag == 0)
						printMapping(0, count) = i;
					else {
						if (printMapping(0, count) == -2)
							printMapping(0, count) = i;
						else
							printMapping(0, count) = -1;
					}

					int maxLoc = theColumns[i]->Size();
					int loc = currentLoc(i);
					int columnCounter = 0;

					printMapping(1, count) = loc;

					(*commonColumns)[colAddCount] = i;
					(*commonColumns)[colAddCount + 1] = loc;

					while (loc < maxLoc && (*theColumns[i])(loc) == count) {
						loc++;
						columnCounter++;
					}

					printMapping(2, count) = columnCounter;
					printMapping(4, count) = printMapping(4, count) + 1;

					colAddCount += 2;

					currentLoc(i) = loc;

					if (loc < maxLoc)
						currentCount(i) = (*theColumns[i])(loc);
					else
						currentCount(i) = -1;
				}
			}
			count++;
		}
		/*
		opserr << "PRINT MAPPING: " << printMapping;
		opserr << "colADD" << *commonColumns;
		opserr << "DONE";
		*/
	}

	return 0;
}

#if _DLL
const char* 
DataFileStream::getStreamHeader() {
	if (headers.empty()) return 0;
	char* tab2 = new char[headers.length() + 1];
	strcpy(tab2, headers.c_str());
	
	return tab2;
}
#endif