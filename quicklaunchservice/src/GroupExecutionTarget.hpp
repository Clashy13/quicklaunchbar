#pragma once

#include "ExecutionTarget.hpp"

#include <QString>
#include <QUrl>

class GroupExecutionTarget : public ExecutionTarget {
    Q_OBJECT

    Q_PROPERTY( QList<QUrl> iconSources READ iconSources CONSTANT )

  public:
    struct Exec {
        QString program;
        QStringList arguments;
    };

    explicit GroupExecutionTarget( const QString& name,
                                   const QList<Exec>& execList,
                                   const QList<QUrl>& iconSources,
                                   QObject* parent = nullptr )
        : ExecutionTarget( name, ExecutionTarget::Type::Group, parent ), _execList( execList ),
          _iconSources( iconSources ) {}

    auto iconSources() const {
        return this->_iconSources;
    }

    void startProcess() override {
        for ( const Exec& exec : this->_execList ) {
            this->startSingleProcess( exec.program, exec.arguments );
        }
    }

  private:
    const QList<Exec> _execList;
    const QList<QUrl> _iconSources;
};
