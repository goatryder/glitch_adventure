// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpItem.h"

#include "Components/SphereComponent.h"

// Sets default values
APickUpItem::APickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

