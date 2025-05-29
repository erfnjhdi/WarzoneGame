#include "./Map/MapLoader.h"
#include "./Map/Map.h"
#include "./Player/player.h"
#include "./Orderslist/Orders.h"
#include "./Cards/Cards.h"
#include "./GameEngine/GameEngine.h"
#include "./Commands/CommandProcessing.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void testLoadMaps();
void playerTester();
void testOrdersLists();
void testCards();
void testGameStates();
void testMainGameLoop(){
    GameEngine game_engine = GameEngine();
    game_engine.mainGameLoop();

};
void testCommandProcessor(int argc, char* argv[]) {
  auto gameEngine = new GameEngine(argc, argv);

    // Command line or file
    std::string decision;

    // More commands to enter or not
    bool moreCommands = true;
    std::string moreCommandsDecision;

    // Initializing command line reading class
    CommandProcessor cpr = CommandProcessor(gameEngine, argc, argv);

    // get raw command line inputs
    auto inputCommandsRaw = cpr.getArgs();

    // argv[0] program name
    // argv[1] decision -file or -console
    // argv[2] - file name
    if(inputCommandsRaw->size() < 2){
      std::cout << "You must choose between -console or -file <filename>" << endl;
      exit(0);
    }

    // Command line
    if (inputCommandsRaw->at(1) == "-console"){
        do {
            cpr.getCommand();
            cout << "Current state is: " << gameEngine->StateToString() <<endl;
            std::cout << "Do you want to enter a command? (y/n): ";
            getline(std::cin, moreCommandsDecision);
            std::cout << std::endl;
            if (!(moreCommandsDecision == "y")){
                moreCommands = false;
            }
        }while(moreCommands);
    }
    else {
        throw std::runtime_error("Invalid Command line arguments");
    }
}

void testPlayerStrategies(int argc, char* argv[]) {
    cout << "*************** Testing Player Strategies ***************" << endl;

    // Initialize Game Engine
    GameEngine gameEngine(argc, argv);

    // Create players and assign different strategies
    Player* humanPlayer = new Player(&gameEngine, new Hand(), "Human Player", "Human");
    Player* aggressivePlayer = new Player(&gameEngine, new Hand(), "Aggressive Player", "Aggressive");
    Player* benevolentPlayer = new Player(&gameEngine, new Hand(), "Benevolent Player", "Benevolent");
    Player* neutralPlayer = new Player(&gameEngine, new Hand(), "Neutral Player", "Neutral");

    // Add players to the game engine
    gameEngine.addPlayer(humanPlayer);
    gameEngine.addPlayer(aggressivePlayer);
    gameEngine.addPlayer(benevolentPlayer);
    gameEngine.addPlayer(neutralPlayer);

    // Test initial strategies
    cout << "\n--- Initial Strategies ---" << endl;
    cout << humanPlayer->getName() << " is using the Human strategy." << endl;
    cout << aggressivePlayer->getName() << " is using the Aggressive strategy." << endl;
    cout << benevolentPlayer->getName() << " is using the Benevolent strategy." << endl;
    cout << neutralPlayer->getName() << " is using the Neutral strategy." << endl;

    // Test each strategy behavior
    cout << "\n--- Testing Strategy Behaviors ---" << endl;

    // Human Strategy
    cout << "\n" << humanPlayer->getName() << " - toDefend(): " << endl;
    humanPlayer->toDefend();

    cout << humanPlayer->getName() << " - toAttack(): " << endl;
    humanPlayer->toAttack();

    humanPlayer->issueOrder();

    // Aggressive Strategy
    cout << "\n" << aggressivePlayer->getName() << " - toDefend(): " << endl;
    aggressivePlayer->toDefend();

    cout << aggressivePlayer->getName() << " - toAttack(): " << endl;
    aggressivePlayer->toAttack();

    aggressivePlayer->issueOrder();

    // Benevolent Strategy
    cout << "\n" << benevolentPlayer->getName() << " - toDefend(): " << endl;
    benevolentPlayer->toDefend();

    cout << benevolentPlayer->getName() << " - toAttack(): " << endl;
    benevolentPlayer->toAttack();

    benevolentPlayer->issueOrder();

    // Neutral Strategy
    cout << "\n" << neutralPlayer->getName() << " - toDefend(): " << endl;
    neutralPlayer->toDefend();

    cout << neutralPlayer->getName() << " - toAttack(): " << endl;
    neutralPlayer->toAttack();

    neutralPlayer->issueOrder();

    /*// Dynamically change the strategy of a player
    cout << "\n--- Changing Strategies Dynamically ---" << endl;
    cout << "Changing " << humanPlayer->getName() << " from Human to Aggressive strategy." << endl;

    humanPlayer->setStrategy(new Aggressive());

    cout << humanPlayer->getName() << " - toDefend(): " << endl;
    humanPlayer->toDefend();

    cout << humanPlayer->getName() << " - toAttack(): " << endl;
    humanPlayer->toAttack();

    humanPlayer->issueOrder();

    // Clean up
    cout << "\n--- Cleaning Up ---" << endl;
    delete humanPlayer;
    delete aggressivePlayer;
    delete benevolentPlayer;
    delete neutralPlayer;

    cout << "*************** Testing Completed ***************" << endl;*/
}

void testTournament(int argc, char* argv[]){
  auto gameEngine = new GameEngine(argc, argv);
  std::string option = "console";
  std::cout << "if you like to enter tournament mode via enter console?" << std::endl;
  std::cout << "Enter Command" << std::endl;
  std::cout << "-> ";
  getline(std::cin, option);


  if(option == "console"){
    gameEngine->startupPhase();
  }

  else{
    exit(0);
  }

}

int main(int argc, char* argv[]) {
    /*// std::cout << "Calling the testLoadMaps function\n\n";
    // testLoadMaps();
    //
    // std::cout << "Calling the playerTester function\n\n";
    // playerTester();
    //
    // std::cout << "Calling the testOrdersLists function\n\n";
    // testOrdersLists();
    //
    // std::cout << "Calling the testCards function\n\n";
    // testCards();

    //std::cout << "Calling the testGameStates function\n\n";
    //testGameStates();

    std::cout << "Starting Game Engine Tests...\n" << std::endl;
    // testMainGameLoop();
    testMainGameLoop();
    //game_engine.mainGameLoop();
    std::cout << "\nTests completed." << std::endl;*/
    //testCommandProcessor(argc, argv);
    //testPlayerStrategies(argc, argv);
    testTournament(argc, argv);
    return 0;
}