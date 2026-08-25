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
              _iconFilePath( iconFilePath ) {}

        auto url() const {
            return this->_url;
        }

        void setUrl( const QUrl& url ) {
            if ( this->_url != url ) {
                this->_url = url;
                emit this->urlChanged();
            }
        }

        auto iconFilePath() const {
            return this->_iconFilePath;
        }

        void setIconFilePath( const QString& iconFilePath ) {
            if ( this->_iconFilePath != iconFilePath ) {
                this->_iconFilePath = iconFilePath;
                emit this->iconFilePathChanged();
            }
        }

      signals:
        void urlChanged();
        void iconFilePathChanged();

      private:
        QUrl _url;
        QString _iconFilePath;
    };
} // namespace Editor::Models