cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTORCC ON)

add_subdirectory(include/shared/external/QHotkey-1.5.0)
add_subdirectory(include/shared/models)
add_subdirectory(include/shared/serializer)

add_library(shared 
    include/shared/ProfileConfigNames.hpp
    include/shared/ProfileConfigPath.hpp
    ${SOURCES}
)

target_include_directories(shared
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Qt6 REQUIRED COMPONENTS Core)

target_link_libraries(shared PRIVATE Qt6::Core)
