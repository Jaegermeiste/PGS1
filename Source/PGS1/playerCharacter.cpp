// Fill out your copyright notice in the Description page of Project Settings.

#include "playerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"


// Sets default values
AplayerCharacter::AplayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set size for colission capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	//Don't rotate when the controller rotates
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Create cmera boom attached to the root
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->RelativeRotation = FRotator(0.f, 270.f, 0.f);

	//Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false;

	//Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	//Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//initialize score to 0 on character creation
	scoreTracker = 0;

	//initialized health to 2 on character creation
	healthTracker = 2.0f;

	//initialized coin counter to 0 on character creation
	coinTracker = 0;

	//setting the values for the double jump
	MaxJumpCount = 2;
	CurrentJumpCount = 0;

	//setting the playerCharacter skeletal mesh
	USkeletalMeshComponent* playerMesh = GetMesh();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/Mesh/playerSkeletonMesh.playerSkeletonMesh'"));
	USkeletalMesh* Asset = MeshAsset.Object;

	playerMesh->SetSkeletalMeshWithoutResettingAnimation(Asset);
}

int AplayerCharacter::getCurrentScore()
{
	return scoreTracker;
}

int AplayerCharacter::getCurrentHealth()
{
	return healthTracker;
}

void AplayerCharacter::updateScore(int addScore)
{
	scoreTracker = scoreTracker + addScore;
}

void AplayerCharacter::updateHealth(int healthChange)
{
	healthTracker = healthTracker + healthChange;
}

int AplayerCharacter::getCoinCount()
{
	return coinTracker;
}

void AplayerCharacter::updateCoinCount(int coinValue)
{
	coinTracker = coinTracker + coinValue;
}

bool AplayerCharacter::CanJumpInternal_Implementation() const
{
	return Super::CanJumpInternal_Implementation() || CurrentJumpCount < MaxJumpCount;
}

void AplayerCharacter::Landed(const FHitResult & Hit)
{
	Super::Landed(Hit);
	CurrentJumpCount = 0;
}

// Called to bind functionality to input
void AplayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AplayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AplayerCharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveX", this, &AplayerCharacter::MoveX);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AplayerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AplayerCharacter::TouchStopped);
}

//Function to handle right and left movement
void AplayerCharacter::MoveX(float Value)
{
	//Add movement in that direction
	AddMovementInput(FVector(-1.f, 0.f, 0.f), Value);
}

void AplayerCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	//Jump on touch
	Jump();
	CurrentJumpCount++;
}

void AplayerCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}