#pragma once

#include <QDir>
#include <QStandardPaths>

namespace ProfileConfig
{
    inline QString filePath()
    {
        return QDir( QStandardPaths::writableLocation( QStandardPaths::GenericConfigLocation ) )
            .filePath( "quicklaunchbar/profiles.json" );
    }
} // namespace ProfileConfig