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
private:
	std::string shop; 
	std::string hores; //opening_hours
	std::string discapacitat; //wheelchair
public:
	PuntDeInteresBotigaSolucio() {} // TODO --> creo que hay que inicializar 
									//"shop", "opening_hours"... con el xml

	std::string getName() override { return PuntDeInteresBase::getName(); }
	unsigned int getColor() override
	{
		unsigned int color = PuntDeInteresBase::getColor();
		if (shop == "supermarket")
			color = 0xA5BE00;
		else if (shop == "tobacco")
			color = 0xFFAD69;
		else if (shop == "bakery")
		{
			// std::string::find(x) retorna std::string::npos si no troba x
			if (hores.find("06:00-22:00") != std::string::npos && discapacitat)
				color = 0x4CB944;
			else
				color = 0xE85D75;
		}
		else
			color = 0xEFD6AC;

		return color;
	}
};

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
private:
	std::string cuina; //cuisine
	std::string discapacitat; //wheelchair
public:
	// TODO --> constructor

	std::string getName() override { return PuntDeInteresBase::getName(); }
	unsigned int getColor() override
	{
		// valor per defecte, pot cambiar si es "pizza", "chinese"...
		unsigned int color = PuntDeInteresBase::getColor();

		if (cuina == "pizza")
			color = 0x04FCBA;
		else if (cuina == "chinese")
			color = 0xA6D9F7;

		if (discapacitat)
			color = 0x251351;

		return color;
	}
};