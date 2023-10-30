// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void USlashOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetGold(int32 Gold)
{
	if (GoldCountText)
	{
		const FString GoldString = FString::Printf(TEXT("%d"), Gold);
		const FText GoldText = FText::FromString(GoldString);
		GoldCountText->SetText(GoldText);
	}
}

void USlashOverlay::SetSouls(int32 Souls)
{
	if (SoulsCountText)
	{
		const FString SoulString = FString::Printf(TEXT("%d"), Souls);
		const FText SoulText = FText::FromString(SoulString);
		SoulsCountText->SetText(SoulText);
	}
}
