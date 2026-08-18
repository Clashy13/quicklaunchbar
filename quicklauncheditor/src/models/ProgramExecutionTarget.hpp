#pragma once

#include "SingleExecutionTarget.hpp"

#include <QUrl>

namespace Editor::Models {

    class ProgramExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( QString command READ command WRITE setCommand NOTIFY commandChanged );

      public:
        explicit ProgramExecutionTarget( const QUuid& uuid,
                                         const QString& name,
                                         const Type type,
                                         const IconSource& iconSource,
                                         const QString& command,
                                         QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, iconSource, parent ), _command( command ) {}

        auto command() const {
            return this->_command;
        }

        void setCommand( const QString& command ) {
            this->_command = command;
            emit this->commandChanged();
        }

      signals:
        void commandChanged();

      private:
        QString _command;
    };
} // namespace Editor::Models