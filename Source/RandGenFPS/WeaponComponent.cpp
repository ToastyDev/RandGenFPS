// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Weapon Created"));

}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::SetMaxMagSize(uint16 input)
{
	MaxMag = input;
	CurrentMag = MaxMag;
}

void UWeaponComponent::SetMaxAmmoSize(uint16 input)
{
	MaxAmmo = input;
	CurrentAmmo = MaxAmmo;
}

void UWeaponComponent::Reload()
{
	if (CurrentAmmo != 0)
	{
		//not enough ammo for full mag
		if (CurrentAmmo < MaxMag)
		{
			CurrentMag = CurrentAmmo;
			//reload anim
			//reload sound
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Reload: Inclomplete Mag. Current Mag = %i"), CurrentMag));
		}
		//can make full mag
		else
		{
			CurrentMag = MaxMag;
			//CurrentAmmo -= MaxMag;
			//reload anim
			//relaod sound
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Reload: Full Mag. Current Mag = %i"), CurrentMag));
		}

	}
	//no ammo, play some animation
	else if (CurrentMag == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Reload: Cannot Reload"));
	}
	//mag full, dont reload
	else if (CurrentMag == MaxMag)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Reload: Mag alrady full"));
	}
}

void UWeaponComponent::Shoot()
{
	if (CurrentMag != 0)
	{
		//spawn projectile
		CurrentMag--;
		CurrentAmmo--;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Shoot: Bullet shot successful. Current Mag = %i"), CurrentMag));
	}
	else
	{
		//play click sound
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Shoot: Empty Mag"));
	}
}