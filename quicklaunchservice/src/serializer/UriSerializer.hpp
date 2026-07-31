#pragma once

#include "shared/serializer/UriSerializer.hpp"

namespace Service::Serializer {
    class UriSerializer : public Shared::Serializer::UriSerializer {

      public:
        static QUrl uriToUrl( const Uri& uri );
    };
} // namespace Service::Serializer