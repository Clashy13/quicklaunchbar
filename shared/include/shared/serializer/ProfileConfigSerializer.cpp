#include "ProfileConfigSerializer.hpp"

#include <QDir>
#include <QJsonArray>
#include <QStandardPaths>

namespace Shared::Serializer {

    QString ProfileConfigSerializer::filePath() {
        return QDir( QStandardPaths::writableLocation( QStandardPaths::GenericConfigLocation ) )
            .filePath( "quicklaunchbar/profiles.json" );
    }

} // namespace Shared::Serializer