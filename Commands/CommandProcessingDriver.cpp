#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include <iostream>
#include <stdexcept>

// Function to test CommandProcessor functionality
/*void testCommandProcessor(int argc, char* argv[]) {
    // Initialize the GameEngine
    auto gameEngine = new GameEngine();

    // Decision for input type (-file or -console)
    std::string inputMode;

    // Variable to track if more commands need to be entered
    bool moreCommands = true;
    std::string moreCommandsDecision;

    // Initialize CommandProcessor and FileCommandProcessorAdapter
    CommandProcessor commandProcessor(gameEngine, argc, argv);
    FileCommandProcessorAdapter fileAdapter(gameEngine, ""); // File name set dynamically later

    // Get raw command line arguments
    std::vector<std::string>* inputArgs = commandProcessor.getArgs();

    // Check if enough arguments are provided
    if (inputArgs->size() < 2) {
        std::cerr << "You must specify either -console or -file <filename>" << std::endl;
        exit(1);
    }

    // Determine input mode based on arguments
    inputMode = inputArgs->at(1);

    // Handle commands via console
    if (inputMode == "-console") {
        do {
            // Get command from CommandProcessor
            Command* command = commandProcessor.getCommand();

            // Print command collection after each command
            commandProcessor.printCommandCollection(commandProcessor.getCommandCollection());

            // Ask user if they want to continue entering commands
            std::cout << "Do you want to enter another command? (y/n): ";
            std::getline(std::cin, moreCommandsDecision);
            std::cout << std::endl;

            // Continue or stop based on user input
            moreCommands = (moreCommandsDecision == "y");
        } while (moreCommands);
    }

    // Handle commands via file
    else if (inputMode == "-file") {
        // Check if file name is provided
        if (inputArgs->size() < 3) {
            std::cerr << "You must provide a file name as the third argument when using -file mode." << std::endl;
            exit(1);
        }

        // Set the file name and open it via the adapter
        std::string fileName = inputArgs->at(2);
        //fileAdapter = FileCommandProcessorAdapter(gameEngine, fileName);

        // Process commands from the file
        while (!fileAdapter.isReadComplete()) {
            Command* command = fileAdapter.getCommand(); // Read command
        }

        // Print all commands processed from the file
        fileAdapter.printCommandCollection(fileAdapter.getCommandCollection());
    }

    // Invalid input mode
    else {
        throw std::runtime_error("Invalid input mode. Use -console or -file <filename>");
    }

    // Cleanup
    delete gameEngine;
}*/
