#pragma once

#include "ProfileManager.hpp"
#include "models/Profile.hpp"

#include <QObject>
#include <QPoint>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QRect>
#include <QScreen>
#include <qtypes.h>

namespace Service {

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

      signals:
        void showProfile( Models::Profile* profile );

        void hideWindow();

      private:
        void toggleProfile( Models::Profile* profile );

        QScreen* newCurrentScreen() const;

        ProfileManager _profileManager{ this };
        QScreen* _currentProfileScreen = nullptr;
    };
} // namespace Service
