// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacterBase.h"

#include "Math/Vector.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
#include "ImageWidget.h"
#include "Animation/AnimInstance.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"

FVector2D AFirstPersonCharacterBase::RandPointInCircle(float Radius)
{
	float BulletCurveFloat = BulletCurve->GetFloatValue(FMath::FRandRange(0.0f, 1.0f));
	float PointX = 0.0f;
	float PointY = 0.0f;
	float DistanceFromCentre = 0.0f;

	BulletAngle = FMath::FRandRange(0.0f, 360.0f);
	DistanceFromCentre = FMath::FRandRange(0.0f, (Radius * BulletCurveFloat));


	PointX = DistanceFromCentre * (FMath::Cos(BulletAngle));
	PointX = DistanceFromCentre * (FMath::Sin(BulletAngle));

	FVector2D Points;
	Points.X = PointX;
	Points.Y = PointY;

	return Points;
	
}


// Sets default values
AFirstPersonCharacterBase::AFirstPersonCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundCue> FireSoundCueObject(TEXT("SoundCue'/Game/FireSoundCue.FireSoundCue'"));
	if (FireSoundCueObject.Succeeded())
	{
		FireSoundCue = FireSoundCueObject.Object;

		FireAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FireAudioComponent"));
		FireAudioComponent->SetupAttachment(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<ADecalActor> BulletHoleObject(TEXT("Texture2D'/Game/Media/T_BulletHole.T_BulletHole'"));
	if (BulletHoleObject.Succeeded())
	{
		BulletHoleDecal = BulletHoleObject.Object;
		BulletHoleComponent = CreateDefaultSubobject<UDecalComponent>(L"BulletHole");
		BulletHoleComponent->SetupAttachment(RootComponent);
	}

}

// Called when the game starts or when spawned
void AFirstPersonCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (FireAudioComponent && FireSoundCue)
	{
		FireAudioComponent->SetSound(FireSoundCue);
	}
	
}

void AFirstPersonCharacterBase::SetGun(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		DefaultCrosshairBool = true;

		//HUD_Widget->RemoveFromParent();
	}
}

void AFirstPersonCharacterBase::SetShotGun(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		DefaultCrosshairBool = false;

		if (IsValid(WidgetClass))
		{
			HUD_Widget = Cast<UImageWidget>(CreateWidget(GetWorld(), WidgetClass));

			if (HUD_Widget != nullptr)
			{
				HUD_Widget.AddToViewPort();
			}
		}
	}
}

void AFirstPersonCharacterBase::LeanLeft(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		LeanLeftKeyDown = true;
	}
}

void AFirstPersonCharacterBase::LeanRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		LeanRightKeyDown = true;
	}
}

void AFirstPersonCharacterBase::Fire(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		if (DefaultCrosshairBool)
		{
			//run handle fire
			HandleFire();
		}
		else
		{
			//run shot gun handle fire
			ShotgunHandleFire();
		}
	}
}

void AFirstPersonCharacterBase::HandleFire()
{
	BulletStrength = 1.0f;

	if (M_FirstPersonFire)
	{
		PlayAnimMontage(M_FirstPersonFire, 1.0f, NAME_None);
	}

	if (FireAudioComponent && FireSoundCue)
	{
		FireAudioComponent->Play(0.0f);
	}

	TraceStart = CameraLocation;

	TraceDirection = CameraForward;

	TraceEnd = TraceDirection.FVector::operator*(100000.0f);
	TraceEnd = TraceEnd.FVector::operator+(TraceStart);

	FHitResult Hit;
	FCollisionQueryParams TraceParams;


	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
	{
		SpawnBulletHole(Hit);
	}

	BulletStrength = BulletStrength - Hit.PhysMaterial().GetSurfaceDensity();
	
	if (BulletStrength > 0)
	{
		TraceDistance = Hit.Actor().GetActorBounds() * 4.0f;

		TraceStart = (TraceDirection * TraceDistance) + Hit.ImpactPoint();

		TraceEnd = TraceDirection.FVector::operator*(TraceDistance * -1) + TraceStart;

		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

		TraceStart = Hit.ImpactPoint();

		if (!GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
		{
			BulletStrength = 0.0f;
		}
		SpawnBulletHole(Hit);
	}
}

void AFirstPersonCharacterBase::ShotgunHandleFire()
{
	//Floats//
	float BulletDistance = 1000.0f;
	float NumBullets = 25.0f;
	float PI;
	for (int i = 0; i < NumBullets; i++)
	{

		FVector ShotGunTraceStart = FVector(0.0f, 0.0f, 0.0f);

		FVector ShotGunTraceEnd = FVector(0.0f, 0.0f, 0.0f);

		FVector ShotGunTraceDirection = FVector(0.0f, 0.0f, 0.0f);
		
		float Radius = 0.0f;

		Radius = (FMath::Tan(BulletAngle) * BulletDistance);

		FVector2D Points = RandPointInCircle(Radius);
		ShotGunTraceStart = CameraLocation;

		CameraForward.FVector::operator*(BulletDistance);
		FVector x = (CameraForward.FVector::operator*(BulletDistance));
		x = x.FVector::operator+(CameraLocation);
		FVector y = CameraRight.FVector::operator*(Points.X);
		FVector z = CameraUp.FVector::operator*(Points.Y);

		ShotGunTraceEnd = ShotGunTraceEnd.FVector::operator+(x);
		ShotGunTraceEnd = ShotGunTraceEnd.FVector::operator+(y);
		ShotGunTraceEnd = ShotGunTraceEnd.FVector::operator+(z);

		FHitResult Hit;
		FCollisionQueryParams TraceParams;

		GetWorld()->LineTraceSingleByChannel(Hit, ShotGunTraceStart, ShotGunTraceEnd, ECC_Visibility, TraceParams);

		if (GetWorld()->LineTraceSingleByChannel(Hit, ShotGunTraceStart, ShotGunTraceEnd, ECC_Visibility, TraceParams))
		{
			SpawnBulletHole(Hit);
		}
	}
}

void AFirstPersonCharacterBase::SpawnBulletHole(FHitResult Hit)
{
	FVector HitImpactNormal = Hit.ImpactNormal();
	FVector HitLocation = Hit.Location();

	if (BulletHoleComponent && BulletHoleDecal)
	{
		BulletHoleComponent->SetLifeSpan(10.0f);
		BulletHoleComponent->DecalSize = FVector(1.0f, 10.0f, 10.0f);
		BulletHoleDecal = GetWorld()->SpawnActor<ADecalActor>(Hit.Location, HitImpactNormal.FVector::Rotation());
	}
}

// Called every frame
void AFirstPersonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	CameraLocation = camManager->GetCameraLocation();

	CameraRight = camManager->GetActorRightVector();

	CameraUp = camManager->GetActorUpVector();

	CameraForward = camManager->GetActorForwardVector();
}

// Called to bind functionality to input
void AFirstPersonCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("SetGun", this, &AFirstPersonCharacterBase::SetGun);
	PlayerInputComponent->BindAxis("SetShotGun", this, &AFirstPersonCharacterBase::SetShotGun);

	PlayerInputComponent->BindAxis("LeanLeft", this, &AFirstPersonCharacterBase::LeanLeft);
	PlayerInputComponent->BindAxis("LeanRight", this, &AFirstPersonCharacterBase::LeanRight);

	PlayerInputComponent->BindAxis("Fire", this, &AFirstPersonCharacterBase::Fire);
}

