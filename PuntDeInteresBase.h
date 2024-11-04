#pragma once

#include <string>
#include "Common.h"

class PuntDeInteresBase {

	private:
		Coordinate m_coord;
		std::string m_name;

	public:		
		PuntDeInteresBase();
		PuntDeInteresBase(Coordinate coord, std::string name);

		virtual std::string getName();
		Coordinate getCoord();
		virtual unsigned int getColor();

};

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
public:
	std::string getName() override
	{

	}
	unsigned int getColor() override;
};

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
public:
	std::string getName() override;
	unsigned int getColor() override;
};