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


class MapaSolucio : public MapaBase {
private:
	std::vector<PuntDeInteresBase*> puntsDeInteres;  
	std::vector<CamiBase*> camins;                  

public:
	void getPdis(std::vector<PuntDeInteresBase*>& pdis) override {
		pdis = puntsDeInteres;
	}

	void getCamins(std::vector<CamiBase*>& cami) override
	{
		CamiBase* camiSol = new CamiSolucio;
		cami = { camiSol };
	}

	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override;
};


