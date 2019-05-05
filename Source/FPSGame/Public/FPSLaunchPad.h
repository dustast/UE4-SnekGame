// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	UPROPERTY(EditInstanceOnly, Category="LaunchPad")
	int LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	int LaunchAngle;

	UPROPERTY(EditDefaultsOnly, Category="LaunchPad")
	UParticleSystem* LaunchParticleSystem;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "MeshComp")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "BoxComp")
	UBoxComponent* BoxComp;

	UFUNCTION()
	void LaunchMe(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
