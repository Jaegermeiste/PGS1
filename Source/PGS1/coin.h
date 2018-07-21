// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "coin.generated.h"

UCLASS()
class PGS1_API Acoin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Acoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//coin root component
	UPROPERTY(EditAnywhere)
		USceneComponent* coinRoot;

	//shape to determine collisions
	UPROPERTY(EditAnywhere)
		UShapeComponent* collisionSphere;

	//add static mesh to the coin actor
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* coinMesh;

	//function to control contact with other actors
	UFUNCTION()
		void onEntry(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

};
