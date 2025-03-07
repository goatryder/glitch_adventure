// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageArea.generated.h"

class UBoxComponent;

UCLASS()
class GLITCHADVENTURE_API ADamageArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float Damage;

	UPROPERTY(EditAnywhere)
		UBoxComponent* DamageBox;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
