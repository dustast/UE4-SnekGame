// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	SphereComp->SetupAttachment(RootComponent);
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::DestroyActors);
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSBlackHole::DestroyActors(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SphereComp->GetOverlappingComponents(OverlappingActors);
	for (int i = 0; i < OverlappingActors.Num(); i++)
	{
		UPrimitiveComponent* PrimComp = OverlappingActors[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			const float RadSize = SphereComp->GetScaledSphereRadius();
			const float RadStrength = -2500.f;
			PrimComp->AddRadialForce(GetActorLocation(), RadSize, RadStrength, ERadialImpulseFalloff::RIF_Constant,true);
		}
		

	}
}

