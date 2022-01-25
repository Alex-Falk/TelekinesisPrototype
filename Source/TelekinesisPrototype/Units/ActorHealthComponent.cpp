// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorHealthComponent.h"
#include <algorithm>

// Sets default values for this component's properties
UActorHealthComponent::UActorHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	m_currentHealth = m_maxHealth;
	// ...
	
}


// Called every frame
void UActorHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UActorHealthComponent::GetHealth()
{
	return m_currentHealth;
}

void UActorHealthComponent::SetHealth(int newHealth)
{
	m_currentHealth = std::min(newHealth, m_maxHealth);
}

void UActorHealthComponent::TakeDamage(int damage)
{
	m_currentHealth = std::max(m_currentHealth - damage, 0);
}

bool UActorHealthComponent::IsAlive()
{
	return m_currentHealth > 0;
}

