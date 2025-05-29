cmake_minimum_required(VERSION 3.29)
project(Comp_345)

set(CMAKE_CXX_STANDARD 14)

add_executable(Comp_345 main.cpp
        Cards/Cards.cpp
        Map/Map.cpp
        GameEngine/GameEngine.cpp
        Player/player.cpp
        Orderslist/Orders.cpp
        LoggingObserver/LoggingObserver.cpp
        Strategies/PlayerStrategies.cpp
        Commands/CommandProcessing.cpp
        )