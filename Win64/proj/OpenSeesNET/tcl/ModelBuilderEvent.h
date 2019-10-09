#ifndef ModelBuilder_H
#define ModelBuilder_H
#pragma once

#include <UniaxialMaterial.h>
#include <SectionForceDeformation.h>
#include <NDMaterial.h>

#include "../materials/uniaxial/UniaxialMaterialWrapper.h"
#include "../materials/section/SectionForceDeformationWrapper.h"
#include "../materials/ndmaterial/NDMaterialWrapper.h"

using namespace System;
using namespace OpenSees::Materials::NDMaterials;
using namespace OpenSees::Materials::Sections;
using namespace OpenSees::Materials::Uniaxials;

namespace OpenSees {
	namespace Tcl {
		namespace ModelBuilder {
			public ref class ModelBuilderAddUniaxialMaterialArgs : EventArgs
			{
			public:
				ModelBuilderAddUniaxialMaterialArgs(UniaxialMaterialWrapper^ theMaterial) :EventArgs() {
					this->theMaterial = theMaterial;
				};
				~ModelBuilderAddUniaxialMaterialArgs() {};
				UniaxialMaterialWrapper^ theMaterial;
			internal:

			private:
			};

			public ref class ModelBuilderRemoveUniaxialMaterialArgs : EventArgs
			{
			public:
				ModelBuilderRemoveUniaxialMaterialArgs(int tag) :EventArgs() {
					this->tag = tag;
				};
				~ModelBuilderRemoveUniaxialMaterialArgs() {};
				int tag;
			internal:

			private:
			};

			public ref class ModelBuilderClearAllUniaxialMaterialArgs : EventArgs
			{
			public:
				ModelBuilderClearAllUniaxialMaterialArgs() :EventArgs() {
				};
				~ModelBuilderClearAllUniaxialMaterialArgs() {};
			internal:

			private:
			};

			public ref class ModelBuilderAddSectionArgs : EventArgs
			{
			public:
				ModelBuilderAddSectionArgs(SectionForceDeformationWrapper^ theSection) :EventArgs() {
					this->theSection = theSection;
				};
				~ModelBuilderAddSectionArgs() {};
				SectionForceDeformationWrapper^ theSection;
			internal:

			private:
			};

			public ref class ModelBuilderRemoveSectionArgs : EventArgs
			{
			public:
				ModelBuilderRemoveSectionArgs(int tag) :EventArgs() {
					this->tag = tag;
				};
				~ModelBuilderRemoveSectionArgs() {};
				int tag;
			internal:

			private:
			};

			public ref class ModelBuilderClearAllSectionArgs : EventArgs
			{
			public:
				ModelBuilderClearAllSectionArgs() :EventArgs() {
				};
				~ModelBuilderClearAllSectionArgs() {};
			internal:

			private:
			};

			public ref class ModelBuilderAddNDMaterialArgs : EventArgs
			{
			public:
				ModelBuilderAddNDMaterialArgs(NDMaterialWrapper^ theNDMaterial) :EventArgs() {
					this->theNDMaterial = theNDMaterial;
				};
				~ModelBuilderAddNDMaterialArgs() {};
				NDMaterialWrapper^ theNDMaterial;
			internal:

			private:
			};

			public ref class ModelBuilderRemoveNDMaterialArgs : EventArgs
			{
			public:
				ModelBuilderRemoveNDMaterialArgs(int tag) :EventArgs() {
					this->tag = tag;
				};
				~ModelBuilderRemoveNDMaterialArgs() {};
				int tag;
			internal:

			private:
			};

			public ref class ModelBuilderClearAllNDMaterialArgs : EventArgs
			{
			public:
				ModelBuilderClearAllNDMaterialArgs() :EventArgs() {
				};
				~ModelBuilderClearAllNDMaterialArgs() {};
			internal:

			private:
			};
		}
	}
}
#endif