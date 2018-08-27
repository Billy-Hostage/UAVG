// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUAVGEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
	void RegisterAssetTypeActions(class IAssetTools& AssetTools, TSharedRef<class IAssetTypeActions> Action);

	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
