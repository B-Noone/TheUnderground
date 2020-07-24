// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "InvBlock.generated.h"

UCLASS(minimalapi)
class AInvBlock : public AActor
{
	GENERATED_BODY()

		/* Dummy root component */
		UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* BlockMesh;

	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollider;

public:
	// Sets default values for this actor's properties
	AInvBlock();

	bool bIsActive;

	// Pointer to white material used on the focused block
	UPROPERTY()
		class UMaterial* BaseMaterial;

	// Pointer to blue material used on inactive blocks
	UPROPERTY()
		class UMaterialInstance* BlueMaterial;

	//The Grid
	UPROPERTY()
		class AInventoryGrid* OwningGrid;

	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadWrite)
		class AActor* StoredItem;

	UPROPERTY(BlueprintReadWrite)
		FVector OriginalSize;

	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadOnly)
		bool ItemCollisions;

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void Highlight(bool bOn);

	UFUNCTION(BlueprintCallable)
		void SetStoredActor(AActor* NewItem);

	UFUNCTION(BlueprintCallable)
		AActor* GetStoredActor() { return StoredItem; }
	// Returns DummyRoot
	/*FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }*/
	// Returns BlockMesh
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
	FORCEINLINE class UBoxComponent* GetBoxComponent() const { return BoxCollider; }
	FORCEINLINE class AActor* GetStoredActor() const { return StoredItem; }
};
