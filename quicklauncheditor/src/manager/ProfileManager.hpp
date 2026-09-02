#pragma once

#include "../models/ProfileListModel.hpp"
// #include "../models/Profile.hpp"

#include <QObject>
#include <qtmetamacros.h>

namespace Editor::Manager {

    class ProfileManager : public QObject {
        Q_OBJECT

        Q_PROPERTY( Models::ProfileListModel* profiles READ profiles NOTIFY profilesChanged )
        Q_PROPERTY(
            Models::Profile* currentProfile READ currentProfile NOTIFY currentProfileChanged )
        Q_PROPERTY( qsizetype currentProfileIndex READ currentProfileIndex WRITE
                        setCurrentProfileIndex NOTIFY currentProfileIndexChanged )
        Q_PROPERTY( bool edited READ edited NOTIFY editedChanged )

      public:
        static ProfileManager* instance();

        auto profiles() {
            return &this->_profiles;
        }

        Models::Profile* currentProfile();

        qsizetype currentProfileIndex();

        void setCurrentProfileIndex( const qsizetype index );

        Q_INVOKABLE void addProfile( const QString& name );

        Q_INVOKABLE void removeCurrentProfile();

        auto edited() const {
            return this->_edited;
        }

        void setEdited( const bool edited ) {
            if ( this->_edited != edited ) {
                this->_edited = edited;
                emit this->editedChanged();
            }
        }

        Q_INVOKABLE void save();

        Q_INVOKABLE void discardEdited();

      signals:
        void profilesChanged();
        void currentProfileIndexChanged();
        void currentProfileChanged();
        void editedChanged();

      private:
        explicit ProfileManager( QObject* parent = nullptr );

        void changeEdited( const bool edited );

        bool isEdited() const;

        void saveEdited();

        Models::ProfileListModel _profiles;
        qsizetype _currentProfileIndex = 0;
        bool _edited = false;
    };
} // namespace Editor::Manager
