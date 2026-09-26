#pragma once

#include "UuidModel.hpp"
#include "shared/models/ExecutionTargetType.hpp"

#include <QObject>
#include <QUuid>

namespace Editor::Models {

    class ExecutionTarget : public UuidModel {

        Q_OBJECT

        Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged );
        Q_PROPERTY( Type type READ type CONSTANT );
        Q_PROPERTY( bool collapsed READ collapsed WRITE setCollapsed NOTIFY collapsedChanged );

      public:
        using Type = Shared::Models::ExecutionTarget::Type;
        Q_ENUM( Type );

        explicit ExecutionTarget( const QUuid& uuid,
                                  const QString& name,
                                  const Type type,
                                  QObject* parent )
            : UuidModel( uuid, parent ), _name( name ), _type( type ), _savedName( name ) {}

        virtual ~ExecutionTarget() = 0;

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

        auto collapsed() const {
            return this->_collapsed;
        }

        void setCollapsed( const bool collapsed ) {
            this->_collapsed = collapsed;
            emit this->collapsedChanged();
        }

        virtual bool isEdited() const override {
            return this->_name != this->_savedName;
        }

        virtual void saveEdited() override {
            this->_savedName = this->_name;
        }

      signals:
        void nameChanged();
        void collapsedChanged();
        void editedChanged( const bool edited );

      private:
        QString _name;
        Type _type;
        bool _collapsed = false;
        QString _savedName;
    };

    inline ExecutionTarget::~ExecutionTarget() = default;

} // namespace Editor::Models