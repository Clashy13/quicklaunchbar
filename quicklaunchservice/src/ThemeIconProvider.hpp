#pragma once

#include <QIcon>
#include <QQuickImageProvider>

class ThemeIconProvider : public QQuickImageProvider {
  public:
    ThemeIconProvider() : QQuickImageProvider( QQuickImageProvider::Pixmap ) {}

    QPixmap requestPixmap( const QString& id, QSize* size, const QSize& requestedSize ) override {
        QIcon icon = QIcon::fromTheme( id );
        return icon.pixmap( requestedSize );
    }
};
