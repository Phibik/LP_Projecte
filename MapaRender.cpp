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
        // Procesamiento de nodos "node" y "way" basado en los atributos y fills
        double lat = 0.0, lon = 0.0;
        std::string name;

        // Buscar atributos en 'atributs'
                for (const auto& attr : element.atributs) {
            if (attr.first == "lat") {
                try {
                    lat = std::stod(attr.second);  // Conversión de string a double
                }
                catch (const std::invalid_argument& e) {
                    // Manejo de error si falla la conversión
                }
            }
            else if (attr.first == "lon") {
                try {
                    lon = std::stod(attr.second);
                }
                catch (const std::invalid_argument& e) {
                    // Manejo de error si falla la conversión
                }
            }
            else if (attr.first == "name") {
                name = attr.second;
            }
        }

        // Si encontramos un punto de interés ("node") con nombre
        if (!name.empty() && lat != 0.0 && lon != 0.0) {
            Coordinate coord = { lat, lon };
            puntsDeInteres.push_back(new PuntDeInteresBase(coord, name));
        }

        // Procesamiento específico para elementos de tipo "way"
        std::vector<Coordinate> caminoCoords;

        for (const auto& fill : element.fills) {
            if (fill.first == "tag") {
                auto tempAtributs = fill.second;
                auto kv = Util::kvDeTag(tempAtributs);
                if (kv.first == "name") {
                    name = kv.second;
                    break;  // Salir al encontrar el nombre del "way"
                }
            }
            else if (fill.first == "nd") {
                for (const auto& refAttr : fill.second) {
                    if (refAttr.first == "ref") {
                        Coordinate coord = { lat, lon };
                        caminoCoords.push_back(coord);
                    }
                }
            }
        }

        // Si el elemento es un "way" con coordenadas
        if (!caminoCoords.empty()) {
            camins.push_back(new CamiSolucio(name, caminoCoords));
            //camins.push_back(new CamiSolucio(name, caminoCoords));
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




