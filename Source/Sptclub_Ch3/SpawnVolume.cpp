#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector Origin = WhereToSpawn->Bounds.Origin;
	FVector Extent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}

void ASpawnVolume::SpawnItem()
{
	if (ItemsToSpawn.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, ItemsToSpawn.Num() - 1);
		TSubclassOf<AActor> SelectedClass = ItemsToSpawn[RandomIndex];

		if (SelectedClass != nullptr)
		{
			FVector SpawnLocation = GetRandomPointInVolume();
			FRotator SpawnRotation = FRotator::ZeroRotator;

			GetWorld()->SpawnActor<AActor>(SelectedClass, SpawnLocation, SpawnRotation);
		}
	}
}
