#include "stdafx.h"
#include "TclWrapper.h"


using namespace OpenSees::Tcl;
using namespace System::Runtime::InteropServices;
TclWrapper::TclWrapper(RedirectStreamWrapper^ opsStream)
{
	this->_opsStream = opsStream;
	this->commandPtr = NULL;
	this->lastResult = gcnew TclExecutionResult(TclExecutionStatus::Init);
}

TclWrapper::TclWrapper()
{
	this->_opsStream = nullptr;
	this->commandPtr = NULL;
	this->lastResult = gcnew TclExecutionResult(TclExecutionStatus::Init);
}

void
TclWrapper::SetOutputStream(RedirectStreamWrapper^ opsStream)
{
	this->_opsStream = opsStream;
}

int
TclWrapper::Init() {
	if (this->_opsStream == nullptr)
		return -1000;
	this->interp = Tcl_CreateInterp();
	opserrPtr = this->_opsStream->_OPS_StreamPtr;
	int ret = OpenSeesAppInit(this->interp);
	this->InitEvents();
	if (ret != 0)
		return ret;
	else
		return 0;

}

void 
TclWrapper::InitEvents() {
	static IntPtr ip;

	// add uni mat
	ModelBuilderEventAddUniaxialMaterial^ _ModelBuilderEventAddUniaxialMaterial =
		gcnew ModelBuilderEventAddUniaxialMaterial(this,
			&TclWrapper::AddUniaxialMaterialEvent);
	gc_ModelBuilderEventAddUniaxialMaterial = GCHandle::Alloc(_ModelBuilderEventAddUniaxialMaterial);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventAddUniaxialMaterial);
	ModelBuilder_AddUniaxialMaterial _ModelBuilder_AddUniaxialMaterial = static_cast<ModelBuilder_AddUniaxialMaterial>(ip.ToPointer());
	
	// remove uni mat
	ModelBuilderEventRemoveUniaxialMaterial^ _ModelBuilderEventRemoveUniaxialMaterial =
		gcnew ModelBuilderEventRemoveUniaxialMaterial(this,
			&TclWrapper::RemoveUniaxialMaterialEvent);
	gc_ModelBuilderEventRemoveUniaxialMaterial = GCHandle::Alloc(_ModelBuilderEventRemoveUniaxialMaterial);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventRemoveUniaxialMaterial);
	ModelBuilder_RemoveUniaxialMaterial _ModelBuilder_RemoveUniaxialMaterial = static_cast<ModelBuilder_RemoveUniaxialMaterial>(ip.ToPointer());

	// clear all uni mats
	ModelBuilderEventClearAllUniaxialMaterial^ _ModelBuilderEventClearAllUniaxialMaterial =
		gcnew ModelBuilderEventClearAllUniaxialMaterial(this,
			&TclWrapper::ClearAllUniaxialMaterialEvent);
	gc_ModelBuilderEventClearAllUniaxialMaterial = GCHandle::Alloc(_ModelBuilderEventClearAllUniaxialMaterial);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventClearAllUniaxialMaterial);
	ModelBuilder_ClearAllUniaxialMaterial _ModelBuilder_ClearAllUniaxialMaterial = static_cast<ModelBuilder_ClearAllUniaxialMaterial>(ip.ToPointer());

	OPSDLL_SetUniaxialMaterialEventHandlers(_ModelBuilder_AddUniaxialMaterial,
		_ModelBuilder_RemoveUniaxialMaterial,
		_ModelBuilder_ClearAllUniaxialMaterial);

	// add Section
	ModelBuilderEventAddSection^ _ModelBuilderEventAddSection =
		gcnew ModelBuilderEventAddSection(this,
			&TclWrapper::AddSectionEvent);
	gc_ModelBuilderEventAddSection = GCHandle::Alloc(_ModelBuilderEventAddSection);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventAddSection);
	ModelBuilder_AddSection _ModelBuilder_AddSection = static_cast<ModelBuilder_AddSection>(ip.ToPointer());

	// remove Section
	ModelBuilderEventRemoveSection^ _ModelBuilderEventRemoveSection =
		gcnew ModelBuilderEventRemoveSection(this,
			&TclWrapper::RemoveSectionEvent);
	gc_ModelBuilderEventRemoveSection = GCHandle::Alloc(_ModelBuilderEventRemoveSection);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventRemoveSection);
	ModelBuilder_RemoveSection _ModelBuilder_RemoveSection = static_cast<ModelBuilder_RemoveSection>(ip.ToPointer());

	// clear all Sections
	ModelBuilderEventClearAllSection^ _ModelBuilderEventClearAllSection =
		gcnew ModelBuilderEventClearAllSection(this,
			&TclWrapper::ClearAllSectionEvent);
	gc_ModelBuilderEventClearAllSection = GCHandle::Alloc(_ModelBuilderEventClearAllSection);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventClearAllSection);
	ModelBuilder_ClearAllSection _ModelBuilder_ClearAllSection = static_cast<ModelBuilder_ClearAllSection>(ip.ToPointer());

	OPSDLL_SetSectionEventHandlers(_ModelBuilder_AddSection,
		_ModelBuilder_RemoveSection,
		_ModelBuilder_ClearAllSection);


	// add NDMaterial
	ModelBuilderEventAddNDMaterial^ _ModelBuilderEventAddNDMaterial =
		gcnew ModelBuilderEventAddNDMaterial(this,
			&TclWrapper::AddNDMaterialEvent);
	gc_ModelBuilderEventAddNDMaterial = GCHandle::Alloc(_ModelBuilderEventAddNDMaterial);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventAddNDMaterial);
	ModelBuilder_AddNDMaterial _ModelBuilder_AddNDMaterial = static_cast<ModelBuilder_AddNDMaterial>(ip.ToPointer());

	// remove NDMaterial
	ModelBuilderEventRemoveNDMaterial^ _ModelBuilderEventRemoveNDMaterial =
		gcnew ModelBuilderEventRemoveNDMaterial(this,
			&TclWrapper::RemoveNDMaterialEvent);
	gc_ModelBuilderEventRemoveNDMaterial = GCHandle::Alloc(_ModelBuilderEventRemoveNDMaterial);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventRemoveNDMaterial);
	ModelBuilder_RemoveNDMaterial _ModelBuilder_RemoveNDMaterial = static_cast<ModelBuilder_RemoveNDMaterial>(ip.ToPointer());

	// clear all NDMaterials
	ModelBuilderEventClearAllNDMaterial^ _ModelBuilderEventClearAllNDMaterial =
		gcnew ModelBuilderEventClearAllNDMaterial(this,
			&TclWrapper::ClearAllNDMaterialEvent);
	gc_ModelBuilderEventClearAllNDMaterial = GCHandle::Alloc(_ModelBuilderEventClearAllNDMaterial);
	ip = Marshal::GetFunctionPointerForDelegate(_ModelBuilderEventClearAllNDMaterial);
	ModelBuilder_ClearAllNDMaterial _ModelBuilder_ClearAllNDMaterial = static_cast<ModelBuilder_ClearAllNDMaterial>(ip.ToPointer());

	OPSDLL_SetNDMaterialEventHandlers(_ModelBuilder_AddNDMaterial,
		_ModelBuilder_RemoveNDMaterial,
		_ModelBuilder_ClearAllNDMaterial);
	
}

void
TclWrapper::TclEvalFile(String^ filename)
{
	char* _filename = (char*)(void*)Marshal::StringToHGlobalAnsi(filename);
	Tcl_EvalFile(this->interp, _filename);
	return;
}

void
TclWrapper::TclEval(String^ command)
{
	char* _command = (char*)(void*)Marshal::StringToHGlobalAnsi(command);
	Tcl_Eval(this->interp, _command);
	return;
}

DomainWrapper^
TclWrapper::GetActiveDomain() {
	DomainWrapper^ dw = gcnew DomainWrapper(ops_TheActiveDomain);
	return dw;
}

TclWrapper::~TclWrapper()
{
	if (this->interp != 0)
	{
		Tcl_Eval(this->interp, "quit");
		delete this->interp;
	}

	if (this->commandPtr != 0)
	{
		delete this->commandPtr;
	}
}



