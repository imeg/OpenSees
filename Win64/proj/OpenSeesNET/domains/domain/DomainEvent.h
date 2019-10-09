#ifndef DomainEvent_H
#define DomainEvent_H
#pragma once
#include "../nodes/NodeWrapper.h"
#include "../../elements/ElementWrapper.h"
#include "../constraints/ConstraintWrapper.h"
#include "../patterns/LoadPatternWrapper.h"
#include "../../recorders/RecorderWrapper.h"

using namespace System;
using namespace OpenSees::Components;
using namespace OpenSees::Components::Constraints;
using namespace OpenSees::Components::LoadPatterns;
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
				this->sp = sp;
			};
			~DomainAddSPEventArgs() {};
			SP_ConstraintWrapper^ sp;
		internal:

		private:
		};

		public ref class DomainRemoveSPEventArgs : EventArgs
		{

		public:
			DomainRemoveSPEventArgs(SP_ConstraintWrapper^ sp) :EventArgs() {
				this->sp = sp;
			};
			~DomainRemoveSPEventArgs() {};
			SP_ConstraintWrapper^ sp;
		internal:

		private:
		};

		public ref class DomainAddMPEventArgs : EventArgs
		{

		public:
			DomainAddMPEventArgs(MP_ConstraintWrapper^ sp) :EventArgs() {
				this->mp = mp;
			};
			~DomainAddMPEventArgs() {};
			MP_ConstraintWrapper^ mp;
		internal:

		private:
		};

		public ref class DomainRemoveMPEventArgs : EventArgs
		{

		public:
			DomainRemoveMPEventArgs(MP_ConstraintWrapper^ mp) :EventArgs() {
				this->mp = mp;
			};
			~DomainRemoveMPEventArgs() {};
			MP_ConstraintWrapper^ mp;
		internal:

		private:
		};

		public ref class DomainAddLoadPatternEventArgs : EventArgs
		{

		public:
			DomainAddLoadPatternEventArgs(LoadPatternWrapper^ sp) :EventArgs() {
				this->mp = mp;
			};
			~DomainAddLoadPatternEventArgs() {};
			LoadPatternWrapper^ mp;
		internal:

		private:
		};

		public ref class DomainRemoveLoadPatternEventArgs : EventArgs
		{

		public:
			DomainRemoveLoadPatternEventArgs(LoadPatternWrapper^ mp) :EventArgs() {
				this->mp = mp;
			};
			~DomainRemoveLoadPatternEventArgs() {};
			LoadPatternWrapper^ mp;
		internal:

		private:
		};

		public ref class DomainAddRecorderEventArgs : EventArgs
		{

		public:
			DomainAddRecorderEventArgs(RecorderWrapper^ rec) :EventArgs() {
				this->rec = rec;
			};
			~DomainAddRecorderEventArgs() {};
			RecorderWrapper^ rec;
		internal:

		private:
		};

		public ref class DomainRemoveRecorderEventArgs : EventArgs
		{

		public:
			DomainRemoveRecorderEventArgs(RecorderWrapper^ rec) :EventArgs() {
				this->rec = rec;
			};
			~DomainRemoveRecorderEventArgs() {};
			RecorderWrapper^ rec;
		internal:

		private:
		};
	}
}
#endif