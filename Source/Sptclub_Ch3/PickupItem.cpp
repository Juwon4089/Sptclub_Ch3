#include "PickupItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Sptclub_Ch3Character.h"
#include "Sptclub_Ch3GameState.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	RootComponent = OverlapVolume;
	OverlapVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bIsHealthPickup = true;
	PickupAmount = 20.0f;
}

void APickupItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ASptclub_Ch3Character* MyCharacter = Cast<ASptclub_Ch3Character>(OtherActor);

	if (MyCharacter != nullptr)
	{
		if (bIsHealthPickup)
		{
			MyCharacter->AddHealth(PickupAmount);
		}
		else
		{
			ASptclub_Ch3GameState* MyGameState = GetWorld()->GetGameState<ASptclub_Ch3GameState>();

			if (MyGameState != nullptr)
			{
				MyGameState->AddScore((int32)PickupAmount);
			}
		}

		Destroy();
	}
}
