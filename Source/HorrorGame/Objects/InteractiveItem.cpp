// Copyright 2018 Adam Brząkała

#include "InteractiveItem.h"

AInteractiveItem::AInteractiveItem() :
	bCanInteract(true),
	bShowTooltip(true),
	bUseHighlighting(true)
{
	PrimaryActorTick.bCanEverTick = false;

	itemRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ItemRoot"));
	RootComponent = itemRoot;

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	itemMesh->SetupAttachment(itemRoot);
	itemMesh->SetRenderCustomDepth(false);
}

void AInteractiveItem::BeginPlay()
{
	Super::BeginPlay();

	if (InventoryUIClass && !InventoryWidget)
	{
		InventoryWidget = CreateWidget<UUserWidget>(this, InventoryUIClass);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AInteractiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractiveItem::interact(AActor *other)
{
	if (bCanInteract)
		interactFunction(other);
}

void AInteractiveItem::OnStartPointingAt()
{
	if (bUseHighlighting)
		highlight();

	if (bShowTooltip)
		showTooltip();
}

void AInteractiveItem::OnEndPointingAt()
{
	stopHighlighting();
	removeTooltip();
}

void AInteractiveItem::highlight()
{
	itemMesh->SetRenderCustomDepth(bUseHighlighting);
}

void AInteractiveItem::stopHighlighting()
{
	itemMesh->SetRenderCustomDepth(false);
}