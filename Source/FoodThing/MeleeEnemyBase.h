// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FoodThing/EnemyComponent.h"
#include "MeleeEnemyBase.generated.h"

UCLASS()
class FOODTHING_API AMeleeEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeEnemyBase();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UEnemyComponent* EnemyComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack(AActor* Actor, float Damage);

	void RecieveDamage(float Damage);

	virtual void Terminate();
};