// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "playerCharacter.generated.h"

UCLASS()
class PGS1_API AplayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

private:

	//integer to track the character's current score
	UPROPERTY(EditAnywhere, Category = "score")
	int scoreTracker;

	//a float to track the amount of health a character has remaining
	UPROPERTY(EditAnywhere, Category = "health")
	int healthTracker;

	//integer to track the number f coins a player has picked up in a level
	UPROPERTY(EditAnywhere, Category = "coins")
	int coinTracker;

	//integer to track the number of lives remaining
	UPROPERTY(EditAnywhere, Category = "lives")
	int lifeTracker;

protected:
	//Input functions
	void MoveX(float AxisValue);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Sets default values for this character's properties
	AplayerCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	///function that returns the player's current score
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "score")
	int getCurrentScore();

	//function to return the player's current health
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "health")
	int getCurrentHealth();

	//function to update the player's current score
	UFUNCTION(BlueprintCallable, Category = "score")
	void updateScore(int addScore);

	//function to update the player's current health
	UFUNCTION(BlueprintCallable, Category = "health")
	void updateHealth(int healthChange);

	//function to return the current number of coins
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "coins")
	int getCoinCount();

	//function to update the number of coins a player currently has
	UFUNCTION(BlueprintCallable, Category = "coins")
	void updateCoinCount(int coinValue);

	//function to return the current number of lives
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "lives")
		int getLifeCount();

	//function to update the number of lives a player currently has
	UFUNCTION(BlueprintCallable, Category = "lives")
		void updateLifeCount(int lifeChange);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
	int32 MaxJumpCount;

	UPROPERTY()
	int32 CurrentJumpCount;

	virtual bool CanJumpInternal_Implementation() const override;

	UFUNCTION()
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION()
	virtual void Jump() override;
};