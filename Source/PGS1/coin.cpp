// Fill out your copyright notice in the Description page of Project Settings.

#include "coin.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "playerCharacter.h"


// Sets default values
Acoin::Acoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create root component for coin class
	coinRoot = CreateDefaultSubobject<USceneComponent>(TEXT("coinRoot"));
	RootComponent = coinRoot;

	//create mesh object for coin class and set coinMesh to it
	coinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("coinMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Mesh/coinMesh.coinMesh'"));
	UStaticMesh* Asset = MeshAsset.Object;

	coinMesh->SetStaticMesh(Asset);

	//attach mesh to the root component
	coinMesh->AttachToComponent(coinRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//create collision shape
	collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("coinCollisionSphere"));
	collisionSphere->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	collisionSphere->bGenerateOverlapEvents = true;
	collisionSphere->OnComponentBeginOverlap.AddDynamic(this, &Acoin::onEntry);

	//atrach collision sphere to the root component
	collisionSphere->AttachToComponent(coinRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

void Acoin::BeginPlay()
{
	Super::BeginPlay();
}

void Acoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Acoin::onEntry(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	//get pointer to player character
	ACharacter* test = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//test that colliding object is the player character
	if (test == otherActor)
	{
		//cast character as custom character class
		AplayerCharacter* player = Cast<AplayerCharacter>(otherActor);
		if (IsValid(player))
		{
			player->updateCoinCount(1);
			player->updateScore(100);
			Destroy();
		}
	}

}

