#include "ProfileView.hpp"

namespace Editor::Models {
    void ProfileView::setMode( const Mode mode ) {
        if ( this->mode != mode ) {
            this->mode = mode;
            emit this->modeChanged();
            emit this->editedChanged( this->mode != this->_savedMode );
        }
    }

    void ProfileView::setPosition( const Position position ) {
        if ( this->position != position ) {
            this->position = position;
            emit this->positionChanged();
            emit this->editedChanged( this->position != this->_savedPosition );
        }
    }

    void ProfileView::setOffset( const qsizetype offset ) {
        if ( this->offset != offset ) {
            this->offset = offset;
            emit this->offsetChanged();
            emit this->editedChanged( this->offset != this->_savedOffset );
        }
    }

    void ProfileView::setWrapMode( const WrapMode wrapMode ) {
        if ( this->wrapMode != wrapMode ) {
            this->wrapMode = wrapMode;
            emit this->wrapModeChanged();
            emit this->editedChanged( this->wrapMode != this->_savedWrapMode );
        }
    }

    void ProfileView::setFlowDirection( const FlowDirection flowDirection ) {
        if ( this->flowDirection != flowDirection ) {
            this->flowDirection = flowDirection;
            emit this->flowDirectionChanged();
            emit this->editedChanged( this->flowDirection != this->_savedFlowDirection );
        }
    }

    bool ProfileView::isEdited() {
        return this->mode != this->_savedMode || this->position != this->_savedPosition ||
               this->offset != this->_savedOffset || this->wrapMode != this->_savedWrapMode ||
               this->flowDirection != this->_savedFlowDirection;
    }

    void ProfileView::saveEdited() {
        this->_savedMode = this->mode;
        this->_savedPosition = this->position;
        this->_savedOffset = this->offset;
        this->_savedWrapMode = this->wrapMode;
        this->_savedFlowDirection = this->flowDirection;
    }
} // namespace Editor::Models