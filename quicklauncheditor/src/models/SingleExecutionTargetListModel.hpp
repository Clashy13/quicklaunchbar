#pragma once

#include "../manager/ExecutionTargetManager.hpp"
#include "ListModel.hpp"
#include "SingleExecutionTarget.hpp"
#include "shared/models/ExecutionTargetType.hpp"

namespace Editor::Models {

    class SingleExecutionTargetListModel : public ListModel<SingleExecutionTarget> {
        Q_OBJECT

      public:
        explicit SingleExecutionTargetListModel(
            const QList<SingleExecutionTarget*>& executionTargets,
            QObject* parent = nullptr )
            : ListModel( executionTargets, parent ) {}

        Q_INVOKABLE SingleExecutionTarget* itemAt( const qsizetype index ) const {
            return this->_items.at( index );
        }

        Q_INVOKABLE void addItem( SingleExecutionTarget* item ) {
            ListModel<SingleExecutionTarget>::addItem( item );
        }

        Q_INVOKABLE void removeItem( qsizetype index ) {
            ListModel<SingleExecutionTarget>::removeItem( index );
        }

        Q_INVOKABLE void moveItem( const qsizetype from, const qsizetype to ) {
            ListModel<SingleExecutionTarget>::moveItem( from, to );
        }

        Q_INVOKABLE void insertItem( const qsizetype index, SingleExecutionTarget* item ) {
            ListModel<SingleExecutionTarget>::insertItem( index, item );
        }

        Q_INVOKABLE void duplicateItem( const qsizetype index ) {
            if ( index < 0 || index > this->_items.size() ) {
                return;
            }

            if ( index == this->_items.size() - 1 ) {
                this->addItem( this->_items.at( index )->copy() );
            } else {
                this->insertItem( index + 1, this->_items.at( index )->copy() );
            }
        }

        Q_INVOKABLE void pasteFromClipboard() {
            if ( const auto executionTarget =
                     Manager::ExecutionTargetManager::instance()->executionTargetFromClipboard() ) {
                if ( executionTarget.value()->type() ==
                     Shared::Models::ExecutionTarget::Type::Group ) {
                    return;
                }
                Manager::ExecutionTargetManager::instance()->renewExecutionTargetUuid(
                    *executionTarget );
                this->addItem( dynamic_cast<SingleExecutionTarget*>( *executionTarget ) );
            }
        }
    };

} // namespace Editor::Models