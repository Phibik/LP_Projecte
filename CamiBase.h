#pragma once
#include "pch.h"

#include "Common.h"
#include <vector>

class CamiBase {
	public:
		virtual std::vector<Coordinate> getCamiCoords() = 0;
};

class CamiSolucio : public CamiBase
{
private: 
	std::string nom;
	std::vector<Coordinate> camins;
public:
	CamiSolucio(std::string name, std::vector<Coordinate> caminoCoords)
	{
		nom = name;
		camins = caminoCoords;
	}

	std::vector<Coordinate> getCamiCoords() override
	{
		/*return
		{
			{41.4928803, 2.1452381},
			{41.4929072, 2.1452474},		TASCA 4
			{41.4933070, 2.1453852},
			{41.4939882, 2.1456419}
		};*/

		return camins;
	}
};

