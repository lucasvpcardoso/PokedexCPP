cmake_minimum_required(VERSION 3.16)
project(PokedexQt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt_standard_project_setup()

add_executable(PokedexQt
    main.cpp
    PokedexWindow.h
    PokedexWindow.cpp
    Pokemon.h
    Pokemon.cpp
)

target_link_libraries(PokedexQt Qt6::Widgets)
