
#ifndef ModelBuilderSectionEventHandler_H
#define ModelBuilderSectionEventHandler_H
#include <TaggedObject.h>
typedef int(__stdcall* ModelBuilder_AddSection) (TaggedObject* theMaterial);
typedef int(__stdcall* ModelBuilder_RemoveSection) (int tag);
typedef int(__stdcall* ModelBuilder_ClearAllSection) ();
class ModelBuilderSectionEventHandler {
public:
	ModelBuilderSectionEventHandler();
	~ModelBuilderSectionEventHandler();

	ModelBuilder_AddSection _ModelBuilder_AddSection;
	ModelBuilder_RemoveSection _ModelBuilder_RemoveSection;
	ModelBuilder_ClearAllSection _ModelBuilder_ClearAllSection;

};
#endif
