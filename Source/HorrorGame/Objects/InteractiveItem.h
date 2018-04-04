// Copyright 2018 Adam Brząkała

#pragma once

#include "EngineMinimal.h"
#include "UserWidget.h"

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

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> InventoryUIClass;
	UPROPERTY(EditAnywhere) UUserWidget *InventoryWidget;

	UPROPERTY(EditAnywhere) bool bCanInteract;
	UPROPERTY(EditAnywhere) bool bShowTooltip;
	UPROPERTY(EditAnywhere) bool bUseHighlighting;

public:	
	AInteractiveItem();
	virtual void Tick(float DeltaTime);

	void interact(AActor *other);
	void OnStartPointingAt();
	void OnEndPointingAt();

protected:
	virtual void BeginPlay() override;

	virtual void showTooltip() PURE_VIRTUAL(AInteractiveItem::showTooltip, );
	virtual void removeTooltip() PURE_VIRTUAL(AInteractiveItem::removeTooltip, );
	virtual void interactFunction(AActor *other) PURE_VIRTUAL(AInteractiveItem::interact, );

private:
	void highlight();
	void stopHighlighting();
	
};
