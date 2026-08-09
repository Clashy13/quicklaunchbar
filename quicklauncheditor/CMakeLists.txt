cmake_minimum_required(VERSION 3.5)

project(quicklauncheditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8.3 REQUIRED COMPONENTS Quick Widgets)
find_package(Boost 1.83.0 REQUIRED)

qt_standard_project_setup()

add_subdirectory(../shared shared_build)
add_subdirectory(src)

qt_add_executable(quicklauncheditor
    main.cpp
    main.qrc
    qml/qml.qrc
    resources/resources.qrc
    ${SOURCES}
)

target_link_libraries(quicklauncheditor PRIVATE Qt6::Quick Qt6::Widgets Boost::boost shared QHotkey::QHotkey)

set_target_properties(quicklauncheditor PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS quicklauncheditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
