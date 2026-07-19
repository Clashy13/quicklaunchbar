#pragma once

#include <QDebug>
#include <QObject>
#include <QProcess>
#include <QString>

class ExecutionTarget : public QObject {
    Q_OBJECT

    Q_PROPERTY( QString name READ name CONSTANT )

    Q_PROPERTY( ExecutionTarget::Type type READ type CONSTANT )

  public:
    enum class Type { Single, Group };
    Q_ENUM( Type )

    explicit ExecutionTarget( const QString& name, Type type, QObject* parent = nullptr )
        : QObject( parent ), _name( name ), _type( type ) {}

    auto name() const {
        return this->_name;
    };

    auto type() const {
        return this->_type;
    };

    virtual void startProcess() = 0;

  protected:
    void startSingleProcess( const QString& program, const QStringList& arguments ) const {
        const bool success = QProcess::startDetached( program, arguments );
        if ( !success ) {
            qWarning().noquote() << "Process failed:" << program << arguments.join( " " );
        }
    }

  private:
    const QString _name;
    const Type _type;
};
