
#ifndef A1COMP345_GAMEENGINE_H
#define A1COMP345_GAMEENGINE_H

#include <string>
#include <iostream> // Required for stream insertion operator
#include <stdexcept>
#include "../Map/Map.h"
#include "../Player/player.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Commands/CommandProcessing.h"
#include "../Strategies/PlayerStrategies.h"
using namespace std;

enum State {
  Start,
  Tournament,
  Map_Loaded,
  Map_Validated,
  Players_Added,
  Reinforcement,
  Issue_Orders,
  Execute_Orders,
  Win
};

class Player;
class CommandProcessor;
class Map;
class Deck;
class Human;

//class FileCommandProcessorAdapter;

class GameEngine : public Subject, public ILoggable{
private:
    // Initial state
    State currentState = Start;
    std::string fileName;
    // For player management
    Player* currentPlayerTurn = nullptr;
    std::vector<Player *> players;
    std::vector<int> playerOrder;
    int numberOfPlayers = 0;

    std::vector<std::vector<std::string>> tournamentResults;

    // Deck Object
    Deck* deck = nullptr;

    // Logger Object
    LogObserver* logObserver = nullptr;

    // Map object
    Map *map = nullptr;;

    // Command Processor
    CommandProcessor* commandProcessor = nullptr;
    //FileCommandProcessorAdapter* adapter = nullptr;

    // CL Args
    int argc;
    char** argv;

    // testing
    bool testing = false;

    bool isDraw = false;
    bool tournamentEnd = false;
    std::vector<std::string> commands = {"tournament -M <mapFiles> -P <playerStrategies> -G <numGames> -D <maxTurns>", "loadmap <filename>", "validatemap", "addplayer <playername>", "gamestart", "replay", "quit"};

public:
    std::vector <std::string> allMaps;
    std::vector <std::string> allPlayerStrategies;
    int numberOfGames = 0;
    int maxNumberOfTurns = 0;
    bool multipleTournaments = false;

    // Constructors
    GameEngine();
    GameEngine(int argc, char** argv, bool testing = false);
    explicit GameEngine(State state, int argc, char** argv, bool testing = false);

    // Copy Constructor
    GameEngine(const GameEngine &other);
    // Assignment Operator
    GameEngine &operator=(const GameEngine &other);
    // Stream Insertion Operator
    friend std::ostream &operator<<(std::ostream &os, const GameEngine &engine);

    // Destructor
    ~GameEngine();


    //getters and setters
    LogObserver* getLogObserver();
    Map *getMap();
    Deck* getDeck();
    State getState(){return currentState;};
    std::string getTournamentResults();
    // print all players from array
    std::vector<Player*>* getPlayers();
    Player* getCurrentPlayerTurn();
    CommandProcessor* getCommandProcessor();

    void setCurrentPlayer(Player* player);

    string StateToString();

    // State Management
    void transition(State newState);


    void printCommands();

    bool isValid(const std::string& strCommand){return strCommand.find("Invalid") == string::npos;}

    // Game Logic
    void loadMap(const std::string &fileName);

    void validateTournament();

    bool validateMap();

    void validateMinPlayers();

    void validateMaxPlayers();

    void addPlayer(Player* player);

    void assignCountries();

    void issueOrder();

    void executeOrder();

    void win();

    void mainGameLoop(int maxRounds = 500);

    void distributeTerritories();

    void determinePlayerOrder();

    void assignInitialArmies(int i);

    void drawInitialCards(int i);

    void endIssueOrders();

    void endExecuteOrders();

    void nextTurn(int &turn);

    void generateRandomDeck(int deckSize = 15);

    void assignCardsEvenly();

    // check win state
    Player* checkWinState();


    void resetGame();
    //bool isTesting() const;
    

    // Added by Woo Jun for Part 3 Assignment 2
    void startupPhase();

    void reinforcementPhase();

    void issueOrdersPhase();

    void executeOrdersPhase();

    static void testMainGameLoop();

    // Torunament
    void runTournament();

    bool isTesting() const;


    //logging
    std::string stringToLog() override;
};

#endif // A1COMP345_GAMEENGINE_H
