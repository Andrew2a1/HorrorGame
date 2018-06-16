// Copyright 2018 Adam Brzakala

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

	tooltipWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Tooltip"));
	tooltipWidget->SetupAttachment(itemMesh);
	tooltipWidget->SetVisibility(false);
}

void AInteractiveItem::interact(AActor *other)
{
	if (bCanInteract)
		interactFunction(other);
}

void AInteractiveItem::OnStartPointingAt()
{
	if (bUseHighlighting && itemMesh)
		highlight();

	if (bShowTooltip && tooltipWidget)
		showTooltip();
}

void AInteractiveItem::OnEndPointingAt()
{
	if(itemMesh)
		stopHighlighting();

	if(bShowTooltip)
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

void AInteractiveItem::showTooltip()
{
	tooltipWidget->SetVisibility(bShowTooltip);
}

void AInteractiveItem::removeTooltip()
{
	tooltipWidget->SetVisibility(false);
}