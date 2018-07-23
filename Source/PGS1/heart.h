// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "heart.generated.h"

UCLASS()
class PGS1_API Aheart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Aheart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//heart root component
	UPROPERTY(EditAnywhere)
		USceneComponent* heartRoot;

	//shape to determine collisions
	UPROPERTY(EditAnywhere)
		UShapeComponent* collisionSphere;

	//add static mesh to the heart actor
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* heartMesh;

	//function to control contact with other actors
	UFUNCTION()
		void onEntry(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);


};
