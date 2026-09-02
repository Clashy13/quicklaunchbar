#include "ProfileManager.hpp"

#include "../serializer/ProfileConfigSerializer.hpp"

namespace Editor::Manager {
    ProfileManager::ProfileManager( QObject* parent )
        : QObject( parent ),
          _profiles( Editor::Serializer::ProfileConfigSerializer::load(), this ) {
        this->connect( &this->_profiles,
                       &Models::ProfileListModel::editedChanged,
                       this,
                       &ProfileManager::changeEdited );
    }

    ProfileManager* ProfileManager::instance() {
        static ProfileManager profileManager;
        return &profileManager;
    }

    Models::Profile* ProfileManager::currentProfile() {
        if ( this->_currentProfileIndex < 0 ||
             this->_currentProfileIndex >= this->_profiles.rowCount() ) {
            return nullptr;
        }
        return this->_profiles.itemAt( this->_currentProfileIndex );
    }

    qsizetype ProfileManager::currentProfileIndex() {
        return this->_currentProfileIndex;
    }

    void ProfileManager::setCurrentProfileIndex( const qsizetype index ) {
        if ( this->_currentProfileIndex != index ) {
            this->_currentProfileIndex = index;
            emit this->currentProfileIndexChanged();
            emit this->currentProfileChanged();
        }
    }

    void ProfileManager::addProfile( const QString& name ) {
        using View = Models::ProfileView;
        this->_profiles.addItem( new Models::Profile( QUuid::createUuid(),
                                                      name,
                                                      true,
                                                      "",
                                                      new View( View::Mode::Icon,
                                                                View::Position::Center,
                                                                0,
                                                                View::WrapMode::Scroll,
                                                                View::FlowDirection::Right ),
                                                      {} ) );
        this->setCurrentProfileIndex( this->_profiles.rowCount() - 1 );
        emit this->profilesChanged();
        this->setEdited( true );
    }

    void ProfileManager::removeCurrentProfile() {
        const auto index = this->_currentProfileIndex;
        const auto lastIndex = this->_currentProfileIndex == this->_profiles.rowCount() - 1;
        this->_profiles.removeItem( index );
        if ( lastIndex ) {
            this->setCurrentProfileIndex( this->_currentProfileIndex - 1 );
        } else {
            emit this->currentProfileChanged();
        }
        emit this->profilesChanged();
        this->setEdited( true );
    }

    void ProfileManager::changeEdited( const bool edited ) {
        if ( edited ) {
            this->setEdited( true );
        } else {
            if ( this->isEdited() ) {
                this->setEdited( true );
            } else {
                this->setEdited( false );
            }
        }
    }

    bool ProfileManager::isEdited() const {
        for ( const auto& profile : this->_profiles.list() ) {
            if ( profile->isEdited() ) {
                return true;
            }
        }
        return false;
    }

    void ProfileManager::saveEdited() {
        for ( const auto& profile : this->_profiles.list() ) {
            profile->saveEdited();
        }
        this->setEdited( false );
    }

    void ProfileManager::save() {
        this->saveEdited();
        this->setEdited( false );
        Serializer::ProfileConfigSerializer::save( this->_profiles.list() );
    }

    void ProfileManager::discardEdited() {
        this->_profiles.setItems( Editor::Serializer::ProfileConfigSerializer::load() );
        if ( this->_currentProfileIndex >= this->_profiles.rowCount() ) {
            this->setCurrentProfileIndex( this->_profiles.rowCount() - 1 );
        } else if ( this->_currentProfileIndex == -1 && this->_profiles.rowCount() > 0 ) {
            this->setCurrentProfileIndex( 0 );
        } else {
            emit this->currentProfileChanged();
        }
        emit this->profilesChanged();
        this->setEdited( false );
    }
} // namespace Editor::Manager