#pragma once

#include <QGuiApplication>
#include <QLocalServer>
#include <QLocalSocket>

namespace Service {

    class SingleSessionManager : public QObject {
        Q_OBJECT

      public:
        static SingleSessionManager* instance();

        bool tryAcquire( const QGuiApplication& app );

      private slots:
        void onNewConnection();

      signals:
        void refreshed();

      private:
        const QString _serverName = "quicklaunchbar-service";
        QLocalServer _server;
    };

} // namespace Service