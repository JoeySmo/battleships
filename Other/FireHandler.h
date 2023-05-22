#pragma once

#include "Enums.h"
#include "../Files/Map.h"

/// @brief Checks positions around the ship to make sure the ship has been destroyed on the X axis
/// @param x 
/// @param y 
/// @return True if destroyed
bool CheckPosX(int x, int y)
{
	// this is really stupid
	// but hey, it works

	int MostLeft = 0;
	int MostRight = 0;
	for (int i = 0; i < 5; i++)
	{
		if (x - i < 0 || RevealedMap[y][x - i] == '?' || RevealedMap[y][x - i] == '-')
			break;

		MostLeft++;
	}

	for (int i = 0; i < 5; i++)
	{
		if (x + i > RevealedMap[y].size() || RevealedMap[y][x + i] == '?' || RevealedMap[y][x + i] == '-')
			break;

		MostRight++;
	}

	for (int i = 0; i < MostLeft; i++)
	{
		if (RevealedMap[y][x - i] == 'o')
			return false;
	}

	for (int i = 0; i < MostRight; i++)
	{
		if (RevealedMap[y][x + i] == 'o')
			return false;
	}

	return true;
}

/// @brief Checks positions around the ship to make sure the ship has been destroyed on the Y axis
/// @param x 
/// @param y 
/// @return True if destroyed
bool CheckPosY(int x, int y)
{
	// similar to the X function

	int MostTop = 0;
	int MostBottom = 0;

	for (int i = 0; i < 5; i++)
	{
		if (y + i > RevealedMap.size() || RevealedMap[y + i][x] == '?' || RevealedMap[y + i][x] == '-')
			break;

		MostTop++;
	}

	for (int i = 0; i < 5; i++)
	{
		if (y - i < 0 || RevealedMap[y - i][x] == '?' || RevealedMap[y - i][x] == '-')
			break;

		MostBottom++;
	}

	for (int i = 0; i < MostBottom; i++)
	{
		if (RevealedMap[y - i][x] == 'o')
			return false;
	}

	for (int i = 0; i < MostTop; i++)
	{
		if (RevealedMap[y + i][x] == 'o')
			return false;
	}

	return true;
}

/// @brief Handles the firing
/// @param X 
/// @param Y 
/// @return from the enum
int HandleShot(int X, int Y)
{
	if (RevealedMap.at(Y)[X] == 'o')
	{
		Map[Y][X] = '+';
		RevealedMap[Y][X] = '+';
		if (CheckPosX(X, Y) && CheckPosY(X, Y))
			return Destroyed;

		return Hit;
	}
	else if (Map.at(Y)[X] == '-' || Map.at(Y)[X] == '+')
		return ShotAlready;

	Map[Y][X] = '-';
	return Miss;
}