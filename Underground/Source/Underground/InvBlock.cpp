// Fill out your copyright notice in the Description page of Project Settings.

#include "InvBlock.h"
#include "InventoryGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
AInvBlock::AInvBlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> CubeMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		FConstructorStatics()
			: CubeMesh(TEXT("/Game/StaticMeshCube.StaticMeshCube"))
			, BaseMaterial(TEXT("/Game/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/BlueMaterial.BlueMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	//DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	//RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.CubeMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(.1f, .1f, 0.025f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider0"));
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxCollider->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//BoxCollider->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BoxCollider->SetRelativeTransform(BlockMesh->GetRelativeTransform());
	BoxCollider->SetRelativeScale3D(FVector(1.f, 1.f, 4.f));
	//BoxCollider->SetHiddenInGame(false);

	//StoredItem = CreateDefaultSubobject<AActor>(TEXT("Item0"));
	//StoredItem->SetActorRelativeScale3D(FVector(1.f, 1.f, 1.f));
	StoredItem = nullptr;

	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
}

//Called when the game starts or when spawned
//void AInvBlock::BeginPlay()
//{
//	Super::BeginPlay();
//}

//// Called every frame
//void AInvBlock::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AInvBlock::Highlight(bool bOn) {
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}

void AInvBlock::SetStoredActor(AActor* NewItem) {
	StoredItem = NewItem;
}