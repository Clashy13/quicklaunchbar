#pragma once

#include "shared/manager/ThemeManager.hpp"

#include <QQmlEngine>

namespace Editor {

    class QmlRegistration {
      public:
        static void registerTypes() {
            qmlRegisterSingletonInstance( QmlRegistration::uri,
                                          QmlRegistration::versionMajor,
                                          QmlRegistration::versionMinor,
                                          "Theme",
                                          ThemeManager::instance() );
            qmlRegisterSingletonType( QUrl( "qrc:/utils/Colors.qml" ),
                                      QmlRegistration::uri,
                                      QmlRegistration::versionMajor,
                                      QmlRegistration::versionMinor,
                                      "Colors" );
            qmlRegisterSingletonType( QUrl( "qrc:/utils/Icons.qml" ),
                                      QmlRegistration::uri,
                                      QmlRegistration::versionMajor,
                                      QmlRegistration::versionMinor,
                                      "Icons" );
        }

      private:
        static constexpr auto uri = "QuickLaunchEditor";
        static const int versionMajor = 1;
        static const int versionMinor = 0;
    };

} // namespace Editor