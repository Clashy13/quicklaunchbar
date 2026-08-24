#pragma once

#include <QAbstractListModel>

namespace Editor::Models {

    template <typename T> class ItemListModel : public QAbstractListModel {

      public:
        enum Roles { ItemRole = Qt::UserRole + 1 };

        explicit ItemListModel( const QList<T*>& items, QObject* parent = nullptr )
            : QAbstractListModel( parent ), _items( items ) {}

        int rowCount( const QModelIndex& parent = {} ) const override {
            if ( parent.isValid() )
                return 0;

            return this->_items.size();
        }

        QVariant data( const QModelIndex& index, int role ) const override {
            if ( !index.isValid() || index.row() < 0 || index.row() >= this->_items.size() )
                return {};

            if ( role == ItemRole )
                return QVariant::fromValue( this->_items.at( index.row() ) );

            return {};
        }

        QHash<int, QByteArray> roleNames() const override {
            return { { ItemRole, "item" } };
        }

        void addItem( T* item ) {
            const int row = this->_items.size();

            beginInsertRows( {}, row, row );
            this->_items.append( item );
            endInsertRows();
        }

        Q_INVOKABLE void removeItem( int row ) {
            if ( row < 0 || row >= this->_items.size() )
                return;

            beginRemoveRows( {}, row, row );
            this->_items.removeAt( row );
            endRemoveRows();
        }

        auto& list() const {
            return this->_items;
        }

      private:
        QList<T*> _items;
    };

} // namespace Editor::Models