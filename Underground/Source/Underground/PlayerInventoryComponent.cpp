// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryComponent.h"

// Sets default values for this component's properties
UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerInventoryComponent::SetPlayerInventory(AInventoryGrid* Inv) {
	Inventory = Inv;
}

void UPlayerInventoryComponent::PickUpItem(AActor* AItem) {
	if (InHand == nullptr && AItem != nullptr) {
		InHand = AItem;
		AItem->SetOwner(this->GetOwner());
		AItem->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
		//ChangePhysics(Blocks[i], false);
		AItem->SetActorEnableCollision(false);
		AItem->SetActorRelativeLocation(FVector(30, 15, 30));
		AItem->SetActorRelativeRotation(FRotator(0, 0, 0));
	}
	else if (InHand != nullptr && AItem != nullptr) {
		DropItem();
		PickUpItem(AItem);
	}
}

void UPlayerInventoryComponent::DropItem() {
	if (InHand != nullptr) {
		InHand->SetActorRelativeLocation(FVector(100, 0, 30));
		InHand->SetOwner(nullptr);
		//InHand->AttachToActor(NULL, FAttachmentTransformRules::KeepWorldTransform);
		InHand->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		InHand->SetActorEnableCollision(true);
		InHand = nullptr;
	}
}

void UPlayerInventoryComponent::NullHand() {
	InHand = nullptr;
}