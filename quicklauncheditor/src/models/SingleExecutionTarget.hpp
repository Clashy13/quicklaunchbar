#pragma once

#include "ExecutionTarget.hpp"
#include "shared/models/IconSource.hpp"
#include "shared/serializer/IconSourceSerializer.hpp"

#include <QUrl>

namespace Editor::Models {

    class SingleExecutionTarget : public ExecutionTarget {

        Q_OBJECT

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

        IconSource _iconSource;
        QUrl _iconUrl;
    };

    inline SingleExecutionTarget::~SingleExecutionTarget() = default;

} // namespace Editor::Models