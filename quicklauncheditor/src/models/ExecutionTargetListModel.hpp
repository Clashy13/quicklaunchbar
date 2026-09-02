#pragma once

#include "ExecutionTarget.hpp"
#include "ListModel.hpp"

#include <qtmetamacros.h>

namespace Editor::Models {

    class ExecutionTargetListModel : public ListModel<ExecutionTarget> {
        Q_OBJECT

      public:
        explicit ExecutionTargetListModel( const QList<ExecutionTarget*>& executionTargets,
                                           QObject* parent = nullptr );

        Q_INVOKABLE void addItem( ExecutionTarget* item ) {
            ListModel<ExecutionTarget>::addItem( item );
            emit this->editedChanged( true );
        }

        Q_INVOKABLE void removeItem( qsizetype index );

        bool isEdited() const;

        void saveEdited();

      signals:
        void editedChanged( const bool edited );

      private:
        QList<QUuid> _uuidList;
    };

} // namespace Editor::Models