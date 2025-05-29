
#include "GameEngine.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <array>

#include <iostream>
#include <map>
#include <random>

#include "Utils.h"
#include <iomanip>

#include "../Map/MapLoader.h"
#include "../Player/player.h"


State currentPhase = Start; // Use your States enum to track the current phase

/**
 * @brief Constructor for the GameEngine class.
 *
 * Initializes the game engine by setting the initial state to StartState.
 */
GameEngine::GameEngine() {
    // currentState = new (); // Start the game with StartState
}

GameEngine::GameEngine(State state, int argc, char** argv, bool testing) {
  this->currentState = state;
  this->deck = new Deck(this);
  this->map = new Map(this);
  this->logObserver = new LogObserver(this);
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  Subject::attach((Observer*)logObserver);

  this->argc = argc;
  this->argv = argv;

  this->testing = testing;
}

GameEngine::GameEngine(int argc, char** argv, bool testing) {
  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->argc = argc;
  this->argv = argv;
  Subject::attach((Observer*)logObserver);
  this->testing = testing;
}

// Copy constructor
GameEngine::GameEngine(const GameEngine &other)
    : currentState(other.currentState),
      numberOfPlayers(other.numberOfPlayers) {
    // Deep copy the players vector
    for (Player* player : other.players) {
        players.push_back(new Player(*player));
    }

    // Deep copy the playerOrder vector
    playerOrder = other.playerOrder;

    // Deep copy the Deck object
    if (other.deck) {
        deck = new Deck(*other.deck);
    } else {
        deck = nullptr;
    }

    // Deep copy the Map object
    if (other.map) {
        map = new Map(*other.map);
    } else {
        map = nullptr;
    }

    // Copy the LogObserver pointer (not deep copied as it’s shared)
    logObserver = other.logObserver;

    // Copy the CommandProcessor object (not deep copied as per usual design patterns)
    if (other.commandProcessor) {
        commandProcessor = new CommandProcessor(*other.commandProcessor);
    } else {
        commandProcessor = nullptr;
    }

    // Copy the FileCommandProcessorAdapter object (if it exists)
    /*if (other.adapter) {
        adapter = new FileCommandProcessorAdapter(*other.adapter);
    } else {
        adapter = nullptr;
    }*/
}


/**
 * @brief Destructor for the GameEngine class.
 *
 * Ensures that the dynamically allocated currentState is deleted
 * to prevent memory leaks when the GameEngine object is destroyed.
 */
GameEngine::~GameEngine() {
  for(auto player : players){
    delete player;
  }
  delete deck;
  delete map;
  delete commandProcessor;
  //delete adapter;
}


Map *GameEngine::getMap() {
    return map;
}

Deck* GameEngine::getDeck() {
  return this->deck;
}

LogObserver* GameEngine::getLogObserver() {
    return this->logObserver;
}

std::vector<Player *> *GameEngine::getPlayers() {
  return &this->players;
}

Player* GameEngine::getCurrentPlayerTurn() {
  return currentPlayerTurn;
}

CommandProcessor* GameEngine::getCommandProcessor() {
    return this->commandProcessor;
}

/**
 * @brief Transitions the game to a new state.
 *
 * Deletes the current state and replaces it with the new state passed
 * as a parameter.
 *
 * @param newState The new state to transition into.
 */
void GameEngine::transition(State newState) {
    currentState = newState;
    Subject::notify(this);
}

/**
 * @brief Loads the game map.
 */
void GameEngine::loadMap(const std::string& path) {
  MapLoader::load(path, this->map);
}

/**
 * @brief Validates the loaded map.
 */
bool GameEngine::validateMap() {
  if(map == nullptr){ throw runtime_error("ASSERT: Map is null."); }
  return map->validate();
}

void GameEngine::setCurrentPlayer(Player* player) {
  currentPlayerTurn = player;
}

/**
 * @brief Adds a player to the game.
 */
void GameEngine::addPlayer(Player* player) {
  if(player == nullptr){
    throw std::runtime_error("GameEngine::Error | Cannot add player to game (nullptr)");
  }
  if(currentState > Players_Added){
    throw std::runtime_error("GameEngine::ASSERT | Cannot add player to game. Game is already in progress.");
  }
  this->players.push_back(player);
}


void GameEngine::validateMaxPlayers() {
  if(players.size() == 6){
    throw std::runtime_error("Maximum number of players(6) reached! Game is ready to be started.");
  }
}

void GameEngine::validateMinPlayers() {
  if(players.size() < 2){
    throw std::runtime_error("Please add at least one more player! Minimum number of players required is two(2).");
  }
}

/**
 * @brief Assigns countries to players.
 */
void GameEngine::assignCountries() {
    std::cout << "Countries assigned.\n";
}

/**
 * @brief Issues an order during the order phase.
 */
void GameEngine::issueOrder() {
    std::cout << "Order issued.\n";
}

/**
 * @brief Executes an order during the execution phase.
 */
void GameEngine::executeOrder() {
    std::cout << "Order executed.\n";
}

/**
 * @brief Ends the order issuing phase.
 */
void GameEngine::endIssueOrders() {
    std::cout << "Orders issuing ended\n";
}

/**
 * @brief Ends the order execution phase.
 */
void GameEngine::endExecuteOrders() {
    std::cout << "Orders execution ended\n";
}

/**
 * @brief Declares the game won.
 */
void GameEngine::win() {
    std::cout << "You win!\n";
}


void GameEngine::mainGameLoop(int maxRounds) {

    startupPhase();
    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();

}

void GameEngine::startupPhase() {
    Command* command;
    std::string strCommand;
    std::string effect;

    if(!commandProcessor){ throw std::runtime_error("GameEngine::startupPhase::ASSERT commandProcessor is null"); }
    cout << "Welcome to the startup phase of the game!\n"<< endl;
    printCommands();
    do{
        command = commandProcessor->getCommand();
        strCommand = command->getCommandString();
        effect = command->getEffect();

        if(effect == "Game successfully restarted") {
          resetGame();
          startupPhase();
        }

        else if(effect == "Tournament started"){
          runTournament();
          strCommand = "quit";
        }

        else if(!isValid(effect) && strCommand != "quit"){
            cout << "The command or its argument is invalid" << endl;
            continue;
        }
    } while(strCommand != "quit" );
}


void GameEngine::distributeTerritories() {
  if(!map){ throw std::runtime_error("GameEngine::distributeTerritories::ASSERT Map is null"); }
  std::vector<Territory*>* territories = map->getTerritories();
  int numPlayers = (int)players.size();
  int territoriesDistr[numPlayers];
  int terrPerPlayer = floor(territories->size() / numPlayers);
  int remainingTerr = (int)territories->size() - (numPlayers * terrPerPlayer);
  int currPlayer = 0;
  int tempTerr = 0;
  Player* player = players.at(currPlayer);

  for(int i = 0; i < numPlayers; i++){
      territoriesDistr[i] = terrPerPlayer;
      if(remainingTerr > 0){
              territoriesDistr[i] +=1;
              remainingTerr--;
      }
  }

  for(Territory *terr : *territories){
      Territory* t = terr;
      if(tempTerr == (territoriesDistr[currPlayer])){
          currPlayer++;
          player = players.at(currPlayer);
          tempTerr = 0;
      }
      player->addTerritory(*t);
      tempTerr++;
  }
}


void GameEngine::determinePlayerOrder() {
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(players), std::end(players), rng);
}

void GameEngine::assignInitialArmies(int i) {
    cout << "\n************* Initial Armies Assigned ***************\n\n";

    for (auto player: players) {
        player->setReinforcementPool(i);
        std::cout << "Player " << player->getName() << " assigned " << i << " armies.\n";
    }
}

void GameEngine::reinforcementPhase()
{
  for (auto& player : players)
  {
    currentPlayerTurn = player;
    player->setPhase("Reinforcement");
    cout << "Player: " << player->getName() << "'s current Reinforcement Pool: "<< player->getReinforcementPool() << endl;
    // check for continents bonus before territories themselves
    // check if players owned number of territories matches a continent that hold n amount of territories in order to gain control bonus
    int reinforcementsToAdd = 0;

    // get continent bonus
    reinforcementsToAdd += player->getContinentBonus();
    if(reinforcementsToAdd > 0){cout << "Player: " << player->getName() << "'s continent bonus is: "<< player->getReinforcementPool() << endl;}

    // get territories reinforcement
    reinforcementsToAdd += (int)(player->getTerritories()->size() / 3) * 3;

    // check if they have min
    if(reinforcementsToAdd < 3){ reinforcementsToAdd = 3;}

    player->addReinforcement(reinforcementsToAdd);

    cout << "Player: " << player->getName() << "'s updated Reinforcement Pool: "<< player->getReinforcementPool() << endl;
  }
}

void GameEngine::issueOrdersPhase() {
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for(auto& player : players){ player->setPhase("Issue Orders"); }

  while(!std::all_of(completed.begin(), completed.end(), [](bool v) { return v; })){
    if(completed[phaseTurn]){ nextTurn(phaseTurn); continue; }
    currentPlayerTurn = players[phaseTurn];

    cout << "Player: " << currentPlayerTurn->getName() << "'s turn to issue an order!" << endl;

    auto human = dynamic_cast<Human*>(currentPlayerTurn->getStrategy());

    // when no more orders need to be issued
    if(currentPlayerTurn->getDeployedArmiesThisTurn() >= currentPlayerTurn->getReinforcementPool() && human == nullptr){
      completed[phaseTurn] = true;
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      continue;
    }

    if(human != nullptr && human->isTurnDone){
      completed[phaseTurn] = true;
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      continue;
    }

    currentPlayerTurn->issueOrder();

    nextTurn(phaseTurn);
  }

  for(auto& player : players){
    player->clearDeploymentArmies();
    // clear the deployment troops for all human players
    if(auto strategy = dynamic_cast<Human*>(player->getStrategy())){
      strategy->reset();
    }
  }
}

void GameEngine::executeOrdersPhase() {
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for(auto& player : players){ player->setPhase("Execute Orders Phase"); }

  while(!std::all_of(completed.begin(), completed.end(), [](bool v) { return v; })){
    if(completed[phaseTurn]){nextTurn(phaseTurn); continue; }
    currentPlayerTurn = players[phaseTurn];
    auto currentPlayerOrders = currentPlayerTurn->getOrdersListObject()->getList();

    // when no more orders need to be issued
    if(currentPlayerOrders->empty()){
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to execute." << endl;
      completed[phaseTurn] = true;
      continue;
    }

    auto topOrder = currentPlayerOrders->at(0);
    cout << "Player: " << currentPlayerTurn->getName() << "'s order: " + topOrder->getLabel() + " is being executed." << endl;
    topOrder->execute();
    currentPlayerOrders->erase(currentPlayerOrders->cbegin());

    delete topOrder;

    nextTurn(phaseTurn);
  }
}

//assignment operator
GameEngine& GameEngine::operator=(const GameEngine &other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    // Clean up existing resources
    for (Player* player : players) {
        delete player;
    }
    players.clear();

    delete deck;
    deck = nullptr;

    delete map;
    map = nullptr;

    delete commandProcessor;
    commandProcessor = nullptr;

    //delete adapter;
    //adapter = nullptr;

    // Copy simple data members
    currentState = other.currentState;
    numberOfPlayers = other.numberOfPlayers;

    // Deep copy the players vector
    for (Player* player : other.players) {
        players.push_back(new Player(*player));
    }

    // Copy the playerOrder vector
    playerOrder = other.playerOrder;

    // Deep copy the Deck object
    if (other.deck) {
        deck = new Deck(*other.deck);
    }

    // Deep copy the Map object
    if (other.map) {
        map = new Map(*other.map);
    }

    // Copy the LogObserver pointer (not deep copied as it’s shared)
    logObserver = other.logObserver;

    // Deep copy the CommandProcessor object
    if (other.commandProcessor) {
        commandProcessor = new CommandProcessor(*other.commandProcessor);
    }

    // Deep copy the FileCommandProcessorAdapter object
    /*if (other.adapter) {
        adapter = new FileCommandProcessorAdapter(*other.adapter);
    }*/

    return *this;
}

void GameEngine::validateTournament() {
  if (allMaps.size() < 1 || allMaps.size() > 5)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of maps must be between 1 to 5";
    exit(0);
  }
  if (allPlayerStrategies.size() < 2 || allPlayerStrategies.size() > 4)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of player strategies must be between 2 to 4";
    exit(0);
  }
  if (numberOfGames < 1 || numberOfGames > 5)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of games must be between 1 to 5";
    exit(0);
  }
  if (maxNumberOfTurns < 10 || maxNumberOfTurns > 50)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of turns must be between 10 to 50";
    exit(0);
  }
  // validate strategy
  string strategies[5] = {"Aggressive", "Benevolent", "Neutral", "Cheater", "Human"};
  int invalidStrategyCounter = 0;

  for (int i = 0; i < allPlayerStrategies.size(); i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (allPlayerStrategies[i] == strategies[j])
      {
        break;
      }
      else if (allPlayerStrategies[i] != strategies[j] && j == 4)
      {
        cout << allPlayerStrategies[i] + " X NOT VALID" << endl;
        invalidStrategyCounter++;
      }
    }
  }
  if (invalidStrategyCounter > 0)
  {
    cout << invalidStrategyCounter;
    throw std::runtime_error("GameEngine::validateTournament::Error | Player strategies entered are not valid");
  }
}

void GameEngine::resetGame() {

  if(multipleTournaments){
    allPlayerStrategies = {};
    numberOfGames = 0;
    maxNumberOfTurns = 0;
  }

  for(auto player : players){
    delete player;
  }

  delete deck;
  delete map;
  //delete adapter;
  delete logObserver;

  this->players = vector<Player*>();
  this->currentPlayerTurn = nullptr;
  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  //this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->resetObservers();

  if(!multipleTournaments){
    delete commandProcessor;
    this->commandProcessor = new CommandProcessor(this, argc, argv);
  }

  Subject::attach((Observer*)logObserver);

}


void GameEngine::runTournament() {
    tournamentEnd = false;
  for(int i = 0; i < allMaps.size(); i++){
    loadMap(allMaps[i]);
    std::vector<std::string> currMap{};
    currMap.push_back(allMaps.at(i));
    int localNumGames = numberOfGames;
    int localMaxTurns = maxNumberOfTurns;
    std::vector<std::string> localAllPlayerStrategies = allPlayerStrategies;
    if(validateMap()){
      for(int j = 0; j < localNumGames; j++){
        generateRandomDeck();
        for (auto & allPlayerStrategies : localAllPlayerStrategies){
          new Player(this, new Hand(), allPlayerStrategies, allPlayerStrategies);
        }
        assignCardsEvenly();
        distributeTerritories();
        mainGameLoop(localMaxTurns);
        currMap.push_back(isDraw? "draw" : checkWinState()->getName());

        resetGame();
        currentState = Tournament;
        loadMap(allMaps[i]);
      }
      resetGame();
    }
    else{
      std::cout << "" << std::endl;
      std::cout << "Map " + std::to_string(i+1) + " is invalid" << std::endl;
      resetGame();
      currentState = Tournament;
    }
      tournamentResults.push_back(currMap);
  }
    tournamentEnd = true;
    Subject::notify(this);
}

// Show tournament results
std::string GameEngine::getTournamentResults() {
    std::stringstream str;
    const char separator = ' ';
    const int mapNameWidth = 25;
    const int nameWidth = 15;
    str << "Tournament Mode: " << endl;
    str << "M: ";
    for(int i = 0; i < tournamentResults.size(); i++){
        str << (tournamentResults.at(i))[0] << ((i != tournamentResults.size()-1)? ',' : ' ');
    }
    str << endl << "P: ";
    for(int i = 0; i < allPlayerStrategies.size(); i++ ){
        str << (allPlayerStrategies.at(i)) << ((i != allPlayerStrategies.size()-1)? ',' : ' ');
    }
    str << endl << "G: " << numberOfGames << endl << "D: " << maxNumberOfTurns << endl;
    str << std::left << std::setw(mapNameWidth) << std::setfill(separator) << "Map Name";

    for(int s = 1; s <= numberOfGames; s++){
        str << std::left << std::setw(nameWidth) << std::setfill(separator) << ("Game " + std::to_string(s));
    }
    str << endl;

    for(auto & tournamentResult : tournamentResults){
        str << std::left << std::setw(mapNameWidth) << std::setfill(separator) << tournamentResult.at(0);

        for(int j = 1; j < tournamentResult.size(); j++) {
            str << std::left << std::setw(nameWidth) << std::setfill(separator) << tournamentResult.at(j);
        }
        str << endl;
    }
    return str.str();
}

string GameEngine::StateToString() {
  switch (getState()) {
    case Start:
        return "start";
    case Tournament:
        return "tournament";
    case Map_Loaded:
        return "maploaded";
    case Map_Validated:
        return "mapvalidated";
    case Players_Added:
        return "playersadded";
    case Reinforcement:
        return "assignreinforcement";
    case Win:
        return "win";
    case Issue_Orders:
      return "issueorders";
    case Execute_Orders:
      return "executeorders";
  }
  throw std::runtime_error("GameEngine::StateToString Assert:Invalid State");
}

std::string GameEngine::stringToLog() {
  std::stringstream ss;
  ss << "Logging GAME ENGINE: \n";
  ss << "State transition to ";
  ss << StateToString();
  ss << "\n";
  return ss.str();
}

void GameEngine::nextTurn(int &turn) {
  turn++;
  turn %= (int)players.size();
}

void GameEngine::generateRandomDeck(int deckSize){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, 4);

  CardType cardOptions[5] = {C_Bomb,C_Reinforcement,C_Blockade, C_Airlift, C_Diplomacy};

  for(int i = 0; i < deckSize; i++){
    int randomNum = distribution(gen);
    deck->addCardToDeck(new Card(cardOptions[randomNum], this));
  };
}

void GameEngine::assignCardsEvenly(){
  for(auto & player : players){
    player->getHand()->addToHand(new Card(CardType::C_Reinforcement, this));
    player->getHand()->addToHand(new Card(CardType::C_Blockade, this));
    player->getHand()->addToHand(new Card(CardType::C_Bomb, this));
    player->getHand()->addToHand(new Card(CardType::C_Diplomacy, this));
    player->getHand()->addToHand(new Card(CardType::C_Airlift, this));
  }
}

Player* GameEngine::checkWinState() {
  if(map == nullptr){throw std::runtime_error("checkWinState::Assert Map is null.");}

  int totalAmountOfTerritories = (int) map->getTerritories()->size();

  for(auto& player: players){
    // check if a player has all the territories
    if(player->getTerritories()->size() == totalAmountOfTerritories){
      return player;
    }
  }
  return nullptr;
}

void GameEngine::printCommands() {
    cout<< "Here are the commands available to you: "<<endl;
    for (const string& cmd: commands) {
        cout << cmd << " ";
    }
    cout << "\n" << endl;
}
bool GameEngine::isTesting() const {
  return testing;
}