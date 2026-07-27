#pragma once

#include <QList>
#include <QObject>
#include <QString>

class QmlExecutionTarget : public QObject {
    Q_OBJECT

    Q_PROPERTY( QString name READ name CONSTANT )
    Q_PROPERTY( QList<QUrl> iconSources READ iconSources CONSTANT )

  public:
    explicit QmlExecutionTarget( const QString& name,
                                 const QList<QUrl>& iconSources,
                                 QObject* parent = nullptr )
        : QObject( parent ), _name( name ), _iconSources( iconSources ) {}

    auto name() const {
        return this->_name;
    }

    auto iconSources() const {
        return this->_iconSources;
    }

  private:
    const QString _name;
    const QList<QUrl> _iconSources;
};
