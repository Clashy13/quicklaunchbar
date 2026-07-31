#pragma once

#include "shared/models/IconSource.hpp"
#include "shared/serializer/IconSourceSerializer.hpp"

#include <QUrl>

namespace Service::Serializer {

    using IconSource = Shared::Models::ExecutionTarget::IconSource;

    class IconSourceSerializer : public Shared::Serializer::IconSourceSerializer {
      public:
        static QUrl iconSourceToUrl( const IconSource& iconSource );
    };

} // namespace Service::Serializer