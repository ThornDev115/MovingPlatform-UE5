// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Sets the start location to the obects stating spot on play
	StartLocation = GetActorLocation();

	FString Name = GetName();

	// Console letting us know this worked
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Calls these methods every frame
		// We use DeltaTime to make sure its not frame dependent because some hardware is better than others
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}


void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		// Makes a new variable called "MoveDirection" which is then set to "PlatformVelocity" which is an FVector with an x, y, z axis
			// "GetSafeNormal()" Gets a normalized copy of the vector, checking it is safe to do so based on the length. Returns zero vector if vector length is too small to safely normalize.
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// StartLocation is made equal to these so the Actor can have a direction and distance to move
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		// Makes the StartingLocation the first location so it can remember to go back to this
		SetActorLocation(StartLocation);
		// PlatformVelcoity then decreases until it hits a certain point
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		// CurrentLocation is set to GetActorLocation
		FVector CurrentLocation = GetActorLocation();
		// CurrentLocation is given a velocity so it can move to the desiered location
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		// Moves the Actpr with the CurrentLocation
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	// Makes it so the Actor Rotation values are able to be modified by CurrentRotation
	FRotator CurrentRotation = GetActorRotation();
	// CurrentRotation is then set to add the RotationVelocity overtime
	CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	// Gives the actor the rotation from current rotation
	SetActorRotation(CurrentRotation);
}


bool AMovingPlatform::ShouldPlatformReturn() const
{
	// Checks if the Distance Moved is greater than Move Distance
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	// Calculates the distance between the ActorLocation and StartLocation
	return FVector::Dist(StartLocation, GetActorLocation());
}
