//NTRHostage

#include "EdGraph_UAVGScript.h"
#include "UAVGScript.h"

UEdGraph_UAVGScript::UEdGraph_UAVGScript()
{

}

UEdGraph_UAVGScript::~UEdGraph_UAVGScript()
{

}

UUAVGScript* UEdGraph_UAVGScript::GetUAVGScript() const
{
	return CastChecked<UUAVGScript>(GetOuter());
}
