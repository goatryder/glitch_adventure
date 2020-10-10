// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"

#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// #include "PickUpItem.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set Default Values
	AttackDelay = 0.8f;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0.f;
	CanAttack = true;
	AttackStarted = false;

	// Trigger Capsule
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);

	BulletLaunchImpulse = 20000.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastStrike += DeltaTime;

	if (TimeSinceLastStrike > AttackTimeout) {


		AttackStarted = false;

		if (!CanAttack) {

			CanAttack = true;
			TimeSinceLastStrike = 0;

		}

	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Yaw", this, &APlayerCharacter::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &APlayerCharacter::Pitch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::OnAttack);
}

void APlayerCharacter::MoveForward(float Val)
{

	if (Controller) {
	
		if (Val == 0.f) {

			IsWalking = false;
			// StrafeRotated = false;
		}

		else {

			IsWalking = true;

			FVector fwd = GetActorForwardVector();
			AddMovementInput(fwd, Val);

		}
	
	}

}

void APlayerCharacter::MoveRight(float Val)
{

	if (Controller) {

		if (Val == 0.f) {

			// Rotate back to normal 
			/*if (StrafeRotated) {

				RootComponent->SetRelativeRotation_Direct(RootComponent->GetRelativeRotation());

			}
			
			StrafeRotated = false;*/

			// IsWalking = false;

		}

		else {
			
			/*UE_LOG(LogTemp, Warning, TEXT("Rotation %s"), *RootComponent->GetRelativeRotation().ToString());

			// Rotate to 90'/-90'
			if (!StrafeRotated) {

				FRotator BaseRotation = RootComponent->GetRelativeRotation();
				BaseRotation.Yaw += StrafeRightRotateAngle * Val;

				RootComponent->SetRelativeRotation_Direct(BaseRotation);

			}

			StrafeRotated = true;

			if (!StrafeRotated)
				LastRightInputValue = Val;
				RootComponent->SetWorldRotation(FRotator(0.f, Val * StrafeRightRotateAngle, 0.f));
				StrafeRotated = true;

			if (LastRightInputValue != Val)
				StrafeRotated = false;*/


			IsWalking = true;

			FVector right = GetActorRightVector();
			AddMovementInput(right, Val);

		}

	}

}

void APlayerCharacter::Yaw(float Val)
{	
	AddControllerYawInput(200.f * Val * GetWorld()->GetDeltaSeconds());

}

void APlayerCharacter::Pitch(float Val)
{	
	AddControllerPitchInput(200.f * Val * GetWorld()->GetDeltaSeconds());
	//APlayerController* const PC = CastChecked<APlayerController>(Controller);
	//PC->AddPitchInput(Val);

}

void APlayerCharacter::OnAttack()
{

	if (CanAttack) {

		AttackStarted = true;

		FVector fwd = GetActorForwardVector();
		FVector nozzle = GetMesh()->GetBoneLocation("ArmR3");

		nozzle += fwd * 55.f;

		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(BPFireball, nozzle, RootComponent->GetComponentRotation());

		CanAttack = false;

		if (bullet) {
			
			bullet->CollisionSphere->AddImpulse(fwd * BulletLaunchImpulse);

		}

	}

}


float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInsigator, AActor* DamageCauser)
{
	HP -= Damage;

	if (HP <= 0.f) {

		HP = 0;

		Dead = true;

		// UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

	}

	return Damage;
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}