#include "ProfileListModel.hpp"

namespace Editor::Models {

    ProfileListModel::ProfileListModel( const QList<Profile*>& profiles, QObject* parent )
        : ListModel( profiles, parent ) {
        this->_uuidList.reserve( profiles.size() );
        for ( const auto& profile : profiles ) {
            this->_uuidList.push_back( profile->uuid() );
            this->connect( profile, &Profile::editedChanged, this, [ this ]( const bool edited ) {
                emit this->editedChanged( edited );
            } );
        }
    }

    void ProfileListModel::setItems( const QList<Profile*>& profiles ) {
        this->beginResetModel();
        this->_items = profiles;
        this->endResetModel();
        for ( const auto& profile : profiles ) {
            this->connect( profile, &Profile::editedChanged, this, [ this ]( const bool edited ) {
                emit this->editedChanged( edited );
            } );
        }
        emit this->editedChanged( true );
    }

    void ProfileListModel::removeItem( qsizetype index ) {
        ListModel<Profile>::removeItem( index );

        if ( this->_items.size() != this->_uuidList.size() ) {
            emit this->editedChanged( true );
            return;
        }

        for ( qsizetype i = 0; i < this->_items.size(); ++i ) {
            if ( this->_items.at( i )->uuid() != this->_uuidList.at( i ) ) {
                emit this->editedChanged( true );
                return;
            }
        }

        emit this->editedChanged( false );
    }

    bool ProfileListModel::isEdited() const {
        if ( this->_items.size() != this->_uuidList.size() ) {
            return true;
        }

        for ( qsizetype i = 0; i < this->_items.size(); ++i ) {
            if ( this->_items.at( i )->uuid() != this->_uuidList.at( i ) ) {
                return true;
            }
        }

        for ( qsizetype i = 0; i < this->_items.size(); ++i ) {
            if ( this->_items.at( i )->isEdited() ) {
                return true;
            }
        }

        return false;
    }

    void ProfileListModel::saveEdited() {
        this->_uuidList.clear();
        this->_uuidList.reserve( this->_items.size() );
        for ( const auto& profile : this->_items ) {
            this->_uuidList.push_back( profile->uuid() );
        }
    }
} // namespace Editor::Models