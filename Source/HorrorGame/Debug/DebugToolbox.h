// Copyright 2018 Adam Brzakala

#pragma once

#ifdef UE_BUILD_DEVELOPMENT

#include "EngineMinimal.h"
#include "CoreMinimal.h"

#endif

inline void PRINT(const FString &msg, float time = 3.0f)
{
#ifdef UE_BUILD_DEVELOPMENT
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, time, FColor::Red, msg);
	}
#endif
}

inline void PRINT(const float &number, float time = 3.0f)
{
#ifdef UE_BUILD_DEVELOPMENT
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, time, FColor::Red, FString::SanitizeFloat(number));
	}
#endif
}
