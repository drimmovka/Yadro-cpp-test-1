cmake_minimum_required(VERSION 3.10)

project(tape-sorting-app VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_subdirectory(third_party/json)

add_executable(${PROJECT_NAME} 
    ./src/delay_settings.cpp
    ./src/main.cpp
    ./src/tape_sorting_app.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)