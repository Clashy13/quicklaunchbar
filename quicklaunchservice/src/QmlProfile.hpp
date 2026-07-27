#pragma once

#include "QmlExecutionTarget.hpp"

#include <QList>
#include <QQmlListProperty>
#include <QString>
#include <QUuid>

class QmlProfile : public QObject {
    Q_OBJECT

    Q_PROPERTY( QString name READ name CONSTANT )
    Q_PROPERTY( QString viewSource READ viewSource CONSTANT )
    Q_PROPERTY(
        QQmlListProperty<QmlExecutionTarget> executionTargets READ executionTargets CONSTANT )

  public:
    explicit QmlProfile( const QString& name,
                         const QString& viewSource,
                         const QList<QmlExecutionTarget*>& executionTargets,
                         QObject* parent = nullptr )
        : QObject( parent ), _name( name ), _viewSource( viewSource ),
          _executionTargets( executionTargets ) {}

    auto name() const {
        return this->_name;
    }

    auto viewSource() const {
        return this->_viewSource;
    }

    QQmlListProperty<QmlExecutionTarget> executionTargets() {
        return QQmlListProperty<QmlExecutionTarget>( this, &this->_executionTargets );
    }

  private:
    const QString _name;
    const QString _viewSource;
    QList<QmlExecutionTarget*> _executionTargets;
};
