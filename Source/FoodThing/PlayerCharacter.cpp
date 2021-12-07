// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMaxHealth = 5;
	PlayerCurrentHealth = PlayerMaxHealth;
	PlayerSpeed = 1000.f;
	MeleeDamage = 55.f;
	RangedDamage = 35.f;
	bIsUsingMelee = true;

	MeleeRange = CreateDefaultSubobject<UBoxComponent>(TEXT("Melee Range"));
	MeleeRange->SetupAttachment(RootComponent);

	GetCharacterMovement()->MaxWalkSpeed = PlayerSpeed;
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &APlayerCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &APlayerCharacter::SwitchWeapons);

}

void APlayerCharacter::MoveUp(float Value)
{
	AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

void APlayerCharacter::Attack()
{

	if (bIsUsingMelee)
	{
		//Executes if melee weapon is currently equipped
		UE_LOG(LogTemp, Warning, TEXT("Melee Attack"))
		//swing melee weapon
	} 
	else 
	{
		//Executes if ranged weapon is currently equipped

		const FTransform ProjSpawn = FTransform(FRotator(0.f, 0.f, GetActorRotation().Yaw), GetActorLocation(), FVector(1.f, 1.f, 1.f));
		APlayerProjectile* SpawnedProj = GetWorld()->SpawnActorDeferred<APlayerProjectile>(PlayerProjectile.Get(), ProjSpawn);
		SpawnedProj->bIsFromPlayer = true;
		SpawnedProj->Damage = RangedDamage;
		SpawnedProj->InitSpeed = 800;
		SpawnedProj->ProjectileMovement->InitialSpeed = SpawnedProj->InitSpeed;
		SpawnedProj->SetActorRotation(FRotator(0.f, GetActorRotation().Yaw, 0.f));
		SpawnedProj->FinishSpawning(ProjSpawn);

	}
}

void APlayerCharacter::SwitchWeapons()
{
	if (bIsUsingMelee) {
		//Change the weapon to the ranged weapon 


		bIsUsingMelee = false;
	}
	else 
	{
		//Change the weapon to melee and set bool to true


		bIsUsingMelee = true;
	}
}

void APlayerCharacter::AddBuff(FString BuffName, float Value)
{
	if (BuffName == "Health") 
	{
		PlayerMaxHealth += Value;
	}
	else if (BuffName == "Damage")
	{
		MeleeDamage += Value;
		RangedDamage += Value;
	}
	else if (BuffName == "Speed")
	{
		GetCharacterMovement()->MaxWalkSpeed += Value;
	}

}

void APlayerCharacter::RecieveDamage(int Damage)
{
	if (PlayerCurrentHealth - Damage <= 0)
	{
		bIsAlive = false;
		return;
	}
	else
	{
		PlayerCurrentHealth -= Damage;
	}
}