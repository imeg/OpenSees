
#ifndef ModelBuilderUniaxialMaterialEventHandler_H
#define ModelBuilderUniaxialMaterialEventHandler_H
#include <TaggedObject.h>
typedef int(__stdcall* ModelBuilder_AddUniaxialMaterial) (TaggedObject* theMaterial);
typedef int(__stdcall* ModelBuilder_RemoveUniaxialMaterial) (int tag);
typedef int(__stdcall* ModelBuilder_ClearAllUniaxialMaterial) ();
class ModelBuilderUniaxialMaterialEventHandler {
public:
	ModelBuilderUniaxialMaterialEventHandler();
	~ModelBuilderUniaxialMaterialEventHandler();

	ModelBuilder_AddUniaxialMaterial _ModelBuilder_AddUniaxialMaterial;
	ModelBuilder_RemoveUniaxialMaterial _ModelBuilder_RemoveUniaxialMaterial;
	ModelBuilder_ClearAllUniaxialMaterial _ModelBuilder_ClearAllUniaxialMaterial;

};
#endif
