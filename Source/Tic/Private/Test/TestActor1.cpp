// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestActor1.h"
#include "Tic.h"

ATestActor1::ATestActor1()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (StaticMesh)
	{
		SetRootComponent(StaticMesh);
	}
}

void ATestActor1::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(WJTest, Log, TEXT("Test LOG"));
}

void ATestActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

