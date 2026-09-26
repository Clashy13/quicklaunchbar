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

        Q_INVOKABLE void removeItem( qsizetype index ) {
            ListModel<SingleExecutionTarget>::removeItem( index );
        }
    };

} // namespace Editor::Models