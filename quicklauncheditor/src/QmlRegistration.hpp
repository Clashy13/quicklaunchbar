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
        }

      private:
        static constexpr auto uri = "QuickLaunchEditor";
        static const int versionMajor = 1;
        static const int versionMinor = 0;
    };

} // namespace Editor