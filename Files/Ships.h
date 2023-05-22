#pragma once
#include <random>

#include "Map.h"

struct Ship
{
	// rotations
	std::vector<std::string> LeftRight = {};
	std::vector<std::string> UpDown = {};

	// constructors
	Ship()
	{
		UpDown = LeftRight = { "o" };
	}

	Ship(int size)
	{
		for (int i = 0; i <= size; i++)
		{
			LeftRight.push_back("o");
			UpDown.push_back("o\n");
		}
	}
};

std::vector<Ship> Ships = {};

class CShips
{
public:
	CShips()
	{
		PopulateShips();
	}

private:
	/// @brief Creates ships
	void PopulateShips()
	{
		// 1cell ships
		for (int i = 0; i < 4; i++)
			Ships.push_back(*(new Ship()));

		// 2cell ships
		for (int i = 0; i < 3; i++)
			Ships.push_back(*(new Ship(2)));

		// 3cell ships
		for (int i = 0; i < 2; i++)
			Ships.push_back(*(new Ship(3)));

		// 4cell ships
		for (int i = 0; i < 1; i++)
			Ships.push_back(*(new Ship(4)));
	}
};

/// @brief Populates the map with ships
inline void PopulateMap()
{
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(0, RAND_MAX);

	while (Ships.size() > 0)
	{
		// for whatever reason, if we use srand(time(0)); it will not place any ships
		// this is a ghetto work around that seems to work quite well
		srand(dist(engine));

		// this does not make sense later on for Y ships
		// but hey, it works!
		for (int i = 0; i < RevealedMap.size(); i++)
		{
			// gotta make sure its empty
			if (Ships.size() <= 0)
				break;

			// we roll a number here to place a ship randomly
			if (rand() % 4 == 0)
			{
				srand(dist(engine));
				int Pos = rand() % (RevealedMap[i].size());
				int ShipPos = rand() % (Ships.size());
				auto Ship = Ships[ShipPos];

				int HigherBound = RevealedMap[i].size() - 1;
				if (Pos + Ship.LeftRight.size() > HigherBound || !CanPlaceShipAtX(Pos, i, Ship.LeftRight.size()))
					continue;

				int SelectedShip = rand() % (Ship.LeftRight.size());
				int ShipSize = Ship.LeftRight.size();
				RevealedMap[i].erase(Pos, ShipSize);

				for (int j = 0; j < Ship.LeftRight.size(); j++)
					RevealedMap[i].insert(Pos, Ship.LeftRight[j]);

				Ships.erase(Ships.begin() + ShipPos);
			}
			else if (rand() % 4 == 2)
			{
				srand(dist(engine));
				int Pos = rand() % RevealedMap.size();
				int PosX = rand() % RevealedMap[Pos].size();
				int SelectedShip = rand() % (Ships.size());
				auto Ship = Ships[SelectedShip];

				if (!CanPlaceShipAtY(PosX, Pos, Ship.UpDown.size()))
					continue;
				
				if (PosX > RevealedMap[Pos].size() - 2 || Pos > RevealedMap.size() - 1)
					continue;

				int EndPosition = Ship.UpDown.size() + Pos;

				if (EndPosition > RevealedMap.size())
					continue;

				for (int j = 0; j < Ship.UpDown.size(); j++)
				{
					RevealedMap[Pos + j].erase(PosX, 1);
					RevealedMap[Pos + j].insert(PosX, "o");
				}
				Ships.erase(Ships.begin() + SelectedShip);
			}
		}
	}
}