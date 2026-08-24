#pragma once

#include "ExecutionTarget.hpp"
#include "ItemListModel.hpp"

#include <qtmetamacros.h>

namespace Editor::Models {

    class ExecutionTargetListModel : public ItemListModel<ExecutionTarget> {
        Q_OBJECT

      public:
        explicit ExecutionTargetListModel( const QList<ExecutionTarget*>& executionTargets,
                                           QObject* parent = nullptr )
            : ItemListModel( executionTargets, parent ) {}

        Q_INVOKABLE void addItem( ExecutionTarget* item ) {
            ItemListModel<ExecutionTarget>::addItem( item );
        }

        Q_INVOKABLE void removeItem( int row ) {
            ItemListModel<ExecutionTarget>::removeItem( row );
        }
    };

} // namespace Editor::Models