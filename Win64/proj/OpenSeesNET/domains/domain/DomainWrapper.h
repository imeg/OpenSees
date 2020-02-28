#ifndef DomainWrapper_H
#define DomainWrapper_H
#pragma once
#include <TaggedObject.h>
#include <DomainComponent.h>
#include <RigidRod.h>
#include <Domain.h>
#include <Node.h>
#include <NodeIter.h>
#include <Element.h>
#include <ElementIter.h>
#include <SP_Constraint.h>
#include <NodalLoad.h>
#include <ElementalLoad.h>
#include <SP_ConstraintIter.h>
#include <MP_Constraint.h>
#include <MP_ConstraintIter.h>
#include <LoadPatternIter.h>
#include <RigidBeam.h>
#include <RigidDiaphragm.h>
#include <RigidRod.h>

#include "BaseDomainWrapper.h"
#include "../../elements/ElementWrapper.h"
#include "../../recorders/RecorderWrapper.h"
#include "../../matrix/MatrixWrapper.h"
#include "../constraints/ConstraintWrapper.h"
#include "../loads/LoadWrapper.h"
#include "../patterns/LoadPatternWrapper.h"
#include "../nodes/NodeWrapper.h"
#include "../../taggeds/TaggedObjectWrapper.h"
#include "DomainEvent.h"
using namespace System;
using namespace OpenSees::Elements;
using namespace OpenSees::Components;
using namespace OpenSees::Components::LoadPatterns;
using namespace OpenSees::Components::Loads;
using namespace OpenSees::Components::Constraints;
using namespace OpenSees::Recorders;
namespace OpenSees {
	namespace Components {

		delegate int DomainEventAddNode(Node* node);
		delegate int DomainEventRemoveNode(Node* node);
		delegate int DomainEventAddElement(Element* element);
		delegate int DomainEventRemoveElement(Element* element);
		delegate int DomainEventAddSP(SP_Constraint* sp);
		delegate int DomainEventRemoveSP(SP_Constraint* sp);
		delegate int DomainEventAddMP(MP_Constraint* mp);
		delegate int DomainEventRemoveMP(MP_Constraint* mp);
		delegate int DomainEventAddLoadPattern(LoadPattern* lp);
		delegate int DomainEventRemoveLoadPattern(LoadPattern* lp);
		delegate int DomainEventAddRecorder(Recorder* rec);
		delegate int DomainEventRemoveRecorder(Recorder* rec);
		delegate int DomainEventAddNodalLoad(NodalLoad* obj,int pattern);
		delegate int DomainEventRemoveNodalLoad(NodalLoad* obj);
		delegate int DomainEventAddElementalLoad(ElementalLoad* obj, int pattern);
		delegate int DomainEventRemoveElementalLoad(ElementalLoad* obj);
		delegate int DomainEventAddSP_Constraint(SP_Constraint* obj, int pattern);
		delegate int DomainEventRemoveSP_Constraint(SP_Constraint* obj);
		delegate int DomainEventClearAll();
		public ref class DomainWrapper : BaseDomainWrapper
		{
		public:
			DomainWrapper();
			~DomainWrapper();
			bool^ AddNode(array<NodeWrapper^>^ nodes);
			bool^ AddNode(NodeWrapper^ node);
			bool^ AddElement(array<ElementWrapper^>^ elements);
			bool^ AddElement(ElementWrapper^ element);
			bool^ AddSP_Constraint(array<SP_ConstraintWrapper^>^ sps);
			bool^ AddSP_Constraint(SP_ConstraintWrapper^ sP_Constraint);
			bool^ AddMP_Constraint(array<MP_ConstraintWrapper^>^ mps);
			bool^ AddMP_Constraint(MP_ConstraintWrapper^ sP_Constraint);
			bool^ AddLoadPattern(LoadPatternWrapper^ loadPattern);
			bool^ AddNodalLoad(NodalLoadWrapper^ nodalLoad, int loadPatternTag);
			bool^ AddNodalLoad(array<NodalLoadWrapper^>^ nodalLoads, int loadPatternTag);
			bool^ AddElementLoad(ElementalLoadWrapper^ eleLoad, int loadPatternTag) {
				return _Domain->addElementalLoad(eleLoad->_ElementalLoad, loadPatternTag);
			}
			bool^ AddRecorder(RecorderWrapper^ recorder) {
				if (_Domain->addRecorder(*recorder->_Recorder) == 0)
					return true;
				else
					return false;
			}
			bool^ RemoveRecorders() {
				if (_Domain->removeRecorders() == 0)
					return true;
				else
					return false;
			}
			VectorWrapper^ GetPhysicalBounds() {
				Vector vec = _Domain->getPhysicalBounds();
				VectorWrapper^ nvec = gcnew VectorWrapper(vec.GetData(), vec.Size());
				return nvec;
			}
			void ClearAll() {
				_Domain->clearAll();
			}
			ElementWrapper^ RemoveElement(int tag) {
				Element* ret = _Domain->removeElement(tag);
				if (ret == 0) return nullptr;
				ElementWrapper^ wret = gcnew ElementWrapper();
				wret->_Element = ret;
				wret->_TaggedObject = ret;
				return wret;
			}
			NodeWrapper^ RemoveNode(int tag) {
				Node* ret = _Domain->removeNode(tag);
				if (ret == 0) return nullptr;
				NodeWrapper^ wret = gcnew NodeWrapper();
				wret->_Node = ret;
				wret->_TaggedObject = ret;
				return wret;
			}
			LoadPatternWrapper^ RemoveLoadPattern(int tag) {
				LoadPattern* ret = _Domain->removeLoadPattern(tag);
				if (ret == 0) return nullptr;
				LoadPatternWrapper^ wret = gcnew LoadPatternWrapper();
				wret->_LoadPattern = ret;
				wret->_TaggedObject = ret;
				return wret;
			}
			NodeWrapper^ GetNode(int tag) {
				Node* node = _Domain->getNode(tag);
				if (node != 0)
				{
					NodeWrapper^ _node = gcnew NodeWrapper();
					_node->_Node = node;
					_node->_TaggedObject = node;
					return _node;
				}
				else
					return nullptr;
			}
			ElementWrapper^ GetElement(int tag) {
				Element* ele = _Domain->getElement(tag);
				if (ele != 0)
				{
					ElementWrapper^ _ele = gcnew ElementWrapper();
					_ele->_Element = ele;
					_ele->_TaggedObject = ele;
					return _ele;
				}
				else
					return nullptr;
			}
			LoadPatternWrapper^ GetLoadPattern(int tag) {
				LoadPattern* pattern = _Domain->getLoadPattern(tag);
				if (pattern != 0)
				{
					LoadPatternWrapper^ _pattern = gcnew LoadPatternWrapper();
					_pattern->_LoadPattern = pattern;
					_pattern->_TaggedObject = pattern;
					return _pattern;
				}
				else
					return nullptr;
			}
			int GetNumNodes() { return _Domain->getNumNodes(); }
			array<NodeWrapper^>^ GetNodes() {
				int num = _Domain->getNumNodes();
				array<NodeWrapper^>^ _nodes = gcnew array<NodeWrapper^>(num);
				NodeIter& iterator = _Domain->getNodes();
				Node* obj = 0;
				int i = 0;
				while ((obj = iterator()) != 0)
				{
					_nodes[i] = gcnew NodeWrapper();
					_nodes[i]->_Node = obj;
					_nodes[i]->_TaggedObject = obj;
					i++;
				}
				return _nodes;
			}
			array<RecorderWrapper^>^ GetRecorders() {
				int num = _Domain->numRecorders;
				if (num == 0) return nullptr;
				Recorder** recorders = _Domain->theRecorders;
				array<RecorderWrapper^>^ _recorders = gcnew array<RecorderWrapper^>(num);
				for (int i = 0; i < num; i++)
				{
					_recorders[i] = gcnew RecorderWrapper(recorders[i]);
				}
				return _recorders;
			}
			int GetNumElements() { return _Domain->getNumElements(); }
			array<ElementWrapper^>^ GetElements() {
				int num = _Domain->getNumElements();
				array<ElementWrapper^>^ _elements = gcnew array<ElementWrapper^>(num);
				ElementIter& iterator = _Domain->getElements();
				Element* obj = 0;
				int i = 0;
				while ((obj = iterator()) != 0)
				{
					_elements[i] = gcnew ElementWrapper();
					_elements[i]->_Element = obj;
					_elements[i]->_TaggedObject = obj;
					i++;
				}
				return _elements;
			}
			int GetNumLoadPatterns() { return _Domain->getNumLoadPatterns(); }
			array<LoadPatternWrapper^>^ GetLoadPatterns() {
				int num = _Domain->getNumLoadPatterns();
				array<LoadPatternWrapper^>^ _patterns = gcnew array<LoadPatternWrapper^>(num);
				LoadPatternIter& iterator = _Domain->getLoadPatterns();
				LoadPattern* obj = 0;
				int i = 0;
				while ((obj = iterator()) != 0)
				{
					_patterns[i] = gcnew LoadPatternWrapper();
					_patterns[i]->_LoadPattern = obj;
					_patterns[i]->_TaggedObject = obj;
					i++;
				}
				return _patterns;
			}
			void RevertToStart() {
				_Domain->revertToStart();
			}
			void RevertToLastCommit() {
				_Domain->revertToLastCommit();
			}
			array<SP_ConstraintWrapper^>^ GetSPs() {
				int numNodes = _Domain->getNumSPs();
				array<SP_ConstraintWrapper^>^ _sps = gcnew array<SP_ConstraintWrapper^>(numNodes);
				SP_ConstraintIter& spIter = _Domain->getSPs();

				SP_Constraint* obj = 0;
				int i = 0;
				while ((obj = spIter()) != 0)
				{
					_sps[i] = gcnew SP_ConstraintWrapper();
					_sps[i]->_SP_Constraint = obj;
					_sps[i]->_TaggedObject = obj;
					i++;
				}
				return _sps;
			}
			array<MP_ConstraintWrapper^>^ GetMPs() {
				int numNodes = _Domain->getNumSPs();
				array<MP_ConstraintWrapper^>^ _mps = gcnew array<MP_ConstraintWrapper^>(numNodes);
				MP_ConstraintIter& mpIter = _Domain->getMPs();

				MP_Constraint* obj = 0;
				int i = 0;
				while ((obj = mpIter()) != 0)
				{
					_mps[i] = gcnew MP_ConstraintWrapper();
					_mps[i]->_MP_Constraint = obj;
					_mps[i]->_TaggedObject = obj;
				}
				return _mps;
			}
			void CreateRigidDiaphragm(int nodeR, IDWrapper^ nodeC, int perpDirnToPlaneConstrained) {
				RigidDiaphragm* rb = new RigidDiaphragm(*this->_Domain, nodeR, *nodeC->_ID, perpDirnToPlaneConstrained);
			};
			void CreateRigidBeam(int nR, int nC) {
				RigidBeam* rb = new RigidBeam(*this->_Domain, nR, nC);
			};
			void CreateRigidRod(int nodeR, int nodeC) {
				RigidRod* rb = new RigidRod(*this->_Domain, nodeR, nodeC);
			};
			void Print(int flag)
			{
				_Domain->Print(opserr, flag);
			};
			void CalculateNodalReactions(int flag)
			{
				_Domain->calculateNodalReactions(flag);
			};
			void SetLoadConst() {
				_Domain->setLoadConstant();
			}
			void SetCurrentTime(double t)
			{
				_Domain->setCurrentTime(t);
			}
			void SetCommittedTime(double t)
			{
				_Domain->setCommittedTime(t);
			}
			void SetMass(int nodeId, MatrixWrapper^ matrix) {
				_Domain->setMass(*matrix->_Matrix, nodeId);
			}
			void SetMass(array<int>^ nodeIds, MatrixWrapper^ matrix) {
				for (int i = 0; i < nodeIds->Length; i++)
					_Domain->setMass(*matrix->_Matrix, nodeIds[i]);
			}
			void SetRayleighDampingFactors(double alphaM, double betaK, double betaK0, double betaKc) {
				_Domain->setRayleighDampingFactors(alphaM, betaK, betaK0, betaKc);
			}
			double GetTime()
			{
				return _Domain->getCurrentTime();
			}
			array<double>^ GetEigenValues()
			{
				Vector vec = _Domain->getEigenvalues();
				int size = vec.Size();
				array<double>^ _vec = gcnew array<double>(size);
				for (int i = 0; i < size; i++)
					_vec[i] = vec[i];
				return _vec;
			}

			//delegate void DomainChanged(int^);
			event EventHandler<DomainAddNodeEventArgs^>^ AddNodeEventHandler;
			event EventHandler<DomainRemoveNodeEventArgs^>^ RemoveNodeEventHandler;
			event EventHandler<DomainAddElementEventArgs^>^ AddElementEventHandler;
			event EventHandler<DomainRemoveElementEventArgs^>^ RemoveElementEventHandler;
			event EventHandler<DomainAddSPEventArgs^>^ AddSPEventHandler;
			event EventHandler<DomainRemoveSPEventArgs^>^ RemoveSPEventHandler;
			event EventHandler<DomainAddMPEventArgs^>^ AddMPEventHandler;
			event EventHandler<DomainRemoveMPEventArgs^>^ RemoveMPEventHandler;
			event EventHandler<DomainAddLoadPatternEventArgs^>^ AddLoadPatternEventHandler;
			event EventHandler<DomainRemoveLoadPatternEventArgs^>^ RemoveLoadPatternEventHandler;
			event EventHandler<DomainAddRecorderEventArgs^>^ AddRecorderEventHandler;
			event EventHandler<DomainRemoveRecorderEventArgs^>^ RemoveRecorderEventHandler;
			event EventHandler<DomainAddNodalLoadEventArgs^>^ AddNodalLoadEventHandler;
			event EventHandler<DomainRemoveNodalLoadEventArgs^>^ RemoveNodalLoadEventHandler;
			event EventHandler<DomainAddElementalLoadEventArgs^>^ AddElementalLoadEventHandler;
			event EventHandler<DomainRemoveElementalLoadEventArgs^>^ RemoveElementalLoadEventHandler;
			event EventHandler<DomainAddSP_ConstraintEventArgs^>^ AddSP_ConstraintEventHandler;
			event EventHandler<DomainRemoveSP_ConstraintEventArgs^>^ RemoveSP_ConstraintEventHandler;
			event EventHandler<DomainClearAllArgs^>^ ClearAllHandler;


		internal:
			DomainWrapper(Domain* domain) {
				_Domain = domain;
				InitEvents();
			};
			void SetDomain(Domain* theDomain) {
				_Domain = theDomain;
			}
			int AddNodeEvent(Node* node) {
				AddNodeEventHandler(this, gcnew DomainAddNodeEventArgs(gcnew NodeWrapper(node)));
				return 0;
			}
			int RemoveNodeEvent(Node* node) {
				RemoveNodeEventHandler(this, 
					gcnew DomainRemoveNodeEventArgs(gcnew NodeWrapper(node)));
				return 0;
			}
			int AddElementEvent(Element* element) {
				AddElementEventHandler(this, gcnew DomainAddElementEventArgs(gcnew ElementWrapper(element)));
				return 0;
			}
			int RemoveElementEvent(Element* element) {
				RemoveElementEventHandler(this, gcnew DomainRemoveElementEventArgs(gcnew ElementWrapper(element)));
				return 0;
			}
			int AddSPEvent(SP_Constraint* SP) {
				AddSPEventHandler(this, gcnew DomainAddSPEventArgs(gcnew SP_ConstraintWrapper(SP)));
				return 0;
			}
			int RemoveSPEvent(SP_Constraint* SP)
			{
				RemoveSPEventHandler(this, gcnew DomainRemoveSPEventArgs(gcnew SP_ConstraintWrapper(SP)));
				return 0;
			}
			int AddMPEvent(MP_Constraint* MP) {
				AddMPEventHandler(this, gcnew DomainAddMPEventArgs(gcnew MP_ConstraintWrapper(MP)));
				return 0;
			}
			int RemoveMPEvent(MP_Constraint* MP)
			{
				RemoveMPEventHandler(this, gcnew DomainRemoveMPEventArgs(gcnew MP_ConstraintWrapper(MP)));
				return 0;
			}
			int AddLoadPatternEvent(LoadPattern* LoadPattern) {
				AddLoadPatternEventHandler(this, gcnew DomainAddLoadPatternEventArgs(gcnew LoadPatternWrapper(LoadPattern)));
				return 0;
			}
			int RemoveLoadPatternEvent(LoadPattern* LoadPattern)
			{
				RemoveLoadPatternEventHandler(this, gcnew DomainRemoveLoadPatternEventArgs(gcnew LoadPatternWrapper(LoadPattern)));
				return 0;
			}
			int AddRecorderEvent(Recorder* Recorder) {
				AddRecorderEventHandler(this, gcnew DomainAddRecorderEventArgs(gcnew RecorderWrapper(Recorder)));
				return 0;
			}
			int RemoveRecorderEvent(Recorder* Recorder)
			{
				RemoveRecorderEventHandler(this, gcnew DomainRemoveRecorderEventArgs(gcnew RecorderWrapper(Recorder)));
				return 0;
			}
			int AddNodalLoadEvent(NodalLoad* NodalLoad, int pattern) {
				AddNodalLoadEventHandler(this, gcnew DomainAddNodalLoadEventArgs(gcnew NodalLoadWrapper(NodalLoad), pattern));
				return 0;
			}
			int RemoveNodalLoadEvent(NodalLoad* NodalLoad)
			{
				RemoveNodalLoadEventHandler(this, gcnew DomainRemoveNodalLoadEventArgs(gcnew NodalLoadWrapper(NodalLoad)));
				return 0;
			}
			int AddElementalLoadEvent(ElementalLoad* ElementalLoad, int pattern) {
				AddElementalLoadEventHandler(this, gcnew DomainAddElementalLoadEventArgs(gcnew ElementalLoadWrapper(ElementalLoad), pattern));
				return 0;
			}
			int RemoveElementalLoadEvent(ElementalLoad* ElementalLoad)
			{
				RemoveElementalLoadEventHandler(this, gcnew DomainRemoveElementalLoadEventArgs(gcnew ElementalLoadWrapper(ElementalLoad)));
				return 0;
			}
			int AddSP_ConstraintEvent(SP_Constraint* SP_Constraint, int pattern) {
				AddSP_ConstraintEventHandler(this, gcnew DomainAddSP_ConstraintEventArgs(gcnew SP_ConstraintWrapper(SP_Constraint), pattern));
				return 0;
			}
			int RemoveSP_ConstraintEvent(SP_Constraint* SP_Constraint)
			{
				RemoveSP_ConstraintEventHandler(this, gcnew DomainRemoveSP_ConstraintEventArgs(gcnew SP_ConstraintWrapper(SP_Constraint)));
				return 0;
			}
			int ClearAllEvent() {
				ClearAllHandler(this, gcnew DomainClearAllArgs());
				return 0;
			}

		private:
			void InitEvents() {
				static IntPtr ip;
				if (_Domain != 0) {
					// add node
					DomainEventAddNode^ _DomainEventAddNode = gcnew DomainEventAddNode(this, 
						&DomainWrapper::AddNodeEvent);
					gc_DomainEventAddNode = GCHandle::Alloc(_DomainEventAddNode);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddNode);
					_Domain->_DomainEvent_AddNode = static_cast<DomainEvent_AddNode>(ip.ToPointer());

					// remove node
					DomainEventRemoveNode^ _DomainEventRemoveNode = gcnew DomainEventRemoveNode(this, 
						&DomainWrapper::RemoveNodeEvent);
					gc_DomainEventRemoveNode = GCHandle::Alloc(_DomainEventRemoveNode);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveNode);
					_Domain->_DomainEvent_RemoveNode = static_cast<DomainEvent_RemoveNode>(ip.ToPointer());

					// add element
					DomainEventAddElement^ _DomainEventAddElement = gcnew DomainEventAddElement(this,
						&DomainWrapper::AddElementEvent);
					gc_DomainEventAddElement = GCHandle::Alloc(_DomainEventAddElement);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddElement);
					_Domain->_DomainEvent_AddElement = static_cast<DomainEvent_AddElement>(ip.ToPointer());

					// remove element
					DomainEventRemoveElement^ _DomainEventRemoveElement = gcnew DomainEventRemoveElement(this,
						&DomainWrapper::RemoveElementEvent);
					gc_DomainEventRemoveElement = GCHandle::Alloc(_DomainEventRemoveElement);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveElement);
					_Domain->_DomainEvent_RemoveElement = static_cast<DomainEvent_RemoveElement>(ip.ToPointer());

					// add sp
					DomainEventAddSP^ _DomainEventAddSP = gcnew DomainEventAddSP(this,
						&DomainWrapper::AddSPEvent);
					gc_DomainEventAddSP = GCHandle::Alloc(_DomainEventAddSP);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddSP);
					_Domain->_DomainEvent_AddSP = static_cast<DomainEvent_AddSP>(ip.ToPointer());

					// remove sp
					DomainEventRemoveSP^ _DomainEventRemoveSP = gcnew DomainEventRemoveSP(this,
						&DomainWrapper::RemoveSPEvent);
					gc_DomainEventRemoveSP = GCHandle::Alloc(_DomainEventRemoveSP);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveSP);
					_Domain->_DomainEvent_RemoveSP = static_cast<DomainEvent_RemoveSP>(ip.ToPointer());


					// add mp
					DomainEventAddMP^ _DomainEventAddMP = gcnew DomainEventAddMP(this,
						&DomainWrapper::AddMPEvent);
					gc_DomainEventAddMP = GCHandle::Alloc(_DomainEventAddMP);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddMP);
					_Domain->_DomainEvent_AddMP = static_cast<DomainEvent_AddMP>(ip.ToPointer());

					// remove mp
					DomainEventRemoveMP^ _DomainEventRemoveMP = gcnew DomainEventRemoveMP(this,
						&DomainWrapper::RemoveMPEvent);
					gc_DomainEventRemoveMP = GCHandle::Alloc(_DomainEventRemoveMP);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveMP);
					_Domain->_DomainEvent_RemoveMP = static_cast<DomainEvent_RemoveMP>(ip.ToPointer());

					// add lp
					DomainEventAddLoadPattern^ _DomainEventAddLoadPattern = gcnew DomainEventAddLoadPattern(this,
						&DomainWrapper::AddLoadPatternEvent);
					gc_DomainEventAddLoadPattern = GCHandle::Alloc(_DomainEventAddLoadPattern);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddLoadPattern);
					_Domain->_DomainEvent_AddLoadPattern = static_cast<DomainEvent_AddLoadPattern>(ip.ToPointer());

					// remove lp
					DomainEventRemoveLoadPattern^ _DomainEventRemoveLoadPattern = gcnew DomainEventRemoveLoadPattern(this,
						&DomainWrapper::RemoveLoadPatternEvent);
					gc_DomainEventRemoveLoadPattern = GCHandle::Alloc(_DomainEventRemoveLoadPattern);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveLoadPattern);
					_Domain->_DomainEvent_RemoveLoadPattern = static_cast<DomainEvent_RemoveLoadPattern>(ip.ToPointer());

					// add rec
					DomainEventAddRecorder^ _DomainEventAddRecorder = gcnew DomainEventAddRecorder(this,
						&DomainWrapper::AddRecorderEvent);
					gc_DomainEventAddRecorder = GCHandle::Alloc(_DomainEventAddRecorder);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddRecorder);
					_Domain->_DomainEvent_AddRecorder = static_cast<DomainEvent_AddRecorder>(ip.ToPointer());

					// remove rec
					DomainEventRemoveRecorder^ _DomainEventRemoveRecorder = gcnew DomainEventRemoveRecorder(this,
						&DomainWrapper::RemoveRecorderEvent);
					gc_DomainEventRemoveRecorder = GCHandle::Alloc(_DomainEventRemoveRecorder);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveRecorder);
					_Domain->_DomainEvent_RemoveRecorder = static_cast<DomainEvent_RemoveRecorder>(ip.ToPointer());

					// add nl
					DomainEventAddNodalLoad^ _DomainEventAddNodalLoad = gcnew DomainEventAddNodalLoad(this,
						&DomainWrapper::AddNodalLoadEvent);
					gc_DomainEventAddNodalLoad = GCHandle::Alloc(_DomainEventAddNodalLoad);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddNodalLoad);
					_Domain->_DomainEvent_AddNodalLoad = static_cast<DomainEvent_AddNodalLoad>(ip.ToPointer());

					// remove nl
					DomainEventRemoveNodalLoad^ _DomainEventRemoveNodalLoad = gcnew DomainEventRemoveNodalLoad(this,
						&DomainWrapper::RemoveNodalLoadEvent);
					gc_DomainEventRemoveNodalLoad = GCHandle::Alloc(_DomainEventRemoveNodalLoad);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveNodalLoad);
					_Domain->_DomainEvent_RemoveNodalLoad = static_cast<DomainEvent_RemoveNodalLoad>(ip.ToPointer());

					// add el
					DomainEventAddElementalLoad^ _DomainEventAddElementalLoad = gcnew DomainEventAddElementalLoad(this,
						&DomainWrapper::AddElementalLoadEvent);
					gc_DomainEventAddElementalLoad = GCHandle::Alloc(_DomainEventAddElementalLoad);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddElementalLoad);
					_Domain->_DomainEvent_AddElementalLoad = static_cast<DomainEvent_AddElementalLoad>(ip.ToPointer());

					// remove el
					DomainEventRemoveElementalLoad^ _DomainEventRemoveElementalLoad = gcnew DomainEventRemoveElementalLoad(this,
						&DomainWrapper::RemoveElementalLoadEvent);
					gc_DomainEventRemoveElementalLoad = GCHandle::Alloc(_DomainEventRemoveElementalLoad);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveElementalLoad);
					_Domain->_DomainEvent_RemoveElementalLoad = static_cast<DomainEvent_RemoveElementalLoad>(ip.ToPointer());


					// add sp
					DomainEventAddSP_Constraint^ _DomainEventAddSP_Constraint = gcnew DomainEventAddSP_Constraint(this,
						&DomainWrapper::AddSP_ConstraintEvent);
					gc_DomainEventAddSP_Constraint = GCHandle::Alloc(_DomainEventAddSP_Constraint);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventAddSP_Constraint);
					_Domain->_DomainEvent_AddSP_Constraint = static_cast<DomainEvent_AddSP_Constraint>(ip.ToPointer());

					// remove sp
					DomainEventRemoveSP_Constraint^ _DomainEventRemoveSP_Constraint = gcnew DomainEventRemoveSP_Constraint(this,
						&DomainWrapper::RemoveSP_ConstraintEvent);
					gc_DomainEventRemoveSP_Constraint = GCHandle::Alloc(_DomainEventRemoveSP_Constraint);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventRemoveSP_Constraint);
					_Domain->_DomainEvent_RemoveSP_Constraint = static_cast<DomainEvent_RemoveSP_Constraint>(ip.ToPointer());


					// clear all
					DomainEventClearAll^ _DomainEventClearAll = gcnew DomainEventClearAll(this, &DomainWrapper::ClearAllEvent);
					gc_DomainEventClearAll = GCHandle::Alloc(_DomainEventClearAll);
					ip = Marshal::GetFunctionPointerForDelegate(_DomainEventClearAll);
					_Domain->_DomainEvent_ClearAll = static_cast<DomainEvent_ClearAll>(ip.ToPointer());
				}
			}

			GCHandle gc_DomainEventAddNode;
			GCHandle gc_DomainEventRemoveNode;
			GCHandle gc_DomainEventAddElement;
			GCHandle gc_DomainEventRemoveElement;
			GCHandle gc_DomainEventAddSP;
			GCHandle gc_DomainEventRemoveSP;
			GCHandle gc_DomainEventAddMP;
			GCHandle gc_DomainEventRemoveMP;
			GCHandle gc_DomainEventAddLoadPattern;
			GCHandle gc_DomainEventRemoveLoadPattern;
			GCHandle gc_DomainEventAddRecorder;
			GCHandle gc_DomainEventRemoveRecorder;
			GCHandle gc_DomainEventAddNodalLoad;
			GCHandle gc_DomainEventRemoveNodalLoad;
			GCHandle gc_DomainEventAddElementalLoad;
			GCHandle gc_DomainEventRemoveElementalLoad;
			GCHandle gc_DomainEventAddSP_Constraint;
			GCHandle gc_DomainEventRemoveSP_Constraint;
			GCHandle gc_DomainEventClearAll;
		};
	}
}
#endif