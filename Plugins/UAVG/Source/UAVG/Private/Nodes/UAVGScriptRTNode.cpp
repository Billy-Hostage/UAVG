//NTRHostage

#include "UAVGScriptRTNode.h"

UUAVGScriptRuntimeNode::UUAVGScriptRuntimeNode()
{

}

UUAVGScriptRuntimeNode* UUAVGScriptRuntimeNode::GetNextNode()
{
	if (MyChildNodes.Num() <= 0)
		return nullptr;

	return MyChildNodes[0];
}

bool UUAVGScriptRuntimeNode::CheckNodeCanBePaentOrChild(UUAVGScriptRuntimeNode* InNode) const
{
	if (InNode == this || InNode == nullptr) return false;//TODO Error Message
	return true;
}

bool UUAVGScriptRuntimeNode::SetChild(TArray<UUAVGScriptRuntimeNode*> InChildNodes)
{
	for (auto Node : InChildNodes)
	{
		if (!CheckNodeCanBePaentOrChild(Node)) return false;//Failed
	}
	MyChildNodes = InChildNodes;
	return true;
}

bool UUAVGScriptRuntimeNode::SetParent(TArray<UUAVGScriptRuntimeNode*> InParentNodes)
{
	for (auto Node : InParentNodes)
	{
		if (!CheckNodeCanBePaentOrChild(Node)) return false;//Falied
	}
	MyParentNodes = InParentNodes;
	return true;
}
