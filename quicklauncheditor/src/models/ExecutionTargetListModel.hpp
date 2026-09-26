#pragma once

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

        Q_INVOKABLE void addItem( ExecutionTarget* item ) {
            ListModel<ExecutionTarget>::addItem( item );
        }

        Q_INVOKABLE void removeItem( qsizetype index ) {
            ListModel<ExecutionTarget>::removeItem( index );
        }
    };

} // namespace Editor::Models