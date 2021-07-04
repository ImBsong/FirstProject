// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class FIRSTPROJECT_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Mesh Component
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return MeshComponent; }
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* Mesh) { MeshComponent = Mesh; }

	// Sphere Component
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* SphereComponent;

	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereComponent; }
	FORCEINLINE void SetSphereComponent(USphereComponent* Sphere) { SphereComponent = Sphere; }

	// Camera Component
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* CameraComponent;

	FORCEINLINE UCameraComponent* GetCameraComponent() { return CameraComponent; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* Camera) { CameraComponent = Camera; }

	// Springarm Component
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* SpringArmComponent;

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArmComponent; }
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* SpringArm) { SpringArmComponent = SpringArm; }

	// Our custom movement component
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UColliderMovementComponent* OurMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void YawCamera(float AxisValue);
	void PitchCamera(float AxisValue);

	FVector2D CameraInput;
};
