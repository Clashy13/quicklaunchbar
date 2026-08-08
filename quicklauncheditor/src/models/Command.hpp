#pragma once

#include "shared/models/Command.hpp"

#include <QObject>

namespace Editor::Models {

    class Command : public QObject, public Shared::Models::ExecutionTarget::Command {

        Q_OBJECT

        Q_PROPERTY( QString program READ getProgram WRITE setProgram NOTIFY programChanged )
        Q_PROPERTY(
            QStringList arguments READ getArguments WRITE setArguments NOTIFY argumentsChanged )

      public:
        explicit Command( const QString& program,
                          const QStringList& arguments,
                          QObject* parent = nullptr )
            : QObject( parent ), Shared::Models::ExecutionTarget::Command( program, arguments ) {}

        auto getProgram() {
            return this->program;
        }

        void setProgram( const QString& program ) {
            this->program = program;
            emit this->programChanged();
        }

        auto getArguments() {
            return this->arguments;
        }

        void setArguments( const QStringList& arguments ) {
            this->arguments = arguments;
            emit this->argumentsChanged();
        }

      signals:
        void programChanged();
        void argumentsChanged();
    };
} // namespace Editor::Models