// Copyright 2018 Adam Brząkała

#pragma once

#include "EngineMinimal.h"
#include "Components/WidgetComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveItem.generated.h"

UCLASS()
class HORRORGAME_API AInteractiveItem : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere) USceneComponent *itemRoot;
	UPROPERTY(EditAnywhere) UStaticMeshComponent *itemMesh;
	UPROPERTY(EditAnywhere) UWidgetComponent *tooltipWidget;

	UPROPERTY(EditAnywhere, Category = "Interactive") bool bCanInteract;
	UPROPERTY(EditAnywhere, Category = "Interactive") bool bShowTooltip;
	UPROPERTY(EditAnywhere, Category = "Interactive") bool bUseHighlighting;

public:	
	AInteractiveItem();

	void interact(AActor *other);
	void OnStartPointingAt();
	void OnEndPointingAt();

protected:
	virtual void interactFunction(AActor *other) PURE_VIRTUAL(AInteractiveItem::interact, );

private:
	void highlight();
	void stopHighlighting();

	void showTooltip();
	void removeTooltip();
};
