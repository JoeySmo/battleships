#include <iostream>
#include <cmath>
#include <windows.h>
#include <cwchar>

#include "Files/Ships.h"
#include "Other/FireHandler.h"
#include "EnemyHandler.h"

void SetupConsole()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_SCRIPT;
	cfi.FontWeight = FW_THIN;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	SetConsoleTitleW(L"Battleships");
}

void Setup()
{
	std::random_device rd;
	std::mt19937 engine(rd());

	std::uniform_int_distribution<int> dist(1, RAND_MAX);
	srand(dist(engine));

	SetupConsole();

	GenerateMap(MAP_SIZE_X, MAP_SIZE_Y);
	RevealedMap = Map;

	CShips();
	PopulateMap();
}

/// @brief runs everything
void Thread()
{
	Setup();
	unsigned int Mode = 0;

	printf("Welcome to Ships!\n");
	printf("What mode would you like to play?\n0 = Solo; 1 = Player vs Box; 2 = Player vs Player (Not implemented)\n");
	std::cin >> Mode;
	PlayMode ChosenMode = HandlePlayMode(Mode);

	switch (ChosenMode)
	{
	case PlayMode::SOLO:
	{
		printf("We have generated a map for you!\nHere it is\n");

Loop:
		for (int i = 0; i < Map.size(); i++)
			printf("%s", Map[i].c_str());

		printf("\n");

		// uncomment for debug map
		//for (int i = 0; i < RevealedMap.size(); i++)
		//	printf("%s", RevealedMap[i].c_str());

		printf("Select coordinates to fire at!\n");

NotANumber:
		int X = 0;
		int Y = 0;
		printf("X coordinate (0-%i): ", MAP_SIZE_X - 1);
		std::cin >> X;
		printf("Y coordinate (0-%i): ", MAP_SIZE_Y - 1);
		std::cin >> Y;

		if (X != X || Y != Y || X < 0 || X > MAP_SIZE_X - 1 || Y < 0 || Y > MAP_SIZE_Y - 1)
		{
			printf("\nInvalid numbers");
			goto NotANumber;
		}

		int ShotHandler = HandleShot(X, Y);
		switch (ShotHandler)
		{
		case Hit:
			printf("\n\nHit!\n");
			break;
		case Miss:
			printf("\n\nMiss!\n");
			break;
		case ShotAlready:
			printf("\n\nYou have already fired there!\n");
			break;
		case Destroyed:
			printf("\n\nShip destroyed!\n");
			break;
		default:
			break;
		}
		goto Loop;
			break;
		}
	case PlayMode::PVE:
		
		break;
	case PlayMode::PVP:
		printf("We have generated a map for you!\nHere it is\n");
		goto Loop;
		break;
	}


}

int main()
{
	Thread();
	return 0;
}