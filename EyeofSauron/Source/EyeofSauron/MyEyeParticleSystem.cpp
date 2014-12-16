// Fill out your copyright notice in the Description page of Project Settings.

#include "EyeofSauron.h"
#include "MyEyeParticleSystem.h"


AMyEyeParticleSystem::AMyEyeParticleSystem(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	EyeCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("EyeSphereComponent"));
	RootComponent = EyeCollisionComponent;
	EyeCollisionComponent->SetWorldLocation(FVector(-1050, -750, 600), false);
	EyeMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("EyeMesh"));

	//turn physics on
	EyeMesh->SetSimulatePhysics(false);

	EyeMesh->AttachTo(RootComponent);
	posChanged = false;
}

void AMyEyeParticleSystem::BeginPlay()
{
	Super::BeginPlay();
	SetParticleSystemUp();
}

void AMyEyeParticleSystem::SetParticleSystemUp_Implementation()
{
	float EyeRadius = 100/*EyeCollisionComponent->GetUnscaledSphereRadius()*/;
	FVector EyeLocation = EyeCollisionComponent->GetComponentLocation();
	FVector BeamEndLoc1(EyeLocation.X + 110, EyeLocation.Y - 110, EyeLocation.Z);
	FVector BeamEndLoc2(EyeLocation.X - 140, EyeLocation.Y + 110, EyeLocation.Z);
	TArray<FVector> PointsOfEyeStart;
	TArray<FVector> PointsOfEyeEnd;
	for (float i = 90; i <= 120; i += 15)
	{
		/*int count = 0;
		for (float j = -30; j <= 30; j += 5)
		{
		PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((i * 22) / (180 * 7)))));
		PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((i * 22) / (180 * 7)))));
		count++;
		}
		count = 0;
		for (float j = 150; j <= 210; j += 5)
		{
		PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
		PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (15 - count)) * cos((j * 22) / (180 * 7)))));
		count++;
		}*/
		int count = 0;
		for (float j = 0; j <= 360; j += 10)
		{
			PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
			PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((j * 22) / (180 * 7)))));
			count++;
		}
	}
	for (float i = 270; i <= 300; i += 15)
	{
		/*int count = 0;
		for (float j = -30; j <= 30; j += 5)
		{
		PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((i * 22) / (180 * 7)))));
		PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((i * 22) / (180 * 7)))));
		count++;
		}
		count = 0;
		for (float j = 150; j <= 210; j += 5)
		{
		PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
		PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (15 - count)) * cos((j * 22) / (180 * 7)))));
		count++;
		}*/
		int count = 0;
		for (float j = 0; j <= 360; j += 10)
		{
			PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
			PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((j * 22) / (180 * 7)))));
			count++;
		}
	}
	for (int i = 0; i < PointsOfEyeStart.Num(); i++)
	{
		P_EyeOfSauronEmitter.Add(UGameplayStatics::SpawnEmitterAttached(ParticleTemplates[1], EyeCollisionComponent, NAME_None, PointsOfEyeStart[i], GetActorRotation(), EAttachLocation::KeepWorldPosition, true));
		P_EyeOfSauronEmitter.Last()->SetBeamEndPoint(0, PointsOfEyeEnd[i]);
	}
	TArray<FVector> PointsOnEye;
	for (float i = 90; i <= 120; i += 10)
	{
		/*for (float j = -60; j <= 60; j += 10)
		{
		PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
		}
		for (float j = 120; j <= 240; j += 10)
		{
		PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
		}*/
		for (float j = 0; j <= 360; j += 30)
		{
			PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
		}
	}
	for (float i = 270; i <= 300; i += 10)
	{
		/*for (float j = -60; j <= 60; j += 10)
		{
		PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
		}
		for (float j = 120; j <= 240; j += 10)
		{
		PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
		}*/
		for (float j = 0; j <= 360; j += 30)
		{
			PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
		}
	}
	//squiggly lines coming out of the eye
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
	//red rays of the eye
}

void AMyEyeParticleSystem::Tick(float deltaSeconds)
{
	static int count = 1;
	static int temp = 250;
	static int offsetX, offsetY;
	if (!posChanged)
	{
		if ((count % temp) == 0)
		{
			posChanged = true;
			count = 0;
			temp = (rand() % 250) + 250;
			//update eye location and particle system start and end points
			offsetX = rand() % 100 * (((rand() % 2) == 0) ? 1 : -1);
			offsetY = rand() % 100 * (((rand() % 2) == 0) ? 1 : -1);
			this->AddActorWorldOffset(FVector(offsetX, offsetY, 0), true);
			/*EyeCollisionComponent->AddWorldOffset(FVector(offset, offset, 0), true);*/
			FVector EyeLocation = EyeCollisionComponent->GetComponentLocation();
			float EyeRadius = 100/*EyeCollisionComponent->GetUnscaledSphereRadius()*/;
			TArray<FVector> PointsOfEyeStart;
			TArray<FVector> PointsOfEyeEnd;
			for (float i = 90; i <= 120; i += 15)
			{
				/*int count = 0;
				for (float j = -30; j <= 30; j += 5)
				{
				PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((i * 22) / (180 * 7)))));
				PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((i * 22) / (180 * 7)))));
				count++;
				}
				count = 0;
				for (float j = 150; j <= 210; j += 5)
				{
				PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (15 - count)) * cos((j * 22) / (180 * 7)))));
				count++;
				}*/
				int count = 0;
				for (float j = 0; j <= 360; j += 10)
				{
					PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
					PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((j * 22) / (180 * 7)))));
					count++;
				}
			}
			for (float i = 270; i <= 300; i += 15)
			{
				/*int count = 0;
				for (float j = -30; j <= 30; j += 5)
				{
				PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((i * 22) / (180 * 7)))));
				PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((i * 22) / (180 * 7)))));
				count++;
				}
				count = 0;
				for (float j = 150; j <= 210; j += 5)
				{
				PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (15 - count)) * cos((j * 22) / (180 * 7)))));
				count++;
				}*/
				int count = 0;
				for (float j = 0; j <= 360; j += 10)
				{
					PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
					PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((j * 22) / (180 * 7)))));
					count++;
				}
			}
			int i = 0;
			for (i = 0; i < PointsOfEyeStart.Num(); i++)
			{
				P_EyeOfSauronEmitter[i]->SetBeamSourcePoint(0, PointsOfEyeStart[i], 0);
				P_EyeOfSauronEmitter[i]->SetBeamEndPoint(0, PointsOfEyeEnd[i]);
			}

			TArray<FVector> PointsOnEye;
			for (float i = 90; i <= 120; i += 10)
			{
				/*for (float j = -60; j <= 60; j += 10)
				{
				PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}
				for (float j = 120; j <= 240; j += 10)
				{
				PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}*/
				for (float j = 0; j <= 360; j += 30)
				{
					PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}
			}
			for (float i = 270; i <= 300; i += 10)
			{
				/*for (float j = -60; j <= 60; j += 10)
				{
				PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}
				for (float j = 120; j <= 240; j += 10)
				{
				PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}*/
				for (float j = 0; j <= 360; j += 30)
				{
					PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}
			}
			//int i = 0; //filler
			for (int j = 0; j < PointsOnEye.Num(); j++)
			{
				P_EyeOfSauronEmitter[i + j]->SetBeamSourcePoint(0, PointsOnEye[j], 0);
			}
		}
		count++;
	}
	else
	{
		if (count < 50)
		{
			count++;
		}
		else
		{
			posChanged = false;
			count = 0;
			this->AddActorWorldOffset(FVector(-offsetX, -offsetY, 0), true);
			/*EyeCollisionComponent->AddWorldOffset(FVector(-offset, -offset, 0), true);*/
			FVector EyeLocation = EyeCollisionComponent->GetComponentLocation();
			float EyeRadius = 100/*EyeCollisionComponent->GetUnscaledSphereRadius()*/;

			TArray<FVector> NewPointsOfEyeStart;
			TArray<FVector> NewPointsOfEyeEnd;
			for (float i = 90; i <= 120; i += 15)
			{
				/*int count = 0;
				for (float j = -30; j <= 30; j += 5)
				{
				PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((i * 22) / (180 * 7)))));
				PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((i * 22) / (180 * 7)))));
				count++;
				}
				count = 0;
				for (float j = 150; j <= 210; j += 5)
				{
				PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (15 - count)) * cos((j * 22) / (180 * 7)))));
				count++;
				}*/
				int count = 0;
				for (float j = 0; j <= 360; j += 10)
				{
					NewPointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
					NewPointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((j * 22) / (180 * 7)))));
					count++;
				}
			}
			for (float i = 270; i <= 300; i += 15)
			{
				/*int count = 0;
				for (float j = -30; j <= 30; j += 5)
				{
				PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((i * 22) / (180 * 7)))));
				PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * cos((j * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((i * 22) / (180 * 7)) * sin((j * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((i * 22) / (180 * 7)))));
				count++;
				}
				count = 0;
				for (float j = 150; j <= 210; j += 5)
				{
				PointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				PointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (15 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (15 - count)) * cos((j * 22) / (180 * 7)))));
				count++;
				}*/
				int count = 0;
				for (float j = 0; j <= 360; j += 10)
				{
					NewPointsOfEyeEnd.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
					NewPointsOfEyeStart.Add(FVector(EyeLocation.X + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + ((EyeRadius / (13 - count)) * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + ((EyeRadius / (13 - count)) * cos((j * 22) / (180 * 7)))));
					count++;
				}
			}
			int i = 0;;
			for (i = 0; i < NewPointsOfEyeStart.Num(); i++)
			{
				P_EyeOfSauronEmitter[i]->SetBeamSourcePoint(0, NewPointsOfEyeStart[i], 0);
				P_EyeOfSauronEmitter[i]->SetBeamEndPoint(0, NewPointsOfEyeEnd[i]);
			}

			TArray<FVector> NewPointsOnEye;
			for (float i = 90; i <= 120; i += 10)
			{
				/*for (float j = -60; j <= 60; j += 10)
				{
				PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}
				for (float j = 120; j <= 240; j += 10)
				{
				PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}*/
				for (float j = 0; j <= 360; j += 30)
				{
					NewPointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}
			}
			for (float i = 270; i <= 300; i += 10)
			{
				/*for (float j = -60; j <= 60; j += 10)
				{
				PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}
				for (float j = 120; j <= 240; j += 10)
				{
				PointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}*/
				for (float j = 0; j <= 360; j += 30)
				{
					NewPointsOnEye.Add(FVector(EyeLocation.X + (EyeRadius * sin((j * 22) / (180 * 7)) * cos((i * 22) / (180 * 7))), EyeLocation.Y + (EyeRadius * sin((j * 22) / (180 * 7)) * sin((i * 22) / (180 * 7))), EyeLocation.Z + (EyeRadius * cos((j * 22) / (180 * 7)))));
				}
			}
			//int i = 0; //filler
			for (int j = 0; j < NewPointsOnEye.Num(); j++)
			{
				P_EyeOfSauronEmitter[i + j]->SetBeamSourcePoint(0, NewPointsOnEye[j], 0);
			}
		}
	}
	Super::Tick(deltaSeconds);
}


