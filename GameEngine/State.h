//
// Created by Amin Boulemkahel on 2024-10-01.
//

#ifndef A1COMP345_STATE_H
#define A1COMP345_STATE_H

#include <string>
#include <iostream> // Required for stream insertion operator

class GameEngine;
/*
class State {
public:
    // Constructor
    State() = default;

    // Copy Constructor
    State(const State& other) = delete; // Disable copying for the base class

    // Assignment Operator
    State& operator=(const State& other) = delete; // Disable assignment for the base class

    // Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& os, const State& state) {
        os << "State base class"; // General output for the base class
        return os;
    }

    virtual ~State() {}
    virtual void handleCommand(GameEngine* game, const std::string& command) = 0;
};
*/
#endif // A1COMP345_STATE_H
