#include "shared/iconprovider/FileIconProvider.hpp"
#include "shared/iconprovider/ThemeIconProvider.hpp"
#include "src/QmlRegistration.hpp"
#include "src/manager/SingleSessionManager.hpp"

#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>

int main( int argc, char* argv[] ) {
    QLoggingCategory::setFilterRules( QStringLiteral( "qt.svg.warning=false" ) );

    QGuiApplication app( argc, argv );
    app.setApplicationName( "Quick Launch Editor" );

    Editor::Manager::SingleSessionManager singleSessionManager;
    if ( !singleSessionManager.tryAcquire() ) {
        return 0;
    }

    Editor::QmlRegistration::registerTypes();

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
