#include "Profile.hpp"

namespace Editor::Models {
    Profile::Profile( const QUuid& uuid,
                      const QString& name,
                      const bool enabled,
                      const QString& shortcut,
                      ProfileView* view,
                      const QList<ExecutionTarget*>& executionTargets,
                      QObject* parent )
        : QObject( parent ), _uuid( uuid ), _name( name ), _enabled( enabled ),
          _shortcut( shortcut ), _view( view ), _executionTargets( executionTargets, this ),
          _savedName( name ), _savedEnabled( enabled ), _savedShortcut( shortcut ) {
        this->_view->setParent( this );
        this->connect( &this->_executionTargets,
                       &ExecutionTargetListModel::editedChanged,
                       this,
                       [ this ]( const bool edited ) { emit this->editedChanged( edited ); } );
        this->connect( this->_view,
                       &ProfileView::editedChanged,
                       this,
                       [ this ]( const bool edited ) { emit this->editedChanged( edited ); } );
    }

    void Profile::setName( const QString& name ) {
        if ( this->_name != name ) {
            this->_name = name;
            emit this->nameChanged();
            emit this->editedChanged( this->_name != this->_savedName );
        }
    }

    void Profile::setEnabled( const bool enabled ) {
        if ( this->_enabled != enabled ) {
            this->_enabled = enabled;
            emit this->enabledChanged();
            emit this->editedChanged( this->_enabled != this->_savedEnabled );
        }
    }

    void Profile::setShortcut( const QString& shortcut ) {
        if ( this->_shortcut != shortcut ) {
            this->_shortcut = shortcut;
            emit this->shortcutChanged();
            emit this->editedChanged( this->_shortcut != this->_savedShortcut );
        }
    }

    bool Profile::isEdited() const {
        return this->_name != this->_savedName || this->_enabled != this->_savedEnabled ||
               this->_shortcut != this->_savedShortcut || this->_view->isEdited() ||
               this->_executionTargets.isEdited();
    }

    void Profile::saveEdited() {
        this->_savedName = this->_name;
        this->_savedEnabled = this->_enabled;
        this->_savedShortcut = this->_shortcut;
        this->_view->saveEdited();
        this->_executionTargets.saveEdited();
    }
} // namespace Editor::Models