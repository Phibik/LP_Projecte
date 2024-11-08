#pragma once

#include <string>
#include "Common.h"

class PuntDeInteresBase {

private:
	std::string id;
	Coordinate m_coord;
	std::string m_name;

public:
	PuntDeInteresBase();
	PuntDeInteresBase(Coordinate coord, std::string name);

	virtual std::string getName();
	Coordinate getCoord();
	virtual unsigned int getColor();
	void setId(const std::string& id) { this->id = id; }

};

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
private:
	std::string shop;
	std::string hores; //opening_hours
	std::string discapacitat; //wheelchair
public:
	PuntDeInteresBotigaSolucio(Coordinate coord, std::string name,
		std::string shop = "", std::string hores = "", std::string discapacitat = "") :
		PuntDeInteresBase(coord, name), shop(shop), hores(hores), discapacitat(discapacitat) {}

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
			if (discapacitat == "yes" && hores.find("06:00-22:00") != std::string::npos)
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
	PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name,
		std::string cuina = "", std::string discapacitat = "") :
		PuntDeInteresBase(coord, name), cuina(cuina), discapacitat(discapacitat) {}

	std::string getName() override { return PuntDeInteresBase::getName(); }
	unsigned int getColor() override
	{
		// valor per defecte, pot cambiar si es "pizza", "chinese"...
		unsigned int color = PuntDeInteresBase::getColor();

		if (cuina == "pizza")
			color = 0x04FCBA;
		else if (cuina == "chinese")
			color = 0xA6D9F7;

		if (discapacitat == "yes")
			color = 0x251351;

		return color;
	}
};