#pragma once

#include "GroupExecutionTarget.hpp"
#include "Profile.hpp"
#include "SingleExecutionTarget.hpp"

#include <QSettings>
#include <QUrl>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;

class ProfileSerializer {
  public:
    static std::optional<Profile*> serializedProfile( const ptree& profileTree );

  private:
    static std::optional<ProfileView*> serializedProfileView( const ptree& profileTree );

    static std::optional<ExecutionTarget*>
    serializedExecutionTarget( const ptree& executionTargetTree );

    static std::optional<SingleExecutionTarget*>
    serializedDesktopApplication( const ptree& executionTargetTree );

    static std::optional<SingleExecutionTarget*>
    serializedExecutableFile( const ptree& executionTargetTree );

    static std::optional<SingleExecutionTarget*>
    serializedCommand( const ptree& executionTargetTree );

    static std::optional<ExecutionTarget*> serializedOpenFile( const ptree& executionTargetTree );

    static std::optional<ExecutionTarget*> serializedOpenUrl( const ptree& executionTargetTree );

    static std::optional<GroupExecutionTarget*> serializedGroup( const ptree& executionTargetTree );

    template <typename T>
    static std::optional<T> getPropertyOfPTree( const char* const propertyName,
                                                const ptree& tree,
                                                const QString& treeName,
                                                bool optional = false );

    static std::optional<QSettings*>
    executionTargetDesktopFileSettings( const ptree& executionTargetTree );

    static std::optional<QUrl> executionTargetIconFile( const ptree& executionTargetTree );

    static QString
    localizedDesktopEntryValue( QSettings* settings, const QString& group, const QString& key );
};
