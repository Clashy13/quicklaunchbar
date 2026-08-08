#pragma once

#include "SingleExecutionTarget.hpp"

#include <QQmlListProperty>

namespace Editor::Models {

    class GroupExecutionTarget : public ExecutionTarget {

        Q_PROPERTY( QQmlListProperty<SingleExecutionTarget> executionTargets READ
                        getExecutionTargets CONSTANT )

      public:
        explicit GroupExecutionTarget( const QUuid& uuid,
                                       const QString& name,
                                       const Type type,
                                       const QList<SingleExecutionTarget*>& executionTargets,
                                       QObject* parent = nullptr )
            : ExecutionTarget( uuid, name, type, parent ), _executionTargets( executionTargets ) {
            for ( auto executionTarget : this->_executionTargets ) {
                executionTarget->setParent( this );
            }
        }

        QQmlListProperty<SingleExecutionTarget> getExecutionTargets() {
            return QQmlListProperty<SingleExecutionTarget>( this, &this->_executionTargets );
        }

        auto executionTargets() const {
            return this->_executionTargets;
        }

      private:
        QList<SingleExecutionTarget*> _executionTargets;
    };
} // namespace Editor::Models