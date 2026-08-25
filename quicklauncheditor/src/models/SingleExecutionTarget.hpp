#pragma once

#include "ExecutionTarget.hpp"

#include <QUrl>

namespace Editor::Models {

    class SingleExecutionTarget : public ExecutionTarget {

        Q_OBJECT

      public:
        explicit SingleExecutionTarget( const QUuid& uuid,
                                        const QString& name,
                                        const Type type,
                                        QObject* parent = nullptr )
            : ExecutionTarget( uuid, name, type, parent ) {}

        virtual ~SingleExecutionTarget() = 0;
    };

    inline SingleExecutionTarget::~SingleExecutionTarget() = default;

} // namespace Editor::Models