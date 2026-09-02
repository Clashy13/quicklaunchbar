#pragma once

#include "shared/models/IconSource.hpp"
#include "shared/serializer/IconSourceSerializer.hpp"

#include <QObject>
#include <QUrl>
#include <qobject.h>
#include <qtmetamacros.h>

namespace Editor::Models {

    class DesktopApplication : public QObject {

        Q_OBJECT

        Q_PROPERTY( QString name READ name CONSTANT )
        Q_PROPERTY( QUrl iconUrl READ iconUrl CONSTANT )
        Q_PROPERTY( QString command READ command CONSTANT )

        using IconSource = Shared::Models::ExecutionTarget::IconSource;

      public:
        explicit DesktopApplication( const QString& name,
                                     const IconSource& iconSource,
                                     const QString& command,
                                     QObject* parent = nullptr )
            : QObject( parent ), _name( name ), _iconSource( iconSource ),
              _iconUrl( Shared::Serializer::IconSourceSerializer::iconSourceToUrl( iconSource ) ),
              _command( command ) {}

        auto name() const {
            return this->_name;
        }

        auto iconUrl() const {
            return this->_iconUrl;
        }

        auto iconSource() const {
            return this->_iconSource;
        }

        auto command() const {
            return this->_command;
        }

      private:
        const QString _name;
        const IconSource _iconSource;
        const QUrl _iconUrl;
        const QString _command;
    };
} // namespace Editor::Models