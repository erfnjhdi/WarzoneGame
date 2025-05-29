//
// Created by vasu on 10/5/2024.
//
#include "MapLoader.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// Function to test loading and validating multiple map files
void testLoadMaps()
{
    // List of map files to test (both valid and invalid)
    vector<std::string> mapFiles = {
        "../Map/Maps/Asia.map",        // valid map
        "../Map/Maps/USA_invalid.map", // invalid map
        "../Map/Maps/USA.map",      // valid map
        "../Map/Maps/World_Total_War.map"  // valid map
    };

    // Create a MapLoader object
    MapLoader* mapLoader = new MapLoader();

    // Iterate through each map file and test loading/validation
    for (const auto& mapFile : mapFiles)
    {
        cout << "\nTesting map: " << mapFile <<"\n"<< endl;

        // Attempt to load the map
        Map* map = mapLoader->MapReader(mapFile);

        // Check if the map is valid
        if (map && map->validate()) {

            // Print a list of Continents and Territories inside the valid map
            cout << "List of Continents and their Territories: \n" << endl;
            for (auto c : map->Continents)
            {
                cout << c->getContinentName() << endl;
                cout << "----------------" << endl;
                for (auto t : c->territories)
                {
                    cout << "  " << t->getTerritoryName() << endl;
                }
                cout << endl;
            }
        }
        cout << "-------------------------" << endl;

    }
    cout << "Thank you for using my program." << endl;

    // Clean up memory
    delete mapLoader;
}


