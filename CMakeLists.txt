cmake_minimum_required(VERSION 3.16)

project(quicklaunchbar VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.8.3 REQUIRED COMPONENTS Quick Widgets)

option(QUICKLAUNCHBAR_QT_DEPLOY
    "Deploy Qt libraries and QML runtime"
    ON
)

add_subdirectory(quicklauncheditor)
add_subdirectory(quicklaunchservice)

set(CPACK_GENERATOR "DEB;RPM")

set(CPACK_PACKAGE_NAME "quicklaunchbar")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/quicklaunchbar")
set(CPACK_PACKAGE_SHLIBDEPS OFF)

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Clashy13")

set(CPACK_RPM_PACKAGE_MAINTAINER "Clashy13")
set(CPACK_RPM_PACKAGE_AUTOREQ OFF)
set(CPACK_RPM_PACKAGE_AUTOPROV OFF)

include(CPack)

install(
    FILES
        "${QT6_INSTALL_PREFIX}/plugins/platformthemes/libqgtk3.so"
    DESTINATION
        "${QT6_INSTALL_PLUGINS}/platformthemes"
)
