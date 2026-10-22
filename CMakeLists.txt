cmake_minimum_required(VERSION 3.16)
project(TICTACTOE)

# 1. Qt6 are nevoie OBLIGATORIU de C++17
set(CMAKE_CXX_STANDARD 17)

# 2. Activăm compilatoarele specifice Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 3. Setăm calea către Qt (folosind calea ta de la celalalt proiect)
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")

# 4. Căutăm pachetul Qt6
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Includem folderele tale
include_directories(DOMAIN)
include_directories(GUI)
include_directories(REPO)
include_directories(SERVICE)

# Creăm executabilul
add_executable(TICTACTOE
        DOMAIN/Joc.cpp
        DOMAIN/Joc.h
        GUI/JocGUI.cpp
        GUI/JocGUI.h
        GUI/JocTableModel.cpp
        GUI/JocTableModel.h
        REPO/JocRepo.cpp
        REPO/JocRepo.h
        SERVICE/JocService.cpp
        SERVICE/JocService.h
        main.cpp)

# 5. Legăm bibliotecile Qt de executabilul tău
target_link_libraries(TICTACTOE PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)