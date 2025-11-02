# ImGui подпроект
project(imgui)

# Источники ImGui
set(IMGUI_SOURCES
    ImGui/imgui.cpp
    ImGui/imgui_draw.cpp
    ImGui/imgui_tables.cpp
    ImGui/imgui_widgets.cpp
    ImGui/backends/imgui_impl_win32.cpp
    ImGui/backends/imgui_impl_opengl3.cpp
)

# Создание библиотеки ImGui
add_library(imgui STATIC ${IMGUI_SOURCES})

# Установка стандарта C++
target_compile_features(imgui PUBLIC cxx_std_17)

# Установка директории для заголовочных файлов
target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/backends
)

# JsonCpp подпроект
set(JSONCPP_SOURCES
    jsoncpp/src/lib_json/json_reader.cpp
    jsoncpp/src/lib_json/json_value.cpp
    jsoncpp/src/lib_json/json_writer.cpp
    jsoncpp/src/lib_json/json_tool.h
    jsoncpp/src/lib_json/json_valueiterator.inl
)

# Создание библиотеки JsonCpp
add_library(jsoncpp STATIC ${JSONCPP_SOURCES})

# Установка стандарта C++
target_compile_features(jsoncpp PUBLIC cxx_std_11)

# Установка директории для заголовочных файлов
target_include_directories(jsoncpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/include
)

# Core подпроект
add_subdirectory(Core)
