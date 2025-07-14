cmake_minimum_required(VERSION 3.10)
project(TaskEngine)

set(CMAKE_CXX_STANDARD 17)

# Явно перечисляем все файлы
add_executable(TaskEngine
    main.cpp
    Engine.cpp
    Test.cpp
)