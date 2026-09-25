cmake_minimum_required(VERSION 3.5)

project(quicklauncheditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_BINDIR "bin")
set(CMAKE_INSTALL_LIBDIR "lib")

find_package(Qt6 6.8.3 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup()

if(NOT TARGET shared)
    add_subdirectory(../shared shared_build)
endif()
add_subdirectory(src)

qt_add_executable(quicklauncheditor
    main.cpp
    main.qrc
    qml/qml.qrc
    resources/resources.qrc
    ${SOURCES}
)

target_link_libraries(quicklauncheditor PRIVATE Qt6::Quick Qt6::Widgets shared QHotkey::QHotkey)

include(GNUInstallDirs)
install(TARGETS quicklauncheditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(TARGETS shared
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES packaging/quicklauncheditor.desktop
    DESTINATION /usr/share/applications
)

install(FILES resources/icons/256x256/quicklauncheditor.png
    DESTINATION /usr/share/icons/hicolor/256x256/apps
)
install(FILES resources/icons/128x128/quicklauncheditor.png
    DESTINATION /usr/share/icons/hicolor/128x128/apps
)
install(FILES resources/icons/64x64/quicklauncheditor.png
    DESTINATION /usr/share/icons/hicolor/64x64/apps
)
install(FILES resources/icons/48x48/quicklauncheditor.png
    DESTINATION /usr/share/icons/hicolor/48x48/apps
)
install(FILES resources/icons/32x32/quicklauncheditor.png
    DESTINATION /usr/share/icons/hicolor/32x32/apps
)
install(FILES resources/icons/16x16/quicklauncheditor.png
    DESTINATION /usr/share/icons/hicolor/16x16/apps
)

if(QUICKLAUNCHBAR_QT_DEPLOY)
    qt_generate_deploy_qml_app_script(
        TARGET quicklauncheditor
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
