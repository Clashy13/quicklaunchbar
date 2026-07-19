#pragma once

#include "Profile.hpp"

#include <QObject>
#include <QPoint>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QRect>
#include <QScreen>

class Backend : public QObject {
    Q_OBJECT
    QML_ELEMENT

  public:
    explicit Backend( QObject* parent = nullptr );

    Q_INVOKABLE void launchExecutionTargetByIndex( const qsizetype index );

    Q_INVOKABLE QPoint contentPosition( const qsizetype width, const qsizetype height ) const;

    Q_INVOKABLE qsizetype availableContentWidth();

    Q_INVOKABLE qsizetype availableContentHeight();

    Q_INVOKABLE void maskWindow( QQuickWindow* window, QRect contentRect );

    Q_INVOKABLE QRect currentScreenRect() const;

    Q_INVOKABLE QString executionTargetViewSource( ProfileView* profileView );

  signals:
    void showProfile( Profile* profile );

    void hideWindow();

  private:
    void setProfilesFromConfigFile();

    void connectShortcutsToProfiles();

    void toggleProfile( Profile* profile );

    QScreen* newCurrentScreen() const;

    QList<Profile*> _profiles;
    Profile* _currentProfile = nullptr;
    QScreen* _currentProfileScreen = nullptr;
};
