// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/TicCollision.h"

FTicCollision::FTicCollision()
{
}

FTicCollision::~FTicCollision()
{
}

ECollisionChannel FTicCollision::CollisionChannel_TicCharacter()
{
	return ECollisionChannel::ECC_GameTraceChannel1;
}

FName FTicCollision::ProfileName_TicCharacter()
{
	return FName("TicCharacter");
}
