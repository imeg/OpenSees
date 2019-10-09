
#ifndef ModelBuilderNDMaterialEventHandler_H
#define ModelBuilderNDMaterialEventHandler_H
#include <TaggedObject.h>
typedef int(__stdcall* ModelBuilder_AddNDMaterial) (TaggedObject* theMaterial);
typedef int(__stdcall* ModelBuilder_RemoveNDMaterial) (int tag);
typedef int(__stdcall* ModelBuilder_ClearAllNDMaterial) ();
class ModelBuilderNDMaterialEventHandler {
public:
	ModelBuilderNDMaterialEventHandler();
	~ModelBuilderNDMaterialEventHandler();

	ModelBuilder_AddNDMaterial _ModelBuilder_AddNDMaterial;
	ModelBuilder_RemoveNDMaterial _ModelBuilder_RemoveNDMaterial;
	ModelBuilder_ClearAllNDMaterial _ModelBuilder_ClearAllNDMaterial;

};
#endif
