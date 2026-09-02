#pragma once

#include "Backend.hpp"
#include "shared/manager/ThemeManager.hpp"

class QmlRegistration {
  public:
    static void registerTypes() {
        qmlRegisterType<Service::Backend>( QmlRegistration::uri,
                                           QmlRegistration::versionMajor,
                                           QmlRegistration::versionMinor,
                                           "Backend" );
        qmlRegisterSingletonType( QUrl( "qrc:/qml/Colors.qml" ),
                                  QmlRegistration::uri,
                                  QmlRegistration::versionMajor,
                                  QmlRegistration::versionMinor,
                                  "Colors" );
        qmlRegisterSingletonType( QUrl( "qrc:/qml/ExecutionTarget/Constants.qml" ),
                                  QmlRegistration::uri,
                                  QmlRegistration::versionMajor,
                                  QmlRegistration::versionMinor,
                                  "Constants" );
        qmlRegisterSingletonInstance( QmlRegistration::uri,
                                      QmlRegistration::versionMajor,
                                      QmlRegistration::versionMinor,
                                      "Theme",
                                      ThemeManager::instance() );
    }

    static void registerThemeManager( ThemeManager* themeManager ) {
        qmlRegisterSingletonInstance( QmlRegistration::uri,
                                      QmlRegistration::versionMajor,
                                      QmlRegistration::versionMinor,
                                      "Theme",
                                      themeManager );
    }

  private:
    static constexpr auto uri = "QuickLaunchService";
    static const int versionMajor = 1;
    static const int versionMinor = 0;
};
