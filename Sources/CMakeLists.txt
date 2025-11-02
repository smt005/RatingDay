cmake_minimum_required(VERSION 4.2)

project(RatingDay VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка пути для исполняемых файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../Execute)

# Добавление подпроекта ImGui
add_subdirectory(Engine)

# Источники программы
set(PROGRAM_SOURCES
    Program/Main.cpp
)

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
add_executable(${PROJECT_NAME} ${PROGRAM_SOURCES} ${IMGUI_HEADERS} ${JSONCPP_HEADERS})

# Связывание с библиотеками
target_link_libraries(${PROJECT_NAME} PRIVATE core)


# Установка свойств для Visual Studio
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

