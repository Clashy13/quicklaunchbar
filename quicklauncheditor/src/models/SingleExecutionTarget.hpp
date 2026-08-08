#pragma once

#include "ExecutionTarget.hpp"
#include "shared/models/IconSource.hpp"
#include "shared/serializer/IconSourceSerializer.hpp"

#include <QUrl>

namespace Editor::Models {

    class SingleExecutionTarget : public ExecutionTarget {

        Q_PROPERTY( QUrl iconUrl READ iconUrl NOTIFY iconUrlChanged );

      public:
        using IconSource = Shared::Models::ExecutionTarget::IconSource;

        explicit SingleExecutionTarget( const QUuid& uuid,
                                        const QString& name,
                                        const Type type,
                                        const IconSource& iconSource,
                                        QObject* parent = nullptr )
            : ExecutionTarget( uuid, name, type, parent ), _iconSource( iconSource ),
              _iconUrl( Shared::Serializer::IconSourceSerializer::iconSourceToUrl( iconSource ) ) {}

        virtual ~SingleExecutionTarget() = 0;

        auto iconUrl() const {
            return this->_iconUrl;
        }

        auto iconSource() const {
            return this->_iconSource;
        }

        void setIconSource( const IconSource& iconSource ) {
            this->_iconSource = iconSource;
            this->_iconUrl =
                Shared::Serializer::IconSourceSerializer::iconSourceToUrl( iconSource );
            emit this->iconUrlChanged();
        }

      signals:
        void iconUrlChanged();

      private:
        // static QUrl iconSourceToUrl( const IconSource& iconSource ) {
        //     switch ( iconSource.type ) {
        //         case IconSource::Type::Theme:
        //             return QUrl( "image://themeicons/" + iconSource.value );
        //         case IconSource::Type::FromFile:
        //             return QUrl( "image://fileicons" + iconSource.value );
        //         case IconSource::Type::Image:
        //             return QUrl( "image:/" + iconSource.value );
        //         case IconSource::Type::Resource:
        //             return QUrl( "qrc:/icons/" + iconSource.value + ".svg" );
        //     }
        // }

        IconSource _iconSource;
        QUrl _iconUrl;
    };

    inline SingleExecutionTarget::~SingleExecutionTarget() = default;

} // namespace Editor::Models