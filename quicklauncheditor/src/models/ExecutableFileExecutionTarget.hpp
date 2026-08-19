#pragma once

#include "SingleExecutionTarget.hpp"

#include <QUrl>

namespace Editor::Models {

    class ExecutableFileExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged );
        Q_PROPERTY( QString arguments READ arguments WRITE setArguments NOTIFY argumentsChanged );
        Q_PROPERTY( QString iconFilePath READ iconFilePath WRITE setIconFilePath NOTIFY
                        iconFilePathChanged );

      public:
        explicit ExecutableFileExecutionTarget( const QUuid& uuid,
                                                const QString& name,
                                                const Type type,
                                                const QString& filePath,
                                                const QString& arguments,
                                                const QString& iconFilePath,
                                                QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, parent ), _filePath( filePath ),
              _arguments( arguments ), _iconFilePath( iconFilePath ) {}

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

        auto iconFilePath() const {
            return this->_iconFilePath;
        }

        void setIconFilePath( const QString& iconFilePath ) {
            this->_iconFilePath = iconFilePath;
            emit this->iconFilePathChanged();
        }

      signals:
        void filePathChanged();
        void argumentsChanged();
        void iconFilePathChanged();

      private:
        QString _filePath;
        QString _arguments;
        QString _iconFilePath;
    };
} // namespace Editor::Models