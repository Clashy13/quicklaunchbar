#include "src/QmlRegistration.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main( int argc, char* argv[] ) {
    QGuiApplication app( argc, argv );

    QQmlApplicationEngine engine;

    Editor::QmlRegistration::registerTypes();

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
