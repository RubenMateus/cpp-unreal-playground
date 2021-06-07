// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();

	Isograms = GetValidWords(Words);

	SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else
	{
		ProcessGuess(Input);
	}
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to Bull Cows!"));

	HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("Welcome to Bull Cows!"));
	PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %i lives."), Lives);
	PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
	if (Guess.Equals(HiddenWord))
	{
		PrintLine(TEXT("You have Won!"));
		EndGame();
		return;
	}

	if (HiddenWord.Len() != Guess.Len())
	{
		PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \n You have %i lives remaining"), Lives);
		return;
	}

	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letter, guess again"));
		return;
	}

	--Lives;
	PrintLine(TEXT("You have lost a life."));

	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"), HiddenWord.Len());
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
		EndGame();
		return;
	}

	FBullCowCount Count = GetBullCows(Guess);

	PrintLine(TEXT("You have %i Bulls and %i Cows"), Count.Bulls, Count.Cows);
	PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	for (int32 i = 0; i < Word.Len(); i++)
	{
		for (int32 j = i + 1; j < Word.Len(); j++)
		{
			if (Word[i] == Word[j])
			{
				return false;
			}
		}
	}

	return true;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
	FBullCowCount Count;

	for (int32 i = 0; i < Guess.Len(); i++)
	{
		if (Guess[i] == HiddenWord[i])
		{
			Count.Bulls++;
			continue;
		}

		for (int32 j = 0; j < HiddenWord.Len(); j++)
		{
			if (Guess[i] == HiddenWord[j])
			{
				Count.Cows++;
				break;
			}
		}
	}

	return Count;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
	TArray<FString> ValidWords;

	for (FString Word : WordList)
	{
		if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
		{
			ValidWords.Emplace(Word);
		}
	}

	return ValidWords;
}
