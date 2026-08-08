#pragma once

#include "ExecutionTarget.hpp"
#include "ProfileView.hpp"

#include <QQmlListProperty>

namespace Editor::Models {

    class Profile : public QObject {

        Q_OBJECT

        Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged );
        Q_PROPERTY( bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged );
        Q_PROPERTY( QString shortcut READ shortcut WRITE setShortcut NOTIFY shortcutChanged );
        Q_PROPERTY( ProfileView* view READ view WRITE setView NOTIFY viewChanged );
        Q_PROPERTY(
            QQmlListProperty<ExecutionTarget> executionTargets READ getExecutionTargets CONSTANT )

      public:
        explicit Profile( const QUuid& uuid,
                          const QString& name,
                          const bool enabled,
                          const QString& shortcut,
                          ProfileView* view,
                          const QList<ExecutionTarget*>& executionTargets,
                          QObject* parent = nullptr )
            : QObject( parent ), _uuid( uuid ), _name( name ), _enabled( enabled ),
              _shortcut( shortcut ), _view( view ), _executionTargets( executionTargets ) {
            this->_view->setParent( this );
            for ( auto executionTarget : this->_executionTargets ) {
                executionTarget->setParent( this );
            }
        }

        auto uuid() const {
            return this->_uuid;
        }

        auto name() const {
            return this->_name;
        }

        void setName( const QString& name ) {
            this->_name = name;
            emit this->nameChanged();
        }

        auto enabled() const {
            return this->_enabled;
        }

        void setEnabled( const bool enabled ) {
            this->_enabled = enabled;
            emit this->enabledChanged();
        }

        auto shortcut() const {
            return this->_shortcut;
        }

        void setShortcut( const QString& shortcut ) {
            this->_shortcut = shortcut;
            emit this->shortcutChanged();
        }

        auto view() const {
            return this->_view;
        }

        void setView( ProfileView* view ) {
            this->_view = view;
            emit this->viewChanged();
        }

        QQmlListProperty<ExecutionTarget> getExecutionTargets() {
            return QQmlListProperty<ExecutionTarget>( this, &this->_executionTargets );
        }

        auto executionTargets() const {
            return this->_executionTargets;
        }

      signals:
        void nameChanged();
        void enabledChanged();
        void shortcutChanged();
        void viewChanged();

      private:
        QUuid _uuid;
        QString _name;
        bool _enabled;
        QString _shortcut;
        ProfileView* _view;
        QList<ExecutionTarget*> _executionTargets;
    };
} // namespace Editor::Models
