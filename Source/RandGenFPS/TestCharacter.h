// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"

#include "WeaponComponent.h"
#include "TestCharacter.generated.h"

UCLASS()
class RANDGENFPS_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

	//1UPROPERTY(VisibleAnywhere, Category = "Core")
	//USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Character")
	USkeletalMeshComponent* TPSkelMesh;
	UPROPERTY(EditAnywhere, Category = "Character")
	USkeletalMeshComponent* FPSkelMesh;

	UPROPERTY(EditAnywhere)
	USkeleton* SkelTest;

	UPROPERTY(EditAnywhere, Category = "Character")
	UWeaponComponent* Weapon;

	UPROPERTY(EditAnywhere, Category = "Hitboxes")
	UBoxComponent* BasicHitbox;

	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* HeadHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* ChestHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* LeftUpperArmHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* LeftLowerArmHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* RightUpperArmHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* RightLowerArmHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* LeftUpperLegHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* LeftLowerLegHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* LeftFootHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* RightUpperLegHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* RightLowerLegHitbox;
	UPROPERTY(VisibleAnywhere, Category = "Hitboxes")
	UBoxComponent* RightFootHitbox;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* HeadSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* ChestSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* LeftUpperArmSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* LeftLowerArmSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* RightUpperArmSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* RightLowerArmSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* LeftUpperLegSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* LeftLowerLegSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* LeftFootSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* RightUpperLegSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* RightLowerLegSocket;
	UPROPERTY(EditAnywhere)
	USkeletalMeshSocket* RightFootSocket;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	float CurrHealth;

public:
	// Sets default values for this character's properties
	ATestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float value);
	UFUNCTION()
	void MoveRight(float value);
	UFUNCTION()
	void StartJump();
	UFUNCTION()
	void EndJump();

	UFUNCTION()
	void Shoot();
	UFUNCTION()
	void Reload();
};
