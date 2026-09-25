cmake_minimum_required(VERSION 3.16)

set(CMAKE_AUTORCC ON)

project(quicklaunchservice VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_BINDIR "bin")
set(CMAKE_INSTALL_LIBDIR "lib")

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

install(TARGETS shared
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES packaging/quicklaunchservice.desktop
    DESTINATION /usr/share/applications
)

install(FILES
    packaging/quicklaunchservice.desktop
    DESTINATION /etc/xdg/autostart
)

if(QUICKLAUNCHBAR_QT_DEPLOY)
    qt_generate_deploy_qml_app_script(
        TARGET quicklaunchservice
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )

    install(SCRIPT ${deploy_script})
else()
    install(
        DIRECTORY /opt/qt/lib/
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        FILES_MATCHING
            PATTERN "*.so"
            PATTERN "*.so.*"
    )

    install(
        DIRECTORY /opt/qt/plugins/
        DESTINATION plugins
    )

    install(
        DIRECTORY /opt/qt/qml/
        DESTINATION qml
    )
endif()
