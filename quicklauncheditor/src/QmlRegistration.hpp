#pragma once

#include "manager/ExecutionTargetManager.hpp"
#include "manager/ProfileManager.hpp"
#include "provider/LinuxApplicationProvider.hpp"
#include "qmlelements/ShortcutEditor.hpp"
#include "shared/manager/ThemeManager.hpp"

#include <QQmlEngine>

namespace Editor {

    class QmlRegistration {
      public:
        static void registerTypes() {
            qmlRegisterType<QmlElements::ShortcutEditor>( QmlRegistration::uri,
                                                          QmlRegistration::versionMajor,
                                                          QmlRegistration::versionMinor,
                                                          "ShortcutEditor" );
            qmlRegisterSingletonInstance( QmlRegistration::uri,
                                          QmlRegistration::versionMajor,
                                          QmlRegistration::versionMinor,
                                          "ProfileManager",
                                          Manager::ProfileManager::instance() );
            qmlRegisterSingletonInstance( QmlRegistration::uri,
                                          QmlRegistration::versionMajor,
                                          QmlRegistration::versionMinor,
                                          "ExecutionTargetManager",
                                          Manager::ExecutionTargetManager::instance() );
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
#ifdef Q_OS_LINUX
            qmlRegisterSingletonInstance( QmlRegistration::uri,
                                          QmlRegistration::versionMajor,
                                          QmlRegistration::versionMinor,
                                          "DesktopApplicationProvider",
                                          Provider::LinuxApplicationProvider::instance() );
#elif defined( Q_OS_WIN )
            qWarning().noquote() << "DesktopApplicationProvider for Windows not yet implemented"
#elif defined( Q_OS_MACOS )
            qWarning().noquote() << "DesktopApplicationProvider for macOS not yet implemented"
#endif
        }

      private:
        static constexpr auto uri = "QuickLaunchEditor";
        static const int versionMajor = 1;
        static const int versionMinor = 0;
    };

} // namespace Editor