#pragma once

#include "ExecutionTarget.hpp"
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
              _iconFilePath( iconFilePath ), _savedCommand( command ),
              _savedIconFilePath( iconFilePath ) {}

        auto command() const {
            return this->_command;
        }

        void setCommand( const QString& command );

        auto iconFilePath() const {
            return this->_iconFilePath;
        }

        void setIconFilePath( const QString& iconFilePath );

        bool isEdited() override;

        void saveEdited() override;

      signals:
        void commandChanged();
        void iconFilePathChanged();

      private:
        QString _command;
        QString _iconFilePath;
        QString _savedCommand;
        QString _savedIconFilePath;
    };
} // namespace Editor::Models