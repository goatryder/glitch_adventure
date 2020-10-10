// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Bullet.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 20.f;
	Health = 100.f;
	AttackTimeout = 1.5f;
	TimeSinceLastAttack = 0.f;

	BulletLaunchImpulse = 10000.f;

	SightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SightSphere"));
	SightSphere->SetupAttachment(RootComponent);

	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeSphere->SetupAttachment(RootComponent);

	IsAttacking = false;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerREF = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// calculate player location
	FVector distanceDifference = PlayerREF->GetActorLocation() - GetActorLocation();
	
	float distanceToPlayer = distanceDifference.Size();

	FRotator toPlayerRotation = distanceDifference.Rotation();
	toPlayerRotation.Pitch = 0;

	if (!IsDead) {

		RootComponent->SetWorldRotation(toPlayerRotation);

	}

	/*
	if (!IsInSightRange(distanceToPlayer)) {

		IsAttacking = false;

		return;

	}
	*/

	IsAttacking = IsInSightRange(distanceToPlayer);

	if (IsInAttackRange(distanceToPlayer) && !IsDead) {

		if (TimeSinceLastAttack == 0.f && IsAttacking) {

			Attack(PlayerREF);

		}

		TimeSinceLastAttack += DeltaTime;
		
		if (TimeSinceLastAttack > AttackTimeout) {

			TimeSinceLastAttack = 0.f;

		}

		return;

	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);





}

void AEnemyCharacter::Attack(AActor* AttackTarget)
{

	UE_LOG(LogTemp, Warning, TEXT("Enemy is Attacking the Player"));

}

float AEnemyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInsigator, AActor* DamageCauser)
{
	return 0.0f;
}

