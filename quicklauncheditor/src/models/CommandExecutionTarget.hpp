#pragma once

#include "SingleExecutionTarget.hpp"

#include <QUrl>

namespace Editor::Models {

    class CommandExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( QString command READ command WRITE setCommand NOTIFY commandChanged );
        Q_PROPERTY( QString iconFilePath READ iconFilePath WRITE setIconFilePath NOTIFY
                        iconFilePathChanged );

      public:
        explicit CommandExecutionTarget( const QUuid& uuid,
                                         const QString& name,
                                         const Type type,
                                         const QString& command,
                                         const QString& iconFilePath,
                                         QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, parent ), _command( command ),
              _iconFilePath( iconFilePath ) {}

        auto command() const {
            return this->_command;
        }

        void setCommand( const QString& command ) {
            if ( this->_command != command ) {
                this->_command = command;
                emit this->commandChanged();
            }
        }

        auto iconFilePath() const {
            return this->_iconFilePath;
        }

        void setIconFilePath( const QString& iconFilePath ) {
            if ( this->_iconFilePath != iconFilePath ) {
                this->_iconFilePath = iconFilePath;
                emit this->iconFilePathChanged();
            }
        }

      signals:
        void commandChanged();
        void iconFilePathChanged();

      private:
        QString _command;
        QString _iconFilePath;
    };
} // namespace Editor::Models