#pragma once

#include "SingleExecutionTarget.hpp"

namespace Editor::Models {

    class OpenFileExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged );
        Q_PROPERTY( QString iconFilePath READ iconFilePath WRITE setIconFilePath NOTIFY
                        iconFilePathChanged );

      public:
        explicit OpenFileExecutionTarget( const QUuid& uuid,
                                          const QString& name,
                                          const Type type,
                                          const QString& filePath,
                                          const QString& iconFilePath,
                                          QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, parent ), _filePath( filePath ),
              _iconFilePath( iconFilePath ) {}

        auto filePath() const {
            return this->_filePath;
        }

        void setFilePath( const QString& filePath ) {
            this->_filePath = filePath;
            emit this->filePathChanged();
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
        void iconFilePathChanged();

      private:
        QString _filePath;
        QString _iconFilePath;
    };
} // namespace Editor::Models