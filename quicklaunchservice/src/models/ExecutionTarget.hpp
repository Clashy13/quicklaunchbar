#pragma once

#include "shared/models/Command.hpp"
#include "shared/models/ExecutionTarget.hpp"
#include "shared/models/Uri.hpp"

#include <QObject>
#include <QUuid>

namespace Service::Models {

    class ExecutionTarget : public QObject {
        Q_OBJECT

        Q_PROPERTY( QString name READ name CONSTANT )
        Q_PROPERTY( QList<QUrl> iconSources READ iconSources CONSTANT )

        using Command = Shared::Models::ExecutionTarget::Command;
        using Uri = Shared::Models::ExecutionTarget::Uri;
        using Type = Shared::Models::ExecutionTarget::ExecutionTarget::Type;

      public:
        explicit ExecutionTarget( const QUuid& uuid,
                                  const QString& name,
                                  const Type type,
                                  const QList<QUrl>& iconSources,
                                  const QList<Command>& commands,
                                  const QList<QUrl>& uriList,
                                  QObject* parent = nullptr )
            : QObject( parent ), _uuid( uuid ), _name( name ), _type( type ),
              _iconSources( iconSources ), _commands( commands ), _uriList( uriList ) {}

        auto uuid() const {
            return this->_uuid;
        }

        auto name() const {
            return this->_name;
        }

        auto type() const {
            return this->_type;
        }

        auto iconSources() const {
            return this->_iconSources;
        }

        auto commands() const {
            return this->_commands;
        }

        auto uriList() const {
            return this->_uriList;
        }

      private:
        QUuid _uuid;
        QString _name;
        Type _type;
        QList<QUrl> _iconSources;
        QList<Command> _commands;
        QList<QUrl> _uriList;
    };
} // namespace Service::Models