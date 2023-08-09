// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	MaxHealth = 100.f;
	CurrHealth = MaxHealth;

	TPSkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP Mesh"));
	TPSkelMesh->SetupAttachment(RootComponent);

	FPSkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP Mesh"));
	FPSkelMesh->SetupAttachment(RootComponent);
	FPSkelMesh->SetOnlyOwnerSee(true);

	BasicHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	BasicHitbox->SetupAttachment(RootComponent);
	BasicHitbox->CanCharacterStepUp(false);

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(FPSkelMesh);

	HeadHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Head Hitbox"));
	HeadHitbox->SetupAttachment(RootComponent);

	ChestHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Chest Hitbox"));
	ChestHitbox->SetupAttachment(RootComponent);

	LeftUpperArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Upper Arm Hitbox"));
	LeftUpperArmHitbox->SetupAttachment(RootComponent);

	LeftLowerArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Lower Arm Hitbox"));
	LeftLowerArmHitbox->SetupAttachment(RootComponent);

	RightUpperArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Upper Arm Hitbox"));
	RightUpperArmHitbox->SetupAttachment(RootComponent);

	RightLowerArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Lower Arm Hitbox"));
	RightLowerArmHitbox->SetupAttachment(RootComponent);

	LeftUpperLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Upper Leg Hitbox"));
	LeftUpperLegHitbox->SetupAttachment(RootComponent);

	LeftLowerLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Lower Leg Hitbox"));
	LeftLowerLegHitbox->SetupAttachment(RootComponent);

	LeftFootHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Foot Hitbox"));
	LeftFootHitbox->SetupAttachment(RootComponent);

	RightUpperLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Upper Leg Hitbox"));
	RightUpperLegHitbox->SetupAttachment(RootComponent);

	RightLowerLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Lower Leg Hitbox"));
	RightLowerLegHitbox->SetupAttachment(RootComponent);

	RightFootHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Foot Hitbox"));
	RightFootHitbox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Character Created"));

	Weapon->SetMaxMagSize(3);
	Weapon->SetMaxAmmoSize(10);

	//config hitbox size based on mesh;
	//probably going with the dictionary style where I will have a file somewhere that this class can access. Populate based on given mesh.
	//BasicHitbox->SetBoxExtent(FVector(TPSkelMesh->Bounds));
	BasicHitbox->SetHiddenInGame(false);
	BasicHitbox->SetBoxExtent(FVector(30.f, 30.f, 50.f));
	UE_LOG(LogTemp, Warning, TEXT("Basic Hit Box Collision: %s"), (BasicHitbox->IsCollisionEnabled() ? TEXT("true") : TEXT("false")));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Weapon: Starting Max Mag = %i"), Weapon->MaxMag));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Weapon: Starting Max Ammo = %i"), Weapon->MaxAmmo));
}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ATestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ATestCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATestCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATestCharacter::EndJump);

	PlayerInputComponent->BindAxis("Turn", this, &ATestCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ATestCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ATestCharacter::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATestCharacter::Reload);

}

void ATestCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.f))
	{
		if (value > 0.f)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Moving Forward"));
		else if (value < 0.f)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moving Backward"));

		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}

}

void ATestCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.f))
	{
		if (value > 0.f)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Moving Right"));
		else if (value < 0.f)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Moving Left"));

		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void ATestCharacter::StartJump()
{
	bPressedJump = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Jumping"));
}

void ATestCharacter::EndJump()
{
	bPressedJump = false;
}

void ATestCharacter::Shoot()
{
	Weapon->Shoot();
}

void ATestCharacter::Reload()
{
	Weapon->Reload();
}

