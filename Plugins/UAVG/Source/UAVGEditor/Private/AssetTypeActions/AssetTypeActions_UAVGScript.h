//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class FAssetTypeActions_UAVGScript : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_UAVGScript(EAssetTypeCategories::Type InAssetCategory);

	// IAssetTypeActions interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
	// End of IAssetTypeActions interface
private:
	EAssetTypeCategories::Type MyAssetCategory;
};