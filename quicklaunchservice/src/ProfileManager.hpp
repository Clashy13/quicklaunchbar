#pragma once

#include "QmlProfile.hpp"
#include "shared/models/Command.hpp"
#include "shared/models/IconSource.hpp"
#include "shared/models/Profile.hpp"

#include <QObject>
#include <qtmetamacros.h>
#include <qtypes.h>

class ProfileManager : public QObject {
    Q_OBJECT

  public:
    ProfileManager( QObject* parent = nullptr );

    void launchExecutionTargetByIndex( const qsizetype index );

    auto qmlProfileAt( qsizetype n ) const {
        return this->_qmlProfiles.at( n );
    }

    bool hasCurrentProfile() const {
        return this->currentProfileIndex != -1;
    }

    auto& currentProfileView() const {
        return this->_profiles.at( this->currentProfileIndex ).view;
    }

    qsizetype currentProfileIndex = -1;

  signals:
    void toggleProfile( qsizetype profileIndex );

  private:
    void connectShortcutsToProfiles();

    void setQmlProfiles();

    static QUrl iconSourceUrl( const Models::ExecutionTarget::IconSource& iconSource );

    static QString executionTargetViewSource( const Models::Profile::ProfileView& profileView );

    void startExecutionTargetProcess( qsizetype index );

    static void startSingleProcess( const Models::ExecutionTarget::Command& command );

    const std::vector<Models::Profile::Profile> _profiles;
    std::vector<QmlProfile*> _qmlProfiles;
};
