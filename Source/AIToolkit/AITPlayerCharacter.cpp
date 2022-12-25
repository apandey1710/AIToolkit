// Fill out your copyright notice in the Description page of Project Settings.
#include "AITPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AITUtilities.h"

// Sets default values
AAITPlayerCharacter::AAITPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Third Person Spring Arm"));
	this->SpringArmComponent->bUsePawnControlRotation = true;
	this->SpringArmComponent->SetupAttachment(this->RootComponent);
	
	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	this->CameraComponent->SetupAttachment(this->SpringArmComponent);

	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	

	

}

// Called when the game starts or when spawned
void AAITPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAITPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	LineStart += GetActorRightVector() * 100.0f;

	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Emerald, false, 0.0f, 0, Thickness);
	
	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

void AAITPlayerCharacter::MoveForward(float Value)
{
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;
	
	AddMovementInput(ControlRotator.Vector(), Value);

	//UE_LOG(LogTemp, Warning, TEXT("MoveForward"));

}

void AAITPlayerCharacter::MoveRight(float Value)
{

	// X - Forward (Red)
	// Y - Right (Green)
	// Z - Up (Blue)
	FRotator ControlRotator = GetControlRotation();
	ControlRotator.Pitch = 0.0f;
	ControlRotator.Roll = 0.0f;

	const FVector RightVector = FRotationMatrix(ControlRotator).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVector, Value);
}

void AAITPlayerCharacter::PrimaryAttack()
{
	
}

// Called to bind functionality to input
void AAITPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAITPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAITPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AAITPlayerCharacter::PrimaryAttack);

}

