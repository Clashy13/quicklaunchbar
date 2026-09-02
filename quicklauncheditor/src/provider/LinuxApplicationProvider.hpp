#pragma once

#include "DesktopApplicationProvider.hpp"

#include <QSettings>
#include <QStringList>
#include <optional>
#include <qobject.h>
#include <qtmetamacros.h>

namespace Editor::Provider {

    class LinuxApplicationProvider : public DesktopApplicationProvider {

        Q_OBJECT

        using IconSource = Shared::Models::ExecutionTarget::IconSource;

      public:
        static LinuxApplicationProvider* instance() {
            static LinuxApplicationProvider provider;
            return &provider;
        }

      private:
        explicit LinuxApplicationProvider( QObject* parent = nullptr )
            : DesktopApplicationProvider( this->applications(),
                                          this->defaultBrowserIconSource(),
                                          parent ) {}

        QList<Models::DesktopApplication*> applications() const;

        IconSource defaultBrowserIconSource() const;

        std::optional<QString> defaultBrowserDesktopFilePath() const;

        std::optional<QString> defaultBrowserDesktopFileName() const;

        QStringList desktopFilePaths( const QStringList& directories ) const;

        QString localizedDesktopEntryValue( QSettings* settings,
                                            const QString& group,
                                            const QString& key ) const;
    };
} // namespace Editor::Provider