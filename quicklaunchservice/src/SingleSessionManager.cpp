#include "SingleSessionManager.hpp"

namespace Service {

    SingleSessionManager* SingleSessionManager::instance() {
        static SingleSessionManager singleSessionManager;
        return &singleSessionManager;
    }

    bool SingleSessionManager::tryAcquire( const QGuiApplication& app ) {
        // Try to connect to an existing instance.
        QLocalSocket socket;
        socket.connectToServer( this->_serverName );
        if ( socket.waitForConnected( 100 ) ) {
            if ( app.arguments().contains( "--refresh" ) ) {
                socket.write( "refresh" );
                socket.flush();
                socket.waitForBytesWritten( 500 );
            }

            return false;
        }

        // The socket may be left behind after a crash
        QLocalServer::removeServer( this->_serverName );

        // Become the single running instance
        if ( !this->_server.listen( this->_serverName ) ) {
            qWarning().noquote() << "Could not start local server:" << this->_server.errorString();
            return false;
        }

        this->connect( &this->_server,
                       &QLocalServer::newConnection,
                       this,
                       &SingleSessionManager::onNewConnection );

        return true;
    }

    void SingleSessionManager::onNewConnection() {
        QLocalSocket* socket = this->_server.nextPendingConnection();

        this->connect( socket, &QLocalSocket::readyRead, this, [ this, socket ]() {
            const QByteArray command = socket->readAll().trimmed();

            if ( command == "refresh" ) {
                emit this->refreshed();
            }

            socket->disconnectFromServer();
        } );

        this->connect( socket, &QLocalSocket::disconnected, socket, &QObject::deleteLater );
    }
} // namespace Service