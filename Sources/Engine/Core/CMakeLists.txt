# Core подпроект
project(core)

# Источники Core
set(CORE_SOURCES
    MainWindow.cpp
    MainWindow.h
	Log.h
	LogSpecification.h
	Help.h
	Help.cpp
	FileManager.h
	FileManager.cpp
)

# Создание библиотеки Core
add_library(core STATIC ${CORE_SOURCES})

# Установка стандарта C++
target_compile_features(core PUBLIC cxx_std_17)

# Установка директории для заголовочных файлов
target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Связывание с библиотеками
target_link_libraries(core PUBLIC imgui jsoncpp)

# Линковка с Windows библиотеками
if(WIN32)
    target_link_libraries(core PRIVATE user32 gdi32 opengl32)
endif()

