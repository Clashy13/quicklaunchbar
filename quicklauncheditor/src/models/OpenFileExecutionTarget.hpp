#pragma once

#include "SingleExecutionTarget.hpp"

namespace Editor::Models {

    class OpenFileExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged );

      public:
        explicit OpenFileExecutionTarget( const QUuid& uuid,
                                          const QString& name,
                                          const Type type,
                                          const IconSource& iconSource,
                                          const QString& filePath,
                                          QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, iconSource, parent ), _filePath( filePath ) {
        }

        auto filePath() const {
            return this->_filePath;
        }

        void setFilePath( const QString& filePath ) {
            this->_filePath = filePath;
            emit this->filePathChanged();
        }

      signals:
        void filePathChanged();

      private:
        QString _filePath;
    };
} // namespace Editor::Models