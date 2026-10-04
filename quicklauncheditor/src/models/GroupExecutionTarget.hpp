#pragma once

#include "SingleExecutionTarget.hpp"
#include "SingleExecutionTargetListModel.hpp"

#include <QQmlListProperty>

namespace Editor::Models {

    class GroupExecutionTarget : public ExecutionTarget {

        Q_OBJECT

        Q_PROPERTY(
            SingleExecutionTargetListModel* executionTargets READ executionTargets CONSTANT )

      public:
        explicit GroupExecutionTarget( const QUuid& uuid,
                                       const QString& name,
                                       const Type type,
                                       const QList<SingleExecutionTarget*>& executionTargets,
                                       QObject* parent = nullptr )
            : ExecutionTarget( uuid, name, type, parent ),
              _executionTargets( executionTargets, this ) {
            this->connect( &this->_executionTargets,
                           &SingleExecutionTargetListModel::editedChanged,
                           this,
                           [ this ]( const bool edited ) { emit this->editedChanged( edited ); } );
        }

        auto executionTargets() {
            return &this->_executionTargets;
        }

        virtual GroupExecutionTarget* copy() const override {
            QList<SingleExecutionTarget*> executionTargets;
            executionTargets.reserve( this->_executionTargets.rowCount() );
            for ( auto executionTarget : this->_executionTargets.list() ) {
                executionTargets.push_back( executionTarget->copy() );
            }
            return new GroupExecutionTarget( QUuid::createUuid(),
                                             this->name(),
                                             this->type(),
                                             executionTargets,
                                             this->parent() );
        }

        virtual bool isEdited() const override {
            return ExecutionTarget::isEdited() || this->_executionTargets.isEdited();
        }

        virtual void saveEdited() override {
            ExecutionTarget::saveEdited();
            this->_executionTargets.saveEdited();
        }

      private:
        SingleExecutionTargetListModel _executionTargets;
    };
} // namespace Editor::Models