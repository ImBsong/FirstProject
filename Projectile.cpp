// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Main.h"
#include "MainPlayerController.h"
#include "Sound/SoundCue.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (RootComponent == nullptr) // !RootComponent
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));

		// if collision component does not exist
		if (!CollisionComponent)
		{
			CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
			
			// Setting the collision preset to the custom "Projectile" channel made
			CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));


			CollisionComponent->InitSphereRadius(15.0f);
			RootComponent = CollisionComponent;
		}
	}

	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3500.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	Damage = 15.f;
	InitialLifeSpan = 5.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Get Main
	Main = Cast<AMain>(UGameplayStatics::GetPlayerPawn(this, 0));

	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// Binding function to projectile collision hit
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		UGameplayStatics::ApplyDamage(Enemy, Damage, WeaponInstigator, this, DamageTypeClass);
		if (Main)
		{
			Enemy->MoveToTarget(Main);
			Main->SetCombatTarget(Enemy);
			Main->SetHasCombatTarget(true);

			if (MainPlayerController)
			{
				MainPlayerController->DisplayEnemyHealthBar();
			}
		}
	}
	
	if (OnHitSound)
	{
		UGameplayStatics::PlaySound2D(this, OnHitSound);
	}

	Destroy();	
}

