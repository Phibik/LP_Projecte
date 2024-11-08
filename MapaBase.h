#pragma once
#include "pch.h"

#include "Common.h"
#include "PuntDeInteresBase.h"
#include "CamiBase.h"
#include "Util.h"


class MapaBase {

	public:
		virtual void getPdis(std::vector<PuntDeInteresBase*>&) = 0;
		virtual void getCamins(std::vector<CamiBase*>&) = 0;
		virtual void parsejaXmlElements(std::vector<XmlElement>& xmlElements) = 0;

};

class MapaSolucio : public MapaBase
{
private:
	std::vector<PuntDeInteresBase*> puntsDeInteres;
	std::vector<CamiBase*> camins;
public:
	void getPdis(std::vector<PuntDeInteresBase*>& pdis) override
	{
		pdis = puntsDeInteres;
	}

	void getCamins(std::vector<CamiBase*>& cami) override
	{
		cami = camins;
	}

	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override
	{
		for (const auto& element : xmlElements)
		{
			if (element.id_element == "node")
			{
				// variables per pdi botiga i restaurant
				double lat = 0.0, lon = 0.0;
				std::string name = "";
				bool botiga = false, restaurant = false;
				std::string shop = "", cuina = "";
				std::string hores = "";
				std::string wheelchair = "no";

				// atributs
				for (const auto& atribut : element.atributs)
				{
					// assignació coordenades
					if (atribut.first == "lat")
						lat = std::stod(atribut.second);
					if (atribut.first == "lon")
						lon = std::stod(atribut.second);
				}

				// fills  (aqui esta el shop, opening_hours...)
				for (const auto& fill : element.fills)
				{
					// extreure una parella <key, value>, e. g. <shop, bakery>
					std::pair<std::string, std::string> parella;
					std::vector <PAIR_ATTR_VALUE> fillet = fill.second;
					parella = Util::kvDeTag(fillet);

					// deteccio de shop o restaurant
					if (parella.first == "shop") {
						botiga = true;
						shop = parella.second;
					}
					else if (parella.first == "cuisine") {
						restaurant = true;
						cuina = parella.second;
					}

					// altres atributs
					if (parella.first == "wheelchair")
						wheelchair = parella.second;
					if (parella.first == "opening_hours")
						hores = parella.second;
				}

				Coordinate coords = { lat, lon };

				// crear PuntDeInteresBase / Botiga / Restaurant
				if (botiga)
				{
					puntsDeInteres.push_back(new PuntDeInteresBotigaSolucio(coords, name, shop, hores, wheelchair));
					//Util::escriuEnMonitor("Botiga");
				}
				else if (restaurant)
				{
					puntsDeInteres.push_back(new PuntDeInteresRestaurantSolucio(coords, name, cuina, wheelchair));
					//Util::escriuEnMonitor("Restaurant");
				}
				else
				{
					puntsDeInteres.push_back(new PuntDeInteresBase(coords, name));
					//Util::escriuEnMonitor("Node");
				}
			}
			else if (element.id_element == "way")
			{
				//Util::escriuEnMonitor("camins");
			}
		}
	}
};



