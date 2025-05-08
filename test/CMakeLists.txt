cmake_minimum_required(VERSION 3.10)

project(test VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Подключаем GoogleTest
add_subdirectory(third_party/googletest)

# Указываем пути к заголовочным файлам
include_directories(
    ../include
    ../third_party/json/include  # Путь к nlohmann_json
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME}
    test.cpp
    ../src/delay_settings.cpp
    ../src/tape_sorting_app.cpp
)

# Подключаем библиотеки
target_link_libraries(${PROJECT_NAME} PRIVATE
    gtest_main
)