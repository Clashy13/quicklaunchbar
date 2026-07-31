#include "serializer/UriSerializer.hpp"

namespace Service::Serializer {

    QUrl UriSerializer::uriToUrl( const Shared::Models::ExecutionTarget::Uri& uri ) {
        switch ( uri.type ) {
            case Uri::Type::File:
                return QUrl::fromLocalFile( uri.value );
            case Uri::Type::Url:
                return QUrl( uri.value );
            default:
                return QUrl( "" );
        }
    }
} // namespace Service::Serializer