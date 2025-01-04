cmake_minimum_required(VERSION 3.30)
project(ProceduralAnimation)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(ProceduralAnimation main.cpp Chain.cpp Chain.h Legs.h Legs.cpp)

target_link_libraries(ProceduralAnimation PRIVATE SFML::Graphics)
