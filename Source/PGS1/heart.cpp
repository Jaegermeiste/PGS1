// Fill out your copyright notice in the Description page of Project Settings.

#include "heart.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "playerCharacter.h"


// Sets default values
Aheart::Aheart()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create root component for coin class
	heartRoot = CreateDefaultSubobject<USceneComponent>(TEXT("heartRoot"));
	RootComponent = heartRoot;

	//create mesh object for coin class
	heartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("heartMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Mesh/heartMesh.heartMesh'"));
	UStaticMesh* Asset = MeshAsset.Object;

	heartMesh->SetStaticMesh(Asset);

	//attach mesh to the root component
	heartMesh->AttachToComponent(heartRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//create collision shape
	collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("heartCollisionSphere"));
	collisionSphere->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	collisionSphere->bGenerateOverlapEvents = true;
	collisionSphere->OnComponentBeginOverlap.AddDynamic(this, &Aheart::onEntry);

	//atrach collision sphere to the root component
	collisionSphere->AttachToComponent(heartRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void Aheart::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void Aheart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Aheart::onEntry(UPrimitiveComponent * overlappedComponent, AActor * otherActor, UPrimitiveComponent * otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult & sweepResult)
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
			player->updateHealth(1.0f);
			Destroy();
		}
	}
}

