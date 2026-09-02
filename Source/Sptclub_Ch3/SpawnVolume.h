#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ASpawnVolume();

	void SpawnItem();

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* WhereToSpawn;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> ItemsToSpawn;

	FVector GetRandomPointInVolume() const;
};
