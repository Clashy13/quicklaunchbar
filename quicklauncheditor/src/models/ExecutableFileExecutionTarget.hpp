#pragma once

#include "SingleExecutionTarget.hpp"

#include <QUrl>

namespace Editor::Models {

    class ExecutableFileExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged );
        Q_PROPERTY( QString arguments READ arguments WRITE setArguments NOTIFY argumentsChanged );

      public:
        explicit ExecutableFileExecutionTarget( const QUuid& uuid,
                                                const QString& name,
                                                const Type type,
                                                const IconSource& iconSource,
                                                const QString& filePath,
                                                const QString& arguments,
                                                QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, iconSource, parent ), _filePath( filePath ),
              _arguments( arguments ) {}

        auto filePath() {
            return this->_filePath;
        }

        void setFilePath( const QString& filePath ) {
            this->_filePath = filePath;
            emit this->filePathChanged();
        }

        auto arguments() const {
            return this->_arguments;
        }

        void setArguments( const QString& arguments ) {
            this->_arguments = arguments;
            emit this->argumentsChanged();
        }

      signals:
        void filePathChanged();
        void argumentsChanged();

      private:
        QString _filePath;
        QString _arguments;
    };
} // namespace Editor::Models