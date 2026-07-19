#pragma once

#include <QFileIconProvider>
#include <QQuickImageProvider>

class FileIconProvider : public QQuickImageProvider {
  public:
    FileIconProvider() : QQuickImageProvider( QQuickImageProvider::Pixmap ) {}

    QPixmap requestPixmap( const QString& id, QSize* size, const QSize& requestedSize ) override {
        QFileIconProvider provider;
        QIcon icon = provider.icon( QFileInfo( id ) );

        QSize s = requestedSize.isValid() ? requestedSize : QSize( 64, 64 );
        if ( size ) {
            *size = s;
        }

        return icon.pixmap( s );
    }
};
