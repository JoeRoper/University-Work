// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacterBase.generated.h"
#include "Components/AudioComponent.h"


UCLASS()
class UNREAL_COURSEWORK_API AFirstPersonCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	////Shotgun Variables/////////////
	//Vectors//

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun C++")
		FVector CameraLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun C++")
		FVector CameraRight = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun C++")
		FVector CameraUp = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun C++")
		FVector CameraForward = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shotgun C++")
		UCurveFloat* BulletCurve;

	//Vectors//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		FVector TraceStart = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		FVector TraceEnd = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		FVector TraceDirection = FVector(0.0f, 0.0f, 0.0f);


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		bool LeanLeftKeyDown = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		bool LeanRightKeyDown = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		bool DefaultCrosshairBool = true;

	UPROPERTY(EditAnywhere, Category = "C++")
		TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "C++")
		class UImageWidget* HUD_Widget;

	/////////////////Handle Fire/////////////////
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		float BulletStrength = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		float TraceDistance = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		class UAnimMontage* M_FirstPersonFire;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		class USoundCue* FireSoundCue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		class UDecalComponent* BulletHoleComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		class ADecalActor* BulletHoleDecal;

	///////////////Shotgun HandleFire//////////////////
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "C++")
		float BulletAngle = 5.0f;

private:
	UAudioComponent* FireAudioComponent;

public:
	// Sets default values for this character's properties
	AFirstPersonCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetGun(float Value);
	void SetShotGun(float Value);
	void LeanLeft(float Value);
	void LeanRight(float Value);

	void Fire(float Value);
	void HandleFire();
	void ShotgunHandleFire();
	void SpawnBulletHole(FHitResult Hit);
	FVector2D RandPointInCircle(float Radius);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
