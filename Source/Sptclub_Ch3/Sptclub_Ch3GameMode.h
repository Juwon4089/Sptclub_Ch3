#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sptclub_Ch3GameMode.generated.h"

class ASpawnVolume;

USTRUCT(BlueprintType)
struct FWaveInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float WaveTime = 20.0f;

	UPROPERTY(EditAnywhere)
	int32 SpawnCount = 5;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 2.0f;
};

UCLASS(minimalapi)
class ASptclub_Ch3GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASptclub_Ch3GameMode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<FWaveInfo> Waves;

	UPROPERTY(EditAnywhere)
	FName NextLevelName;

	int32 CurrentWaveIndex;
	int32 SpawnedCountThisWave;
	float CurrentWaveTimeRemaining;

	TArray<ASpawnVolume*> SpawnVolumes;

	FTimerHandle SpawnTimerHandle;
	FTimerHandle CountdownTimerHandle;

	void StartWave();
	void SpawnItem();
	void UpdateCountdown();
	void EndWave();
};
