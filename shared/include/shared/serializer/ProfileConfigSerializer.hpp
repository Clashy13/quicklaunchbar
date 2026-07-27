#pragma once

#include "../models/Profile.hpp"

#include <QString>

namespace Serializer {

    using Profile = Models::Profile::Profile;

    class ProfileConfigSerializer {
      public:
        static std::vector<Profile> load();

        static void save( const std::vector<Profile>& profiles );

      private:
        static QString filePath();

        static constexpr auto profilesStr = "profiles";
    };
} // namespace Serializer