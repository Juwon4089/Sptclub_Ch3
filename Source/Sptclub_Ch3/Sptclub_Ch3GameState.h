#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Sptclub_Ch3GameState.generated.h"

UCLASS()
class ASptclub_Ch3GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASptclub_Ch3GameState();

	UFUNCTION(BlueprintPure)
	int32 GetScore() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentWave() const;

	UFUNCTION(BlueprintPure)
	float GetTimeRemaining() const;

	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void SetCurrentWave(int32 NewWave);

	UFUNCTION(BlueprintCallable)
	void SetTimeRemaining(float NewTime);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentWave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeRemaining;
};
