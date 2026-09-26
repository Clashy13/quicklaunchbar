#pragma once

#include "ExecutionTarget.hpp"
#include "ExecutionTargetListModel.hpp"
#include "ProfileView.hpp"
#include "UuidModel.hpp"

#include <QQmlListProperty>

namespace Editor::Models {

    class Profile : public UuidModel {

        Q_OBJECT

        Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged );
        Q_PROPERTY( bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged );
        Q_PROPERTY( QString shortcut READ shortcut WRITE setShortcut NOTIFY shortcutChanged );
        Q_PROPERTY( ProfileView* view READ view CONSTANT );
        Q_PROPERTY( ExecutionTargetListModel* executionTargets READ executionTargets CONSTANT )

      public:
        explicit Profile( const QUuid& uuid,
                          const QString& name,
                          const bool enabled,
                          const QString& shortcut,
                          ProfileView* view,
                          const QList<ExecutionTarget*>& executionTargets,
                          QObject* parent = nullptr );

        auto name() const {
            return this->_name;
        }

        void setName( const QString& name );

        auto enabled() const {
            return this->_enabled;
        }

        void setEnabled( const bool enabled );

        auto shortcut() const {
            return this->_shortcut;
        }

        void setShortcut( const QString& shortcut );

        auto view() const {
            return this->_view;
        }

        auto executionTargets() {
            return &this->_executionTargets;
        }

        virtual bool isEdited() const override;

        virtual void saveEdited() override;

      signals:
        void nameChanged();
        void enabledChanged();
        void shortcutChanged();
        void editedChanged( const bool edited );

      private:
        QString _name;
        bool _enabled;
        QString _shortcut;
        ProfileView* _view;
        ExecutionTargetListModel _executionTargets;

        QString _savedName;
        bool _savedEnabled;
        QString _savedShortcut;
    };
} // namespace Editor::Models
