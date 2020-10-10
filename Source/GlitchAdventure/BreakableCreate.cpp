// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableCreate.h"

#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "PickUpItem.h"

// Sets default values
ABreakableCreate::ABreakableCreate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionBox);

	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	ExplosionFX->AttachToComponent(CollisionBox, FAttachmentTransformRules::KeepRelativeTransform, FName(""));


	Health = 100.f;

}

// Called when the game starts or when spawned
void ABreakableCreate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableCreate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableCreate::LootDrop()
{

	if (FMath::RandRange(0, 10) > 5) {

		FVector up = GetActorUpVector();
		FVector offset = CollisionBox->GetComponentLocation();

		offset += up;

		APickUpItem* pickup = GetWorld()->SpawnActor<APickUpItem>(BPPickupItem, offset, RootComponent->GetComponentRotation());

	}

}

float ABreakableCreate::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInsigator, AActor* DamageCauser)
{

	Health -= Damage;

	if (Health <= 0.f) {

		LootDrop();
	
		ExplosionFX->ToggleActive();

		Mesh->ToggleVisibility(false);

		SetLifeSpan(0.1f);
	
	}

	return 0.0f;
}

