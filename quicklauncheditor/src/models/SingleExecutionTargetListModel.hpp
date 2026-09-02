#pragma once

#include "ListModel.hpp"
#include "SingleExecutionTarget.hpp"

namespace Editor::Models {

    class SingleExecutionTargetListModel : public ListModel<SingleExecutionTarget> {
        Q_OBJECT

      public:
        explicit SingleExecutionTargetListModel(
            const QList<SingleExecutionTarget*>& executionTargets,
            QObject* parent = nullptr );

        Q_INVOKABLE void addItem( SingleExecutionTarget* item ) {
            ListModel<SingleExecutionTarget>::addItem( item );
            emit this->editedChanged( true );
        }

        Q_INVOKABLE void removeItem( int row );

        bool isEdited() const;

        void saveEdited();

      signals:
        void editedChanged( const bool edited );

      private:
        QList<QUuid> _uuidList;
    };

} // namespace Editor::Models