#pragma once

#include <QIcon>
#include <QQuickImageProvider>

namespace Shared::IconProvider {

    class ThemeIconProvider : public QQuickImageProvider {
      public:
        ThemeIconProvider() : QQuickImageProvider( QQuickImageProvider::Pixmap ) {}

        QPixmap
        requestPixmap( const QString& id, QSize* size, const QSize& requestedSize ) override {
            QIcon icon = QIcon::fromTheme( id );

            QSize s = requestedSize.isValid() ? requestedSize : QSize( 64, 64 );
            if ( size ) {
                *size = s;
            }

            return icon.pixmap( s );
        }
    };
} // namespace Shared::IconProvider
