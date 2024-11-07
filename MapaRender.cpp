#include "pch.h"
#include "MapaRender.h"
#include "Util.h"

MapaRender* MapaRender::m_singleton = nullptr;

MapaRender::MapaRender() {
    this->m_xml4osm_util = new XML4OSMUtil();
    this->m_mapaBase = new MapaSolucio();  
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements) {
    for (const auto& element : xmlElements) {
        if (element.name == "node") {
            // Procesar punts d'interes basics
            double lat = 0.0, lon = 0.0;
            std::string name;

          
            for (const auto& attr : element.attributes) {
                if (attr.first == "lat") lat = std::stod(attr.second);
                if (attr.first == "lon") lon = std::stod(attr.second);
                if (attr.first == "name") name = attr.second;
            }

          
            if (!name.empty()) {
                Coordinate coord = { lat, lon };
                puntsDeInteres.push_back(new PuntDeInteresBase(coord, name));
            }

        }
        else if (element.name == "way") {
           
            std::string name;
            std::vector<Coordinate> caminoCoords;

          
            for (const auto& attr : element.attributes) {
                if (attr.first == "name") name = attr.second;
            }

            
            for (const auto& child : element.children) {
                if (child.first == "nd") {
                   
                    for (const auto& refAttr : child.second) {
                        if (refAttr.first == "ref") {
                            Coordinate coord = Util::getNodeCoordinate(refAttr.second);
                            caminoCoords.push_back(coord);
                        }
                    }
                }
            }

           
            if (!caminoCoords.empty()) {
                camins.push_back(new CamiSolucio(name, caminoCoords));
            }
        }
    }
}

// DO NOT TOUCH THIS
std::vector<WayBridge> MapaRender::renderWays() {
    std::vector<WayBridge> renderedWays = {};
    std::vector<CamiBase*> vec_camiBase = {};

    if (this->m_mapaBase != nullptr) {
        this->m_mapaBase->getCamins(vec_camiBase);

        for (CamiBase* way : vec_camiBase) {
            WayBridge wayBridge;
            wayBridge.lats = new double[way->getCamiCoords().size()];
            wayBridge.lons = new double[way->getCamiCoords().size()];

            for (int i = 0; i < way->getCamiCoords().size(); i++) {
                wayBridge.lats[i] = way->getCamiCoords()[i].lat;
                wayBridge.lons[i] = way->getCamiCoords()[i].lon;

                double lat = wayBridge.lats[i];
                double lon = wayBridge.lons[i];

            }

            wayBridge.size = way->getCamiCoords().size();

            renderedWays.push_back(wayBridge);
        }

    }
    return renderedWays;
}

// DO NOT TOUCH THIS!
MapaRender* MapaRender::instance() {
    // Protect using a mutex, and create the RIGHT singleton pattern against a multi-thread approach
    if (m_singleton == nullptr) {
        m_singleton = new MapaRender();
    }

    return m_singleton;
}

// DO NOT TOUCH THIS!
std::vector<PoiBridge> MapaRender::renderPois() {
    std::vector<PoiBridge> renderedPois = {};

    if (this->m_mapaBase != nullptr) {
        int i = 0;
        std::vector<PuntDeInteresBase*> vec_puntsDeInteres = {};

        this->m_mapaBase->getPdis(vec_puntsDeInteres);

        for (PuntDeInteresBase* poi : vec_puntsDeInteres ) {
            char* title = new char[poi->getName().size() + 1];
            strcpy_s(title, poi->getName().size() + 1, poi->getName().c_str());
            renderedPois.push_back( PoiBridge{ i, poi->getCoord().lat, poi->getCoord().lon, poi->getColor(), title });
            i++;
        }
    }

    return renderedPois;
}

// DO NOT TOUCH THIS
void MapaRender::construeixOSM(const std::string& path_map) {
    if (m_mapaBase != nullptr) {
        std::vector<XmlElement> result = m_xml4osm_util->parseXML(path_map.c_str());

        if (!result.empty()) {
            m_mapaBase->parsejaXmlElements(result);
        }
    }
    else {//Aquest missatge sortirà quan encara no has fet la part del projecte que carrega el mapa
        Util::escriuEnMonitor("No has instanciat correctament MapaBase!");
    }
}




