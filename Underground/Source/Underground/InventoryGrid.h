// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvBlock.h"
#include "InventoryGrid.generated.h"

UCLASS()
class AInventoryGrid : public AActor
{
	GENERATED_BODY()

		/** Dummy root component */
		UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

public:
	// Sets default values for this actor's properties
	AInventoryGrid();

	// Number of blocks
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		int32 Size;

	// Block spacing 
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float BlockSpacing;

	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadOnly)
		TArray<AInvBlock*> Blocks;

	UFUNCTION(BlueprintCallable)
		AActor* GetInventoryActor();

	UFUNCTION(BlueprintCallable)
		void OnPickUp(AActor* NewItem);

	//UFUNCTION(BlueprintCallable)
	//	void OnDrop(AInvBlock* InvSlot, FVector SpawnPos);

	UFUNCTION(BlueprintCallable)
		void ChangePhysics(AActor* ObjActor, bool bOn);

	UFUNCTION(BlueprintCallable)
		TArray<AInvBlock*> GetBlocks() { return Blocks; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	// Returns DummyRoot
	FORCEINLINE class USceneComponent * GetDummyRoot() const { return DummyRoot; }
};
