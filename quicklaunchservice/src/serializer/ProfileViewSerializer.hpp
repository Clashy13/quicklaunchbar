#pragma once

#include "shared/models/ProfileView.hpp"
#include "shared/serializer/ProfileViewSerializer.hpp"

namespace Service::Serializer {

    class ProfileViewSerializer : public Shared::Serializer::ProfileViewSerializer {

        using ProfileView = Shared::Models::Profile::ProfileView;

      public:
        static QString viewToSource( const ProfileView& view );
    };
} // namespace Service::Serializer