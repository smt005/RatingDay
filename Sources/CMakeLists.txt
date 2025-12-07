cmake_minimum_required(VERSION 4.2)

set(PROJECT_NAME RatingDay)

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка пути для исполняемых файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../Bin)

# Добавление подпроекта ImGui
add_subdirectory(Engine)

# Укажите папку с исходниками
set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/Program)

# Рекурсивно добавьте все файлы .cpp и .h из папки Sources
file(GLOB_RECURSE PROGRAM_SOURCES
    ${SOURCES_DIR}/*.cpp
    ${SOURCES_DIR}/*.h
)
source_group(TREE ${SOURCES_DIR} TREE PREFIX "" FILES ${PROGRAM_SOURCES})

# Заголовочные файлы ImGui
set(IMGUI_HEADERS
    Engine/ImGui/imgui.h
    Engine/ImGui/imgui_internal.h
    Engine/ImGui/imconfig.h
    Engine/ImGui/imstb_rectpack.h
    Engine/ImGui/imstb_textedit.h
    Engine/ImGui/imstb_truetype.h
    Engine/ImGui/backends/imgui_impl_win32.h
    Engine/ImGui/backends/imgui_impl_opengl3.h
)

# Заголовочные файлы JsonCpp
set(JSONCPP_HEADERS
    Engine/jsoncpp/include/json/json.h
    Engine/jsoncpp/include/json/value.h
    Engine/jsoncpp/include/json/reader.h
    Engine/jsoncpp/include/json/writer.h
    Engine/jsoncpp/include/json/config.h
    Engine/jsoncpp/include/json/forwards.h
    Engine/jsoncpp/include/json/json_features.h
    Engine/jsoncpp/include/json/assertions.h
    Engine/jsoncpp/include/json/allocator.h
    Engine/jsoncpp/include/json/version.h
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/Engine/Platforms/Win32/main.cpp ${PROGRAM_SOURCES} ${IMGUI_HEADERS} ${JSONCPP_HEADERS})

# Устанавливаем подсистему Windows (не консоль)
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
    # Добавляем флаг /utf-8 для поддержки UTF-8 в строках
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

include_directories(${PROGRAM_SOURCES})

# Запускаемый проект
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Связывание с библиотеками
target_link_libraries(${PROJECT_NAME} PRIVATE core)


# Установка свойств для Visual Studio
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

