#pragma once

#include "ListModel.hpp"
#include "Profile.hpp"

#include <qtmetamacros.h>
#include <qtypes.h>

namespace Editor::Models {

    class ProfileListModel : public ListModel<Profile> {
        Q_OBJECT

      public:
        explicit ProfileListModel( const QList<Profile*>& profiles, QObject* parent = nullptr )
            : ListModel( profiles, parent ) {}

        Q_INVOKABLE Profile* itemAt( const qsizetype index ) const {
            return this->_items.at( index );
        }

        void setItems( const QList<Profile*>& profiles ) {
            this->beginResetModel();
            this->_items = profiles;
            this->endResetModel();
            for ( const auto& profile : profiles ) {
                QObject::connect( profile,
                                  &Profile::editedChanged,
                                  this,
                                  &ListModelBase::emitEditedChanged );
            }
            emit this->editedChanged( true );
        }

        Q_INVOKABLE void addItem( Profile* item ) {
            ListModel<Profile>::addItem( item );
        }

        Q_INVOKABLE void removeItem( qsizetype index ) {
            ListModel<Profile>::removeItem( index );
        }
    };

} // namespace Editor::Models