#include <iostream>

void PrintIntroduction(int Difficulty)
{
	std::cout << "\n\nYou are a secret agent breaking into a level " << Difficulty;
	std::cout << "secure server room ... \nYou need to enter the correct codes to continue...  \n\n";
}

bool PlayGame(int Difficulty)
{
	PrintIntroduction(Difficulty);

	const int CodeA = rand() % Difficulty + Difficulty;
	const int CodeB = rand() % Difficulty + Difficulty;
	const int CodeC = rand() % Difficulty + Difficulty;

	const int CodeSum = CodeA + CodeB + CodeC;
	const int CodeProduct = CodeA * CodeB * CodeC;

	std::cout << "+ There are 3 numbers in the code";
	std::cout << "\n+ The 3 codes add-up to: " << CodeSum;
	std::cout << "\n+ The 3 codes multiply to: " << CodeProduct << std::endl;

	int GuessA, GuessB, GuessC;

	std::cin >> GuessA;
	std::cin >> GuessB;
	std::cin >> GuessC;

	const int GuessSum = GuessA + GuessB + GuessC;
	const int GuessProduct = GuessA * GuessB * GuessC;

	if (GuessSum == CodeSum && GuessProduct == CodeProduct)
	{
		std::cout << "\n*** Well done agent! You have extracted a file! Keep going! ***";
		return true;
	}
	else
	{
		std::cout << "\n*** You entered the wrong code! Careful agent! Try again! ***";
		return false;
	}
}

int main()
{
	const int MaxDifficulty = 5;
	int LevelDifficulty = 1;

	while (MaxDifficulty >= LevelDifficulty)
	{
		bool bLevelComplete = PlayGame(LevelDifficulty);
		std::cin.clear();
		std::cin.ignore();

		if (bLevelComplete)
		{
			++LevelDifficulty;
		}
	}

	std::cout << "\n*** Great work agent! You got all the files! Now get out of there! ***\n";

	return 0;
}
