#ifndef DomainEvent_H
#define DomainEvent_H
#pragma once
#include "../nodes/NodeWrapper.h"

using namespace System;
using namespace OpenSees::Components;

namespace OpenSees {
	namespace Components {
		
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
	}
}
#endif