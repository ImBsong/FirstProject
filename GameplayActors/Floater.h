// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class FIRSTPROJECT_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category= "ActorMeshComponents")
	UStaticMeshComponent* StaticMesh;

	// Location used by SetActorLocation() when BeginPlay() is called
	UPROPERTY(EditInstanceOnly, BluePrintReadWrite, Category = "Floater Variables")
	FVector InitialLocation;

	// Location of the Actor when dragged in from the Editor
	UPROPERTY(VisibleInstanceOnly, BluePrintReadWrite, Category = "Floater Variables")
	FVector PlacedLocation;

	UPROPERTY(VisibleDefaultsOnly, BluePrintReadOnly, Category = "Floater Variables")
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	bool bShouldFloat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
	bool bInitializeFloaterLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables")
	bool bShouldRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables")
	FRotator SpinCycle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables")
	FVector InitialForce;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")
	FVector InitialTorque;

private:
	float RunningTime;

	float BaseZLocation;

public:
	// Amplitude - Amplitude of the up and down
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	float A;
	
	// Period - (2 * PI / abs(B)) - How fast it oscillates up and down
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	float B;

	// Phase Shift - You can have it start lower or bottom of the sin wave
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	float C;

	// Verticle Shift - This is where you offset the entire wave
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	float D;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
