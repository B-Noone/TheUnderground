// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryGrid.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

// Sets default values
AInventoryGrid::AInventoryGrid()
{
	// Set this actor to call Tick() every frame.
	//PrimaryActorTick.bCanEverTick = true;
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	Size = 5;
	BlockSpacing = 50.f;
}

// Called when the game starts or when spawned
void AInventoryGrid::BeginPlay()
{
	Super::BeginPlay();
	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++)
	{
		const float ZOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(ZOffset, YOffset, 0.f);

		// Spawn a block
		AInvBlock* NewBlock = GetWorld()->SpawnActor<AInvBlock>(BlockLocation, FRotator(90, 0, 90));
		NewBlock->GetBlockMesh()->AttachTo(RootComponent);
		NewBlock->GetBoxComponent()->AttachTo(NewBlock->GetBlockMesh());
		//NewBlock->GetStoredActor()->AttachToActor(NewBlock, FAttachmentTransformRules::KeepRelativeTransform);

		//this->SetupAttachment(DummyRoot);
		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
			Blocks.Add(NewBlock);
		}
	}
}

AActor* AInventoryGrid::GetInventoryActor() {
	return this;
}

void AInventoryGrid::OnPickUp(AActor* NewItem) {
	NewItem->SetOwner(nullptr);
	NewItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	for (int i = 0; i < Blocks.Num(); i++) {
		if (Blocks[i]->GetStoredActor() == nullptr && NewItem->GetOwner() == nullptr) {
			Blocks[i]->SetStoredActor(NewItem);
			Blocks[i]->ItemCollisions = NewItem->GetActorEnableCollision();
			NewItem->SetOwner((AActor*)Blocks[i]);
			NewItem->AttachToActor(Blocks[i], FAttachmentTransformRules::KeepWorldTransform);
			ChangePhysics(Blocks[i], false);
			NewItem->SetActorEnableCollision(false);
			NewItem->SetActorRelativeLocation(FVector(0, 0, 0));
			Blocks[i]->OriginalSize = NewItem->GetActorScale();
			float biggest = NewItem->GetActorRelativeScale3D().Y;
			float blockAxis = Blocks[i]->GetActorRelativeScale3D().Y;
			NewItem->SetActorRelativeRotation(FRotator(0, 0, 0));
			if (NewItem->GetActorRelativeScale3D().X > biggest) {
				biggest = NewItem->GetActorRelativeScale3D().X;
				blockAxis = Blocks[i]->GetActorRelativeScale3D().X;
				NewItem->SetActorRelativeRotation(FRotator(90, 0, 0));
			}
			if (NewItem->GetActorRelativeScale3D().Z > biggest) {
				biggest = NewItem->GetActorRelativeScale3D().Z;
				blockAxis = Blocks[i]->GetActorRelativeScale3D().Z;
				NewItem->SetActorRelativeRotation(FRotator(0, 0, 90));
			}
			if (biggest > blockAxis) {
				float NewSize = (blockAxis / biggest) * 100;
				NewItem->SetActorRelativeScale3D((NewItem->GetActorRelativeScale3D() * NewSize));
			}
		}
	}
}

//void AInventoryGrid::OnDrop(AInvBlock* InvSlot, FVector SpawnPos) {
//	if (InvSlot->GetStoredActor() != nullptr) {
//		AActor* ItemToDrop = InvSlot->GetStoredActor();
//		ItemToDrop->SetOwner(nullptr);
//		ItemToDrop->AttachToActor(nullptr, FAttachmentTransformRules::KeepWorldTransform);
//		ItemToDrop->SetActorLocation(SpawnPos);
//		InvSlot->SetStoredActor(nullptr);
//		//ChangePhysics(ItemToDrop, true);
//		ItemToDrop->SetActorEnableCollision(true);
//	}
//}

void AInventoryGrid::ChangePhysics(AActor* ObjActor, bool bOn) {
	for (UActorComponent* Component : ObjActor->GetComponents())
	{
		if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Component))
		{
			PrimComp->SetSimulatePhysics(bOn);
		}
	}
}

//TArray<AInvBlock*> AInventoryGrid::GetBlocks() {
//	return Blocks;
//}

//
//// Called every frame
//void AInventoryGrid::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}