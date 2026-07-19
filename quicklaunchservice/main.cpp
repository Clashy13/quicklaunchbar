#include "FileIconProvider.hpp"
#include "QmlRegistration.hpp"
#include "ThemeIconProvider.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main( int argc, char* argv[] ) {
    QGuiApplication app( argc, argv );

    QmlRegistration::registerTypes();
    ThemeManager themeManager;
    QmlRegistration::registerThemeManager( &themeManager );

    QQmlApplicationEngine engine;
    engine.addImageProvider( "fileicons", new FileIconProvider );
    engine.addImageProvider( "themeicons", new ThemeIconProvider );
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
