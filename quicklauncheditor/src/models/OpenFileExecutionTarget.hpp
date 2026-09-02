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
              _iconFilePath( iconFilePath ), _savedFilePath( filePath ),
              _savedIconFilePath( iconFilePath ) {}

        auto filePath() const {
            return this->_filePath;
        }

        void setFilePath( const QString& filePath );

        auto iconFilePath() const {
            return this->_iconFilePath;
        }

        void setIconFilePath( const QString& iconFilePath );

        bool isEdited() override;

        void saveEdited() override;

      signals:
        void filePathChanged();
        void iconFilePathChanged();

      private:
        QString _filePath;
        QString _iconFilePath;
        QString _savedFilePath;
        QString _savedIconFilePath;
    };
} // namespace Editor::Models