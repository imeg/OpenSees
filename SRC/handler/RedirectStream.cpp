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
// $Date: 12 sep 2019$
// $Source: /usr/local/cvs/OpenSees/SRC/handler/RedirectStream.cpp,v $

#include <RedirectStream.h>
#include <Vector.h>

RedirectStream::RedirectStream(int indent, bool echo)
	:OPS_Stream(OPS_STREAM_TAGS_FileStream),
	echoApplication(echo), indentSize(indent), numIndent(-1), prec(6),
	_RedirectStream_WriteVector(0), _RedirectStream_WriteConstCharString(0), _RedirectStream_WriteConstUnsignedCharString(0),
	_RedirectStream_WriteSignedCharString(0), _RedirectStream_OperatorChar(0), _RedirectStream_OperatorUnsignedChar(0),
	_RedirectStream_OperatorSignedChar(0), _RedirectStream_OperatorConstCharString(0), _RedirectStream_OperatorConstUnsignedCharString(0),
	_RedirectStream_OperatorConstSignedCharString(0), _RedirectStream_OperatorInt(0), _RedirectStream_OperatorUnsignedInt(0),
	_RedirectStream_OperatorShortInt(0), _RedirectStream_OperatorUnsignedShortInt(0), _RedirectStream_OperatorLong(0),
	_RedirectStream_OperatorUnsignedLong(0), _RedirectStream_OperatorBool(0), _RedirectStream_OperatorDouble(0),
	_RedirectStream_OperatorFloat(0)
{
	if (indentSize < 1) 
		indentSize = 1;
	indentString = new char[indentSize + 1];
	for (int i = 0; i < indentSize; i++)
		strcpy(indentString, " ");
}

RedirectStream::~RedirectStream()
{
	
}

int
RedirectStream::write(Vector& data)
{
	this->_RedirectStream_WriteVector(data);
	return 0;
}


OPS_Stream&
RedirectStream::write(const char* s, int n)
{
	if (echoApplication == true)
		this->_RedirectStream_WriteConstCharString(s,n);

	return *this;
}

OPS_Stream&
RedirectStream::write(const unsigned char* s, int n)
{
	if (echoApplication == true)
		this->_RedirectStream_WriteConstUnsignedCharString(s,n);

	return *this;
}
OPS_Stream&
RedirectStream::write(const signed char* s, int n)
{
	if (echoApplication == true)
		this->_RedirectStream_WriteSignedCharString(s,n);

	return *this;
}
OPS_Stream&
RedirectStream::write(const void* s, int n)
{
	return this->_RedirectStream_WriteConstCharString((const char*)s, n);
}

OPS_Stream&
RedirectStream::operator<<(char c)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorChar(c);
	return *this;
}
OPS_Stream&
RedirectStream::operator<<(unsigned char c)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorUnsignedChar(c);

	return *this;
}
OPS_Stream&
RedirectStream::operator<<(signed char c)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorSignedChar(c);
	return *this;
}

OPS_Stream&
RedirectStream::operator<<(const char* s)
{
	// note that we do the flush so that a "/n" before
	// a crash will cause a flush() - similar to what 
	if (echoApplication == true) {
		this->_RedirectStream_OperatorConstCharString(s);

		return *this;
	}
}

OPS_Stream&
RedirectStream::operator<<(const unsigned char* s)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorConstUnsignedCharString(s);

	return *this;
}

OPS_Stream&
RedirectStream::operator<<(const signed char* s)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorConstSignedCharString(s);

	return *this;
}
OPS_Stream&
RedirectStream::operator<<(const void* p)
{
	return *this;
}
OPS_Stream&
RedirectStream::operator<<(int n)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorInt(n);

	return *this;
}

OPS_Stream&
RedirectStream::operator<<(unsigned int n)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorUnsignedInt(1.0 * n);

	return *this;
}
OPS_Stream&
RedirectStream::operator<<(long n)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorLong(n);
	return *this;
}
OPS_Stream&
RedirectStream::operator<<(unsigned long n)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorUnsignedLong(n);

	return *this;
}
OPS_Stream&
RedirectStream::operator<<(short n)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorShortInt(n);

	return *this;
}
OPS_Stream&
RedirectStream::operator<<(unsigned short n)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorUnsignedShortInt(n);

	return *this;
}

OPS_Stream&
RedirectStream::operator<<(bool b)
{
	if (echoApplication == true)
		this->_RedirectStream_OperatorBool(b);

	return *this;
}
OPS_Stream&
RedirectStream::operator<<(double n)
{
	if (echoApplication == true)
		_RedirectStream_OperatorDouble(n);
	return *this;
}
OPS_Stream&
RedirectStream::operator<<(float n)
{
	if (echoApplication == true)
		_RedirectStream_OperatorFloat(n);
	return *this;
}


void
RedirectStream::indent(void)
{
	for (int i = 0; i < numIndent; i++) {
		_RedirectStream_WriteConstCharString(indentString, indentSize);
	}
}

int
RedirectStream::sendSelf(int commitTag, Channel& theChannel)
{
	return 0;
}

int
RedirectStream::recvSelf(int commitTag, Channel& theChannel,
	FEM_ObjectBroker& theBroker)
{

	return 0;
}
