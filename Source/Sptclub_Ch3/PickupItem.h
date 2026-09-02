#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class APickupItem : public AActor
{
	GENERATED_BODY()

public:
	APickupItem();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* OverlapVolume;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	bool bIsHealthPickup;

	UPROPERTY(EditAnywhere)
	float PickupAmount;
};
