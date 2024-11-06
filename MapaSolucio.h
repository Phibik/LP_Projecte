#pragma once
#include "MapaBase.h"
#include "CamiBase.h"

class MapaSolucio : public MapaBase {
public: 
	MapaSolucio(){}
	virtual ~MapaSolucio(){}

	void getPdis(std::vector<PuntDeInteresBase*>& pdis) override {
		pdis =  m_pdis;
	}

	void getCamins(std::vector<CamiBase*>& camins) override {  
		camins = m_camins;
	}
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override;




private: 
	std::vector<PuntDeInteresBase*> m_pdis;
	std::vector<CamiBase*> m_camins;




};