// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyEyeParticleSystem.generated.h"

/**
 * 
 */
UCLASS()
class EYEOFSAURON_API AMyEyeParticleSystem : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = ParticleSystem)
	TSubobjectPtr<USphereComponent> EyeCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<UStaticMeshComponent> EyeMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = ParticleSystem)
	TArray<UParticleSystemComponent*> P_EyeOfSauronEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	TArray<UParticleSystem*> ParticleTemplates;

	UFUNCTION(BlueprintNativeEvent)
	void SetParticleSystemUp();

	virtual void BeginPlay() override;
	
	virtual void Tick(float deltaSeconds) override;

	bool posChanged;
};
