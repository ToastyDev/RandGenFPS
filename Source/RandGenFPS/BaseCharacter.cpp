// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	MaxHealth = 100.f;
	CurrHealth = MaxHealth;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Root;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));

	TPSkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP Mesh"));
	TPSkelMesh->SetupAttachment(Root);

	FPSkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP Mesh"));
	FPSkelMesh->SetupAttachment(Root);

	BasicHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	BasicHitbox->SetupAttachment(Root);
	BasicHitbox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	WepMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WepMesh->SetupAttachment(TPSkelMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(TPSkelMesh);

	HeadHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Head Hitbox"));
	HeadHitbox->SetupAttachment(Root);

	ChestHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Chest Hitbox"));
	ChestHitbox->SetupAttachment(Root);

	LeftUpperArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Upper Arm Hitbox"));
	LeftUpperArmHitbox->SetupAttachment(Root);

	LeftLowerArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Lower Arm Hitbox"));
	LeftLowerArmHitbox->SetupAttachment(Root);

	RightUpperArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Upper Arm Hitbox"));
	RightUpperArmHitbox->SetupAttachment(Root);

	RightLowerArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Lower Arm Hitbox"));
	RightLowerArmHitbox->SetupAttachment(Root);

	LeftUpperLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Upper Leg Hitbox"));
	LeftUpperLegHitbox->SetupAttachment(Root);

	LeftLowerLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Lower Leg Hitbox"));
	LeftLowerLegHitbox->SetupAttachment(Root);

	LeftFootHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Foot Hitbox"));
	LeftFootHitbox->SetupAttachment(Root);

	RightUpperLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Upper Leg Hitbox"));
	RightUpperLegHitbox->SetupAttachment(Root);

	RightLowerLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Lower Leg Hitbox"));
	RightLowerLegHitbox->SetupAttachment(Root);

	RightFootHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Foot Hitbox"));
	RightFootHitbox->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//config hitbox size based on mesh;
	//probably going with the dictionary style where I will have a file somewhere that this class can access. Populate based on given mesh.
	//BasicHitbox->SetBoxExtent(FVector(TPSkelMesh->Bounds));
	BasicHitbox->SetHiddenInGame(false);
	BasicHitbox->SetBoxExtent(FVector(30.f, 30.f, 30.f));
	BasicHitbox->SetSimulatePhysics(true);
	UE_LOG(LogTemp, Warning, TEXT("Basic Hit Box Collision: %s"), (BasicHitbox->IsCollisionEnabled() ? TEXT("true") : TEXT("false")));

	//orient weapon based on mesh;

	//set remote visible

	//make local invisible
	if (this->IsLocallyControlled())
		TPSkelMesh->SetHiddenInGame(true);
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABaseCharacter::EndJump);
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);

}

void ABaseCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.f))
	{
		if (value > 0.f)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Moving Forward"));
		else if (value < 0.f)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moving Backward"));

		const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, value);
		//AddMovementInput(GetActorForwardVector(), value);
	}
	
}

void ABaseCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.f))
	{
		if (value > 0.f)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Moving Right"));
		else if (value < 0.f)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moving Left"));

		const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, value);
		//AddMovementInput(GetActorRightVector(), value);
	}
}

void ABaseCharacter::StartJump()
{
	bIsJumping = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Jumping"));

	BasicHitbox->AddImpulse(GetActorUpVector() * 100.f);
}

void ABaseCharacter::EndJump()
{
	bIsJumping = false;
}

