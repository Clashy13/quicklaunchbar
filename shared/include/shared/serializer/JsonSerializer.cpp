#include "JsonSerializer.hpp"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

namespace Shared::Serializer {
    QJsonObject JsonSerializer::loadJsonObject( const QString& filePath ) {
        QFile file( filePath );

        if ( !file.open( QIODevice::ReadOnly ) ) {
            qWarning().noquote() << "Could not open file:" << filePath;
            return QJsonObject();
        }

        QByteArray data = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson( data, &parseError );

        if ( parseError.error != QJsonParseError::NoError ) {
            qWarning().noquote() << "JSON parse error:" << parseError.errorString();
            return QJsonObject();
        }

        if ( !doc.isObject() ) {
            qWarning().noquote() << "JSON root is not an object.";
            return QJsonObject();
        }

        return doc.object();
    }

    bool JsonSerializer::saveJsonObject( const QJsonObject& json, const QString& filePath ) {
        QFileInfo fileInfo( filePath );

        QDir dir = fileInfo.dir();
        if ( !dir.exists() && !dir.mkpath( "." ) ) {
            qWarning().noquote() << "Failed to create directory:" << dir.path();
            return false;
        }

        QFile file( filePath );
        if ( !file.open( QIODevice::WriteOnly ) ) {
            qWarning().noquote() << "Could not open file for writing:" << filePath;
            return false;
        }

        QJsonDocument doc( json );
        if ( file.write( doc.toJson( QJsonDocument::Indented ) ) == -1 ) {
            qWarning().noquote() << "Failed to write JSON to file.";
            return false;
        }

        return true;
    }
} // namespace Shared::Serializer