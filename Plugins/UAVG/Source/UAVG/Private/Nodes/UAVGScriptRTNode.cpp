//NTRHostage

#include "UAVGScriptRTNode.h"

UUAVGScriptRuntimeNode::UUAVGScriptRuntimeNode()
{

}

bool UUAVGScriptRuntimeNode::CheckNodeCanBePaentOrChild(UUAVGScriptRuntimeNode* InNode) const
{
	if (InNode == this || InNode == nullptr) return false;//TODO Error Message
	return true;
}

void UUAVGScriptRuntimeNode::SetChild(TArray<UUAVGScriptRuntimeNode*> InChildNodes)
{
	for (auto Node : InChildNodes)
	{
		if (!CheckNodeCanBePaentOrChild(Node)) return;
	}
	MyChildNodes = InChildNodes;
}

void UUAVGScriptRuntimeNode::SetParent(TArray<UUAVGScriptRuntimeNode*> InParentNodes)
{
	for (auto Node : InParentNodes)
	{
		if (!CheckNodeCanBePaentOrChild(Node)) return;
	}
	MyParentNodes = InParentNodes;
}
