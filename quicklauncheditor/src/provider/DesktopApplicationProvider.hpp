#pragma once

#include "../models/DesktopApplication.hpp"

#include <QQmlListProperty>
#include <QStandardPaths>
#include <QString>

namespace Editor::Provider {

    class DesktopApplicationProvider : public QObject {

        Q_OBJECT

        Q_PROPERTY( QQmlListProperty<Models::DesktopApplication> applications READ applications
                        NOTIFY applicationsChanged )

        using IconSource = Shared::Models::ExecutionTarget::IconSource;

      public:
        explicit DesktopApplicationProvider( const QList<Models::DesktopApplication*>& applications,
                                             const IconSource& defaultBrowserIconSource,
                                             QObject* parent = nullptr )
            : QObject( parent ), _applications( applications ),
              _defaultBrowserIconSource( defaultBrowserIconSource ) {}

        QQmlListProperty<Models::DesktopApplication> applications() {
            return QQmlListProperty<Models::DesktopApplication>( this, &this->_applications );
        }

        auto defaultBrowserIconSource() const {
            return this->_defaultBrowserIconSource;
        }

      signals:
        void applicationsChanged();

      protected:
        QStringList locations() const {
            return QStandardPaths::standardLocations( QStandardPaths::ApplicationsLocation );
        }

      private:
        QList<Models::DesktopApplication*> _applications;
        const IconSource _defaultBrowserIconSource;
    };
} // namespace Editor::Provider
