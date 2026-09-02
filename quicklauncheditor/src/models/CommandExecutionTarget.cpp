#include "CommandExecutionTarget.hpp"

namespace Editor::Models {

    void CommandExecutionTarget::setCommand( const QString& command ) {
        if ( this->_command != command ) {
            this->_command = command;
            emit this->commandChanged();
            emit this->editedChanged( this->_command != this->_savedCommand );
        }
    }

    void CommandExecutionTarget::setIconFilePath( const QString& iconFilePath ) {
        if ( this->_iconFilePath != iconFilePath ) {
            this->_iconFilePath = iconFilePath;
            emit this->iconFilePathChanged();
            emit this->editedChanged( this->_iconFilePath != this->_savedIconFilePath );
        }
    }

    bool CommandExecutionTarget::isEdited() {
        return ExecutionTarget::isEdited() || this->_command != this->_savedCommand ||
               this->_iconFilePath != this->_savedIconFilePath;
    }

    void CommandExecutionTarget::saveEdited() {
        ExecutionTarget::saveEdited();
        this->_savedCommand = this->_command;
        this->_savedIconFilePath = this->_iconFilePath;
    }
} // namespace Editor::Models