#include "ProfileSerializer.hpp"

#include "GroupExecutionTarget.hpp"
#include "ProfileView.hpp"
#include "SingleExecutionTarget.hpp"
#include "shared/ProfileConfigNames.hpp"

#include <QFileInfo>
#include <QImageReader>
#include <QProcess>
#include <QUrl>
#include <QUuid>
#include <cstddef>
#include <optional>

std::optional<Profile*> ProfileSerializer::serializedProfile( const ptree& profileTree ) {
    QUuid uuid;
    if ( const auto uuidOpt =
             ProfileSerializer::getPropertyOfPTree<std::string>( ProfileConfig::Key::Profile::Uuid,
                                                                 profileTree,
                                                                 "profile" ) ) {
        uuid = QUuid( *uuidOpt );
    } else {
        return std::nullopt;
    }

    QString name;
    if ( const auto nameOpt =
             ProfileSerializer::getPropertyOfPTree<std::string>( ProfileConfig::Key::Profile::Name,
                                                                 profileTree,
                                                                 "profile" ) ) {
        name = QString::fromStdString( *nameOpt );
    } else {
        return std::nullopt;
    }

    QString shortcut;
    if ( const auto shortcutOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::Shortcut,
             profileTree,
             "profile" ) ) {
        shortcut = QString::fromStdString( *shortcutOpt );
    } else {
        return std::nullopt;
    }

    ProfileView* view = nullptr;
    if ( const auto viewTree =
             profileTree.get_child_optional( ProfileConfig::Key::Profile::View::Key ) ) {
        if ( const auto viewOpt = ProfileSerializer::serializedProfileView( *viewTree ) ) {
            view = *viewOpt;
        } else {
            return std::nullopt;
        }
    } else {
        qWarning().noquote() << "Could not find property '" +
                                    QString( ProfileConfig::Key::Profile::View::Key ) +
                                    "' of profile";
        return std::nullopt;
    }

    QList<ExecutionTarget*> executionTargets;
    if ( const auto executionTargetsOpt =
             profileTree.get_child_optional( ProfileConfig::Key::Profile::ExecutionTarget::Key ) ) {
        for ( const auto executionTarget : *executionTargetsOpt ) {
            if ( const auto serializedExecutionTarget =
                     ProfileSerializer::serializedExecutionTarget( executionTarget.second ) ) {
                executionTargets.push_back( *serializedExecutionTarget );
            }
        }

        if ( executionTargets.empty() ) {
            qWarning().noquote() << "No valid execution targets found for profile";
            return std::nullopt;
        }

    } else {
        qWarning().noquote() << "Could not find property '" +
                                    QString( ProfileConfig::Key::Profile::ExecutionTarget::Key ) +
                                    "' of profile";
        return std::nullopt;
    }

    return new Profile( uuid, name, shortcut, view, executionTargets );
}

std::optional<ProfileView*> ProfileSerializer::serializedProfileView( const ptree& profileTree ) {
    namespace View = ProfileConfig::Value::Profile::View;
    QString mode;
    if ( const auto modeOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::View::Mode,
             profileTree,
             "profile view" ) ) {
        mode = QString::fromStdString( *modeOpt );
        if ( mode != View::Mode::Icon && mode != View::Mode::List ) {
            qWarning().noquote() << "No known profile view"
                                 << QString( ProfileConfig::Key::Profile::View::Mode ) + ":"
                                 << mode;
            return std::nullopt;
        }
    } else {
        return std::nullopt;
    }

    QString horizontalAnchor;
    if ( const auto horizontalAnchorOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::View::HorizontalAnchor,
             profileTree,
             "profile view" ) ) {
        horizontalAnchor = QString::fromStdString( *horizontalAnchorOpt );
        if ( horizontalAnchor != View::HorizontalAnchor::Left &&
             horizontalAnchor != View::HorizontalAnchor::Center &&
             horizontalAnchor != View::HorizontalAnchor::Right ) {
            qWarning().noquote() << "No known profile view"
                                 << QString( ProfileConfig::Key::Profile::View::HorizontalAnchor ) +
                                        ":"
                                 << horizontalAnchor;
            return std::nullopt;
        }
    } else {
        return std::nullopt;
    }

    QString verticalAnchor;
    if ( const auto verticalAnchorOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::View::VerticalAnchor,
             profileTree,
             "profile view" ) ) {
        verticalAnchor = QString::fromStdString( *verticalAnchorOpt );
        if ( verticalAnchor != View::VerticalAnchor::Top &&
             verticalAnchor != View::VerticalAnchor::Center &&
             verticalAnchor != View::VerticalAnchor::Bottom ) {
            qWarning().noquote() << "No known profile view"
                                 << QString( ProfileConfig::Key::Profile::View::VerticalAnchor ) +
                                        ":"
                                 << verticalAnchor;
            return std::nullopt;
        }
    } else {
        return std::nullopt;
    }

    qsizetype margin = 0;
    if ( const auto marginOpt = ProfileSerializer::getPropertyOfPTree<std::size_t>(
             ProfileConfig::Key::Profile::View::Margin,
             profileTree,
             "profile view" ) ) {
        margin = *marginOpt;
    } else {
        return std::nullopt;
    }

    QString wrapMode;
    if ( const auto wrapModeOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::View::WrapMode,
             profileTree,
             "profile view" ) ) {
        wrapMode = QString::fromStdString( *wrapModeOpt );
        if ( wrapMode != View::WrapMode::Scroll && wrapMode != View::WrapMode::Grid ) {
            qWarning().noquote() << "No known profile view"
                                 << QString( ProfileConfig::Key::Profile::View::WrapMode ) + ":"
                                 << wrapMode;
            return std::nullopt;
        }
    } else {
        return std::nullopt;
    }

    QString flowDirection;
    if ( mode == ProfileConfig::Value::Profile::View::Mode::Icon ) {
        if ( const auto flowDirectionOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
                 ProfileConfig::Key::Profile::View::FlowDirection,
                 profileTree,
                 "profile view" ) ) {
            flowDirection = QString::fromStdString( *flowDirectionOpt );
            if ( flowDirection != View::FlowDirection::Horizontal &&
                 flowDirection != View::FlowDirection::Vertical ) {
                qWarning().noquote()
                    << "No known profile view"
                    << QString( ProfileConfig::Key::Profile::View::FlowDirection ) + ":"
                    << flowDirection;
                return std::nullopt;
            }
        } else {
            return std::nullopt;
        }
    }

    return new ProfileView( mode,
                            horizontalAnchor,
                            verticalAnchor,
                            margin,
                            wrapMode,
                            flowDirection );
}

std::optional<ExecutionTarget*>
ProfileSerializer::serializedExecutionTarget( const ptree& executionTargetTree ) {
    namespace ExecType = ProfileConfig::Value::Profile::ExecutionTarget::Type;

    if ( const auto type = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::Type,
             executionTargetTree,
             "execution target" ) ) {
        if ( *type == ExecType::DesktopApplication ) {
            return ProfileSerializer::serializedDesktopApplication( executionTargetTree );
        } else if ( *type == ExecType::ExecutableFile ) {
            return ProfileSerializer::serializedExecutableFile( executionTargetTree );
        } else if ( *type == ExecType::Command ) {
            return ProfileSerializer::serializedCommand( executionTargetTree );
        } else if ( *type == ExecType::OpenFile ) {
            return ProfileSerializer::serializedOpenFile( executionTargetTree );
        } else if ( *type == ExecType::OpenUrl ) {
            return ProfileSerializer::serializedOpenUrl( executionTargetTree );
        } else if ( *type == ExecType::Group ) {
            return ProfileSerializer::serializedGroup( executionTargetTree );
        } else {
            qWarning().noquote() << "No known execution target type '" +
                                        QString::fromStdString( *type ) + "'";
            return std::nullopt;
        }
    } else {
        return std::nullopt;
    }
}

std::optional<SingleExecutionTarget*>
ProfileSerializer::serializedDesktopApplication( const ptree& executionTargetTree ) {
    QSettings* settings;
    if ( const auto settingsOpt =
             ProfileSerializer::executionTargetDesktopFileSettings( executionTargetTree ) ) {
        settings = *settingsOpt;
    } else {
        return std::nullopt;
    }

    const QString name =
        ProfileSerializer::localizedDesktopEntryValue( settings, "Desktop Entry", "Name" );
    const QString iconTheme = settings->value( "Desktop Entry/Icon" ).toString();
    const QString exec = settings->value( "Desktop Entry/Exec" ).toString();

    QStringList arguments = QProcess::splitCommand( exec );

    for ( QString& arg : arguments ) {
        if ( arg == "%f" || arg == "%F" || arg == "%u" || arg == "%U" ) {
            arg.clear();
        }
    }
    arguments.removeAll( "" );

    const QString program = arguments.takeFirst();

    const auto iconSource = QUrl( "image://themeicons/" + iconTheme );

    return new SingleExecutionTarget( name, program, arguments, iconSource );
}

std::optional<SingleExecutionTarget*>
ProfileSerializer::serializedExecutableFile( const ptree& executionTargetTree ) {
    QString name;
    if ( const auto nameOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::Name,
             executionTargetTree,
             "execution target" ) ) {
        name = QString::fromStdString( *nameOpt );
    } else {
        return std::nullopt;
    }

    QString executableFilePath;
    if ( const auto executableOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::ExecutableFile,
             executionTargetTree,
             "execution target" ) ) {
        executableFilePath = QString::fromStdString( *executableOpt );
    } else {
        return std::nullopt;
    }

    const QFileInfo fileInfo( executableFilePath );
    if ( !fileInfo.exists() || !fileInfo.isFile() ) {
        qWarning().noquote() << "File does not exist: " + executableFilePath;
        return std::nullopt;
    }

    if ( !fileInfo.isExecutable() ) {
        qWarning().noquote() << "File is not executable: " + executableFilePath;
        return std::nullopt;
    }

    QStringList arguments{};
    if ( const auto argumentsOpt = executionTargetTree.get_child_optional(
             ProfileConfig::Key::Profile::ExecutionTarget::Arguments ) ) {
        for ( const auto argument : *argumentsOpt ) {
            arguments.push_back(
                QString::fromStdString( argument.second.get_value<std::string>() ) );
        }
    }

    QUrl iconSource;
    if ( const auto iconSourceOpt =
             ProfileSerializer::executionTargetIconFile( executionTargetTree ) ) {
        iconSource = *iconSourceOpt;
    } else {
        iconSource = QUrl( "image://fileicons" + executableFilePath );
    }

    return new SingleExecutionTarget( name, executableFilePath, arguments, iconSource );
}

std::optional<SingleExecutionTarget*>
ProfileSerializer::serializedCommand( const ptree& executionTargetTree ) {
    QString name;
    if ( const auto nameOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::Name,
             executionTargetTree,
             "execution target" ) ) {
        name = QString::fromStdString( *nameOpt );
    } else {
        return std::nullopt;
    }

    QString program;
    QStringList arguments{};
    if ( const auto cmd = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::Command,
             executionTargetTree,
             "execution target" ) ) {
        const QString command = QString::fromStdString( *cmd );
        arguments = QProcess::splitCommand( command );
        program = arguments.takeFirst();
    } else {
        return std::nullopt;
    }

    QUrl iconSource;
    if ( const auto iconSourceOpt =
             ProfileSerializer::executionTargetIconFile( executionTargetTree ) ) {
        iconSource = *iconSourceOpt;
    } else {
        iconSource = QUrl( "qrc:/icons/command_icon.svg" );
    }

    return new SingleExecutionTarget( name, program, arguments, iconSource );
}

std::optional<ExecutionTarget*>
ProfileSerializer::serializedOpenFile( const ptree& executionTargetTree ) {
    QString name;
    if ( const auto nameOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::Name,
             executionTargetTree,
             "execution target" ) ) {
        name = QString::fromStdString( *nameOpt );
    } else {
        return std::nullopt;
    }

    QString fileToOpenPath;
    if ( const auto file = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::FileToOpen,
             executionTargetTree,
             "execution target" ) ) {
        fileToOpenPath = QString::fromStdString( *file );
    } else {
        return std::nullopt;
    }

    const QFileInfo fileInfo( fileToOpenPath );

    if ( !fileInfo.exists() || !fileInfo.isFile() ) {
        qWarning().noquote() << "File does not exist: " + fileToOpenPath;
        return std::nullopt;
    }

    QSettings* settings;
    if ( const auto settingsOpt =
             ProfileSerializer::executionTargetDesktopFileSettings( executionTargetTree ) ) {
        settings = *settingsOpt;
    } else {
        return std::nullopt;
    }

    const QString exec = settings->value( "Desktop Entry/Exec" ).toString();

    QStringList arguments = QProcess::splitCommand( exec );

    bool placeholderFound = false;
    for ( QString& arg : arguments ) {
        if ( placeholderFound && ( arg == "%f" || arg == "%F" || arg == "%u" || arg == "%U" ) ) {
            arg.clear();
        } else if ( arg == "%f" || arg == "%F" ) {
            placeholderFound = true;
            arg = fileToOpenPath;
        } else if ( arg == "%u" || arg == "%U" ) {
            placeholderFound = true;
            arg = QUrl::fromLocalFile( fileToOpenPath ).toString();
        }
    }
    arguments.removeAll( "" );

    if ( !placeholderFound ) {
        arguments.push_back( fileToOpenPath );
    }

    const QString program = arguments.takeFirst();

    QUrl iconSource;
    if ( const auto iconSourceOpt =
             ProfileSerializer::executionTargetIconFile( executionTargetTree ) ) {
        iconSource = *iconSourceOpt;
    } else {
        iconSource = QUrl( "image://fileicons" + fileToOpenPath );
    }

    return new SingleExecutionTarget( name, program, arguments, iconSource );
}

std::optional<ExecutionTarget*>
ProfileSerializer::serializedOpenUrl( const ptree& executionTargetTree ) {
    QString name;
    if ( const auto nameOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::Name,
             executionTargetTree,
             "execution target" ) ) {
        name = QString::fromStdString( *nameOpt );
    } else {
        return std::nullopt;
    }

    QString url;
    if ( const auto urlOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::Url,
             executionTargetTree,
             "execution target" ) ) {
        url = QString::fromStdString( *urlOpt );
    } else {
        return std::nullopt;
    }

    QSettings* settings;
    if ( const auto settingsOpt =
             ProfileSerializer::executionTargetDesktopFileSettings( executionTargetTree ) ) {
        settings = *settingsOpt;
    } else {
        return std::nullopt;
    }

    const QString exec = settings->value( "Desktop Entry/Exec" ).toString();
    const QString iconTheme = settings->value( "Desktop Entry/Icon" ).toString();

    QStringList arguments = QProcess::splitCommand( exec );

    bool placeholderFound = false;
    for ( QString& arg : arguments ) {
        if ( arg == "%u" || arg == "%U" ) {
            arg = url;
            placeholderFound = true;
            break;
        }
    }
    for ( QString& arg : arguments ) {
        if ( arg == "%f" || arg == "%F" || arg == "%u" || arg == "%U" ) {
            arg.clear();
        }
    }
    arguments.removeAll( "" );

    if ( !placeholderFound ) {
        arguments.push_back( url );
    }

    const QString program = arguments.takeFirst();

    const auto iconSource = QUrl( "image://themeicons/" + iconTheme );

    return new SingleExecutionTarget( name, program, arguments, iconSource );
}

std::optional<GroupExecutionTarget*>
ProfileSerializer::serializedGroup( const ptree& executionTargetTree ) {
    QString name;
    if ( const auto nameOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::Name,
             executionTargetTree,
             "execution target" ) ) {
        name = QString::fromStdString( *nameOpt );
    } else {
        return std::nullopt;
    }

    QList<GroupExecutionTarget::Exec> execList{};
    QList<QUrl> iconSources;
    unsigned int iconCount = 4;
    if ( const auto targets = executionTargetTree.get_child_optional(
             ProfileConfig::Key::Profile::ExecutionTarget::ExecutionTargets ) ) {
        for ( const auto target : *targets ) {
            if ( const auto type = ProfileSerializer::getPropertyOfPTree<std::string>(
                     ProfileConfig::Key::Profile::ExecutionTarget::Type,
                     target.second,
                     "execution target" ) ) {
                if ( type == ProfileConfig::Value::Profile::ExecutionTarget::Type::Group ) {
                    qWarning().noquote() << "Execution target group recursion not allowed";
                    continue;
                }
            }

            if ( const auto executionTarget =
                     ProfileSerializer::serializedExecutionTarget( target.second ) ) {
                if ( const auto singleExecutionTarget =
                         dynamic_cast<SingleExecutionTarget*>( *executionTarget ) ) {
                    GroupExecutionTarget::Exec exec;
                    exec.program = singleExecutionTarget->program();
                    exec.arguments = singleExecutionTarget->arguments();
                    execList.push_back( exec );

                    if ( iconCount > 0 ) {
                        iconSources.push_back( singleExecutionTarget->iconSource() );
                        iconCount--;
                    }
                } else {
                    continue;
                }
            } else {
                continue;
            }
        }
    }

    if ( execList.empty() ) {
        return std::nullopt;
    }

    return new GroupExecutionTarget( name, execList, iconSources );
}

template <typename T>
std::optional<T> ProfileSerializer::getPropertyOfPTree( const char* const propertyName,
                                                        const ptree& tree,
                                                        const QString& treeName,
                                                        bool optional ) {
    if ( const auto value = tree.get_optional<T>( propertyName ) ) {
        return *value;
    }
    if ( !optional ) {
        qWarning().noquote() << "Could not find property '" + QString( propertyName ) + "' of " +
                                    treeName;
    }
    return std::nullopt;
}

std::optional<QSettings*>
ProfileSerializer::executionTargetDesktopFileSettings( const ptree& executionTargetTree ) {
    QString filePath;
    if ( const auto fileOpt = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::DesktopFile,
             executionTargetTree,
             "execution target" ) ) {
        filePath = QString::fromStdString( *fileOpt );
    } else {
        return std::nullopt;
    }

    const QFileInfo fileInfo( filePath );

    if ( !fileInfo.exists() || !fileInfo.isFile() ) {
        qWarning().noquote() << "File does not exist: " + filePath;
        return std::nullopt;
    }

    if ( fileInfo.suffix() != "desktop" ) {
        qWarning().noquote() << "Invalid file type. Expected: .desktop";
        return std::nullopt;
    }

    return new QSettings( filePath, QSettings::IniFormat );
}

std::optional<QUrl> ProfileSerializer::executionTargetIconFile( const ptree& executionTargetTree ) {
    if ( const auto icon = ProfileSerializer::getPropertyOfPTree<std::string>(
             ProfileConfig::Key::Profile::ExecutionTarget::IconFile,
             executionTargetTree,
             "execution target",
             true ) ) {
        QString iconPath = QString::fromStdString( *icon );

        const QFileInfo fileInfo( iconPath );

        if ( !fileInfo.exists() || !fileInfo.isFile() ) {
            qWarning().noquote() << "File does not exist: " + iconPath;
            return std::nullopt;
        }

        if ( !QImageReader( iconPath ).canRead() ) {
            qWarning().noquote() << "Not a supported image format: ." + fileInfo.suffix();
            return std::nullopt;
        }

        return QUrl::fromLocalFile( iconPath );
    } else {
        return std::nullopt;
    }
}

QString ProfileSerializer::localizedDesktopEntryValue( QSettings* settings,
                                                       const QString& group,
                                                       const QString& key ) {
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
