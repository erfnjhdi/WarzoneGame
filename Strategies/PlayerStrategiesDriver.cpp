//#include "PlayerStrategies.h"
//#include "../Player/player.h"
//#include "../GameEngine/GameEngine.h"
//#include <iostream>
//#include <vector>
//#include <memory>
//
//using namespace std;
//
//void testPlayerStrategies() {
//    cout << "*************** Testing Player Strategies ***************" << endl;
//
//    // Initialize Game Engine
//    GameEngine gameEngine;
//
//    // Create players and assign different strategies
//    Player* humanPlayer = new Player(&gameEngine, new Hand(), "Human Player", "Human");
//    Player* aggressivePlayer = new Player(&gameEngine, new Hand(), "Aggressive Player", "Aggressive");
//    Player* benevolentPlayer = new Player(&gameEngine, new Hand(), "Benevolent Player", "Benevolent");
//    Player* neutralPlayer = new Player(&gameEngine, new Hand(), "Neutral Player", "Neutral");
//
//    // Add players to the game engine
//    gameEngine.addPlayer(humanPlayer);
//    gameEngine.addPlayer(aggressivePlayer);
//    gameEngine.addPlayer(benevolentPlayer);
//    gameEngine.addPlayer(neutralPlayer);
//
//    // Test initial strategies
//    cout << "\n--- Initial Strategies ---" << endl;
//    cout << humanPlayer->getName() << " is using the Human strategy." << endl;
//    cout << aggressivePlayer->getName() << " is using the Aggressive strategy." << endl;
//    cout << benevolentPlayer->getName() << " is using the Benevolent strategy." << endl;
//    cout << neutralPlayer->getName() << " is using the Neutral strategy." << endl;
//
//    // Test each strategy behavior
//    cout << "\n--- Testing Strategy Behaviors ---" << endl;
//
//    // Human Strategy
//    cout << "\n" << humanPlayer->getName() << " - toDefend(): " << endl;
//    humanPlayer->toDefend();
//
//    cout << humanPlayer->getName() << " - toAttack(): " << endl;
//    humanPlayer->toAttack();
//
//    humanPlayer->issueOrder();
//
//    // Aggressive Strategy
//    cout << "\n" << aggressivePlayer->getName() << " - toDefend(): " << endl;
//    aggressivePlayer->toDefend();
//
//    cout << aggressivePlayer->getName() << " - toAttack(): " << endl;
//    aggressivePlayer->toAttack();
//
//    aggressivePlayer->issueOrder();
//
//    // Benevolent Strategy
//    cout << "\n" << benevolentPlayer->getName() << " - toDefend(): " << endl;
//    benevolentPlayer->toDefend();
//
//    cout << benevolentPlayer->getName() << " - toAttack(): " << endl;
//    benevolentPlayer->toAttack();
//
//    benevolentPlayer->issueOrder();
//
//    // Neutral Strategy
//    cout << "\n" << neutralPlayer->getName() << " - toDefend(): " << endl;
//    neutralPlayer->toDefend();
//
//    cout << neutralPlayer->getName() << " - toAttack(): " << endl;
//    neutralPlayer->toAttack();
//
//    neutralPlayer->issueOrder();
//
//    /*// Dynamically change the strategy of a player
//    cout << "\n--- Changing Strategies Dynamically ---" << endl;
//    cout << "Changing " << humanPlayer->getName() << " from Human to Aggressive strategy." << endl;
//
//    humanPlayer->setStrategy(new Aggressive());
//
//    cout << humanPlayer->getName() << " - toDefend(): " << endl;
//    humanPlayer->toDefend();
//
//    cout << humanPlayer->getName() << " - toAttack(): " << endl;
//    humanPlayer->toAttack();
//
//    humanPlayer->issueOrder();
//
//    // Clean up
//    cout << "\n--- Cleaning Up ---" << endl;
//    delete humanPlayer;
//    delete aggressivePlayer;
//    delete benevolentPlayer;
//    delete neutralPlayer;
//
//    cout << "*************** Testing Completed ***************" << endl;*/
//}
