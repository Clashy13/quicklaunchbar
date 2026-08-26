#include "SingleExecutionTargetListModel.hpp"

namespace Editor::Models {
    SingleExecutionTargetListModel::SingleExecutionTargetListModel(
        const QList<SingleExecutionTarget*>& executionTargets,
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

    void SingleExecutionTargetListModel::removeItem( int row ) {
        ListModel<SingleExecutionTarget>::removeItem( row );

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

    bool SingleExecutionTargetListModel::isEdited() const {
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

    void SingleExecutionTargetListModel::saveEdited() {
        this->_uuidList.clear();
        this->_uuidList.reserve( this->_items.size() );
        for ( const auto& executionTarget : this->_items ) {
            this->_uuidList.push_back( executionTarget->uuid() );
        }
    }
} // namespace Editor::Models