#pragma once

#include "SingleExecutionTarget.hpp"

#include <QUrl>

namespace Editor::Models {

    class OpenUrlExecutionTarget : public SingleExecutionTarget {

        Q_PROPERTY( QUrl url READ url WRITE setUrl NOTIFY urlChanged );

      public:
        explicit OpenUrlExecutionTarget( const QUuid& uuid,
                                         const QString& name,
                                         const Type type,
                                         const IconSource& iconSource,
                                         const QUrl& url,
                                         QObject* parent = nullptr )
            : SingleExecutionTarget( uuid, name, type, iconSource, parent ), _url( url ) {}

        auto url() const {
            return this->_url;
        }

        void setUrl( const QUrl& url ) {
            this->_url = url;
            emit this->urlChanged();
        }

      signals:
        void urlChanged();

      private:
        QUrl _url;
    };
} // namespace Editor::Models