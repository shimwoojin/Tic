// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/TicPlayerCharacter.h"
#include "Tic.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Character/TicPlayerState.h"
#include "AbilitySystem/AttributeSets/TicPlayerAttributeSet.h"

ATicPlayerCharacter::ATicPlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	//Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArm)
	{
		SpringArm->SetupAttachment(GetRootComponent());
		SpringArm->SocketOffset = FVector(0.0f, 0.0f, 80.0f);
		SpringArm->TargetArmLength = 400.0f;
		SpringArm->bUsePawnControlRotation = true;
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera)
	{
		Camera->SetupAttachment(SpringArm);
		Camera->bUsePawnControlRotation = false;
	}
}

void ATicPlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		PlayerController->ConsoleCommand(TEXT("showdebug abilitysystem"));
	}

	if (AbilitySystemComponent)
	{
		const UTicPlayerAttributeSet* Set = AbilitySystemComponent->GetSet<UTicPlayerAttributeSet>();
		if (Set)
		{
			UE_LOG(WJTest, Log, TEXT("Attribute Set's TestData : %.0f"), Set->GetTestData());
			UE_LOG(WJTest, Log, TEXT("Attribute Set's HP : %.0f"), Set->GetHP());
		}
	}
}

void ATicPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATicPlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATicPlayerCharacter::Look);

		SetupGASInputComponent();
	}
	else
	{
		UE_LOG(TicCommonLog, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATicPlayerCharacter::SetupGASInputComponent()
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (IsValid(AbilitySystemComponent) && IsValid(EnhancedInputComponent))
	{
		UE_LOG(TicInput, Log, TEXT("SetupGASInputComponent"));

		//Jump	
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::GasInputPressed, 0);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::GasInputReleased, 0);

		//LMouse
		EnhancedInputComponent->BindAction(LMouseAction, ETriggerEvent::Started, this, &ThisClass::GasInputPressed, 1);
		EnhancedInputComponent->BindAction(LMouseAction, ETriggerEvent::Completed, this, &ThisClass::GasInputReleased, 1);

		//RMouse
		EnhancedInputComponent->BindAction(RMouseAction, ETriggerEvent::Started, this, &ThisClass::GasInputPressed, 2);
		EnhancedInputComponent->BindAction(RMouseAction, ETriggerEvent::Completed, this, &ThisClass::GasInputReleased, 2);
	}
}

void ATicPlayerCharacter::GasInputPressed(int32 InputID)
{
	UE_LOG(TicInput, Log, TEXT("Input Pressed, InputID : %d"), InputID);
	check(AbilitySystemComponent);
	AbilitySystemComponent->PressInputID(InputID);
}

void ATicPlayerCharacter::GasInputReleased(int32 InputID)
{
	UE_LOG(TicInput, Log, TEXT("Input Released, InputID : %d"), InputID);
	check(AbilitySystemComponent);
	AbilitySystemComponent->ReleaseInputID(InputID);
}

void ATicPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATicPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATicPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerState* TicPlayerState = GetPlayerState<ATicPlayerState>();
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(TicPlayerState);
	if (AbilitySystemInterface)
	{
		AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
		check(AbilitySystemComponent);
		AbilitySystemComponent->InitAbilityActorInfo(TicPlayerState, this);

		InitStartAbilities();
	}
}

void ATicPlayerCharacter::InitStartAbilities()
{
	Super::InitStartAbilities();

	for (const auto& StartInputAbility : StartInputAbilities)
	{
		FGameplayAbilitySpec Spec(StartInputAbility.Value);
		Spec.InputID = StartInputAbility.Key;
		AbilitySystemComponent->GiveAbility(Spec);
	}
}
