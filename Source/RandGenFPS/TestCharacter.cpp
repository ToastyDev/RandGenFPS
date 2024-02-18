// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	//Vars
	MaxHealth = 100.f;
	CurrHealth = MaxHealth;

	//Meshes
	TPSkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP Mesh"));
	TPSkelMesh->SetupAttachment(RootComponent);
	TPSkelMesh->SetVisibility(true);

	FPSkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP Mesh"));
	FPSkelMesh->SetupAttachment(RootComponent);
	FPSkelMesh->SetOnlyOwnerSee(true);

	//Test Hitbox
	BasicHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	BasicHitbox->SetupAttachment(RootComponent);
	BasicHitbox->CanCharacterStepUp(false);

	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(FPSkelMesh);

	SkelTest = CreateDefaultSubobject<USkeleton>(TEXT("Skeleton"));
	ConstructorHelpers::FObjectFinder<USkeleton> SkeletonAsset(TEXT("/Game/Female_Mannequin/Skeletons_and_Physics_Assets/SKEL_Female_Tall_Body_MNQ.SKEL_Female_Tall_Body_MNQ"));
	if (SkeletonAsset.Succeeded())
		SkelTest = SkeletonAsset.Object;
	
	//Sockets Create
	HeadSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	ChestSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	LeftUpperArmSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	LeftLowerArmSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	RightUpperArmSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	RightLowerArmSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	LeftUpperLegSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	LeftLowerLegSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	LeftFootSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	RightUpperLegSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	RightLowerLegSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	RightFootSocket = NewObject<USkeletalMeshSocket>(SkelTest);
	
	//Sockets Add
	SkelTest->Modify();

	HeadSocket->SocketName = "HeadSocket";
	HeadSocket->BoneName = "head";
	SkelTest->Sockets.Add(HeadSocket);

	ChestSocket->SocketName = "ChestSocket";
	ChestSocket->BoneName = "spine_03";
	SkelTest->Sockets.Add(ChestSocket);

	LeftUpperArmSocket->SocketName = "LeftUpperArmSocket";
	LeftUpperArmSocket->BoneName = "lowerarm_l";
	SkelTest->Sockets.Add(LeftUpperArmSocket);

	LeftLowerArmSocket->SocketName = "LeftLowerArmSocket";
	LeftLowerArmSocket->BoneName = "Hand_L";
	SkelTest->Sockets.Add(LeftLowerArmSocket);

	RightUpperArmSocket->SocketName = "RightUpperArmSocket";
	RightUpperArmSocket->BoneName = "lowerarm_r";
	SkelTest->Sockets.Add(RightUpperArmSocket);

	RightLowerArmSocket->SocketName = "RightLowerArmSocket";
	RightLowerArmSocket->BoneName = "Hand_R";
	SkelTest->Sockets.Add(RightLowerArmSocket);

	LeftUpperLegSocket->SocketName = "LeftUpperLegSocket";
	LeftUpperLegSocket->BoneName = "calf_l";
	SkelTest->Sockets.Add(LeftUpperLegSocket);

	LeftLowerLegSocket->SocketName = "LeftLowerLegSocket";
	LeftLowerLegSocket->BoneName = "Foot_L";
	SkelTest->Sockets.Add(LeftLowerLegSocket);

	LeftFootSocket->SocketName = "LeftFootSocket";
	LeftFootSocket->BoneName = "ball_l";
	SkelTest->Sockets.Add(LeftFootSocket);

	RightUpperLegSocket->SocketName = "RightUpperLegSocket";
	RightUpperLegSocket->BoneName = "calf_r";
	SkelTest->Sockets.Add(RightUpperLegSocket);

	RightLowerLegSocket->SocketName = "RightLowerLegSocket";
	RightLowerLegSocket->BoneName = "Foot_R";
	SkelTest->Sockets.Add(RightLowerLegSocket);

	RightFootSocket->SocketName = "RightFootSocket";
	RightFootSocket->BoneName = "ball_r";
	SkelTest->Sockets.Add(RightFootSocket);
	
	//Hitboxes
	HeadHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Head Hitbox"));
	HeadHitbox->SetupAttachment(RootComponent);
	HeadHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "HeadSocket");
	HeadHitbox->SetHiddenInGame(false);
	HeadHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	ChestHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Chest Hitbox"));
	ChestHitbox->SetupAttachment(RootComponent);
	ChestHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "ChestSocket");
	ChestHitbox->SetHiddenInGame(false);
	ChestHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	LeftUpperArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Upper Arm Hitbox"));
	LeftUpperArmHitbox->SetupAttachment(RootComponent);
	LeftUpperArmHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "LeftUpperArmSocket");
	LeftUpperArmHitbox->SetHiddenInGame(false);
	LeftUpperArmHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	LeftLowerArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Lower Arm Hitbox"));
	LeftLowerArmHitbox->SetupAttachment(RootComponent);
	LeftLowerArmHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "LeftLowerArmSocket");
	LeftLowerArmHitbox->SetHiddenInGame(false);
	LeftLowerArmHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	RightUpperArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Upper Arm Hitbox"));
	RightUpperArmHitbox->SetupAttachment(RootComponent);
	RightUpperArmHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "RightUpperArmSocket");
	RightUpperArmHitbox->SetHiddenInGame(false);
	RightUpperArmHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	RightLowerArmHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Lower Arm Hitbox"));
	RightLowerArmHitbox->SetupAttachment(RootComponent);
	RightLowerArmHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "RightLowerArmSocket");
	RightLowerArmHitbox->SetHiddenInGame(false);
	RightLowerArmHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	LeftUpperLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Upper Leg Hitbox"));
	LeftUpperLegHitbox->SetupAttachment(RootComponent);
	LeftUpperLegHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "LeftUpperLegSocket");
	LeftUpperLegHitbox->SetHiddenInGame(false);
	LeftUpperLegHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	LeftLowerLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Lower Leg Hitbox"));
	LeftLowerLegHitbox->SetupAttachment(RootComponent);
	LeftLowerLegHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "LeftLowerLegSocket");
	LeftLowerLegHitbox->SetHiddenInGame(false);
	LeftLowerLegHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	LeftFootHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Foot Hitbox"));
	LeftFootHitbox->SetupAttachment(RootComponent);
	LeftFootHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "LeftFootSocket");
	LeftFootHitbox->SetHiddenInGame(false);
	LeftFootHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	RightUpperLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Upper Leg Hitbox"));
	RightUpperLegHitbox->SetupAttachment(RootComponent);
	RightUpperLegHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "RightUpperLegSocket");
	RightUpperLegHitbox->SetHiddenInGame(false);
	RightUpperLegHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	RightLowerLegHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Lower Leg Hitbox"));
	RightLowerLegHitbox->SetupAttachment(RootComponent);
	RightLowerLegHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "RightLowerLegSocket");
	RightLowerLegHitbox->SetHiddenInGame(false);
	RightLowerLegHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	RightFootHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Foot Hitbox"));
	RightFootHitbox->SetupAttachment(RootComponent);
	RightFootHitbox->AttachToComponent(TPSkelMesh, FAttachmentTransformRules::KeepRelativeTransform, "RightFootSocket");
	RightFootHitbox->SetHiddenInGame(false);
	RightFootHitbox->SetBoxExtent(FVector(10.f, 10.f, 10.f));

	
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Character Created"));

	Weapon->SetMaxMagSize(3);
	Weapon->SetMaxAmmoSize(10);

	//Weapon->AttachToComponent();

	//config hitbox size based on mesh;
	//probably going with the dictionary style where I will have a file somewhere that this class can access. Populate based on given mesh.
	//BasicHitbox->SetBoxExtent(FVector(TPSkelMesh->Bounds));
	BasicHitbox->SetHiddenInGame(true);
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

