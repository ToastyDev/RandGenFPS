// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"

#include "BaseCharacter.generated.h"

UCLASS()
class RANDGENFPS_API ABaseCharacter : public APawn
{
	GENERATED_BODY()


private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* TPSkelMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* FPSkelMesh;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WepMesh;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BasicHitbox;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HeadHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ChestHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* LeftUpperArmHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* LeftLowerArmHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* RightUpperArmHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* RightLowerArmHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* LeftUpperLegHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* LeftLowerLegHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* LeftFootHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* RightUpperLegHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* RightLowerLegHitbox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* RightFootHitbox;

	UPROPERTY(VisibleAnywhere)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere)
	float CurrHealth;

	UPROPERTY(VisibleAnywhere)
	bool bIsJumping;


public:
	// Sets default values for this pawn's properties
	ABaseCharacter();

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
};
