#pragma once

#include "CoreMinimal.h"
#include "ItemDescriptor.generated.h"

USTRUCT()
struct FItemDescriptor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) FName ID;
	UPROPERTY(EditAnywhere) FText name;
	UPROPERTY(EditAnywhere) FText description;
};