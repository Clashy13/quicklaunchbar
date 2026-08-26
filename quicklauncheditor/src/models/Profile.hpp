#pragma once

#include "ExecutionTarget.hpp"
#include "ExecutionTargetListModel.hpp"
#include "ProfileView.hpp"

#include <QQmlListProperty>

namespace Editor::Models {

    class Profile : public QObject {

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

        auto uuid() const {
            return this->_uuid;
        }

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

        bool isEdited() const;

        void saveEdited();

      signals:
        void nameChanged();
        void enabledChanged();
        void shortcutChanged();
        void editedChanged( const bool edited );

      private:
        QUuid _uuid;
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
