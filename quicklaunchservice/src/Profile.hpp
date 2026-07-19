#pragma once

#include "ExecutionTarget.hpp"
#include "ProfileView.hpp"

#include <QList>
#include <QQmlListProperty>
#include <QString>
#include <QUuid>

class Profile : public QObject {
    Q_OBJECT

    Q_PROPERTY( QString name READ name CONSTANT )
    Q_PROPERTY( ProfileView* view READ view CONSTANT )
    Q_PROPERTY( QQmlListProperty<ExecutionTarget> executionTargets READ executionTargets CONSTANT )

  public:
    explicit Profile( const QUuid& uuid,
                      const QString& name,
                      const QString& shortcut,
                      ProfileView* view,
                      const QList<ExecutionTarget*>& executionTargets,
                      QObject* parent = nullptr )
        : QObject( parent ), _uuid( uuid ), _name( name ), _shortcut( shortcut ), _view( view ),
          _executionTargets( executionTargets ) {}

    auto uuid() const {
        return this->_uuid;
    }

    auto name() const {
        return this->_name;
    }

    auto shortcut() const {
        return this->_shortcut;
    }

    auto view() const {
        return this->_view;
    }

    QQmlListProperty<ExecutionTarget> executionTargets() {
        return QQmlListProperty<ExecutionTarget>( this, &this->_executionTargets );
    }

    auto executionTargetAt( qsizetype index ) const {
        return this->_executionTargets.at( index );
    }

    bool operator==( Profile* other ) const {
        return this->uuid() == other->uuid();
    }

  private:
    const QUuid _uuid;
    const QString _name;
    const QString _shortcut;
    ProfileView* _view;
    QList<ExecutionTarget*> _executionTargets;
};
