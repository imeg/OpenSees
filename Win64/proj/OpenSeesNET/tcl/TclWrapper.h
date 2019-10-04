#pragma once
#include <tcl.h>
#include <tclDecls.h>
#include <commands.h>
#include <Domain.h>

#include "../domains/domain/DomainWrapper.h"
#include "../handlers/HandlerWrapper.h"

using namespace System;

namespace OpenSees {
	namespace Tcl {
		public enum class  TclExecutionStatus : int {
			Init = 0,
			Success = 1,
			Failed = 2,
			Partial = 3,
			Empty = 4,
		};

		public ref class TclExecutionResult
		{
		public:
			TclExecutionResult() {};
			TclExecutionResult(TclExecutionStatus status) {
				this->ExecutionStatus = (int)status;
			};
			~TclExecutionResult() {};

			int ExecutionStatus;
			String^ Result;
			String^ ErrorMessage;
		};

		public ref class TclWrapper
		{
		public:
			TclWrapper(RedirectStreamWrapper^ opsStream);
			int Init();
			TclExecutionResult^ Execute(String^ command) {
				static int length = 0;
				if (command == nullptr || command->Length == 0)
				{
					if (lastResult->ExecutionStatus != (int)TclExecutionStatus::Partial)
						lastResult->ExecutionStatus = (int)TclExecutionStatus::Empty;
					lastResult->Result = "";
					lastResult->ErrorMessage = "";
					goto end;
				}

				if (command->Trim() == "\n" && lastResult->ExecutionStatus == (int)TclExecutionStatus::Partial)
				{
					goto end;
				}

				if (commandPtr == 0)
				{
					commandPtr = Tcl_NewObj();
					Tcl_IncrRefCount(commandPtr);
				}


				const char* _cmd = (char*)(void*)Marshal::StringToHGlobalAnsi(command);
				Tcl_AppendToObj(commandPtr, _cmd, command->Length);
				Tcl_AppendToObj(commandPtr, "\n", 1);
				char* stringrep = Tcl_GetStringFromObj(commandPtr, NULL);
				if (Tcl_CommandComplete(stringrep) == 0)
				{
					// partial cmd
					lastResult->ExecutionStatus = (int)TclExecutionStatus::Partial;
					goto end;
				}

				// execute complete command

				System::Console::WriteLine(command);
				int code = Tcl_RecordAndEvalObj(interp, commandPtr, 0);
				// result pointer
				Tcl_Obj* result = Tcl_GetObjResult(interp);

				// convert to string
				const char* resultString = Tcl_GetStringFromObj(result, &length);

				if (code != TCL_OK) {
					// failed
					lastResult->ErrorMessage = length > 0 ? gcnew String(resultString) : "";
					lastResult->Result = "";
					lastResult->ExecutionStatus = (int)TclExecutionStatus::Failed;
				}
				else {
					// success
					lastResult->ErrorMessage = "";
					lastResult->ExecutionStatus = (int)TclExecutionStatus::Success;
					lastResult->Result = length > 0 ? gcnew String(resultString) : "";
				}

				Tcl_DecrRefCount(commandPtr);
				commandPtr = Tcl_NewObj();
				Tcl_IncrRefCount(commandPtr);
			end:
				return lastResult;
			}
			void TclEvalFile(String^ filename);
			void TclEval(String^ command);
			DomainWrapper^ GetActiveDomain();
			~TclWrapper();

		internal:

		private:
			Tcl_Interp* interp;
			Tcl_Obj* commandPtr;
			TclExecutionResult^ lastResult;
			RedirectStreamWrapper^ _opsStream;
		};
	}
}
