#pragma once

#include "ExecutionTarget.hpp"

#include <QString>
#include <QUrl>

class SingleExecutionTarget : public ExecutionTarget {
    Q_OBJECT

    Q_PROPERTY( QUrl iconSource READ iconSource CONSTANT )

  public:
    explicit SingleExecutionTarget( const QString& name,
                                    const QString& program,
                                    const QStringList& arguments,
                                    const QUrl& iconSource,
                                    QObject* parent = nullptr )
        : ExecutionTarget( name, ExecutionTarget::Type::Single, parent ), _program( program ),
          _arguments( arguments ), _iconSource( iconSource ) {}

    auto iconSource() const {
        return this->_iconSource;
    }

    auto program() const {
        return this->_program;
    }

    auto arguments() const {
        return this->_arguments;
    }

    void startProcess() override {
        this->startSingleProcess( this->_program, this->_arguments );
    }

  private:
    const QString _program;
    const QStringList _arguments;
    const QUrl _iconSource;
};
