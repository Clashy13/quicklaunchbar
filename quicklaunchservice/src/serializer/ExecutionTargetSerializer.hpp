#pragma once

#include "../models/ExecutionTarget.hpp"
#include "shared/serializer/ExecutionTargetSerializer.hpp"

namespace Service::Serializer {

    class ExecutionTargetSerializer : public Shared::Serializer::ExecutionTargetSerializer {

        using Command = Shared::Models::ExecutionTarget::Command;
        using Type = Shared::Models::ExecutionTarget::Type;

      public:
        static std::optional<Models::ExecutionTarget*> serialized( const QJsonObject& obj );

      private:
        static bool serializeSingleProperties( QList<QUrl>& iconSources,
                                               QList<Command>& commands,
                                               QList<QUrl>& uriList,
                                               const Type type,
                                               const QJsonObject& obj );
    };
} // namespace Service::Serializer