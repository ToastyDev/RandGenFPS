// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

#include "BaseCharacter.generated.h"

UCLASS()
class RANDGENFPS_API ABaseCharacter : public APawn
{
	GENERATED_BODY()


private:
	USkeletalMeshComponent* SkelMesh;
	UBoxComponent* BasicHitbox;

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

};
