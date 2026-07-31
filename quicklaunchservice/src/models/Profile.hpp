#pragma once

#include "../models/ExecutionTarget.hpp"
#include "shared/models/ProfileView.hpp"

#include <QObject>
#include <QQmlListProperty>

namespace Service::Models {

    class Profile : public QObject {
        Q_OBJECT

        Q_PROPERTY( QString name READ name CONSTANT )
        Q_PROPERTY( QString viewSource READ viewSource CONSTANT )
        Q_PROPERTY(
            QQmlListProperty<ExecutionTarget> executionTargets READ executionTargets CONSTANT )

        using ProfileView = Shared::Models::Profile::ProfileView;

      public:
        explicit Profile( const QUuid& uuid,
                          const QString& name,
                          const QString& shortcut,
                          const ProfileView& view,
                          const QString& viewSource,
                          const QList<ExecutionTarget*>& executionTargets )
            : _uuid( uuid ), _name( name ), _shortcut( shortcut ), _view( view ),
              _viewSource( viewSource ), _executionTargets( executionTargets ) {
            for ( auto executionTarget : this->_executionTargets ) {
                executionTarget->setParent( this );
            }
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

        auto viewSource() const {
            return this->_viewSource;
        }

        QQmlListProperty<ExecutionTarget> executionTargets() {
            return QQmlListProperty<ExecutionTarget>( this, &this->_executionTargets );
        }

        auto executionTargetAt( qsizetype index ) const {
            return this->_executionTargets.at( index );
        }

      private:
        const QUuid _uuid;
        const QString _name;
        const QString _shortcut;
        const ProfileView _view;
        const QString _viewSource;
        QList<ExecutionTarget*> _executionTargets;
    };
} // namespace Service::Models