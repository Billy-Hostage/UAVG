//NTRHostage

#pragma once

#include "Layout/ArrangedWidget.h"
#include "Widgets/SWidget.h"
#include "ConnectionDrawingPolicy.h"

class FUAVGScriptGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy
{
public:
	FUAVGScriptGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj);

	// FConnectionDrawingPolicy interface
	/** Determine how the wires looks */
	void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, /*inout*/ FConnectionParams& Params) override;

	/** Determinte to what geometries the wires are connected. */
	void DetermineLinkGeometry(FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget,
		UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
		/*out*/ FArrangedWidget*& StartWidgetGeometry, /*out*/ FArrangedWidget*& EndWidgetGeometry) override;

	/** How should we draw the spline and arrow arrow? */
	void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params) override;
	void DrawSplineWithArrow(const FVector2D& StartPoint, const FVector2D& EndPoint, const FConnectionParams& Params) override;

	/** The method that actually draws the spline */
	void DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params) override;

	/** Sometimes the panel draws a preview connector; e.g. when the user is connecting pins */
	void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint, const FVector2D& EndPoint, UEdGraphPin* Pin) override;

	/** Compute the tangent of the spline. */
	FVector2D ComputeSplineTangent(const FVector2D& Start, const FVector2D& End) const override;

	/** Draws the wire */
	void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& PinGeometries, FArrangedChildren& ArrangedNodes) override;

	// End of FConnectionDrawingPolicy interface

protected:
	UEdGraph* Graph;

	TMap<UEdGraphNode*, int32> NodeWidgetMap;

	void Internal_DrawLineWithArrow(const FVector2D& StartAnchorPoint, const FVector2D& EndAnchorPoint, const FConnectionParams& Params);
};