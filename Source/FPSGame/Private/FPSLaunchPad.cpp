// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(75, 75, 50));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::LaunchMe);
	LaunchStrength = 45;
	LaunchAngle = 35;
}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSLaunchPad::LaunchMe(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	FRotator LaunchRot = GetActorRotation();
	LaunchRot.Pitch = LaunchAngle;
	FVector LaunchVelocity = LaunchRot.Vector() * LaunchStrength;

	
	ACharacter* OtherChar = Cast<ACharacter>(OtherActor);
	if (OtherChar)
	{
		OtherChar->LaunchCharacter(LaunchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAttached(LaunchParticleSystem, RootComponent);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity*10, NAME_None,true);
		UGameplayStatics::SpawnEmitterAttached(LaunchParticleSystem, RootComponent);
	}
	

	
}