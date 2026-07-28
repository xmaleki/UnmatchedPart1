cmake_minimum_required(VERSION 3.24)
project(Unmatched CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
            main.cpp
            src/Board.cpp
            src/Hero.cpp
            src/Map.cpp
            src/TerminalView.cpp
            src/Movement.cpp
            src/Space.cpp
            src/Card.cpp
            src/Deck.cpp
            src/Dracula.cpp
            src/GameManager.cpp
            src/Player.cpp
            src/Sherlock.cpp
            src/Sister.cpp
            src/Watson.cpp
            src/Combat.cpp
            )


include_directories(include)
