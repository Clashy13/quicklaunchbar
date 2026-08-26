#include "ExecutableFileExecutionTarget.hpp"

namespace Editor::Models {

    void ExecutableFileExecutionTarget::setFilePath( const QString& filePath ) {
        if ( this->_filePath != filePath ) {
            this->_filePath = filePath;
            emit this->filePathChanged();
            emit this->editedChanged( this->_filePath != this->_savedFilePath );
        }
    }

    void ExecutableFileExecutionTarget::setArguments( const QString& arguments ) {
        if ( this->_arguments != arguments ) {
            this->_arguments = arguments;
            emit this->argumentsChanged();
            emit this->editedChanged( this->_arguments != this->_savedArguments );
        }
    }

    void ExecutableFileExecutionTarget::setIconFilePath( const QString& iconFilePath ) {
        if ( this->_iconFilePath != iconFilePath ) {
            this->_iconFilePath = iconFilePath;
            emit this->iconFilePathChanged();
            emit this->editedChanged( this->_iconFilePath != this->_savedIconFilePath );
        }
    }

    bool ExecutableFileExecutionTarget::isEdited() {
        return ExecutionTarget::isEdited() || this->_filePath != this->_savedFilePath ||
               this->_arguments != this->_savedArguments ||
               this->_iconFilePath != this->_savedIconFilePath;
    }

    void ExecutableFileExecutionTarget::saveEdited() {
        ExecutionTarget::saveEdited();
        this->_savedFilePath = this->_filePath;
        this->_savedArguments = this->_arguments;
        this->_savedIconFilePath = this->_iconFilePath;
    }
} // namespace Editor::Models