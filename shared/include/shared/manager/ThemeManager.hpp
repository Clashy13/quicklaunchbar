#pragma once

#include <QGuiApplication>
#include <QObject>
#include <QStyleHints>

class ThemeManager : public QObject {
    Q_OBJECT

    Q_PROPERTY( bool isDark READ isDark NOTIFY isDarkChanged )

  public:
    static ThemeManager* instance() {
        static ThemeManager themeManager;
        return &themeManager;
    }

    bool isDark() const {
        return this->_isDark;
    }

  signals:
    void isDarkChanged();

  private:
    explicit ThemeManager( QObject* parent = nullptr ) : QObject( parent ) {
        this->updateIsDark();
        connect( qApp->styleHints(),
                 &QStyleHints::colorSchemeChanged,
                 this,
                 &ThemeManager::updateIsDark );
    }

    void updateIsDark() {
        this->_isDark = qApp->styleHints()->colorScheme() == Qt::ColorScheme::Dark;
        emit this->isDarkChanged();
    }

    bool _isDark;
};
