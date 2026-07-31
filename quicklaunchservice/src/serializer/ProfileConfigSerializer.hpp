#pragma once

#include "../models/Profile.hpp"
#include "shared/serializer/ProfileConfigSerializer.hpp"

namespace Service::Serializer {

    class ProfileConfigSerializer : public Shared::Serializer::ProfileConfigSerializer {

      public:
        static QList<Models::Profile*> load();
    };
} // namespace Service::Serializer