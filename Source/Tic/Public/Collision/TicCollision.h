// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TIC_API FTicCollision
{
public:
	FTicCollision();
	~FTicCollision();

	//CollisionChannel
	static ECollisionChannel CollisionChannel_TicCharacter();

	//Collision Preset
	static FName ProfileName_TicCharacter();
};
