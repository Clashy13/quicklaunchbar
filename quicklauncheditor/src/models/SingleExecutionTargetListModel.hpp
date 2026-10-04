#pragma once

#include "ListModel.hpp"
#include "SingleExecutionTarget.hpp"

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
    };

} // namespace Editor::Models