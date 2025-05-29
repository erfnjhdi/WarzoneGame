#include "CommandProcessing.h"

using namespace std;

regex matchMap("loadmap .+.map$");
regex matchPlayer("addplayer .+");

// Command Implementation
Command::Command(const std::string& cmd, GameEngine* gameEngine) {
  this->game = gameEngine;
  command = cmd;
  effect = "Command has not been executed yet";
  Subject::attach((Observer*)game->getLogObserver());
}
Command::Command(const Command& other) : Subject(other) {
  game = other.game;
  command = other.command;
  effect = other.effect;
    Subject::attach((Observer*)game->getLogObserver());
}

Command::~Command() {
    if(game){
    Subject::detach((Observer* )game->getLogObserver());
  }
}

void Command::saveEffect(string _effect){
    effect = std::move(_effect);
    Subject::notify(this);
}

string Command::getEffect(){
    return effect;
}

string Command::getCommandString(){
    return command;
}

void Command::setCommand(string _command){
    command = std::move(_command);
}

ostream & operator << (ostream &out, const Command &c)
{
    out << c.command << " : " << c.effect << endl;
    return out;
}

Command& Command::operator=(const Command &other) {
  if(this == &other){
    return *this;
  }

  this->command = other.command;
  this->effect = other.effect;
  Subject::attach((Observer*)game->getLogObserver());

  return *this;
}

std::string Command::stringToLog() {
    return "Logging COMMAND: \nSaved Effect \"" + getEffect() + "\"\n";
}

// CommandProcessor Implementation

CommandProcessor::CommandProcessor(GameEngine* game, int argc, char* argv[]) : game(game) {
  commands = {};
  // add all program arguments to a raw string
  for(int i = 0; i < argc; i++){ args.emplace_back(argv[i]); }
  Subject::attach((Observer*)game->getLogObserver());
}

CommandProcessor::CommandProcessor(const CommandProcessor& other) : Subject(other) {
    commands = {};
    for(auto i : other.commands){
        commands.push_back(new Command(*i));
    }
    this->args = other.args;
    this->game = other.game;
    Subject::attach((Observer*)game->getLogObserver());
}

CommandProcessor::~CommandProcessor() {
  if(game){
    Subject::detach((Observer* )game->getLogObserver());
  }
}

Command* CommandProcessor::getCommand(){
    string userInput = readCommand() ;
    Command* currentCommand = validate(userInput);
    saveCommand(currentCommand);
    return currentCommand;
}

string CommandProcessor::readCommand(){
    string userInput;
    cout << "Please enter a command: ";
    getline(cin, userInput);
    std::cout << std::endl;
    return userInput;
}

void CommandProcessor::saveCommand(Command* _currentCommand){
    commands.push_back(_currentCommand);
    Subject::notify(this);
}

int CommandProcessor::getCurrentState(){
    return game->getState();
}

Command* CommandProcessor::validate(const string& _userInput){

    auto currentCommandObj = new Command(_userInput, game);
    State current_game_state = game->getState();
    std::string strCommand = currentCommandObj->getCommandString();

    switch(current_game_state){
        case Start:
            if (std::regex_match(_userInput, matchMap)){
              size_t pos = strCommand.find(' ');
              std::string mapName = "res/" + MapLoader::trim(strCommand.substr(pos));
              try {
                game->loadMap(mapName);
              }
              catch(std::runtime_error& err){
                cout<< err.what() << endl;
                break;
              }
              game->transition(Map_Loaded);
              currentCommandObj->saveEffect("Map successfully loaded");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }

            else if (_userInput.substr(0, _userInput.find(' ')) == "tournament"){
              TournamentFunctionInput(_userInput);
              try {
                game->validateTournament();
              }
              catch(std::runtime_error& err){
                cout<< err.what() << endl;
                game->transition(Start);
                break;
              }
              game->transition(Tournament);
              currentCommandObj->saveEffect("Tournament started");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }

            break;


        case Map_Loaded:
            if (_userInput == "validatemap"){

              try{
                game->validateMap();
              }
              catch(std::runtime_error& err){
                cout<< err.what() << endl;
                game->transition(Start);
                break;
              }

              game->transition(Map_Validated);
              currentCommandObj->saveEffect("Map successfully validated");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }
            else if (std::regex_match(_userInput, matchMap)){
                cout << "Map already loaded" << endl;
            }
            break;

        case Map_Validated:
            if (std::regex_match(_userInput, matchPlayer)){

                size_t pos = strCommand.find(' ');
                std::string playerName = strCommand.substr(pos);

                // trim spacing
                std::string::iterator end_pos = std::remove(playerName.begin(), playerName.end(), ' ');
                playerName.erase(end_pos, playerName.end());

                if(game->isTesting()){
                  cout << "Game Engine is in testing mode, player will be added automatically as Aggressive." << endl;
                  new Player(game, new Hand(), playerName, "Random");
                } else {
                  new Player(game, new Hand(), playerName, "Human");
                }
                currentCommandObj->saveEffect("Player" + playerName + " has been added successfully");
                game->transition(Players_Added);
                cout << currentCommandObj->getEffect() << endl;
                return currentCommandObj;
            }
            break;

        case Players_Added:
            if (std::regex_match(_userInput, matchPlayer)){

              try {
                game->validateMaxPlayers();
              }
              catch(std::runtime_error& err){
                cout << err.what() << endl;
                break;
              }

              size_t pos = strCommand.find(' ');
              std::string playerName = strCommand.substr(pos);

              // trim spacing
              std::string::iterator end_pos = std::remove(playerName.begin(), playerName.end(), ' ');
              playerName.erase(end_pos, playerName.end());

              if(game->isTesting()){
                cout << "Game Engine is in testing mode, player will be added automatically as Aggressive." << endl;
                new Player(game, new Hand(), playerName, "Random");
              } else {
                new Player(game, new Hand(), playerName, "Human");
              }

              currentCommandObj->saveEffect("Player" + playerName + " has been added successfully");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }
            else if(_userInput == "gamestart"){

              // Check for minimum 2 players before starting
              try {
                game->validateMinPlayers();
              }
              catch(std::runtime_error& err){
                cout << err.what() << endl;
                break;
              }

              game->distributeTerritories();
              cout<< "Territories distributed."<<endl;

              game->determinePlayerOrder();
              cout<< "Order of play of players determined."<<endl;

              // initialize deck
              game->getDeck()->create_deck();

              try{
                for(Player* player : *game->getPlayers()){
                  player->setReinforcementPool(50);
                  game->setCurrentPlayer(player);
                  Hand &hand = *player->getHand();
                  game->getDeck()->draw(hand);
                  game->getDeck()->draw(hand);
                }
              }
              catch(std::runtime_error& err){
                cout << err.what() <<endl;
                break;
              }

              game->transition(Reinforcement);
              currentCommandObj->saveEffect("Game successfully started");
              cout << currentCommandObj->getEffect() << endl;
              game->mainGameLoop();
              return currentCommandObj;
            }
            break;

        case Win:
            if (_userInput == "replay"){
                game->transition(Start);
                currentCommandObj->saveEffect("Game successfully restarted");
                cout << currentCommandObj->getEffect() << "!\n" << endl;
                return currentCommandObj;
            }
            else if(_userInput == "quit"){
                cout << "Quitting game";
                exit(0);
            }
            break;
        case Reinforcement:
          throw std::runtime_error("CommandProcessor::GE_Reinforcement Not Implemented Yet");
        case Issue_Orders:
          throw std::runtime_error("CommandProcessor::GE_Issue_Orders Not Implemented Yet");
        case Execute_Orders:
          throw std::runtime_error("CommandProcessor::GE_Execute_Orders Not Implemented Yet");
        case Tournament:
          throw std::runtime_error("Tournament mode.");
    }

    currentCommandObj->saveEffect("Invalid Command");
    return currentCommandObj;

}

void CommandProcessor::printCommandCollection(const std::vector<Command*>& collection){
    for(auto & i : collection){
        cout << (*i) << endl;
    }
    cout << "Current Game State: " << game->StateToString() << endl;
}

vector<Command*> CommandProcessor::getCommandCollection(){
    return commands;
}


std::ostream& operator<<(std::ostream& out, const CommandProcessor& cp) {
    for (const Command* cmd : cp.commands) {
        out << *cmd << std::endl;
    }
    return out;
}

CommandProcessor& CommandProcessor::operator=(const CommandProcessor &other) {
  if(this == &other){
      return *this;
  }
  this->commands = other.commands;
  Subject::attach((Observer*)game->getLogObserver());
  return *this;
}
// Logging
std::string CommandProcessor::stringToLog() {
  return "Logging COMMAND PROCESSOR: \nSaved command :\"" + commands.back()->getCommandString() + "\"\n";
}
// Return array of args
std::vector<std::string> *CommandProcessor::getArgs() {
  return &args;
}

std::vector<std::string> CommandProcessor::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    
    tokens.push_back(str.substr(start));
    return tokens;
}

void CommandProcessor::TournamentFunctionInput(string input) {
  vector<string> enteredTournamentString = split(input, " ");
  int i = 1; // skip the first word "tournament"
  while (i < enteredTournamentString.size()) {
    if (enteredTournamentString[i] == "-M") {
      while (enteredTournamentString[++i] != "-P") {
        game->allMaps.push_back(enteredTournamentString[i]);
      }
    }
    else if (enteredTournamentString[i] == "-P") {
      while (enteredTournamentString[++i] != "-G") {
        game->allPlayerStrategies.push_back(enteredTournamentString[i]);
      }

    }
    else if (enteredTournamentString[i] == "-G") {
      i++;
      string temp;
      temp = enteredTournamentString[i++];
      if (!isdigit(temp[0])) {
        cout << "The number of games has to be a digit" << endl;
        exit(0);
      }
      game->numberOfGames = stoi(temp);

    }
    else if (enteredTournamentString[i] == "-D") {
      i++;
      string temp;
      temp = enteredTournamentString[i++];
      if (!isdigit(temp[0])) {
        cout << "The max number of turns has to be a digit" << endl;
        exit(0);
      }
      game->maxNumberOfTurns = stoi(temp);
    }
  }
}

void CommandProcessor::FileTournamentFunctionInput(string input) {

  std::ifstream temp(input);
  int numberOfTournaments = 0;
  int tournamentsPlayed = 0;
  std::string lineCounter;
  while (std::getline(temp , lineCounter)){
    numberOfTournaments++;
  }

  if(numberOfTournaments > 1){
    game->multipleTournaments = true;
  }

  temp.close();
  ifstream ifs;
  string line;
  ifs.open(input);

  if(!ifs.is_open()){
    throw std::runtime_error("File already open");
  }
  while(getline(ifs, line)){
    TournamentFunctionInput(line);
    game->validateTournament();
    game->runTournament();
    tournamentsPlayed++;
    std::cout << std::endl;
    if(tournamentsPlayed < numberOfTournaments){
      std::cout << "------- NEXT TOURNAMENT STARTING NOW! -------" << std::endl;
    }
  }
  ifs.close();
}

/*
FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game, const std::string& fileName)
    : CommandProcessor(game, 0, nullptr), fileName(fileName) {
    // Open the file
    commandFile.open(fileName);
    if (!commandFile.is_open()) {
        throw std::runtime_error("Could not open file: " + fileName);
    }
}

 FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other)
    : CommandProcessor(other) { // Copy the base class (CommandProcessor)
    // Copy the file name (fileName)
    this->fileName = other.fileName;

    // Ensure the file stream is closed in the source object
    if (other.commandFile.is_open()) {
        throw std::runtime_error("Cannot copy an open file stream.");
    }

    // Copy other member variables
    this->readComplete = other.readComplete;
    this->currentLine = other.currentLine;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    if (commandFile.is_open()) {
        commandFile.close();
    }
}

std::string FileCommandProcessorAdapter::readCommand() {
    if (readComplete) {
        throw std::runtime_error("All commands have been read from the file.");
    }

    std::string line;
    // Jump to the current line
    goToLine(commandFile, currentLine);

    // Read the line
    if (std::getline(commandFile, line)) {
        currentLine++;
        // Check if this is the last line
        if (currentLine > countTotalLines(fileName)) {
            readComplete = true;
        }
        return line;
    } else {
        readComplete = true;
        throw std::runtime_error("No more commands to read.");
    }
}

std::ifstream& FileCommandProcessorAdapter::goToLine(std::ifstream& file, unsigned int line) {
    file.clear();
    file.seekg(0, std::ios::beg); // Reset to beginning of the file
    for (unsigned int i = 0; i < line - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return file;
}

int FileCommandProcessorAdapter::countTotalLines(const std::string& fileName) {
    std::ifstream tempFile(fileName);
    int lineCount = 0;
    std::string line;
    while (std::getline(tempFile, line)) {
        lineCount++;
    }
    return lineCount;
}

bool FileCommandProcessorAdapter::isReadComplete() const {
    return readComplete;
}

int FileCommandProcessorAdapter::getCurrentLine() const {
    return currentLine;
}

std::ostream& operator<<(std::ostream& out, const FileCommandProcessorAdapter& adapter) {
    out << "FileCommandProcessorAdapter currently reading from file: " << adapter.fileName << "\n";
    out << "Current line: " << adapter.currentLine << "\n";
    out << "Read complete: " << (adapter.readComplete ? "Yes" : "No") << "\n";
    return out;
}*/
