#include "OpenFileExecutionTarget.hpp"

namespace Editor::Models {

    void OpenFileExecutionTarget::setFilePath( const QString& filePath ) {
        if ( this->_filePath != filePath ) {
            this->_filePath = filePath;
            emit this->filePathChanged();
            emit this->editedChanged( this->_filePath != this->_savedFilePath );
        }
    }

    void OpenFileExecutionTarget::setIconFilePath( const QString& iconFilePath ) {
        if ( this->_iconFilePath != iconFilePath ) {
            this->_iconFilePath = iconFilePath;
            emit this->iconFilePathChanged();
            emit this->editedChanged( this->_iconFilePath != this->_savedIconFilePath );
        }
    }

    OpenFileExecutionTarget* OpenFileExecutionTarget::copy() const {
        return new OpenFileExecutionTarget( QUuid::createUuid(),
                                            this->name(),
                                            this->type(),
                                            this->filePath(),
                                            this->iconFilePath(),
                                            this->parent() );
    }

    bool OpenFileExecutionTarget::isEdited() const {
        return ExecutionTarget::isEdited() || this->_filePath != this->_savedFilePath ||
               this->_iconFilePath != this->_savedIconFilePath;
    }

    void OpenFileExecutionTarget::saveEdited() {
        ExecutionTarget::saveEdited();
        this->_savedFilePath = this->_filePath;
        this->_savedIconFilePath = this->_iconFilePath;
    }
} // namespace Editor::Models