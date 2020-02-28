#pragma once
#include <OPS_Stream.h>
#include <DataFileStream.h>
#include <BinaryFileStream.h>
#include <XmlFileStream.h>
#include <TCP_Stream.h>
#include <RedirectStream.h>

#include "../actors/IMovableObjectWrapper.h"
#include "../matrix/VectorWrapper.h"
#include "../OPS.h"

using namespace System;
using namespace OpenSees;
using namespace System::IO;

namespace OpenSees {
	namespace Handlers {

		public enum class  OpenModeWrapper : int { OVERWRITE, APPEND };
		public enum class  FloatFieldWrapper { FIXEDD, SCIENTIFIC };

		public ref class OPS_StreamWrapper : IMovableObjectWrapper
		{
		public:
			OPS_StreamWrapper() {};

			// output format
			int SetFile(String^ filename, int mode, bool echo) {
				char* _filename = OPS::StringToChar(filename);
				return _OPS_StreamPtr->setFile(_filename, (openMode)mode, echo);
			};

			int SetPrecision(int precision) {
				return _OPS_StreamPtr->setPrecision(precision);
			};

			int SetFloatField(int _floatField) {
				return _OPS_StreamPtr->setFloatField((floatField)_floatField);
			};

			int Precision(int precision) {
				return _OPS_StreamPtr->precision(precision);
			};

			int Width(int width) {
				return _OPS_StreamPtr->width(width);
			};

			int Tag(String^ tagName) {
				return _OPS_StreamPtr->tag(OPS::StringToChar(tagName));
			};

			int Tag(String^ tagName, String^ value) {
				return _OPS_StreamPtr->tag(OPS::StringToChar(tagName), OPS::StringToChar(value));
			};

			int EndTag() {
				return _OPS_StreamPtr->endTag();
			};

			int Attr(String^ name, int n) {
				return _OPS_StreamPtr->attr(OPS::StringToChar(name), n);
			};

			int Attr(String^ name, double val) {
				return _OPS_StreamPtr->attr(OPS::StringToChar(name), val);
			};

			int Attr(String^ name, String^ value) {
				return _OPS_StreamPtr->attr(OPS::StringToChar(name), OPS::StringToChar(value));
			};

			int Write(VectorWrapper^ vec) {
				return _OPS_StreamPtr->write(*vec->_Vector);
			};

			String^ GetClassType() {
				const char* type = _OPS_StreamPtr->getClassType();
				return gcnew String(type);
			}

			int GetClassTag() {
				return _OPS_StreamPtr->getClassTag();
			}

			String^ GetStreamHeader() {
				const char* headerChar = _OPS_StreamPtr->getStreamHeader();
				if (headerChar == 0)
					return nullptr;
				else
				{
					String^ header = gcnew String(headerChar);
					return header;
				}
			}

			int CloseStreamHeader() {
				if (_OPS_StreamPtr != 0)
					return _OPS_StreamPtr->closeHandler();
				else
					return -1;	
			}

			~OPS_StreamWrapper() {
				if (_OPS_StreamPtr != 0)
					delete _OPS_StreamPtr;
			};
		internal:
			OPS_StreamWrapper(OPS_Stream* opsstr) {
				_OPS_StreamPtr = opsstr;
			};
			OPS_Stream* _OPS_StreamPtr;
		private:

		};

		public ref class DataFileStreamWrapper : OPS_StreamWrapper
		{
		public:
			DataFileStreamWrapper(String^ filename);
			DataFileStreamWrapper(String^ filename, int mode, int indent, int doCSV,
				bool closeOnWrite, int precision, bool doScientific);
			~DataFileStreamWrapper() {
				if (_OPS_StreamPtr != 0)
					delete _OPS_StreamPtr;
			};


		};

		public ref class BinaryFileStreamWrapper : OPS_StreamWrapper
		{
		public:
			BinaryFileStreamWrapper(String^ filename);
			BinaryFileStreamWrapper(String^ filename, int mode);
			~BinaryFileStreamWrapper() {
				if (_OPS_StreamPtr != 0)
					delete _OPS_StreamPtr;
			};


		};

		public ref class XmlFileStreamWrapper : OPS_StreamWrapper
		{
		public:
			XmlFileStreamWrapper(String^ filename, int mode);
			~XmlFileStreamWrapper() {
				if (_OPS_StreamPtr != 0)
					delete _OPS_StreamPtr;
			};
		};

		public ref class TCP_StreamWrapper : OPS_StreamWrapper
		{
		public:
			TCP_StreamWrapper(unsigned int other_Port,
				String^ other_InetAddr,
				bool checkEndianness);
			~TCP_StreamWrapper() {
				if (_OPS_StreamPtr != 0)
					delete _OPS_StreamPtr;
			};
		};

		delegate void RedirectStreamOperatorConstCharString(const char* s);
		delegate void RedirectStreamOperatorDouble(double d);
		delegate void RedirectStreamWriteVector(Vector&);
		delegate void RedirectStreamWriteConstCharString(const char* s, int n);
		delegate void RedirectStreamWriteConstUnsignedCharString(const unsigned char* s, int n);
		delegate void RedirectStreamWriteSignedCharString(const signed char* s, int n);
		delegate void RedirectStreamOperatorChar(char c);
		delegate void RedirectStreamOperatorUnsignedChar(unsigned char c);
		delegate void RedirectStreamOperatorSignedChar(signed char c);
		delegate void RedirectStreamOperatorConstUnsignedCharString(const unsigned char* s);
		delegate void RedirectStreamOperatorConstSignedCharString(const signed char* s);
		delegate void RedirectStreamOperatorInt(int n);
		delegate void RedirectStreamOperatorUnsignedInt(unsigned int n);
		delegate void RedirectStreamOperatorShortInt(short int n);
		delegate void RedirectStreamOperatorUnsignedShortInt(unsigned short int n);
		delegate void RedirectStreamOperatorLong(long n);
		delegate void RedirectStreamOperatorUnsignedLong(unsigned long n);
		delegate void RedirectStreamOperatorBool(bool b);
		delegate void RedirectStreamOperatorFloat(float f);

		public ref class RedirectStreamWrapper : OPS_StreamWrapper {
		public:
			RedirectStreamWrapper(TextWriter^ writer);
			~RedirectStreamWrapper() {
				if (_OPS_StreamPtr != 0)
					delete _OPS_StreamPtr;
				gc_RedirectStreamWriteVector.Free();
				gc_RedirectStreamWriteConstCharString.Free();
				gc_RedirectStreamWriteConstUnsignedCharString.Free();
				gc_RedirectStreamWriteSignedCharString.Free();
				gc_RedirectStreamOperatorChar.Free();
				gc_RedirectStreamOperatorUnsignedChar.Free();
				gc_RedirectStreamOperatorSignedChar.Free();
				gc_RedirectStreamOperatorConstCharString.Free();
				gc_RedirectStreamOperatorConstUnsignedCharString.Free();
				gc_RedirectStreamOperatorConstSignedCharString.Free();
				gc_RedirectStreamOperatorInt.Free();
				gc_RedirectStreamOperatorUnsignedInt.Free();
				gc_RedirectStreamOperatorShortInt.Free();
				gc_RedirectStreamOperatorUnsignedShortInt.Free();
				gc_RedirectStreamOperatorLong.Free();
				gc_RedirectStreamOperatorUnsignedLong.Free();
				gc_RedirectStreamOperatorBool.Free();
				gc_RedirectStreamOperatorDouble.Free();
				gc_RedirectStreamOperatorFloat.Free();
			};
		internal:
			void WriteVector(Vector& vec) {
				if (vec == 0 || vec.Size() == 0) return;
				double* data = vec.GetData();
				String^ response = "";
				for (size_t i = 0; i < vec.Size(); i++)
				{
					response += (data[i]).ToString() + " ";
				}
				_writer->Write(response);
			}
			void WriteConstCharString(const char* s, int n) {
				if (s == 0) return;
				String^ clistr = gcnew String(s);
				_writer->Write(clistr);
			}
			void WriteConstUnsignedCharString(const unsigned char* s, int n) {
				if (s == 0) return;
				String^ clistr = gcnew String(reinterpret_cast<const char*>(s));
				_writer->Write(clistr);
			}
			void WriteSignedCharString(const signed char* s, int n) {
				if (s == 0) return;
				String^ clistr = gcnew String(reinterpret_cast<const char*>(s));
				_writer->Write(clistr);
			}
			void OperatorChar(char c) {
				if (c == 0) return;
				String^ clistr = c.ToString();
				_writer->Write(clistr);
			}
			void OperatorUnsignedChar(unsigned char c) {
				if (c == 0) return;
				String^ clistr = c.ToString();
				_writer->Write(clistr);
			}
			void OperatorSignedChar(signed char c) {
				if (c == 0) return;
				String^ clistr = c.ToString();
				_writer->Write(clistr);
			}
			void OperatorConstCharString(const char* s) {
				if (s == 0) return;
				String^ clistr = gcnew String(s);
				_writer->Write(clistr);
			}
			void OperatorConstUnsignedCharString(const unsigned char* s) {
				if (s == 0) return;
				String^ clistr = gcnew String(reinterpret_cast<const char*>(s));
				_writer->Write(clistr);
			}
			void OperatorConstSignedCharString(const signed char* s) {
				if (s == 0) return;
				String^ clistr = gcnew String(reinterpret_cast<const char*>(s));
				_writer->Write(clistr);
			}
			void OperatorInt(int n) {
				_writer->Write(n);
			}
			void OperatorUnsignedInt(unsigned int n) {
				_writer->Write(n);
			}
			void OperatorShortInt(short int n) {
				_writer->Write(n);
			}
			void OperatorUnsignedShortInt(unsigned short int n) {
				_writer->Write(n);
			}
			void OperatorLong(long n) {
				_writer->Write(n);
			}
			void OperatorUnsignedLong(unsigned long n) {
				_writer->Write(n*1.0);
			}
			void OperatorBool(bool b) {
				_writer->Write(b);
			}
			void OperatorDouble(double d) {
				_writer->Write(d);
			}
			void OperatorFloat(float f) {
				_writer->Write(f);
			}
			

		private:
			TextWriter^ _writer;
			GCHandle gc_RedirectStreamWriteVector;
			GCHandle gc_RedirectStreamWriteConstCharString;
			GCHandle gc_RedirectStreamWriteConstUnsignedCharString;
			GCHandle gc_RedirectStreamWriteSignedCharString;
			GCHandle gc_RedirectStreamOperatorChar;
			GCHandle gc_RedirectStreamOperatorUnsignedChar;
			GCHandle gc_RedirectStreamOperatorSignedChar;
			GCHandle gc_RedirectStreamOperatorConstCharString;
			GCHandle gc_RedirectStreamOperatorConstUnsignedCharString;
			GCHandle gc_RedirectStreamOperatorConstSignedCharString;
			GCHandle gc_RedirectStreamOperatorInt;
			GCHandle gc_RedirectStreamOperatorUnsignedInt;
			GCHandle gc_RedirectStreamOperatorShortInt;
			GCHandle gc_RedirectStreamOperatorUnsignedShortInt;
			GCHandle gc_RedirectStreamOperatorLong;
			GCHandle gc_RedirectStreamOperatorUnsignedLong;
			GCHandle gc_RedirectStreamOperatorBool;
			GCHandle gc_RedirectStreamOperatorDouble;
			GCHandle gc_RedirectStreamOperatorFloat;
		};
	}
}