// Fill out your copyright notice in the Description page of Project Settings.

#include "TelekinesisAbilityComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UTelekinesisAbilityComponent::UTelekinesisAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_focusPositionOffset = FVector(200, 0, 200);
	_throwPower = 400000.f;
	_pickupRange = 1000.f;

	_mode = SetVelocity;
	// ...
}


// Called when the game starts
void UTelekinesisAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	_inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	_camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	if (_inputComponent)
	{
		_inputComponent->BindAction("Use", IE_Pressed, this, &UTelekinesisAbilityComponent::PickupObject);
		_inputComponent->BindAction("Drop", IE_Pressed, this, &UTelekinesisAbilityComponent::DropObjects);
		_inputComponent->BindAction("Shoot", IE_Pressed, this, &UTelekinesisAbilityComponent::ThrowObjects);
	}
	// ...

}

void UTelekinesisAbilityComponent::UseAbility()
{
	if (_selectedObjects.Num() > 0) {
		DropObjects();
	}
	else {
		PickupObject();
	}
}

void UTelekinesisAbilityComponent::PickupObject()
{
	FVector start = GetOwner()->GetActorLocation();
	FVector end = _camManager->GetCameraLocation() + _pickupRange * _camManager->GetCameraRotation().Vector();

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());
	for (UStaticMeshComponent* obj : _selectedObjects) {
		actorsToIgnore.Add(obj->GetOwner());
	}

	TArray<FHitResult> hitArray;

	if (UKismetSystemLibrary::SphereTraceMulti(GetOwner()->GetWorld(), start, end, 20, UEngineTypes::ConvertToTraceType(ECC_Camera), false, actorsToIgnore, EDrawDebugTrace::ForDuration, hitArray, true))
	{
		for (const FHitResult hitResult : hitArray)
		{
			auto mesh = Cast<UStaticMeshComponent>(hitResult.GetComponent());

			if (mesh && mesh->IsSimulatingPhysics() && !_selectedObjects.Contains(mesh)) {
				_selectedObjects.Add(mesh);
				mesh->SetEnableGravity(false);
			}
		}
	}
}

void UTelekinesisAbilityComponent::ThrowObjects()
{
	for (UStaticMeshComponent* mesh : _selectedObjects) {
		mesh->SetEnableGravity(true);
		mesh->AddImpulse(_throwPower * _camManager->GetCameraRotation().Vector());
	}

	_selectedObjects.Empty();
}

void UTelekinesisAbilityComponent::DropObjects()
{
	for (auto mesh : _selectedObjects) {
		mesh->SetEnableGravity(true);
	}

	_selectedObjects.Empty();
}


// Called every frame
void UTelekinesisAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto targetPos = GetOwner()->GetActorLocation() + GetOwner()->GetActorTransform().GetRotation().RotateVector(_focusPositionOffset);

	for (UStaticMeshComponent* mesh : _selectedObjects)
	{
		switch (_mode)
		{
		case SetPosition:
			mesh->SetAllPhysicsPosition(targetPos);
			break;
		case SetVelocity:
		{
			FVector current = mesh->GetCenterOfMass();
			FVector diff = (targetPos - current);
			FVector newVelocity = diff;
			if (diff.Size() > 1.f) {
				newVelocity *= 10.f;
				mesh->SetPhysicsLinearVelocity(newVelocity);
			}
			else {

			}
		}
		break;
		case SetAcceleration:
			break;
		default:
			break;
		}


	}

	// ...
}


