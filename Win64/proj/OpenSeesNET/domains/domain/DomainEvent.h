#ifndef DomainEvent_H
#define DomainEvent_H
#pragma once
#include "../nodes/NodeWrapper.h"
#include "../../elements/ElementWrapper.h"
#include "../constraints/ConstraintWrapper.h"
#include "../loads/LoadWrapper.h"
#include "../patterns/LoadPatternWrapper.h"
#include "../../recorders/RecorderWrapper.h"

using namespace System;
using namespace OpenSees::Components;
using namespace OpenSees::Components::Constraints;
using namespace OpenSees::Components::LoadPatterns;
using namespace OpenSees::Components::Loads;
using namespace OpenSees::Elements;
using namespace OpenSees::Recorders;

namespace OpenSees {
	namespace Components {
		
		public ref class DomainClearAllArgs : EventArgs
		{

		public:
			DomainClearAllArgs() :EventArgs() {
				
			};
			~DomainClearAllArgs() {};
		internal:

		private:
		};

		public ref class DomainAddNodeEventArgs : EventArgs
		{
			
		public:
			DomainAddNodeEventArgs(NodeWrapper^ node) :EventArgs(){
				this->Node = node;
			};
			~DomainAddNodeEventArgs() {};
			NodeWrapper^ Node;
		internal:
			
		private:
		};

		public ref class DomainRemoveNodeEventArgs : EventArgs
		{

		public:
			DomainRemoveNodeEventArgs(NodeWrapper^ node) :EventArgs() {
				this->Node = node;
			};
			~DomainRemoveNodeEventArgs() {};
			NodeWrapper^ Node;
		internal:

		private:
		};

		public ref class DomainAddElementEventArgs : EventArgs
		{

		public:
			DomainAddElementEventArgs(ElementWrapper^ element) :EventArgs() {
				this->Element = element;
			};
			~DomainAddElementEventArgs() {};
			ElementWrapper^ Element;
		internal:

		private:
		};

		public ref class DomainRemoveElementEventArgs : EventArgs
		{

		public:
			DomainRemoveElementEventArgs(ElementWrapper^ element) :EventArgs() {
				this->Element = element;
			};
			~DomainRemoveElementEventArgs() {};
			ElementWrapper^ Element;
		internal:

		private:
		};

		public ref class DomainAddSPEventArgs : EventArgs
		{

		public:
			DomainAddSPEventArgs(SP_ConstraintWrapper^ sp) :EventArgs() {
				this->SPConstraint = sp;
			};
			~DomainAddSPEventArgs() {};
			SP_ConstraintWrapper^ SPConstraint;
		internal:

		private:
		};

		public ref class DomainRemoveSPEventArgs : EventArgs
		{

		public:
			DomainRemoveSPEventArgs(SP_ConstraintWrapper^ sp) :EventArgs() {
				this->SPConstraint = sp;
			};
			~DomainRemoveSPEventArgs() {};
			SP_ConstraintWrapper^ SPConstraint;
		internal:

		private:
		};

		public ref class DomainAddMPEventArgs : EventArgs
		{

		public:
			DomainAddMPEventArgs(MP_ConstraintWrapper^ mp) :EventArgs() {
				this->MPConstraint = mp;
			};
			~DomainAddMPEventArgs() {};
			MP_ConstraintWrapper^ MPConstraint;
		internal:

		private:
		};

		public ref class DomainRemoveMPEventArgs : EventArgs
		{

		public:
			DomainRemoveMPEventArgs(MP_ConstraintWrapper^ mp) :EventArgs() {
				this->MPConstraint = mp;
			};
			~DomainRemoveMPEventArgs() {};
			MP_ConstraintWrapper^ MPConstraint;
		internal:

		private:
		};

		public ref class DomainAddLoadPatternEventArgs : EventArgs
		{

		public:
			DomainAddLoadPatternEventArgs(LoadPatternWrapper^ lp) :EventArgs() {
				this->LoadPattern = lp;
			};
			~DomainAddLoadPatternEventArgs() {};
			LoadPatternWrapper^ LoadPattern;
		internal:

		private:
		};

		public ref class DomainRemoveLoadPatternEventArgs : EventArgs
		{

		public:
			DomainRemoveLoadPatternEventArgs(LoadPatternWrapper^ lp) :EventArgs() {
				this->LoadPattern = lp;
			};
			~DomainRemoveLoadPatternEventArgs() {};
			LoadPatternWrapper^ LoadPattern;
		internal:

		private:
		};

		public ref class DomainAddRecorderEventArgs : EventArgs
		{

		public:
			DomainAddRecorderEventArgs(RecorderWrapper^ rec) :EventArgs() {
				this->Recorder = rec;
			};
			~DomainAddRecorderEventArgs() {};
			RecorderWrapper^ Recorder;
		internal:

		private:
		};

		public ref class DomainRemoveRecorderEventArgs : EventArgs
		{

		public:
			DomainRemoveRecorderEventArgs(RecorderWrapper^ rec) :EventArgs() {
				this->Recorder = rec;
			};
			~DomainRemoveRecorderEventArgs() {};
			RecorderWrapper^ Recorder;
		internal:

		private:
		};

		public ref class DomainAddNodalLoadEventArgs : EventArgs
		{

		public:
			DomainAddNodalLoadEventArgs(NodalLoadWrapper^ obj, int pattern) :EventArgs() {
				this->NodalLoad = obj;
				this->Pattern = pattern;
			};
			~DomainAddNodalLoadEventArgs() {};
			NodalLoadWrapper^ NodalLoad;
			int Pattern;
		internal:

		private:
		};

		public ref class DomainRemoveNodalLoadEventArgs : EventArgs
		{

		public:
			DomainRemoveNodalLoadEventArgs(NodalLoadWrapper^ obj) :EventArgs() {
				this->NodalLoad = obj;
			};
			~DomainRemoveNodalLoadEventArgs() {};
			NodalLoadWrapper^ NodalLoad;
		internal:

		private:
		};

		public ref class DomainAddElementalLoadEventArgs : EventArgs
		{

		public:
			DomainAddElementalLoadEventArgs(ElementalLoadWrapper^ obj, int pattern) :EventArgs() {
				this->ElementalLoad = obj;
				this->Pattern = pattern;
			};
			~DomainAddElementalLoadEventArgs() {};
			ElementalLoadWrapper^ ElementalLoad;
			int Pattern;
		internal:

		private:
		};

		public ref class DomainRemoveElementalLoadEventArgs : EventArgs
		{

		public:
			DomainRemoveElementalLoadEventArgs(ElementalLoadWrapper^ obj) :EventArgs() {
				this->ElementalLoad = obj;
			};
			~DomainRemoveElementalLoadEventArgs() {};
			ElementalLoadWrapper^ ElementalLoad;
		internal:

		private:
		};

		public ref class DomainAddSP_ConstraintEventArgs : EventArgs
		{

		public:
			DomainAddSP_ConstraintEventArgs(SP_ConstraintWrapper^ obj, int pattern) :EventArgs() {
				this->SP_Constraint = obj;
				this->Pattern = pattern;
			};
			~DomainAddSP_ConstraintEventArgs() {};
			SP_ConstraintWrapper^ SP_Constraint;
			int Pattern;
		internal:

		private:
		};

		public ref class DomainRemoveSP_ConstraintEventArgs : EventArgs
		{

		public:
			DomainRemoveSP_ConstraintEventArgs(SP_ConstraintWrapper^ obj) :EventArgs() {
				this->SP_Constraint = obj;
			};
			~DomainRemoveSP_ConstraintEventArgs() {};
			SP_ConstraintWrapper^ SP_Constraint;
		internal:

		private:
		};
	}
}
#endif