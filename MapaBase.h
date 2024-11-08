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
		for (std::vector<PuntDeInteresBase*>::const_iterator it = puntsDeInteres.begin(); it != puntsDeInteres.end(); it++)
		{
			pdis.push_back(*it);
		}
	}

	void getCamins(std::vector<CamiBase*>& cami) override
	{
		for (std::vector<CamiBase*>::iterator it = camins.begin(); it != camins.end(); it++)
		{
			cami.push_back((*it)->clone());
		}
	}

	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override
	{
		for (const auto& element : xmlElements)
		{
			if (element.id_element == "node")
			{
				// atributs lat i lon, id
				std::string id;
				double lat = 0.0, lon = 0.0;
				for (const auto& atribut : element.atributs)
				{
					// assignació coordenades
					if (atribut.first == "lat")
						lat = std::stod(atribut.second);
					else if (atribut.first == "lon")
						lon = std::stod(atribut.second);
					//id
					else if (atribut.first == "id")
						id = atribut.second;
				}

				// fills  (aqui esta el shop, opening_hours...)
				/// inicialitzar variables
				std::string name = "";
				bool botiga = false, restaurant = false;
				std::string shop = "", cuina = "";
				std::string hores = "";
				std::string wheelchair = "no";

				/// bucle que busca shops, wheelcharis...
				for (const auto& fill : element.fills)
				{
					// extreure una parella <key, value>, e. g. <shop, bakery>
					std::pair<std::string, std::string> parella;	// pair<string, string>
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
					else if (parella.first == "wheelchair")
						wheelchair = parella.second;
					else if (parella.first == "opening_hours")
						hores = parella.second;
					else if (parella.first == "name")
						name = parella.second;
				}

				Coordinate coords = { lat, lon };

				// crear PuntDeInteresBase / Botiga / Restaurant
				if (botiga)
				{
					PuntDeInteresBase* p = new PuntDeInteresBotigaSolucio(coords, name, shop, hores, wheelchair);
					p->setId(id);
					puntsDeInteres.push_back(p);
					//Util::escriuEnMonitor("Botiga");
				}
				else if (restaurant)
				{
					PuntDeInteresBase* p = new PuntDeInteresRestaurantSolucio(coords, name, cuina, wheelchair);
					p->setId(id);
					puntsDeInteres.push_back(p);
					//Util::escriuEnMonitor("Restaurant");
				}
				else
				{
					PuntDeInteresBase* p = new PuntDeInteresBase(coords, name);
					p->setId(id);
					puntsDeInteres.push_back(p);
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



