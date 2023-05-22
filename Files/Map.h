#pragma once
#include <vector>
#include <string>

#define MAP_SIZE_X 25
#define MAP_SIZE_Y 10

std::vector<std::string> Map = {};
std::vector<std::string> RevealedMap = {};

/// @brief Generates the whole map
/// @param X Width
/// @param Y Height
inline void GenerateMap(int X = 5, int Y = 5)
{
	Map.clear();

	std::string consutruced = {};

	for (int j = 0; j < Y; j++)
	{
		consutruced = {};
		for (int i = 0; i < X; i++)
		{
			consutruced.append("?");
			if (i >= X - 1)
				consutruced.append("\n");
		}
		Map.emplace_back(consutruced);
	}
}

/// @brief Checks spaces around for ship space
/// @param x X position
/// @param y Y position
/// @return Returns true if there are no ships next to the one we are trying to place
inline bool CanPlaceShipAtX(int x, int y, int ShipSize)
{
	if (x + ShipSize > RevealedMap[y].size() || y - 1 < 0 || y + 1 > RevealedMap.size() - 1)
		return false;

	// this part is litearlly the stupidest thing i have wrote so far
	if (RevealedMap[y][x] == 'o')
		return false;

	if (RevealedMap[y][x - 1] == 'o')
		return false;
			
	if (RevealedMap[y][x + 1] == 'o')
		return false;

	if (RevealedMap[y - 1][x] == 'o')
		return false;
			
	if (RevealedMap[y + 1][x] == 'o')
		return false;

	// hey it works!

	for (int i = 0; i < ShipSize; i++)
	{
		if (x + i > 0 && x + i < RevealedMap[y].size())
		{
			if (RevealedMap[y - 1][x + i] == 'o')
				return false;
			
			if (RevealedMap[y + 1][x + i] == 'o')
				return false;
		}
	}

	return true;
}

/// @brief Checks spaces around for ship space, this one included Y size
/// @param x X position
/// @param y Y position
/// @return Returns true if there are no ships next to the one we are trying to place
inline bool CanPlaceShipAtY(int x, int y, int ShipSize)
{
	bool ToReturn = true;

	std::vector<int> Positions = {};
	std::vector<int> PositionsY = {};

	// gather all the possible positions
	for (int i = -1; i < ShipSize; i++)
	{
		if (y + i > 0 && y + i < RevealedMap.size())
		{
			if (x + 1 < RevealedMap[y + i].size())
				Positions.emplace_back(x + 1);

			if (x - 1 > 0)
				Positions.emplace_back(x - 1);

			PositionsY.emplace_back(y + i);
		}
	}

	for (auto& pos : Positions)
	{
		if (RevealedMap[y][pos] == 'o')
		{
			ToReturn = false;
			break;
		}
	}

	for (auto& posY : PositionsY)
	{
		for (auto& pos : Positions)
		{
			if (RevealedMap[y][pos] == 'o')
			{
				ToReturn = false;
				break;
			}

			if (RevealedMap[posY][pos] == 'o')
			{
				ToReturn = false;
				break;
			}
		}
	}

	return ToReturn;
}