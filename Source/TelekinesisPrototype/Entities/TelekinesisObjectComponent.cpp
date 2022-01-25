// Fill out your copyright notice in the Description page of Project Settings.


#include "TelekinesisObjectComponent.h"

UTelekinesisObjectComponent::UTelekinesisObjectComponent()
{

}

void UTelekinesisObjectComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{	
}

void UTelekinesisObjectComponent::BeginPlay()
{
	UStaticMeshComponent* comp = GetOwner()->FindComponentByClass<UStaticMeshComponent>();

	if (comp)
		comp->OnComponentHit.AddDynamic(this, &UTelekinesisObjectComponent::OnHit);
}
