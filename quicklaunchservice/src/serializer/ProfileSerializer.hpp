#pragma once

#include "../models/Profile.hpp"
#include "models/ExecutionTarget.hpp"
#include "shared/serializer/ProfileSerializer.hpp"

namespace Service::Serializer {
    class ProfileSerializer : Shared::Serializer::ProfileSerializer {

      public:
        static std::optional<Models::Profile*> serialized( const QJsonObject& obj );

      private:
        static std::optional<QList<Models::ExecutionTarget*>>
        serializedExecutionTargets( const QJsonObject& obj );
    };
} // namespace Service::Serializer