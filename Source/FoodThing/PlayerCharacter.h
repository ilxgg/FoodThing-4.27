// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerProjectile.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FOODTHING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();


	//Box Component used to damage all enemies infront the player
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* MeleeRange;


	/*Variable used for Player's Health value */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables | Health & Damage")
	int PlayerMaxHealth;

	/*Variable used to determine player's current health*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables | Health & Damage")
	int PlayerCurrentHealth;

	/*Variable Used to set player's Speed*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables | Movement")
	float PlayerSpeed;

	/*Amount of damage player deals when attackign with Melee weapon*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables | Health & Damage")
	float MeleeDamage;

	/*Amount of damage when player deals damage with ranged projectiles*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables | Health & Damage")
	float RangedDamage;

	/*Used to determine if player can shoot or can use melee*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Variables | Health & Damage")
	bool bIsUsingMelee;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Player Variables | Health & Damage")
	bool bIsAlive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Variables | Health & Damage", meta = (BlueprintBaseOnly, DisplayName = "Blueprint Projectile Refference", DisplayThumbnail = true))
	TSubclassOf<APlayerProjectile> PlayerProjectile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveUp(float Value);

	void MoveRight(float Value);

	void Attack();

	void SwitchWeapons();

	void AddBuff(FString BuffName, float Value);

	void RecieveDamage(int Damage);

};