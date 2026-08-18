#pragma once

#include "Command.hpp"
#include "SingleExecutionTarget.hpp"

#include <QUrl>

namespace Editor::Models {

    class ProgramExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( Command* command READ command WRITE setCommand NOTIFY commandChanged );

      public:
        explicit ProgramExecutionTarget( const QUuid& uuid,
                                         const QString& name,
                                         const Type type,
                                         const IconSource& iconSource,
                                         Command* command,
                                         QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, iconSource, parent ), _command( command ) {
            this->_command->setParent( this );
        }

        auto command() const {
            return this->_command;
        }

        void setCommand( Command* command ) {
            this->_command = command;
            emit this->commandChanged();
        }

      signals:
        void commandChanged();

      private:
        Command* _command;
    };
} // namespace Editor::Models