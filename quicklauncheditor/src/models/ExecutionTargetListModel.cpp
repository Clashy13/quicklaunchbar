#include "ExecutionTargetListModel.hpp"

namespace Editor::Models {

    ExecutionTargetListModel::ExecutionTargetListModel(
        const QList<ExecutionTarget*>& executionTargets,
        QObject* parent )
        : ListModel( executionTargets, parent ) {
        this->_uuidList.reserve( executionTargets.size() );
        for ( const auto& executionTarget : executionTargets ) {
            this->_uuidList.push_back( executionTarget->uuid() );
            this->connect( executionTarget,
                           &ExecutionTarget::editedChanged,
                           this,
                           [ this ]( const bool edited ) { emit this->editedChanged( edited ); } );
        }
    }

    void ExecutionTargetListModel::removeItem( qsizetype index ) {
        ListModel<ExecutionTarget>::removeItem( index );

        if ( this->_items.size() != this->_uuidList.size() ) {
            emit this->editedChanged( true );
            return;
        }

        for ( qsizetype i = 0; i < this->_items.size(); ++i ) {
            if ( this->_items.at( i )->uuid() != this->_uuidList.at( i ) ) {
                emit this->editedChanged( true );
                return;
            }
        }

        emit this->editedChanged( false );
    }

    bool ExecutionTargetListModel::isEdited() const {
        if ( this->_items.size() != this->_uuidList.size() ) {
            return true;
        }

        for ( qsizetype i = 0; i < this->_items.size(); ++i ) {
            if ( this->_items.at( i )->uuid() != this->_uuidList.at( i ) ) {
                return true;
            }
        }

        for ( qsizetype i = 0; i < this->_items.size(); ++i ) {
            if ( this->_items.at( i )->isEdited() ) {
                return true;
            }
        }

        return false;
    }

    void ExecutionTargetListModel::saveEdited() {
        this->_uuidList.clear();
        this->_uuidList.reserve( this->_items.size() );
        for ( const auto& executionTarget : this->_items ) {
            executionTarget->saveEdited();
            this->_uuidList.push_back( executionTarget->uuid() );
        }
    }
} // namespace Editor::Models