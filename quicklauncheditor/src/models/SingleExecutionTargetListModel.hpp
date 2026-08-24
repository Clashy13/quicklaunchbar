#pragma once

#include "ItemListModel.hpp"
#include "SingleExecutionTarget.hpp"

namespace Editor::Models {

    class SingleExecutionTargetListModel : public ItemListModel<SingleExecutionTarget> {
        Q_OBJECT

      public:
        explicit SingleExecutionTargetListModel(
            const QList<SingleExecutionTarget*>& executionTargets,
            QObject* parent = nullptr )
            : ItemListModel( executionTargets, parent ) {}

        Q_INVOKABLE void addItem( SingleExecutionTarget* item ) {
            ItemListModel<SingleExecutionTarget>::addItem( item );
        }

        Q_INVOKABLE void removeItem( int row ) {
            ItemListModel<SingleExecutionTarget>::removeItem( row );
        }
    };

} // namespace Editor::Models