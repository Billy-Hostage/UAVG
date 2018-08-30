//NTRHostage

#include "EdGraph_UAVGScript.h"
#include "UAVGScript.h"

UEdGraph_UAVGScript::UEdGraph_UAVGScript()
{

}

UEdGraph_UAVGScript::~UEdGraph_UAVGScript()
{

}

bool UEdGraph_UAVGScript::Modify(bool bAlwaysMarkDirty /*= true*/)
{
	if (!CanModify())
	{
		return false;
	}

	bool bWasSaved = Super::Modify(bAlwaysMarkDirty);
	//TODO Here
	return bWasSaved;
}

UUAVGScript* UEdGraph_UAVGScript::GetUAVGScript() const
{
	return CastChecked<UUAVGScript>(GetOuter());
}
