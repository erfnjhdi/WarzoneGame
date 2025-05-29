#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include "../GameEngine/GameEngine.h"
#include "../LoggingObserver/LoggingObserver.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

class GameEngine;
class LoggingObserver;

// Represents a single command and its effect
class Command : public Subject, ILoggable {
private:
    std::string command;
    std::string effect;

    GameEngine* game = nullptr;

public:
    // Constructor and Destructor
    Command(const std::string& cmd, GameEngine* gameEngine);
    Command(const Command& other); // Copy constructor

    // Desructor
    ~Command() override;

    // Getters and Setters
    std::string getCommandString();
    void saveEffect(std::string effect);
    std::string getEffect();
    void setCommand(std::string _command);

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const Command& c);
    Command& operator=(const Command& other); // Assignment operator

    // Logging
    std::string stringToLog() override;
};

// Handles the processing of commands from the console
class CommandProcessor : public Subject, ILoggable {
private:
    // Collection of commands
    std::vector<Command*> commands;
    GameEngine* game;

    // command line arguments
    std::vector<std::string> args;

protected:
    virtual std::string readCommand();

public:
    //Constructors
    explicit CommandProcessor(GameEngine*, int argc,char* argv[]);
    CommandProcessor(const CommandProcessor &other);
    // Destructor
    ~CommandProcessor() override;

    void saveCommand(Command* c);
    Command* validate(const std::string& input);

    // Public interface to get a command
    Command* getCommand();
    // get current state from GameEngine
    int getCurrentState();
    // Getter for command collection
    std::vector<Command*> getCommandCollection();
    // Get array of args
    std::vector<std::string>* getArgs();

    //Operator Overloading
    friend std::ostream & operator << (std::ostream &out, const CommandProcessor &c);
    // Assignment overloading
    CommandProcessor& operator=(const CommandProcessor& other);

    // Print commands
    void printCommandCollection(const std::vector<Command *> &collection);
    std::string StateToString();

    void FileTournamentFunctionInput(std::string input);
    void TournamentFunctionInput(std::string);
    bool validateTournament();

    std::vector<std::string> split(const std::string& str, const std::string& delimiter);

    // for Logging
    std::string stringToLog() override;
};


class FileLineReader{

    private:
        std::string fileName;
        bool readComplete = false;
        int currentLine = 1;

    public:
    
        // Default constructor
        FileLineReader() = default;

        // Copy constructor
        FileLineReader(const FileLineReader &flr);

        // Reading line from file
        virtual std::string readLineFromFile();
        
        // Jump to num line number
        std::ifstream& GotoLine(std::ifstream& file, unsigned int num);
        
        // Return maximum number of lines in _fileName
        int maxNumberOfLines(const std::string& _fileName);
        
        // Relevant getters and setters
        void setFile(std::string _fileName);
        bool getReadComplete();
        int getCurrentLine();
        
        void incrementCurrentLine();

        //Operator Overloading
        friend std::ostream & operator << (std::ostream &out, const FileLineReader &flr);
        FileLineReader& operator=(const FileLineReader& other);
};
// Adapts the CommandProcessor to read commands from a file
class FileCommandProcessorAdapter : public CommandProcessor {
    
    private:
        FileLineReader *flr = nullptr;
    public:
        void commandLineToFile(FileLineReader* _flr);
        std::string readCommand() override;
        ~FileCommandProcessorAdapter() override = default;
        FileCommandProcessorAdapter(GameEngine* game, int argc, char** argv);

        // Copy constructor
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpA) = default;
        
        //Operator Overloading
        friend std::ostream & operator << (std::ostream &out, const FileCommandProcessorAdapter &ffcpAr);
        FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);
};

#endif // COMMANDPROCESSING_H
