//#include "LoggingObserver.h"
//#include "../Commands/CommandProcessing.h"
//#include "../Orderslist/Orders.h"
//#include "../GameEngine/GameEngine.h"
//#include <iostream>
//#include <fstream>
//
//void testLoggingObserver() {
//    std::cout << "\n========== Testing Logging Observer ==========\n";
//
//    // Get the LogObserver instance
//    LogObserver* logger = LogObserver::getInstance();
//
//    // Test 1: Command Processing Logging
//    std::cout << "\nTest 1: Command Processing Logging\n";
//    std::cout << "--------------------------------------\n";
//
//    CommandProcessor* cmdProcessor = new CommandProcessor();
//    cmdProcessor->attach(logger);
//
//    GameEngine* engine = new GameEngine();
//    cmdProcessor->setGameEngine(engine);
//
//    // Create and process commands
//    Command* cmd1 = new Command("loadmap testmap.txt");
//    cmdProcessor->saveCommand(cmd1);
//    cmd1->saveEffect("Map loaded successfully");
//
//    Command* cmd2 = new Command("validatemap");
//    cmdProcessor->saveCommand(cmd2);
//    cmd2->saveEffect("Map validation completed");
//
//    std::cout << "Commands processed and logged\n";
//
//    // Test 2: Order Logging
//    std::cout << "\nTest 2: Order Logging\n";
//    std::cout << "--------------------------------------\n";
//
//    Player* player1 = new Player("Player1");
//    Territory* territory1 = new Territory("Territory1");
//    player1->addTerritory(territory1);
//
//    OrdersList* ordersList = new OrdersList();
//    ordersList->attach(logger);
//
//    DeployOrder* deployOrder = new DeployOrder(player1, territory1, 5);
//    deployOrder->attach(logger);
//
//    std::cout << "Adding and executing orders...\n";
//    ordersList->add(deployOrder);
//    deployOrder->execute();
//
//    // Test 3: Game State Logging
//    std::cout << "\nTest 3: Game State Logging\n";
//    std::cout << "--------------------------------------\n";
//
//    engine->attach(logger);
//
//    std::cout << "Testing state transitions...\n";
//    engine->transition(GameState::MapLoaded);
//    engine->transition(GameState::MapValidated);
//    engine->transition(GameState::PlayersAdded);
//
//    // Test 4: Verify Log File
//    std::cout << "\nTest 4: Verifying Log File Content\n";
//    std::cout << "--------------------------------------\n";
//
//    std::cout << "Reading first few lines of log file:\n";
//    std::ifstream logFile("logs/gamelog.txt");
//    if (logFile.is_open()) {
//        std::string line;
//        int lineCount = 0;
//        while (std::getline(logFile, line) && lineCount < 5) {
//            std::cout << line << std::endl;
//            lineCount++;
//        }
//        logFile.close();
//    }
//
//    // Test 5: Complex Interaction Logging
//    std::cout << "\nTest 5: Complex Interaction Logging\n";
//    std::cout << "--------------------------------------\n";
//
//    // Simulate a series of game actions
//    engine->addPlayer("Player2");
//    Territory* territory2 = new Territory("Territory2");
//    territory1->addNeighbor(territory2);
//
//    AdvanceOrder* advanceOrder = new AdvanceOrder(player1, territory1, territory2, 3);
//    advanceOrder->attach(logger);
//    ordersList->add(advanceOrder);
//    advanceOrder->execute();
//
//    // Cleanup
//    delete cmdProcessor;
//    delete engine;
//    delete player1;
//    delete territory1;
//    delete territory2;
//    delete ordersList;
//    delete cmd1;
//    delete cmd2;
//
//    std::cout << "\nLogging Observer testing completed.\n";
//    std::cout << "Full test results available in gamelog.txt\n";
//}