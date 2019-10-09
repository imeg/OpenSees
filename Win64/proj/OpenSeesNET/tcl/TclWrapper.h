#ifndef TclWrapper_H
#define TclWrapper_H
#pragma once
#include <tcl.h>
#include <tclDecls.h>
#include <commands.h>
#include <Domain.h>
#include <TaggedObject.h>
#include <UniaxialMaterial.h>
#include <SectionForceDeformation.h>
#include <NDMaterial.h>
#include <ModelBuilderUniaxialMaterialEventHandler.h>
#include <ModelBuilderSectionEventHandler.h>
#include <ModelBuilderNDMaterialEventHandler.h>

#include "../domains/domain/DomainWrapper.h"
#include "../handlers/HandlerWrapper.h"
#include "../materials/uniaxial/UniaxialMaterialWrapper.h"
#include "../materials/section/SectionForceDeformationWrapper.h"
#include "../materials/ndmaterial/NDMaterialWrapper.h"

#include "./ModelBuilderEvent.h"
using namespace System;
using namespace OpenSees::Tcl::ModelBuilder;
using namespace OpenSees::Materials::NDMaterials;
using namespace OpenSees::Materials::Sections;
using namespace OpenSees::Materials::Uniaxials;

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

		delegate int ModelBuilderEventAddUniaxialMaterial(TaggedObject* theUniaxialMaterial);
		delegate int ModelBuilderEventRemoveUniaxialMaterial(int tag);
		delegate int ModelBuilderEventClearAllUniaxialMaterial();
		delegate int ModelBuilderEventAddSection(TaggedObject* theSection);
		delegate int ModelBuilderEventRemoveSection(int tag);
		delegate int ModelBuilderEventClearAllSection();
		delegate int ModelBuilderEventAddNDMaterial(TaggedObject* theNDMaterial);
		delegate int ModelBuilderEventRemoveNDMaterial(int tag);
		delegate int ModelBuilderEventClearAllNDMaterial();
		public ref class TclWrapper
		{
		public:
			TclWrapper();
			TclWrapper(RedirectStreamWrapper^ opsStream);
			void SetOutputStream(RedirectStreamWrapper^ opsStream);
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

			// events
			event EventHandler<ModelBuilderAddUniaxialMaterialArgs^>^ AddUniaxialMaterialEventHandler;
			event EventHandler<ModelBuilderRemoveUniaxialMaterialArgs^>^ RemoveUniaxialMaterialEventHandler;
			event EventHandler<ModelBuilderClearAllUniaxialMaterialArgs^>^ ClearAllUniaxialMaterialEventHandler;
			event EventHandler<ModelBuilderAddSectionArgs^>^ AddSectionEventHandler;
			event EventHandler<ModelBuilderRemoveSectionArgs^>^ RemoveSectionEventHandler;
			event EventHandler<ModelBuilderClearAllSectionArgs^>^ ClearAllSectionEventHandler;
			event EventHandler<ModelBuilderAddNDMaterialArgs^>^ AddNDMaterialEventHandler;
			event EventHandler<ModelBuilderRemoveNDMaterialArgs^>^ RemoveNDMaterialEventHandler;
			event EventHandler<ModelBuilderClearAllNDMaterialArgs^>^ ClearAllNDMaterialEventHandler;
		internal:
			int AddUniaxialMaterialEvent(TaggedObject* theUniaxialMaterial) {
				AddUniaxialMaterialEventHandler(this, 
					gcnew ModelBuilderAddUniaxialMaterialArgs(gcnew UniaxialMaterialWrapper((UniaxialMaterial*)theUniaxialMaterial)));
				return 0;
			}
			int RemoveUniaxialMaterialEvent(int tag) {
				RemoveUniaxialMaterialEventHandler(this,
					gcnew ModelBuilderRemoveUniaxialMaterialArgs(tag));
				return 0;
			}
			int ClearAllUniaxialMaterialEvent() {
				ClearAllUniaxialMaterialEventHandler(this, gcnew ModelBuilderClearAllUniaxialMaterialArgs());
				return 0;
			}
			int AddSectionEvent(TaggedObject* theSection) {
				AddSectionEventHandler(this,
					gcnew ModelBuilderAddSectionArgs(gcnew SectionForceDeformationWrapper((SectionForceDeformation*)theSection)));
				return 0;
			}
			int RemoveSectionEvent(int tag) {
				RemoveSectionEventHandler(this,
					gcnew ModelBuilderRemoveSectionArgs(tag));
				return 0;
			}
			int ClearAllSectionEvent() {
				ClearAllSectionEventHandler(this, gcnew ModelBuilderClearAllSectionArgs());
				return 0;
			}
			int AddNDMaterialEvent(TaggedObject* theNDMaterial) {
				AddNDMaterialEventHandler(this,
					gcnew ModelBuilderAddNDMaterialArgs(gcnew NDMaterialWrapper((NDMaterial*)theNDMaterial)));
				return 0;
			}
			int RemoveNDMaterialEvent(int tag) {
				RemoveNDMaterialEventHandler(this,
					gcnew ModelBuilderRemoveNDMaterialArgs(tag));
				return 0;
			}
			int ClearAllNDMaterialEvent() {
				ClearAllNDMaterialEventHandler(this, gcnew ModelBuilderClearAllNDMaterialArgs());
				return 0;
			}
		private:
			void InitEvents();
			Tcl_Interp* interp;
			Tcl_Obj* commandPtr;
			TclExecutionResult^ lastResult;
			RedirectStreamWrapper^ _opsStream;

			GCHandle gc_ModelBuilderEventAddUniaxialMaterial;
			GCHandle gc_ModelBuilderEventRemoveUniaxialMaterial;
			GCHandle gc_ModelBuilderEventClearAllUniaxialMaterial;
			GCHandle gc_ModelBuilderEventAddSection;
			GCHandle gc_ModelBuilderEventRemoveSection;
			GCHandle gc_ModelBuilderEventClearAllSection;
			GCHandle gc_ModelBuilderEventAddNDMaterial;
			GCHandle gc_ModelBuilderEventRemoveNDMaterial;
			GCHandle gc_ModelBuilderEventClearAllNDMaterial;
		};
	}
}
#endif