// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"


void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (HUDOverlayAsset)
    {
        HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
    }

    HUDOverlay->AddToViewport();
    HUDOverlay->SetVisibility(ESlateVisibility::Visible);

    /** If Enemy Health Bar is set in blueprint */
    if (WEnemyHealthBar)
    {
        EnemyHealthBar = CreateWidget<UUserWidget>(this, WEnemyHealthBar);
        if (EnemyHealthBar)
        {
            EnemyHealthBar->AddToViewport();
            EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
        }
        FVector2D Alignment(0.f, 0.f);
        EnemyHealthBar->SetAlignmentInViewport(Alignment);
    }

    if (WPauseMenu)
    {
        PauseMenu = CreateWidget<UUserWidget>(this, WPauseMenu);
        if (WPauseMenu)
        {
            PauseMenu->AddToViewport();
            PauseMenu->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if (WCrosshair)
    {
        Crosshair = CreateWidget<UUserWidget>(this, WCrosshair);
        if (WCrosshair)
        {
            Crosshair->AddToViewport();
            Crosshair->SetVisibility(ESlateVisibility::Hidden);
            bCrosshairVisible = false;
        }
    }
}

void AMainPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /** This is to set the health bar above the enemy */
    if (EnemyHealthBar)
    {
        FVector2D PositionInViewport;
        ProjectWorldLocationToScreen(EnemyLocation, PositionInViewport);
        PositionInViewport.Y -= 100.f;
        PositionInViewport.X -= 100.f;

        FVector2D SizeInViewport = FVector2D(300.f, 25.f);

        EnemyHealthBar->SetPositionInViewport(PositionInViewport);
        EnemyHealthBar->SetDesiredSizeInViewport(SizeInViewport);
    }
}

void AMainPlayerController::DisplayEnemyHealthBar()
{
    if (EnemyHealthBar)
    {
        bEnemyHealthBarVisible = true;
        EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
    }
}

void AMainPlayerController::RemoveEnemyHealthBar()
{
    if (EnemyHealthBar)
    {
        bEnemyHealthBarVisible = false;
        EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AMainPlayerController::DisplayPauseMenu_Implementation()
{
    if (PauseMenu)
    {
        bPauseMenuVisible = true;
        PauseMenu->SetVisibility(ESlateVisibility::Visible);

        FInputModeGameAndUI InputModeGameAndUI;

        SetInputMode(InputModeGameAndUI);
        bShowMouseCursor = true;
    }
}

void AMainPlayerController::RemovePauseMenu_Implementation()
{
    if (PauseMenu)
    {
        GameModeOnly();

        bShowMouseCursor = false;

        bPauseMenuVisible = false;
    }
}

void AMainPlayerController::TogglePauseMenu()
{
    if (bPauseMenuVisible)
    {
        RemovePauseMenu();
    }
    else
    {
        DisplayPauseMenu();
    }
}

void AMainPlayerController::GameModeOnly()
{
    FInputModeGameOnly InputModeGameOnly;

    SetInputMode(InputModeGameOnly);
}

void AMainPlayerController::DisplayCrosshair_Implementation()
{
    if (Crosshair)
    {
        bCrosshairVisible = true;
    }
}

void AMainPlayerController::RemoveCrosshair()
{
    if (Crosshair)
    {
        bCrosshairVisible = false;
        Crosshair->SetVisibility(ESlateVisibility::Hidden);
    }
}