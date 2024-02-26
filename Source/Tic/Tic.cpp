// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tic.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Tic, "Tic" );

DEFINE_LOG_CATEGORY(WJTest);
DEFINE_LOG_CATEGORY(TicCommonLog);
DEFINE_LOG_CATEGORY(TicInput);
DEFINE_LOG_CATEGORY(TicAttributeBaseChange);
DEFINE_LOG_CATEGORY(TicAttributeChange);
DEFINE_LOG_CATEGORY(TicActivateAbility);
DEFINE_LOG_CATEGORY(TicEndAbility);
DEFINE_LOG_CATEGORY(TicAssetNotFound);