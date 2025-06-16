cmake_minimum_required(VERSION 3.16)
project(BootChecker LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(BootChecker main.cpp)
target_link_libraries(BootChecker PRIVATE Qt6::Widgets)
set_target_properties(BootChecker PROPERTIES CXX_STANDARD 17)
