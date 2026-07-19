#pragma once

#include "Backend.hpp"
#include "ExecutionTarget.hpp"
#include "ThemeManager.hpp"

class QmlRegistration {
  public:
    static void registerTypes() {
        qmlRegisterType<Backend>( QmlRegistration::uri,
                                  QmlRegistration::versionMajor,
                                  QmlRegistration::versionMinor,
                                  "Backend" );
        qmlRegisterUncreatableType<ExecutionTarget>( QmlRegistration::uri,
                                                     QmlRegistration::versionMajor,
                                                     QmlRegistration::versionMinor,
                                                     "ExecutionTarget",
                                                     "Enums only" );
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
