#pragma once

#include "SingleExecutionTarget.hpp"
#include "shared/serializer/IconSourceSerializer.hpp"

#include <QUrl>

namespace Editor::Models {

    class DesktopApplicationExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( QString command READ command WRITE setCommand NOTIFY commandChanged );
        Q_PROPERTY( QUrl iconUrl READ iconUrl NOTIFY iconUrlChanged );

        using IconSource = Shared::Models::ExecutionTarget::IconSource;

      public:
        explicit DesktopApplicationExecutionTarget( const QUuid& uuid,
                                                    const QString& name,
                                                    const Type type,
                                                    const IconSource& iconSource,
                                                    const QString& command,
                                                    QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, parent ), _command( command ),
              _iconSource( iconSource ),
              _iconUrl( Shared::Serializer::IconSourceSerializer::iconSourceToUrl( iconSource ) ) {}

        auto command() const {
            return this->_command;
        }

        void setCommand( const QString& command ) {
            if ( this->_command != command ) {
                this->_command = command;
                emit this->commandChanged();
            }
        }

        auto iconUrl() const {
            return this->_iconUrl;
        }

        auto iconSource() const {
            return this->_iconSource;
        }

        void setIconSource( const IconSource& iconSource ) {
            if ( this->_iconSource != iconSource ) {
                this->_iconSource = iconSource;
                this->_iconUrl =
                    Shared::Serializer::IconSourceSerializer::iconSourceToUrl( iconSource );
                emit this->iconUrlChanged();
            }
        }

      signals:
        void commandChanged();
        void iconUrlChanged();

      private:
        QString _command;
        IconSource _iconSource;
        QUrl _iconUrl;
    };
} // namespace Editor::Models