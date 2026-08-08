#pragma once

#include "../models/Profile.hpp"
#include "shared/serializer/ProfileConfigSerializer.hpp"

namespace Editor::Serializer {

    class ProfileConfigSerializer : public Shared::Serializer::ProfileConfigSerializer {

      public:
        static QList<Models::Profile*> load();

        static void save( const QList<Models::Profile*>& profiles );
    };
} // namespace Editor::Serializer