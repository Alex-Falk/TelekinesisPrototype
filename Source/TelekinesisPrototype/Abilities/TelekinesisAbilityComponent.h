// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TelekinesisAbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TELEKINESISPROTOTYPE_API UTelekinesisAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTelekinesisAbilityComponent();

	UPROPERTY(EditAnywhere)
		float _throwPower;

	UPROPERTY(EditAnywhere)
		FVector _focusPositionOffset;

	UPROPERTY(EditAnywhere)
		float _pickupRange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void UseAbility();

	void PickupObject();

	void ThrowObjects();

	void DropObjects();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UInputComponent* _inputComponent;
	APlayerCameraManager* _camManager;

	TArray<UStaticMeshComponent*> _selectedObjects;



	enum Mode {
		SetPosition,
		SetVelocity,
		SetAcceleration,
	};

	Mode _mode;
		
};
