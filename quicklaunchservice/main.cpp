#include "QmlRegistration.hpp"
#include "SingleSessionManager.hpp"
#include "shared/iconprovider/FileIconProvider.hpp"
#include "shared/iconprovider/ThemeIconProvider.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main( int argc, char* argv[] ) {
    QGuiApplication app( argc, argv );

    if ( !Service::SingleSessionManager::instance()->tryAcquire( app ) ) {
        return 0;
    }

    QmlRegistration::registerTypes();

    QQmlApplicationEngine engine;
    engine.addImageProvider( "fileicons", new Shared::IconProvider::FileIconProvider );
    engine.addImageProvider( "themeicons", new Shared::IconProvider::ThemeIconProvider );
    const QUrl url( QStringLiteral( "qrc:/Main.qml" ) );
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit( -1 ); },
        Qt::QueuedConnection );
    engine.load( url );

    return app.exec();
}
