#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

/**
 * Interface for objects that can be logged
 * Any class that needs to be logged should inherit from this
 */
class GameEngine;
class ILoggable {
public:
    virtual ~ILoggable() = default;
    virtual std::string stringToLog() = 0;
};

/**
 * Observer base class for implementing the Observer pattern
 */
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(ILoggable* loggable) = 0;
};

class ISubject {
public:
  virtual ~ISubject() = default;
  virtual void attach(Observer* observer) = 0;
  virtual void detach(Observer* observer) = 0;
  virtual void notify(ILoggable*) = 0;
  virtual void resetObservers() = 0;
};

/**
 * Subject base class that can be observed
 * Classes that need to be observed should inherit from this
 */
class Subject : ISubject {
private:
  std::vector<Observer*> observers;
public:
  Subject() = default;
  ~Subject() override = default;

  void attach(Observer* observer) override;
  void detach(Observer* observer) override;
  void notify(ILoggable*) override;
  void resetObservers() override;

};

/**
 * Concrete observer that logs to a file
 * Implements Singleton pattern
 */
class LogObserver : public Observer {
private:
    // Gameengine object
    GameEngine* game;

public:

    // Constructors
    explicit LogObserver(GameEngine*);
    ~LogObserver() override = default;
    explicit LogObserver(LogObserver*);

    void update(ILoggable*) override;

    // Stream Operator
    friend std::ostream &operator << (std::ostream &out, const LogObserver &log);

    // Assignment Operator
    LogObserver& operator=(const LogObserver &other);
};