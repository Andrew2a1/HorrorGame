#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "DoorSettings.generated.h"

constexpr float MaxDoorRotationDelta = 3.0f;
constexpr float DefaultOpenDoorTimeSec = 1.0f;
constexpr float DefaultOpenDoorRotation = 100.0f;

UENUM(BlueprintType)
enum class DoorOpenDirection : uint8
{
	Inside,
	Outside
};