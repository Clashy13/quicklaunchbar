#pragma once

#include "../manager/ExecutionTargetManager.hpp"
#include "ExecutionTarget.hpp"
#include "ListModel.hpp"

#include <qtmetamacros.h>

namespace Editor::Models {

    class ExecutionTargetListModel : public ListModel<ExecutionTarget> {
        Q_OBJECT

      public:
        explicit ExecutionTargetListModel( const QList<ExecutionTarget*>& executionTargets,
                                           QObject* parent = nullptr )
            : ListModel( executionTargets, parent ) {}

        Q_INVOKABLE ExecutionTarget* itemAt( const qsizetype index ) const {
            return this->_items.at( index );
        }

        Q_INVOKABLE void addItem( ExecutionTarget* item ) {
            ListModel<ExecutionTarget>::addItem( item );
        }

        Q_INVOKABLE void removeItem( qsizetype index ) {
            ListModel<ExecutionTarget>::removeItem( index );
        }

        Q_INVOKABLE void moveItem( const qsizetype from, const qsizetype to ) {
            ListModel<ExecutionTarget>::moveItem( from, to );
        }

        Q_INVOKABLE void insertItem( const qsizetype index, ExecutionTarget* item ) {
            ListModel<ExecutionTarget>::insertItem( index, item );
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
                Manager::ExecutionTargetManager::instance()->renewExecutionTargetUuid(
                    *executionTarget );
                this->addItem( *executionTarget );
            }
        }
    };

} // namespace Editor::Models