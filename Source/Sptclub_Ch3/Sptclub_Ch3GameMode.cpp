#include "Sptclub_Ch3GameMode.h"
#include "Sptclub_Ch3Character.h"
#include "Sptclub_Ch3GameState.h"
#include "SpawnVolume.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ASptclub_Ch3GameMode::ASptclub_Ch3GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = ASptclub_Ch3GameState::StaticClass();

	CurrentWaveIndex = 0;
	SpawnedCountThisWave = 0;
	CurrentWaveTimeRemaining = 0.0f;
}

void ASptclub_Ch3GameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for (int32 i = 0; i < FoundVolumes.Num(); i++)
	{
		ASpawnVolume* Volume = Cast<ASpawnVolume>(FoundVolumes[i]);

		if (Volume != nullptr)
		{
			SpawnVolumes.Add(Volume);
		}
	}

	CurrentWaveIndex = 0;
	StartWave();
}

void ASptclub_Ch3GameMode::StartWave()
{
	if (Waves.IsValidIndex(CurrentWaveIndex))
	{
		SpawnedCountThisWave = 0;
		CurrentWaveTimeRemaining = Waves[CurrentWaveIndex].WaveTime;

		FString Message = FString::Printf(TEXT("Wave %d 시작!"), CurrentWaveIndex + 1);
		UE_LOG(LogTemp, Log, TEXT("%s"), *Message);

		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Message);
		}

		ASptclub_Ch3GameState* MyGameState = Cast<ASptclub_Ch3GameState>(GameState);
		if (MyGameState != nullptr)
		{
			MyGameState->SetCurrentWave(CurrentWaveIndex + 1);
			MyGameState->SetTimeRemaining(CurrentWaveTimeRemaining);
		}

		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASptclub_Ch3GameMode::SpawnItem, Waves[CurrentWaveIndex].SpawnInterval, true);
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ASptclub_Ch3GameMode::UpdateCountdown, 1.0f, true);
	}
	else
	{
		if (NextLevelName != NAME_None)
		{
			UGameplayStatics::OpenLevel(this, NextLevelName);
		}
		else
		{
			if (GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("게임 클리어!"));
			}
		}
	}
}

void ASptclub_Ch3GameMode::SpawnItem()
{
	if (SpawnVolumes.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, SpawnVolumes.Num() - 1);
		ASpawnVolume* SelectedVolume = SpawnVolumes[RandomIndex];

		if (SelectedVolume != nullptr)
		{
			SelectedVolume->SpawnItem();
		}
	}

	SpawnedCountThisWave = SpawnedCountThisWave + 1;

	if (SpawnedCountThisWave >= Waves[CurrentWaveIndex].SpawnCount)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void ASptclub_Ch3GameMode::UpdateCountdown()
{
	CurrentWaveTimeRemaining = CurrentWaveTimeRemaining - 1.0f;

	ASptclub_Ch3GameState* MyGameState = Cast<ASptclub_Ch3GameState>(GameState);
	if (MyGameState != nullptr)
	{
		MyGameState->SetTimeRemaining(CurrentWaveTimeRemaining);
	}

	if (CurrentWaveTimeRemaining <= 0.0f)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		EndWave();
	}
}

void ASptclub_Ch3GameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

	CurrentWaveIndex = CurrentWaveIndex + 1;
	StartWave();
}
