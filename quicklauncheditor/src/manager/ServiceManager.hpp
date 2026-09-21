#pragma once

#include <QLocalSocket>
#include <QProcess>
#include <qprocess.h>

namespace Editor::Manager {

    class ServiceManager {

      public:
        static ServiceManager* instance() {
            static ServiceManager serviceManager;
            return &serviceManager;
        }

        void sendRefresh() {
            QLocalSocket socket;

            socket.connectToServer( "quicklaunchbar-service" );

            // if server cannot be found, quicklaunchservice is not running
            if ( !socket.waitForConnected( 500 ) ) {
                QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                env.insert( "QT_QPA_PLATFORM", "xcb" );

                this->_process.setProcessEnvironment( env );
                this->_process.setProgram( "/opt/quicklaunchbar/bin/quicklaunchservice" );
                this->_process.setArguments( { "--refresh" } );

                this->_process.startDetached();
            } else {
                socket.write( "refresh" );
                socket.flush();

                socket.waitForBytesWritten( 500 );
                socket.disconnectFromServer();
            }
        }

      private:
        explicit ServiceManager() {}

        QProcess _process;
    };
} // namespace Editor::Manager