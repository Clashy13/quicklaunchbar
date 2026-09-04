cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTORCC ON)

project(quicklaunchservice VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8.3 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

if(NOT TARGET shared)
    add_subdirectory(../shared shared_build)
endif()
add_subdirectory(src)

qt_add_executable(quicklaunchservice
    main.cpp
    main.qrc
    qml/qml.qrc
    ${SOURCES}
)

set_target_properties(quicklaunchservice PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(quicklaunchservice PUBLIC src)

target_link_libraries(quicklaunchservice
    PRIVATE Qt6::Quick Qt6::Widgets QHotkey::QHotkey shared
)

include(GNUInstallDirs)
install(TARGETS quicklaunchservice
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
