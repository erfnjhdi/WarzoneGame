////
//// Created by vasu on 10/5/2024.
////
//#include "MapLoader.h"
//#include "Map.h"
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <regex>
//
//using namespace std;
//using std::cin;
//using std::cout;
//using std::istringstream;
//using std::string;
//
///**
// * Method that splits a long string (sentence) into multiple strings
// * @param line
// * @return words<string>
// */
//std::vector<string> divideTerritoryBoundary(string line) {
//    std::vector<string> words;
//    istringstream ss(line);
//    std::string word;
//
//    while (getline(ss, word, ',')) {
//        words.push_back(word);
//    }
//    return words;
//};
//
///**
// * Method that splits a long string (sentence) into multiple strings
// * @param line
// * @return words<string>
// */
//std::vector<string> divideContinentBoundary(string line) {
//    std::vector<string> words;
//    istringstream ss(line);
//    std::string word;
//
//    while (getline(ss, word, '=')) {
//        words.push_back(word);
//    }
//    return words;
//};
//
///**
// * Default constructor
// */
//MapLoader::MapLoader() {
//}
//
///**
// * copy constructor
// */
//MapLoader::MapLoader(const MapLoader &orig) {
//}
//
///**
// * Destructor
// */
//MapLoader::~MapLoader() {
//}
//
//Map *MapLoader::MapReader(string fileName) {
//    istringstream stringStream;
//    ifstream inputFile(fileName);
//
//    if (!inputFile.is_open()) {
//        std::cerr << "Error: Could not open file " << fileName << std::endl;
//        return nullptr; // or handle the error as needed
//    }
//
//    bool mapIsValid = true;
//    std::vector<string> words;
//    string line;
//    string tempName; // temporary string containing the name of an entity
//    bool hasContinents = false;
//    bool hasTerritory = false;
//    int cont_counter = 0;
//    int ter_counter = 0;
//
//    //  Create map object
//    Map *map = new Map();
//
//    // For each line of the file, we want to check for a ["Map"] section, a ["Continents"] section
//    for (; getline(inputFile, line);) {
//        if (line == "")
//            continue;
//
//        if (!mapIsValid) {
//            std::cerr << "The map provided is invalid, please try again";
//        }
//        // if wantedString exists in the line we are currently on,
//        if (line.substr(0, 3) == "map") {
//            map->setName(line.substr(4, line.length() - 4));
//            continue;
//        } else if (!line.compare("[Continents]")) {
//            hasContinents = true;
//            continue;
//        } else if (!line.compare("[Territories]")) {
//            hasContinents = false; // set to false to that the program can go into the next if
//            hasTerritory = true;
//            continue;
//        } else if (hasContinents) {
//            if (line.length() > 0 && line != "\r") {
//                Continent *continent = new Continent();
//                words = divideContinentBoundary(line);
//                continent->setContinentID(++cont_counter);
//                continent->setContinentName(words[0]);
//
//                map->Continents.push_back(continent);
//            } else {
//                hasContinents = false;
//            }
//        } else if (hasTerritory) {
//            words = divideTerritoryBoundary(line);
//
//            string territoryName = words[0];
//
//            if (line.length() > 0 && line != "\r") {
//                Territory *territory = map->getTerritoryByName(territoryName);
//
//                if (territory == nullptr) {
//                    territory = new Territory(territoryName, ++ter_counter);
//                    map->Territories.push_back(territory);
//                }
//
//                int x, y;
//
//                std::istringstream() >> x;
//                territory->setCoordinateX(x);
//
//                istringstream(words[2]) >> y;
//                territory->setCoordinateY(y);
//
//                string continentName = words[3];
//
//                territory->setContinentName(continentName);
//
//                Continent *c = map->getContinentByName(continentName);
//
//                territory->setContinentId(c->getContinentID());
//
//                for (int i = 4; i < words.size(); ++i) {
//                    Territory *t = map->getTerritoryByName(words[i]);
//
//                    if (t == nullptr) {
//                        t = new Territory(words[i], ++ter_counter);
//                        map->Territories.push_back(t);
//                    }
//                    territory->adjTerritories.push_back(t->getTerritoryID());
//                }
//                for (int i = 0; i < map->Continents.size(); i++) {
//                    if (map->Continents[i]->getContinentName() == continentName) {
//                        map->Continents[i]->territories.push_back(territory);
//                    }
//                }
//            } else {
//                if (cont_counter > ter_counter) {
//                    mapIsValid = false;
//                    std::cerr <<
//                            "The map is invalid!!,because the number of continents is greater than the number of countries."
//                            << endl;
//                }
//                hasTerritory = false;
//            }
//        }
//    };
//
//    return map;
//}
