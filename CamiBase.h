#pragma once
#include "pch.h"

#include "Common.h"
#include <vector>

class CamiBase {
	public:
		virtual std::vector<Coordinate> getCamiCoords() = 0;
		virtual CamiBase* clone() = 0;
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
		return camins;
	}

	CamiSolucio* clone() { return new CamiSolucio(*this); }
};

