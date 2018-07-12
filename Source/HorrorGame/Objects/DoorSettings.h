#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "DoorSettings.generated.h"

constexpr float MAX_DOOR_ROTATION_DELTA = 3.0f;
constexpr float DEFAULT_OPEN_DOOR_TIME = 1.0f;
constexpr float DEFAULT_OPEN_DOOR_ROTATION = 100.0f;

UENUM(BlueprintType)
enum class DoorOpenDirection : uint8
{
	Inside,
	Outside
};