// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AttackAnimCharacter.h"
#include "AnimInst.h"
#include "AttackWeapon.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AAttackAnimCharacter

AAttackAnimCharacter::AAttackAnimCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	/*
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("/Game/Action/Fight_Idle.Fight_Idle"));
	if (SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}
	*/
	/*
	FName WeaponSocket(TEXT("right_hand_S"));
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/Action/SK_Blade_Sucker.SK_Blade_Sucker"));
		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetSkeletalMesh(SK_WEAPON.Object);
		}
		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}
	*/

	IsAttacking = false;
	IsNextAttack = false;
	ClickCount = 1;
	TotalDamage = 0;
	/*
	while (MontNum.Num() <= 5)
	{
		MontNum.Add(FMath::RandRange(1, 5));
	}
	*/
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AAttackAnimCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AAttackAnimCharacter::Attack);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAttackAnimCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAttackAnimCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AAttackAnimCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AAttackAnimCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AAttackAnimCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AAttackAnimCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AAttackAnimCharacter::OnResetVR);
}

//모든 컴포넌트가 초기화 된 후에 돌아감 (생성자 이후에 돌아감)
void AAttackAnimCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AAnim = Cast<UAnimInst>(GetMesh()->GetAnimInstance());
	if (::IsValid(AAnim))
	{
		AAnim->OnMontageEnded.AddDynamic(this, &AAttackAnimCharacter::OnAttackMontageEnded);
	}
	
	AAnim->OnNextAttackCheck.AddLambda([this]()->void
	{
		UE_LOG(LogTemp, Warning, TEXT("Character: NextAttackCheck"));
		this->IsAttacking = false;


		if (this->IsNextAttack)
		{
			this->IsNextAttack = false;
			while (true)
			{
				int32 rdNum = FMath::RandRange(1, 5);
				bool exist = list.Contains(rdNum);
				if (!exist)
				{
					list.Add(rdNum);
					break;
				}
			}
			this->ClickCount = list.Last();
			if (list.Num() > 3) list.RemoveAt(0);
			//this->ClickCount++;
			//if (this->ClickCount == 4) this->ClickCount = 1;
			this->IsAttacking = true;
			AAnim->PlayAttackMontage(this->ClickCount);
		}
		else
		{
			this->ClickCount = 1;
		}
	});

	AAnim->OnAttackHitCheck.AddUObject(this, &AAttackAnimCharacter::AttackCheck);
	
}

float AAttackAnimCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	TotalDamage += FinalDamage;
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s took Damage: %f"), *GetName(), TotalDamage);

	if (TotalDamage >= 150.0F)
	{
		AAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	}
	return TotalDamage;
}

void AAttackAnimCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	//IsAttacking = false;
}

bool AAttackAnimCharacter::CanSetWeapon()
{
	return (nullptr == CurrentWeapon);
}

void AAttackAnimCharacter::SetWeapon(AAttackWeapon * NewWeapon)
{
	FName WeaponSocket(TEXT("right_hand_S"));
	if (nullptr != NewWeapon)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

void AAttackAnimCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector()*150.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0F),
		Params
	);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name: %s"), *HitResult.Actor->GetName());
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(50.0F, DamageEvent, GetController(), this);
		}
	}
}

void AAttackAnimCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*
	FName WeaponSocket(TEXT("right_hand_S"));
	auto CurWeapon = GetWorld()->SpawnActor<AAttackWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);\
		if (nullptr != CurWeapon)
		{
			CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}
		*/
}

void AAttackAnimCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AAttackAnimCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AAttackAnimCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AAttackAnimCharacter::Attack()
{
	if (IsAttacking)
	{
		IsNextAttack = true;
	}
	else
	{
		IsAttacking = true;
		AAnim->PlayAttackMontage(ClickCount);
	}

	/*
	if (IsAttacking) return;

	//AAnim->PlayAttackMontage();
	if (ClickCount == 3) ClickCount = 0;
	ClickCount += 1;
	FString sSection = FString::Printf(TEXT("Attack%d"), ClickCount);
	AAnim->PlaySection(FName(*sSection));
	IsAttacking = true;
	*/
}

void AAttackAnimCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AAttackAnimCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AAttackAnimCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAttackAnimCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
