#pragma once

#include "Common.h"
#include <vector>

class CamiBase {
	public:
		virtual std::vector<Coordinate> getCamiCoords() = 0;
};

class CamiSolucio : public CamiBase
{
public:
	std::vector<Coordinate> getCamiCoords() override
	{	
		return 
		{
			{41.4928803, 2.1452381},
			{41.4929072, 2.1452474},
			{41.4933070, 2.1453852},
			{41.4939882, 2.1456419}
		};
	}
};
