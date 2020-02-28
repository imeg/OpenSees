#pragma once
#include <LoadPattern.h>
#include <NodalLoadIter.h>
#include <SingleDomSP_Iter.h>
#include <ElementalLoadIter.h>
#include <EarthquakePattern.h>
#include <UniformExcitation.h>
#include <FireLoadPattern.h>
#include <MultiSupportPattern.h>
#include <PeerNGAMotion.h>

#include "../components/DomainComponentWrapper.h"
#include "../constraints/ConstraintWrapper.h"
#include "../loads/LoadWrapper.h"
#include "../timeSeries/TimeSeriesWrapper.h"
#include "../groundmotion/GroudMotionWrapper.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace OpenSees::Components::GroundMotions;
using namespace OpenSees::Components::Loads;
using namespace OpenSees::Components::Constraints;
using namespace OpenSees::Components::Timeseries;

namespace OpenSees {
	namespace Components {
		namespace LoadPatterns {
			public ref class LoadPatternWrapper : DomainComponentWrapper
			{
			public:
				LoadPatternWrapper();
				LoadPatternWrapper(int tag);
				void SetTimeSeries(TimeSeriesWrapper^ timeSeries);

				TimeSeriesWrapper^ GetTimeSeries() {
					TimeSeries* ts = _LoadPattern->getTimeSeries();
					if (ts == 0) return nullptr;
					TimeSeriesWrapper^ tsw = gcnew TimeSeriesWrapper(ts);
					return tsw;
				}

				int^ AddMotion(GroundMotionWrapper^ theMotion, int tag) {
					return _LoadPattern->addMotion(*theMotion->_GroundMotion, tag);
				};

				virtual int GetTag() override {
					return _LoadPattern->getTag();
				}

				List<NodalLoadWrapper^>^ GetNodalLoads() {
					NodalLoadIter nlIter = _LoadPattern->getNodalLoads();
					List<NodalLoadWrapper^>^ _nls = gcnew List<NodalLoadWrapper^>();
					NodalLoadWrapper^ wret = gcnew NodalLoadWrapper();
					NodalLoad* nodalload = 0;
					int counter = 0;
					while ((nodalload = nlIter()) != 0)
					{
						NodalLoadWrapper^ nodew = gcnew NodalLoadWrapper();
						nodew->_NodalLoad = nodalload;
						nodew->_TaggedObject = nodalload;
						_nls->Add(nodew);
					}
					return _nls;
				}

				List<SP_ConstraintWrapper^>^ GetSPs() {
					SingleDomSP_Iter spIter = (SingleDomSP_Iter&)_LoadPattern->getSPs();
					List<SP_ConstraintWrapper^>^ _nls = gcnew List<SP_ConstraintWrapper^>();
					SP_Constraint* sp = 0;
					int counter = 0;
					while ((sp = spIter()) != 0)
					{
						SP_ConstraintWrapper^ nodew = gcnew SP_ConstraintWrapper(sp);
						_nls->Add(nodew);
					}
					return _nls;
				}

				List<ElementalLoadWrapper^>^ GetElementalLoads() {
					ElementalLoadIter nlIter = _LoadPattern->getElementalLoads();
					List<ElementalLoadWrapper^>^ _nls = gcnew List<ElementalLoadWrapper^>();
					ElementalLoadWrapper^ wret = gcnew ElementalLoadWrapper();
					ElementalLoad* nodalload = 0;
					int counter = 0;
					while ((nodalload = nlIter()) != 0)
					{
						ElementalLoadWrapper^ nodew = gcnew ElementalLoadWrapper();
						nodew->_ElementalLoad = nodalload;
						nodew->_TaggedObject = nodalload;
						_nls->Add(nodew);
					}
					return _nls;
				}

				NodalLoadWrapper^ RemoveNodalLoad(int tag) {
					NodalLoad* ret = _LoadPattern->removeNodalLoad(tag);
					if (ret == 0) return nullptr;
					NodalLoadWrapper^ wret = gcnew NodalLoadWrapper();
					wret->_NodalLoad = ret;
					wret->_TaggedObject = ret;
					return wret;
				}

				ElementalLoadWrapper^ RemoveElementalLoad(int tag) {
					ElementalLoad* ret = _LoadPattern->removeElementalLoad(tag);
					if (ret == 0) return nullptr;
					ElementalLoadWrapper^ wret = gcnew ElementalLoadWrapper();
					wret->_ElementalLoad = ret;
					wret->_TaggedObject = ret;
					return wret;
				}

				SP_ConstraintWrapper^ RemoveSP_Constraint(int tag) {
					SP_Constraint* ret = _LoadPattern->removeSP_Constraint(tag);
					if (ret == 0) return nullptr;
					SP_ConstraintWrapper^ wret = gcnew SP_ConstraintWrapper(ret);
					return wret;
				}

				double GetLoadFactor() {
					return _LoadPattern->getLoadFactor();
				}

				void ClearAll() {
					_LoadPattern->clearAll();
				}

				~LoadPatternWrapper() {
					if (_LoadPattern != 0)
						delete _LoadPattern;
				};
				
			internal:
				LoadPatternWrapper(LoadPattern* lp) {
					this->_LoadPattern = lp;
					this->_TaggedObject = lp;
				};
				LoadPattern * _LoadPattern;
			};

			public ref class EarthquakePatternWrapper abstract : LoadPatternWrapper
			{
			public:
				EarthquakePatternWrapper(int tag);
				~EarthquakePatternWrapper() {
					if (_LoadPattern != 0)
						delete _LoadPattern;
				};
			internal:

			};

			public ref class UniformExcitationWrapper : EarthquakePatternWrapper
			{
			public:
				UniformExcitationWrapper(int tag, GroundMotionWrapper^ groudMotion,
					int dof, double vel0, double fact);
				~UniformExcitationWrapper() {
					if (_LoadPattern != 0)
						delete _LoadPattern;
				};
			internal:

			};

			public ref class FireLoadPatternWrapper : LoadPatternWrapper
			{
			public:
				FireLoadPatternWrapper(int tag);
				void SetFireTimeSeries(TimeSeriesWrapper^ theSeries1, TimeSeriesWrapper^ theSeries2,
					TimeSeriesWrapper^ theSeries3, TimeSeriesWrapper^ theSeries4, TimeSeriesWrapper^ theSeries5,
					TimeSeriesWrapper^ theSeries6, TimeSeriesWrapper^ theSeries7, TimeSeriesWrapper^ theSeries8, TimeSeriesWrapper^ theSeries9);
				~FireLoadPatternWrapper() {
					if (_LoadPattern != 0)
						delete _LoadPattern;
				};
			internal:

			};

			public ref class MultiSupportPatternWrapper : LoadPatternWrapper
			{
			public:
				MultiSupportPatternWrapper(int tag);
				
				~MultiSupportPatternWrapper() {
					if (_LoadPattern != 0)
						delete _LoadPattern;
				};
			internal:

			};
		}
	}
}
