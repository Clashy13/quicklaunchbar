#pragma once

#include "SingleExecutionTarget.hpp"
#include "SingleExecutionTargetListModel.hpp"

#include <QQmlListProperty>

namespace Editor::Models {

    class GroupExecutionTarget : public ExecutionTarget {

        Q_OBJECT

        Q_PROPERTY(
            SingleExecutionTargetListModel* executionTargets READ executionTargets CONSTANT )

      public:
        explicit GroupExecutionTarget( const QUuid& uuid,
                                       const QString& name,
                                       const Type type,
                                       const QList<SingleExecutionTarget*>& executionTargets,
                                       QObject* parent = nullptr )
            : ExecutionTarget( uuid, name, type, parent ),
              _executionTargets( executionTargets, this ) {}

        auto executionTargets() {
            return &this->_executionTargets;
        }

      private:
        SingleExecutionTargetListModel _executionTargets;
    };
} // namespace Editor::Models