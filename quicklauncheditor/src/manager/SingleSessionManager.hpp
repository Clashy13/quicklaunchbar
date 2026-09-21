#pragma once

#include <QLocalServer>
#include <QLocalSocket>

namespace Editor::Manager {

    class SingleSessionManager {

      public:
        bool tryAcquire() {
            // Try to connect to an existing instance.
            QLocalSocket socket;
            socket.connectToServer( this->_servername );
            if ( socket.waitForConnected( 100 ) ) {
                return false;
            }

            // The socket may be left behind after a crash
            QLocalServer::removeServer( this->_servername );

            // Become the single running instance
            if ( !this->_server.listen( this->_servername ) ) {
                qWarning().noquote()
                    << "Could not start local server:" << this->_server.errorString();
                return false;
            }
            return true;
        }

      private:
        const QString _servername = "quicklaunchbar-editor";
        QLocalServer _server;
    };

} // namespace Editor::Manager