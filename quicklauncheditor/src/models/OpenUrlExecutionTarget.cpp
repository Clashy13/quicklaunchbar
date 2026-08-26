#include "OpenUrlExecutionTarget.hpp"

namespace Editor::Models {

    void OpenUrlExecutionTarget::setUrl( const QUrl& url ) {
        if ( this->_url != url ) {
            this->_url = url;
            emit this->urlChanged();
            emit this->editedChanged( this->_url != this->_savedUrl );
        }
    }

    void OpenUrlExecutionTarget::setIconFilePath( const QString& iconFilePath ) {
        if ( this->_iconFilePath != iconFilePath ) {
            this->_iconFilePath = iconFilePath;
            emit this->iconFilePathChanged();
            emit this->editedChanged( this->_iconFilePath != this->_savedIconFilePath );
        }
    }

    bool OpenUrlExecutionTarget::isEdited() {
        return ExecutionTarget::isEdited() || this->_url != this->_savedUrl ||
               this->_iconFilePath != this->_savedIconFilePath;
    }

    void OpenUrlExecutionTarget::saveEdited() {
        ExecutionTarget::saveEdited();
        this->_savedUrl = this->_url;
        this->_savedIconFilePath = this->_iconFilePath;
    }
} // namespace Editor::Models