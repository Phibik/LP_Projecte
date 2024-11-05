#pragma once
#include "pch.h"

#include "Common.h"
#include "PuntDeInteresBase.h"
#include "CamiBase.h"


class MapaBase {

	public:
		virtual void getPdis(std::vector<PuntDeInteresBase*>&) = 0; // potser s'ha de posar pdis
		virtual void getCamins(std::vector<CamiBase*>&) = 0;
		virtual void parsejaXmlElements(std::vector<XmlElement>& xmlElements) = 0;

};

class MapaSolucio: public MapaBase
{
public:
	void getPdis(std::vector<PuntDeInteresBase*>& pdis) override
	{
		Coordinate cBotiga = { 41.4918606, 2.1465411 };
		Coordinate cRestaurant = { 41.4902204, 2.1406477 };
		PuntDeInteresBase* botiga = new PuntDeInteresBotigaSolucio(cBotiga, "La Millor Pastisseria",
			"bakery");
		PuntDeInteresBase* restaurant = new PuntDeInteresRestaurantSolucio(cRestaurant, 
			"El Millor Restaurant", "regional", "yes");
		pdis = { botiga, restaurant };
	}

	void getCamins(std::vector<CamiBase*>& cami) override
	{
		CamiBase* camiSol = new CamiSolucio;
		cami = { camiSol };
	}

	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override;
};

