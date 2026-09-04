cmake_minimum_required(VERSION 3.16)

project(quicklaunchbar VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.8.3 REQUIRED COMPONENTS Quick Widgets)

add_subdirectory(quicklauncheditor)
add_subdirectory(quicklaunchservice)
