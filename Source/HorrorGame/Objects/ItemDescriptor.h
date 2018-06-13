#pragma once

#include "CoreMinimal.h"
#include "ItemDescriptor.generated.h"

USTRUCT(BlueprintType)
struct FItemDescriptor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText description;
};