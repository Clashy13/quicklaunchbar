#pragma once

#include "ListModel.hpp"
#include "Profile.hpp"

#include <qtmetamacros.h>
#include <qtypes.h>

namespace Editor::Models {

    class ProfileListModel : public ListModel<Profile> {
        Q_OBJECT

      public:
        explicit ProfileListModel( const QList<Profile*>& profiles, QObject* parent = nullptr );

        Q_INVOKABLE Profile* itemAt( const qsizetype index ) const {
            return this->_items.at( index );
        }

        void setItems( const QList<Profile*>& profiles );

        Q_INVOKABLE void addItem( Profile* item ) {
            ListModel<Profile>::addItem( item );
            emit this->editedChanged( true );
        }

        Q_INVOKABLE void removeItem( qsizetype index );

        bool isEdited() const;

        void saveEdited();

      signals:
        void editedChanged( const bool edited );

      private:
        QList<QUuid> _uuidList;
    };

} // namespace Editor::Models