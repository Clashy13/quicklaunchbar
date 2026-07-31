#include "ExecutionTargetSerializer.hpp"

#include "serializer/IconSourceSerializer.hpp"
#include "serializer/UriSerializer.hpp"
#include "shared/serializer/ExecutionTargetSerializer.hpp"

namespace Service::Serializer {

    std::optional<Models::ExecutionTarget*>
    ExecutionTargetSerializer::serialized( const QJsonObject& obj ) {
        if ( const auto executionTarget =
                 Shared::Serializer::ExecutionTargetSerializer::serialized( obj ) ) {
            return new Models::ExecutionTarget(
                executionTarget->uuid,
                executionTarget->name,
                executionTarget->type,
                ExecutionTargetSerializer::iconSourcesToIconUrls( executionTarget->iconSources ),
                executionTarget->commands,
                ExecutionTargetSerializer::uriListToUrlList( executionTarget->uriList ) );
        } else {
            return std::nullopt;
        }
    }

    QList<QUrl> ExecutionTargetSerializer::iconSourcesToIconUrls(
        const QList<Shared::Models::ExecutionTarget::IconSource>& iconSources ) {
        QList<QUrl> urls;
        for ( const auto& iconSource : iconSources ) {
            urls.push_back( IconSourceSerializer::iconSourceToUrl( iconSource ) );
        }
        return urls;
    }

    QList<QUrl> ExecutionTargetSerializer::uriListToUrlList(
        const QList<Shared::Models::ExecutionTarget::Uri>& uriList ) {
        QList<QUrl> urls;
        for ( const auto& uri : uriList ) {
            urls.push_back( UriSerializer::uriToUrl( uri ) );
        }
        return urls;
    }

} // namespace Service::Serializer