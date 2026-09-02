#pragma once

#include "shared/models/ExecutionTargetType.hpp"

#include <QObject>
#include <QUuid>

namespace Editor::Models {

    class ExecutionTarget : public QObject {

        Q_OBJECT

        Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged );
        Q_PROPERTY( Type type READ type CONSTANT );

      public:
        using Type = Shared::Models::ExecutionTarget::Type;
        Q_ENUM( Type );

        explicit ExecutionTarget( const QUuid& uuid,
                                  const QString& name,
                                  const Type type,
                                  QObject* parent )
            : QObject( parent ), _uuid( uuid ), _name( name ), _type( type ), _savedName( name ) {}

        virtual ~ExecutionTarget() = 0;

        auto uuid() const {
            return this->_uuid;
        }

        auto name() const {
            return this->_name;
        }

        void setName( const QString& name ) {
            if ( this->_name != name ) {
                this->_name = name;
                emit this->nameChanged();
                emit this->editedChanged( this->_name != this->_savedName );
            }
        }

        auto type() const {
            return this->_type;
        }

        virtual bool isEdited() {
            return this->_name != this->_savedName;
        }

        virtual void saveEdited() {
            this->_savedName = this->_name;
        }

      signals:
        void nameChanged();
        void editedChanged( const bool edited );

      private:
        QUuid _uuid;
        QString _name;
        Type _type;
        QString _savedName;
    };

    inline ExecutionTarget::~ExecutionTarget() = default;

} // namespace Editor::Models