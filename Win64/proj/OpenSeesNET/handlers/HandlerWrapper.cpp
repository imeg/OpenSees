#include "stdafx.h"
#include "HandlerWrapper.h"

using namespace System::Runtime::InteropServices;
using namespace OpenSees::Handlers;

DataFileStreamWrapper::DataFileStreamWrapper(String^ filename) {
	_OPS_StreamPtr = new DataFileStream((char*)(void*)Marshal::StringToHGlobalAnsi(filename));
}

DataFileStreamWrapper::DataFileStreamWrapper(String^ filename, int mode, int indent, int doCSV,
	bool closeOnWrite, int precision, bool doScientific) {
	_OPS_StreamPtr = new DataFileStream((char*)(void*)Marshal::StringToHGlobalAnsi(filename), (openMode)mode, indent, doCSV, closeOnWrite, precision, doScientific);
}

BinaryFileStreamWrapper::BinaryFileStreamWrapper(String^ filename) {
	_OPS_StreamPtr = new BinaryFileStream((char*)(void*)Marshal::StringToHGlobalAnsi(filename));
}

BinaryFileStreamWrapper::BinaryFileStreamWrapper(String^ filename, int mode) {
	_OPS_StreamPtr = new BinaryFileStream((char*)(void*)Marshal::StringToHGlobalAnsi(filename), (openMode)mode);
}

XmlFileStreamWrapper::XmlFileStreamWrapper(String^ filename, int mode) {
	_OPS_StreamPtr = new XmlFileStream((char*)(void*)Marshal::StringToHGlobalAnsi(filename), (openMode)mode);
}

TCP_StreamWrapper::TCP_StreamWrapper(unsigned int other_Port,
	String^ other_InetAddr,
	bool checkEndianness) {
	_OPS_StreamPtr = new TCP_Stream(other_Port, (char*)(void*)Marshal::StringToHGlobalAnsi(other_InetAddr), checkEndianness);
}

RedirectStreamWrapper::RedirectStreamWrapper(TextWriter^ writer) {
	this->_writer = writer;
	RedirectStream *ptr = new RedirectStream(0,true);

	IntPtr ip;
	
	RedirectStreamWriteVector^ _RedirectStreamWriteVector = gcnew RedirectStreamWriteVector(this, &RedirectStreamWrapper::WriteVector);
	gc_RedirectStreamWriteVector = GCHandle::Alloc(_RedirectStreamWriteVector);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamWriteVector);
	ptr->_RedirectStream_WriteVector = static_cast<RedirectStream_WriteVector>(ip.ToPointer());
	
	RedirectStreamWriteConstCharString^ _RedirectStreamWriteConstCharString = gcnew RedirectStreamWriteConstCharString(this, &RedirectStreamWrapper::WriteConstCharString);
	gc_RedirectStreamWriteConstCharString = GCHandle::Alloc(_RedirectStreamWriteConstCharString);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamWriteConstCharString);
	ptr->_RedirectStream_WriteConstCharString = static_cast<RedirectStream_WriteConstCharString>(ip.ToPointer());
	
	RedirectStreamWriteConstUnsignedCharString^ _RedirectStreamWriteConstUnsignedCharString = gcnew RedirectStreamWriteConstUnsignedCharString(this, &RedirectStreamWrapper::WriteConstUnsignedCharString);
	gc_RedirectStreamWriteConstUnsignedCharString = GCHandle::Alloc(_RedirectStreamWriteConstUnsignedCharString);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamWriteConstUnsignedCharString);
	ptr->_RedirectStream_WriteConstUnsignedCharString = static_cast<RedirectStream_WriteConstUnsignedCharString>(ip.ToPointer());
	
	RedirectStreamWriteSignedCharString^ _RedirectStreamWriteSignedCharString = gcnew RedirectStreamWriteSignedCharString(this, &RedirectStreamWrapper::WriteSignedCharString);
	gc_RedirectStreamWriteSignedCharString = GCHandle::Alloc(_RedirectStreamWriteSignedCharString);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamWriteSignedCharString);
	ptr->_RedirectStream_WriteSignedCharString = static_cast<RedirectStream_WriteSignedCharString>(ip.ToPointer());
	
	RedirectStreamOperatorChar^ _RedirectStreamOperatorChar = gcnew RedirectStreamOperatorChar(this, &RedirectStreamWrapper::OperatorChar);
	gc_RedirectStreamOperatorChar = GCHandle::Alloc(_RedirectStreamOperatorChar);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorChar);
	ptr->_RedirectStream_OperatorChar = static_cast<RedirectStream_OperatorChar>(ip.ToPointer());
	
	RedirectStreamOperatorUnsignedChar^ _RedirectStreamOperatorUnsignedChar = gcnew RedirectStreamOperatorUnsignedChar(this, &RedirectStreamWrapper::OperatorUnsignedChar);
	gc_RedirectStreamOperatorUnsignedChar = GCHandle::Alloc(_RedirectStreamOperatorUnsignedChar);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorUnsignedChar);
	ptr->_RedirectStream_OperatorUnsignedChar = static_cast<RedirectStream_OperatorUnsignedChar>(ip.ToPointer());
	
	RedirectStreamOperatorSignedChar^ _RedirectStreamOperatorSignedChar = gcnew RedirectStreamOperatorSignedChar(this, &RedirectStreamWrapper::OperatorSignedChar);
	gc_RedirectStreamOperatorSignedChar = GCHandle::Alloc(_RedirectStreamOperatorSignedChar);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorSignedChar);
	ptr->_RedirectStream_OperatorSignedChar = static_cast<RedirectStream_OperatorSignedChar>(ip.ToPointer());
	
	RedirectStreamOperatorConstCharString^ _RedirectStreamOperatorConstCharString = gcnew RedirectStreamOperatorConstCharString(this, &RedirectStreamWrapper::OperatorConstCharString);
	gc_RedirectStreamOperatorConstCharString = GCHandle::Alloc(_RedirectStreamOperatorConstCharString);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorConstCharString);
	ptr->_RedirectStream_OperatorConstCharString = static_cast<RedirectStream_OperatorConstCharString>(ip.ToPointer());
	
	RedirectStreamOperatorConstUnsignedCharString^ _RedirectStreamOperatorConstUnsignedCharString = gcnew RedirectStreamOperatorConstUnsignedCharString(this, &RedirectStreamWrapper::OperatorConstUnsignedCharString);
	gc_RedirectStreamOperatorConstUnsignedCharString = GCHandle::Alloc(_RedirectStreamOperatorConstUnsignedCharString);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorConstUnsignedCharString);
	ptr->_RedirectStream_OperatorConstUnsignedCharString = static_cast<RedirectStream_OperatorConstUnsignedCharString>(ip.ToPointer());
	
	RedirectStreamOperatorConstSignedCharString^ _RedirectStreamOperatorConstSignedCharString = gcnew RedirectStreamOperatorConstSignedCharString(this, &RedirectStreamWrapper::OperatorConstSignedCharString);
	gc_RedirectStreamOperatorConstSignedCharString = GCHandle::Alloc(_RedirectStreamOperatorConstSignedCharString);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorConstSignedCharString);
	ptr->_RedirectStream_OperatorConstSignedCharString = static_cast<RedirectStream_OperatorConstSignedCharString>(ip.ToPointer());
	
	RedirectStreamOperatorInt^ _RedirectStreamOperatorInt = gcnew RedirectStreamOperatorInt(this, &RedirectStreamWrapper::OperatorInt);
	gc_RedirectStreamOperatorInt = GCHandle::Alloc(_RedirectStreamOperatorInt);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorInt);
	ptr->_RedirectStream_OperatorInt = static_cast<RedirectStream_OperatorInt>(ip.ToPointer());
	
	RedirectStreamOperatorUnsignedInt^ _RedirectStreamOperatorUnsignedInt = gcnew RedirectStreamOperatorUnsignedInt(this, &RedirectStreamWrapper::OperatorUnsignedInt);
	gc_RedirectStreamOperatorUnsignedInt = GCHandle::Alloc(_RedirectStreamOperatorUnsignedInt);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorUnsignedInt);
	ptr->_RedirectStream_OperatorUnsignedInt = static_cast<RedirectStream_OperatorUnsignedInt>(ip.ToPointer());
	
	RedirectStreamOperatorShortInt^ _RedirectStreamOperatorShortInt = gcnew RedirectStreamOperatorShortInt(this, &RedirectStreamWrapper::OperatorShortInt);
	gc_RedirectStreamOperatorShortInt = GCHandle::Alloc(_RedirectStreamOperatorShortInt);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorShortInt);
	ptr->_RedirectStream_OperatorShortInt = static_cast<RedirectStream_OperatorShortInt>(ip.ToPointer());
	
	RedirectStreamOperatorUnsignedShortInt^ _RedirectStreamOperatorUnsignedShortInt = gcnew RedirectStreamOperatorUnsignedShortInt(this, &RedirectStreamWrapper::OperatorUnsignedShortInt);
	gc_RedirectStreamOperatorUnsignedShortInt = GCHandle::Alloc(_RedirectStreamOperatorUnsignedShortInt);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorUnsignedShortInt);
	ptr->_RedirectStream_OperatorUnsignedShortInt = static_cast<RedirectStream_OperatorUnsignedShortInt>(ip.ToPointer());
	
	RedirectStreamOperatorLong^ _RedirectStreamOperatorLong = gcnew RedirectStreamOperatorLong(this, &RedirectStreamWrapper::OperatorLong);
	gc_RedirectStreamOperatorLong = GCHandle::Alloc(_RedirectStreamOperatorLong);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorLong);
	ptr->_RedirectStream_OperatorLong = static_cast<RedirectStream_OperatorLong>(ip.ToPointer());
	
	RedirectStreamOperatorUnsignedLong^ _RedirectStreamOperatorUnsignedLong = gcnew RedirectStreamOperatorUnsignedLong(this, &RedirectStreamWrapper::OperatorUnsignedLong);
	gc_RedirectStreamOperatorUnsignedLong = GCHandle::Alloc(_RedirectStreamOperatorUnsignedLong);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorUnsignedLong);
	ptr->_RedirectStream_OperatorUnsignedLong = static_cast<RedirectStream_OperatorUnsignedLong>(ip.ToPointer());
	
	RedirectStreamOperatorBool^ _RedirectStreamOperatorBool = gcnew RedirectStreamOperatorBool(this, &RedirectStreamWrapper::OperatorBool);
	gc_RedirectStreamOperatorBool = GCHandle::Alloc(_RedirectStreamOperatorBool);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorBool);
	ptr->_RedirectStream_OperatorBool = static_cast<RedirectStream_OperatorBool>(ip.ToPointer());
	
	RedirectStreamOperatorDouble^ _RedirectStreamOperatorDouble = gcnew RedirectStreamOperatorDouble(this, &RedirectStreamWrapper::OperatorDouble);
	gc_RedirectStreamOperatorDouble = GCHandle::Alloc(_RedirectStreamOperatorDouble);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorDouble);
	ptr->_RedirectStream_OperatorDouble = static_cast<RedirectStream_OperatorDouble>(ip.ToPointer());
	
	RedirectStreamOperatorFloat^ _RedirectStreamOperatorFloat = gcnew RedirectStreamOperatorFloat(this, &RedirectStreamWrapper::OperatorFloat);
	gc_RedirectStreamOperatorFloat = GCHandle::Alloc(_RedirectStreamOperatorFloat);
	ip = Marshal::GetFunctionPointerForDelegate(_RedirectStreamOperatorFloat);
	ptr->_RedirectStream_OperatorFloat = static_cast<RedirectStream_OperatorFloat>(ip.ToPointer());

	_OPS_StreamPtr = ptr;
}



