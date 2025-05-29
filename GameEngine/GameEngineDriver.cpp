
/*
#include "../GameEngine/GameEngine.h"
#include "../Player/player.h"
#include "../Map/Map.h"
#include "../Map/MapLoader.h"
#include "../Cards/Cards.h"
#include <iostream>
using namespace std;
*
 * @brief Function to test the game state transitions.
 *
 * This function creates a GameEngine instance and enters a loop where the user
 * can input commands. Based on the commands entered, the game will change states
 * and execute corresponding actions. The loop ends when the user enters the "end" command.

void testGameStates() {
    GameEngine engine;  // Create a GameEngine instance
    std::string command;

    std::cout << "Game Engine Started\n";
    while (true) {
        // Prompt the user to enter a command
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        // Handle the command using the current state of the game
        engine.handleCommand(command);

        // Exit the loop if the "end" command is entered
        if (command == "end") {
            break;
        }
    }
    
    
}
void testMainGameLoop() {
    cout << "\n========= Testing Main Game Loop =========\n" << endl;
    
    // Create game engine and initialize game
    GameEngine* gameEngine = new GameEngine();
    MapLoader* mapLoader = new MapLoader();
    Map* gameMap = mapLoader->MapReader("../Map/Maps/Asia.map");
    gameEngine->loadMap("Asia.map");
    
    // Test 1: Reinforcement Phase - Different cases of army unit allocation
    cout << "Test 1: Reinforcement Phase" << endl;
    cout << "Creating players with different territory counts..." << endl;
    
    Player* player1 = new Player("Player1");
    Player* player2 = new Player("Player2");
    
    // Set game map for players
    player1->setGameMap(gameMap);
    player2->setGameMap(gameMap);
    player1->setGameEngine(gameEngine);   
    player2->setGameEngine(gameEngine);
    // Add territories to players with different counts
    Territory* t1 = gameMap->getTerritoryById(1);
    Territory* t2 = gameMap->getTerritoryById(2);
    Territory* t3 = gameMap->getTerritoryById(3);
    
    // Player1: 3 territories = 3 reinforcements
    if (t1) {
        t1->setNumOfArmies(0);
        player1->addTerritory(1, t1->getTerritoryName());
    }
    if (t2) {
        t2->setNumOfArmies(0);
        player1->addTerritory(2, t2->getTerritoryName());
    }
    if (t3) {
        t3->setNumOfArmies(0);
        player1->addTerritory(3, t3->getTerritoryName());
    }
    
    // Player2: 5 territories = 5 reinforcements
    Territory* t4 = gameMap->getTerritoryById(4);
    Territory* t5 = gameMap->getTerritoryById(5);
    if (t4 && t5) {
        t4->setNumOfArmies(0);
        t5->setNumOfArmies(0);
        player2->addTerritory(4, t4->getTerritoryName());
        player2->addTerritory(5, t5->getTerritoryName());
    }
    
    gameEngine->players.push_back(player1);
    gameEngine->players.push_back(player2);
    
    // Test reinforcement assignment
    gameEngine->reinforcementPhase();
    cout << "Player1 reinforcements: " << player1->getReinforcementPool() << endl;
    cout << "Player2 reinforcements: " << player2->getReinforcementPool() << endl;
    
    // Test 2: Deploy Orders Only with Reinforcements
    cout << "\nTest 2: Deploy Orders Only with Reinforcements" << endl;
    cout << "Player1 issuing orders with reinforcements..." << endl;
    
    while (player1->getReinforcementPool() > 0) {
        // Display current armies status
        cout << "\nCurrent territory status:" << endl;
        for (size_t i = 0; i < player1->player_territories.size(); i++) {
            Territory* territory = gameMap->getTerritoryById(player1->player_territories[i]->getTerritoryID());
            cout << i + 1 << ". " << territory->getTerritoryName() 
                 << " (Current armies: " << territory->getNumOfArmies() << ")" << endl;
        }

        // Get user input for territory selection
        int choice;
        cout << "\nChoose territory to deploy armies (1-" << player1->player_territories.size() << "): ";
        cin >> choice;
        cin.ignore();

        if (choice < 1 || choice > player1->player_territories.size()) {
            cout << "Invalid territory selection. Please try again." << endl;
            continue;
        }

        // Get number of armies to deploy
        int armies;
        cout << "How many armies to deploy (1-" << player1->getReinforcementPool() << ")? ";
        cin >> armies;
        cin.ignore();

        if (armies < 1 || armies > player1->getReinforcementPool()) {
            cout << "Invalid number of armies. Please try again." << endl;
            continue;
        }

        // Create and execute deploy order
        DeployOrder* deployOrder = new DeployOrder(player1, player1->player_territories[choice-1], armies);
        if (deployOrder->execute()) {
            cout << "Deploy order issued: " << armies << " armies to " 
                 << player1->player_territories[choice-1]->getTerritoryName() << endl;
        }
        delete deployOrder;

        cout << "Reinforcements remaining: " << player1->getReinforcementPool() << endl;
    }

    // Display final status
    cout << "\nFinal territory status:" << endl;
    for (auto territory : player1->player_territories) {
        Territory* actualTerritory = gameMap->getTerritoryById(territory->getTerritoryID());
        cout << actualTerritory->getTerritoryName() 
             << " (Final armies: " << actualTerritory->getNumOfArmies() 
             << ")" << endl;
    }
    
    // Test 3: Advance Orders (Attack and Defend)
    cout << "\nTest 3: Advance Orders" << endl;
    
    // Set up adjacency for territories
    if (t1 && t2 && t4) {
        t1->adjTerritories.push_back(t4->getTerritoryID());  // For attack
        t1->adjTerritories.push_back(t2->getTerritoryID());  // For defend
        t4->adjTerritories.push_back(t1->getTerritoryID());  
        t2->adjTerritories.push_back(t1->getTerritoryID());  
    }
    
    cout << "Testing attack advance:" << endl;
    player1->issueOrder("advance");  // Should use toAttack() list
    
    cout << "Testing defend advance:" << endl;
    player1->issueOrder("advance");  // Should use toDefend() list
    
    // Test 4: Card Orders
    cout << "\nTest 4: Card Orders" << endl;
    
    // Give cards to player1
    Deck* deck = new Deck();
    deck->draw(player1->getHand());
    cout << "Player1's hand: " << player1->getHand() << endl;
    
    cout << "Testing card order:" << endl;
    player1->issueOrder("card");
    
    // Test 5: Player Removal
    cout << "\nTest 5: Player Removal" << endl;
    
    // Remove all territories from player2
    while (!player2->player_territories.empty()) {
        player2->removeTerritory(player2->player_territories[0]->getTerritoryID());
    }
    
    cout << "Checking if Player2 should be removed:" << endl;
    cout << "Player2 territories count: " << player2->player_territories.size() << endl;
    
    // Test 6: Game End Condition
    cout << "\nTest 6: Game End Condition" << endl;
    
    // Give all territories to player1
    if (t4 && t5) {
        player1->addTerritory(4, t4->getTerritoryName());
        player1->addTerritory(5, t5->getTerritoryName());
    }
    
    bool gameEnded = true;
    for (const auto& player : gameEngine->players) {
        if (player != player1 && !player->player_territories.empty()) {
            gameEnded = false;
            break;
        }
    }
    
    cout << "Game end condition met: " << (gameEnded ? "Yes" : "No") << endl;
    cout << "Player1 controls all territories: " << player1->player_territories.size() << endl;
    
    // Cleanup
    delete deck;
    delete mapLoader;
    delete gameEngine;
}*/