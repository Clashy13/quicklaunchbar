#pragma once

#include "SingleExecutionTarget.hpp"

#include <QUrl>

namespace Editor::Models {

    class OpenUrlExecutionTarget : public SingleExecutionTarget {

        Q_OBJECT

        Q_PROPERTY( QUrl url READ url WRITE setUrl NOTIFY urlChanged );
        Q_PROPERTY( QString iconFilePath READ iconFilePath WRITE setIconFilePath NOTIFY
                        iconFilePathChanged );

      public:
        explicit OpenUrlExecutionTarget( const QUuid& uuid,
                                         const QString& name,
                                         const Type type,
                                         const QUrl& url,
                                         const QString& iconFilePath,
                                         QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, parent ), _url( url ),
              _iconFilePath( iconFilePath ), _savedUrl( url ), _savedIconFilePath( iconFilePath ) {}

        auto url() const {
            return this->_url;
        }

        void setUrl( const QUrl& url );

        auto iconFilePath() const {
            return this->_iconFilePath;
        }

        void setIconFilePath( const QString& iconFilePath );

        bool isEdited() override;

        void saveEdited() override;

      signals:
        void urlChanged();
        void iconFilePathChanged();

      private:
        QUrl _url;
        QString _iconFilePath;
        QUrl _savedUrl;
        QString _savedIconFilePath;
    };
} // namespace Editor::Models