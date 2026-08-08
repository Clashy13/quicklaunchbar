#include "QmlRegistration.hpp"
#include "shared/iconprovider/FileIconProvider.hpp"
#include "shared/iconprovider/ThemeIconProvider.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main( int argc, char* argv[] ) {
    QGuiApplication app( argc, argv );

    QmlRegistration::registerTypes();
    ThemeManager themeManager;
    QmlRegistration::registerThemeManager( &themeManager );

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
