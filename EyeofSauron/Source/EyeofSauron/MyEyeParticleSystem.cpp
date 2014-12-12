// Fill out your copyright notice in the Description page of Project Settings.

#include "EyeofSauron.h"
#include "MyEyeParticleSystem.h"


AMyEyeParticleSystem::AMyEyeParticleSystem(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	EyeCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("EyeSphereComponent"));
	RootComponent = EyeCollisionComponent;
	EyeCollisionComponent->SetWorldLocation(FVector(-1050, -750, 600), false);
	EyeMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("EyeMesh"));

	//turn physics on
	EyeMesh->SetSimulatePhysics(false);

	EyeMesh->AttachTo(RootComponent);
}

void AMyEyeParticleSystem::BeginPlay()
{
	Super::BeginPlay();
	SetParticleSystemUp();
}

void AMyEyeParticleSystem::SetParticleSystemUp_Implementation()
{
	float EyeRadius = EyeCollisionComponent->GetUnscaledSphereRadius();
	FVector EyeLocation = EyeCollisionComponent->GetComponentLocation();
	FVector BeamEndLoc1(EyeLocation.X + 150, EyeLocation.Y - 65, EyeLocation.Z);
	FVector BeamEndLoc2(EyeLocation.X - 150, EyeLocation.Y + 65, EyeLocation.Z);
	TArray<FVector> PointsOnEye;
	for (float i = 0; i <= 360; i += 30)
	{
		for (float j = 0; j <= 360; j += 30)
		{
			PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((i * 22) / (180 * 7)))));
		}
	}
	for (int i = 0; i < PointsOnEye.Num(); i++)
	{
		P_EyeOfSauronEmitter.Add(UGameplayStatics::SpawnEmitterAttached(ParticleTemplates[0], EyeCollisionComponent, NAME_None, PointsOnEye[i], GetActorRotation(), EAttachLocation::KeepWorldPosition, true));
		if (PointsOnEye[i].X > EyeLocation.X)
			P_EyeOfSauronEmitter.Last()->SetBeamEndPoint(0, BeamEndLoc1);
		else if (PointsOnEye[i].X < EyeLocation.X)
			P_EyeOfSauronEmitter.Last()->SetBeamEndPoint(0, BeamEndLoc2);
		else if (PointsOnEye[i].X == EyeLocation.X)
		{
			P_EyeOfSauronEmitter.Last()->SetBeamEndPoint(0, BeamEndLoc1);
			P_EyeOfSauronEmitter.Last()->SetBeamEndPoint(0, BeamEndLoc2);
		}
	}
}


