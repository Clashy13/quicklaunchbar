#include "DesktopApplicationExecutionTarget.hpp"

namespace Editor::Models {

    void DesktopApplicationExecutionTarget::setCommand( const QString& command ) {
        if ( this->_command != command ) {
            this->_command = command;
            emit this->commandChanged();
            emit this->editedChanged( this->_command != this->_savedCommand );
        }
    }

    void DesktopApplicationExecutionTarget::setIconSource( const IconSource& iconSource ) {
        if ( this->_iconSource != iconSource ) {
            this->_iconSource = iconSource;
            this->_iconUrl =
                Shared::Serializer::IconSourceSerializer::iconSourceToUrl( iconSource );
            emit this->iconUrlChanged();
            emit this->editedChanged( this->_iconSource != this->_savedIconSource );
        }
    }

    DesktopApplicationExecutionTarget* DesktopApplicationExecutionTarget::copy() const {
        const IconSource iconSource( this->iconSource().type, this->iconSource().value );
        return new DesktopApplicationExecutionTarget( QUuid::createUuid(),
                                                      this->name(),
                                                      this->type(),
                                                      iconSource,
                                                      this->command(),
                                                      this->parent() );
    }

    bool DesktopApplicationExecutionTarget::isEdited() const {
        return ExecutionTarget::isEdited() || this->_command != this->_savedCommand ||
               this->_iconSource != this->_savedIconSource;
    }

    void DesktopApplicationExecutionTarget::saveEdited() {
        ExecutionTarget::saveEdited();
        this->_savedCommand = this->_command;
        this->_savedIconSource = this->_iconSource;
    }
} // namespace Editor::Models