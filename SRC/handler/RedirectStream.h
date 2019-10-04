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

// $Revision: 1.3 $
// $Date: 2006-08-03 23:24:56 $
// $Source: /usr/local/cvs/OpenSees/SRC/handler/StandardStream.h,v $

#ifndef _RedirectStream
#define _RedirectStream
#include <OPS_Stream.h>
typedef int(__stdcall* RedirectStream_WriteVector) (Vector& vec);
typedef OPS_Stream& (__stdcall* RedirectStream_WriteConstCharString) (const char* s, int n);
typedef OPS_Stream& (__stdcall* RedirectStream_WriteConstUnsignedCharString) (const unsigned char* s, int n);
typedef OPS_Stream& (__stdcall* RedirectStream_WriteSignedCharString) (const signed char* s, int n);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorChar) (char c);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorUnsignedChar) (unsigned char c);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorSignedChar) (signed char c);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorConstCharString) (const char *s);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorConstUnsignedCharString) (const unsigned char* s);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorConstSignedCharString) (const signed char* s);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorInt) (int n);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorUnsignedInt) (unsigned int n);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorShortInt) (short int n);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorUnsignedShortInt) (unsigned short int n);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorLong) (long n);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorUnsignedLong) (unsigned long n);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorBool) (bool b);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorDouble) (double d);
typedef OPS_Stream& (__stdcall* RedirectStream_OperatorFloat) (float f);


class RedirectStream : public OPS_Stream
{
public:
	RedirectStream(int indentSize = 2, bool echo = true);
	~RedirectStream();

	virtual int setFile(const char* fileName, openMode mode = OVERWRITE, bool echo = false) { return 0; }
	int setLink() { return 0; };
	int setPrecision(int precision) { return 0; };
	int setFloatField(floatField) { return 0; };;
	int precision(int precision) { return 0; };
	int width(int width) { return 0; };

	// xml stuff
	int tag(const char*) { return 0; };
	int tag(const char*, const char*) { return 0; };
	int endTag() { return 0; };
	int attr(const char* name, int value) { return 0; };
	int attr(const char* name, double value) { return 0; };
	int attr(const char* name, const char* value) { return 0; };
	int write(Vector& data);


	OPS_Stream& write(const char* s, int n);
	OPS_Stream& write(const unsigned char* s, int n);
	OPS_Stream& write(const signed char* s, int n);
	OPS_Stream& write(const void* s, int n);
	OPS_Stream& operator<<(char c);
	OPS_Stream& operator<<(unsigned char c);
	OPS_Stream& operator<<(signed char c);
	OPS_Stream& operator<<(const char* s);
	OPS_Stream& operator<<(const unsigned char* s);
	OPS_Stream& operator<<(const signed char* s);
	OPS_Stream& operator<<(const void* p);
	OPS_Stream& operator<<(int n);
	OPS_Stream& operator<<(unsigned int n);
	OPS_Stream& operator<<(long n);
	OPS_Stream& operator<<(unsigned long n);
	OPS_Stream& operator<<(short n);
	OPS_Stream& operator<<(unsigned short n);
	OPS_Stream& operator<<(bool b);
	OPS_Stream& operator<<(double n);
	OPS_Stream& operator<<(float n);

	int sendSelf(int commitTag, Channel& theChannel);
	int recvSelf(int commitTag, Channel& theChannel,
		FEM_ObjectBroker& theBroker);

	RedirectStream_WriteVector _RedirectStream_WriteVector;
	RedirectStream_WriteConstCharString _RedirectStream_WriteConstCharString;
	RedirectStream_WriteConstUnsignedCharString _RedirectStream_WriteConstUnsignedCharString;
	RedirectStream_WriteSignedCharString _RedirectStream_WriteSignedCharString;
	RedirectStream_OperatorChar _RedirectStream_OperatorChar;
	RedirectStream_OperatorUnsignedChar _RedirectStream_OperatorUnsignedChar;
	RedirectStream_OperatorSignedChar _RedirectStream_OperatorSignedChar;
	RedirectStream_OperatorConstCharString _RedirectStream_OperatorConstCharString;
	RedirectStream_OperatorConstUnsignedCharString _RedirectStream_OperatorConstUnsignedCharString;
	RedirectStream_OperatorConstSignedCharString _RedirectStream_OperatorConstSignedCharString;
	RedirectStream_OperatorInt _RedirectStream_OperatorInt;
	RedirectStream_OperatorUnsignedInt _RedirectStream_OperatorUnsignedInt;
	RedirectStream_OperatorShortInt _RedirectStream_OperatorShortInt;
	RedirectStream_OperatorUnsignedShortInt _RedirectStream_OperatorUnsignedShortInt;
	RedirectStream_OperatorLong _RedirectStream_OperatorLong;
	RedirectStream_OperatorUnsignedLong _RedirectStream_OperatorUnsignedLong;
	RedirectStream_OperatorBool _RedirectStream_OperatorBool;
	RedirectStream_OperatorDouble _RedirectStream_OperatorDouble;
	RedirectStream_OperatorFloat _RedirectStream_OperatorFloat;

private:
	bool echoApplication;
	void indent(void);
	int indentSize;
	int numIndent;
	int prec;
	char* indentString;


};

#endif
