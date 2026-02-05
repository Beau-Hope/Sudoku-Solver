cmake_minimum_required(VERSION 3.16)
project(SudokuSolverQt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt automoc / autouic / autorcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(SudokuSolverQt
    src/main.cpp
    src/gui/MainWindow.cpp
    src/gui/MainWindow.h
    src/gui/SudokuTable.cpp
    src/gui/SudokuTable.h
    src/sudoku/Board.cpp
    src/sudoku/Board.h
    src/sudoku/Solver.cpp
    src/sudoku/Solver.h
)

target_link_libraries(SudokuSolverQt
    Qt6::Widgets
)
