#pragma once

#include "../models/ExecutionTarget.hpp"
#include "shared/models/IconSource.hpp"
#include "shared/serializer/ExecutionTargetSerializer.hpp"

namespace Service::Serializer {

    class ExecutionTargetSerializer : public Shared::Serializer::ExecutionTargetSerializer {

      public:
        static std::optional<Models::ExecutionTarget*> serialized( const QJsonObject& obj );

      private:
        static QList<QUrl> iconSourcesToIconUrls(
            const QList<Shared::Models::ExecutionTarget::IconSource>& iconSources );

        static QList<QUrl>
        uriListToUrlList( const QList<Shared::Models::ExecutionTarget::Uri>& uriList );
    };
} // namespace Service::Serializer