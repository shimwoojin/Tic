// Fill out your copyright notice in the Description page of Project Settings.


#include "TicGameModeBase.h"
#include "Character/TicPlayerController.h"
#include "Character/TicPlayerCharacter.h"
#include "Character/TicPlayerState.h"

ATicGameModeBase::ATicGameModeBase()
{
	//DefaultPawnClass = ATicPlayerCharacter::StaticClass();
	PlayerControllerClass = ATicPlayerController::StaticClass();
	PlayerStateClass = ATicPlayerState::StaticClass();
}
