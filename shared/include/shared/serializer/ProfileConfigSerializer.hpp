#pragma once

#include <QString>

namespace Shared::Serializer {

    class ProfileConfigSerializer {

      public:
        static QString filePath();

      protected:
        static constexpr auto profilesStr = "profiles";
    };
} // namespace Shared::Serializer