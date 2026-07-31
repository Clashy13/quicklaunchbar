#pragma once

#include <QString>

namespace Shared::Serializer {

    class ProfileConfigSerializer {

      protected:
        static QString filePath();

        static constexpr auto profilesStr = "profiles";
    };
} // namespace Shared::Serializer