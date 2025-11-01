cmake_minimum_required(VERSION 4.2)

project(RatingDay VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка пути для исполняемых файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../Execute)

# Источники программы
set(PROGRAM_SOURCES
    Program/Main.cpp
    Program/MainWindow.cpp
    Program/MainWindow.h
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${PROGRAM_SOURCES})

# Установка свойств для Visual Studio
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

