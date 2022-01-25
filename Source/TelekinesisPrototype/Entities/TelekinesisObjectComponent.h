// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TelekinesisObjectComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class TELEKINESISPROTOTYPE_API UTelekinesisObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTelekinesisObjectComponent();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


};
