#include "LinuxApplicationProvider.hpp"

#include <QDir>
#include <QDirIterator>
#include <QProcess>
#include <algorithm>

namespace Editor::Provider {

    QList<Models::DesktopApplication*> LinuxApplicationProvider::applications() const {
        const auto directories = this->locations();
        const auto desktopFilePaths = this->desktopFilePaths( directories );

        QList<Models::DesktopApplication*> desktopApplications{};
        for ( const auto filePath : desktopFilePaths ) {
            QSettings settings( filePath, QSettings::IniFormat );

            if ( !settings.childGroups().contains( "Desktop Entry" ) ) {
                continue;
            }

            const auto name =
                this->localizedDesktopEntryValue( &settings, "Desktop Entry", "Name" );

            if ( name.isEmpty() ) {
                continue;
            }

            const auto exec = settings.value( "Desktop Entry/Exec" ).toString();

            if ( exec.isEmpty() ) {
                continue;
            }

            QStringList arguments = QProcess::splitCommand( exec );

            for ( QString& arg : arguments ) {
                if ( arg == "%f" || arg == "%F" || arg == "%u" || arg == "%U" ) {
                    arg.clear();
                }
            }
            arguments.removeAll( "" );

            const auto command = arguments.join( " " );

            IconSource iconSource( IconSource::Type::Theme,
                                   settings.value( "Desktop Entry/Icon" ).toString() );

            if ( iconSource.value.isEmpty() ) {
                continue;
            }

            auto it = std::find_if( desktopApplications.begin(),
                                    desktopApplications.end(),
                                    [ &command ]( Models::DesktopApplication* application ) {
                                        return application->command() == command;
                                    } );

            if ( it == desktopApplications.end() ) {
                desktopApplications.push_back(
                    new Models::DesktopApplication( name, iconSource, command ) );
            }
        }
        return desktopApplications;
    }

    LinuxApplicationProvider::IconSource
    LinuxApplicationProvider::defaultBrowserIconSource() const {
        const auto desktopFilePath = this->defaultBrowserDesktopFilePath();
        if ( const auto desktopFilePath = this->defaultBrowserDesktopFilePath() ) {
            QSettings settings( *desktopFilePath, QSettings::IniFormat );
            IconSource iconSource( IconSource::Type::Theme,
                                   settings.value( "Desktop Entry/Icon" ).toString() );
            return iconSource;
        } else {
            IconSource iconSource( IconSource::Type::Image, "" );
            return iconSource;
        }
    }

    std::optional<QString> LinuxApplicationProvider::defaultBrowserDesktopFilePath() const {
        if ( const auto desktopFile = this->defaultBrowserDesktopFileName() ) {
            const auto directories = this->locations();
            for ( const QString& dir : directories ) {
                QString totalPath = dir + "/" + *desktopFile;
                if ( QFileInfo::exists( totalPath ) ) {
                    return totalPath;
                }
            }
            qWarning().noquote() << "Could not find directory for desktop file:" << *desktopFile;
            return std::nullopt;
        } else {
            return std::nullopt;
        }
    }

    std::optional<QString> LinuxApplicationProvider::defaultBrowserDesktopFileName() const {
        QProcess process;
        process.start( "xdg-mime", { "query", "default", "x-scheme-handler/http" } );
        process.waitForFinished();
        const auto fileName = QString::fromUtf8( process.readAllStandardOutput() ).trimmed();
        if ( fileName.isEmpty() ) {
            qWarning().noquote() << "Could not find default browser";
            return std::nullopt;
        }
        return fileName;
    }

    QStringList LinuxApplicationProvider::desktopFilePaths( const QStringList& directories ) const {
        QStringList desktopFiles;

        for ( const QString& dirPath : directories ) {
            QDir dir( dirPath );

            if ( !dir.exists() ) {
                continue;
            }

            QDirIterator it( dirPath,
                             QStringList() << "*.desktop",
                             QDir::Files,
                             QDirIterator::Subdirectories );

            while ( it.hasNext() ) {
                desktopFiles.append( it.next() );
            }
        }

        return desktopFiles;
    }

    QString LinuxApplicationProvider::localizedDesktopEntryValue( QSettings* settings,
                                                                  const QString& group,
                                                                  const QString& key ) const {
        settings->beginGroup( group );

        const QLocale locale;

        // e.g. "fr_CA"
        const QString localeName = locale.name();

        // e.g. "fr"
        const QString language = localeName.section( '_', 0, 0 );

        // Try the full locale first
        QString value = settings->value( QString( "%1[%2]" ).arg( key, localeName ) ).toString();

        // Then the language only
        if ( value.isEmpty() )
            value = settings->value( QString( "%1[%2]" ).arg( key, language ) ).toString();

        // Finally the unlocalized value
        if ( value.isEmpty() )
            value = settings->value( key ).toString();

        settings->endGroup();
        return value;
    }

} // namespace Editor::Provider