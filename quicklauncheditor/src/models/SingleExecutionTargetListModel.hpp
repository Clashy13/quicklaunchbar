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

        Q_INVOKABLE void addItem( SingleExecutionTarget* item ) {
            ListModel<SingleExecutionTarget>::addItem( item );
        }

        Q_INVOKABLE void removeItem( int row ) {
            ListModel<SingleExecutionTarget>::removeItem( row );
        }
    };

} // namespace Editor::Models