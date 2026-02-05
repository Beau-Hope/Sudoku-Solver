cmake_minimum_required(VERSION 3.16)
project(SudokuSolverQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt automoc / autouic / autorcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(SudokuSolverQt
    src/main.cpp
    src/MainWindow.h
    src/MainWindow.cpp
    src/sudoku/Board.cpp
    src/sudoku/Solver.cpp
)

target_include_directories(SudokuSolverQt PRIVATE
    src
)

target_link_libraries(SudokuSolverQt
    Qt6::Widgets
)
