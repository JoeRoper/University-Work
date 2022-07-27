// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ImageWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COURSEWORK_API UImageWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* Image_74;
};
