cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTORCC ON)

add_subdirectory(include/shared/external/QHotkey-1.5.0)
add_subdirectory(include/shared/models)
add_subdirectory(include/shared/serializer)
add_subdirectory(include/shared/iconprovider)
add_subdirectory(include/shared/manager)

qt_add_library(shared
    include/shared/resources/resources.qrc
    ${SOURCES}
)

target_include_directories(shared
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

target_link_libraries(shared PRIVATE Qt6::Core Qt6::Quick)
