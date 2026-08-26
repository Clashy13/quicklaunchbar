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
              _arguments( arguments ), _iconFilePath( iconFilePath ), _savedFilePath( filePath ),
              _savedArguments( arguments ), _savedIconFilePath( iconFilePath ) {}

        auto filePath() {
            return this->_filePath;
        }

        void setFilePath( const QString& filePath );

        auto arguments() const {
            return this->_arguments;
        }

        void setArguments( const QString& arguments );

        auto iconFilePath() const {
            return this->_iconFilePath;
        }

        void setIconFilePath( const QString& iconFilePath );

        bool isEdited() override;

        void saveEdited() override;

      signals:
        void filePathChanged();
        void argumentsChanged();
        void iconFilePathChanged();

      private:
        QString _filePath;
        QString _arguments;
        QString _iconFilePath;

        QString _savedFilePath;
        QString _savedArguments;
        QString _savedIconFilePath;
    };
} // namespace Editor::Models