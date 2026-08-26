#pragma once

#include <QAbstractListModel>

namespace Editor::Models {

    template <typename T> class ListModel : public QAbstractListModel {

      public:
        enum Roles { ItemRole = Qt::UserRole + 1 };

        explicit ListModel( const QList<T*>& items, QObject* parent = nullptr )
            : QAbstractListModel( parent ), _items( items ) {}

        int rowCount( const QModelIndex& parent = {} ) const override {
            if ( parent.isValid() ) {
                return 0;
            } else {
                return this->_items.size();
            }
        }

        QVariant data( const QModelIndex& index, int role ) const override {
            if ( !index.isValid() || index.row() < 0 || index.row() >= this->_items.size() ) {
                return {};
            }

            if ( role == ItemRole ) {
                return QVariant::fromValue( this->_items.at( index.row() ) );
            }

            return {};
        }

        QHash<int, QByteArray> roleNames() const override {
            return { { ItemRole, "item" } };
        }

        void addItem( T* item ) {
            const int row = this->_items.size();
            this->beginInsertRows( {}, row, row );
            this->_items.append( item );
            this->endInsertRows();
        }

        Q_INVOKABLE void removeItem( qsizetype index ) {
            if ( index < 0 || index >= this->_items.size() ) {
                return;
            }

            this->beginRemoveRows( {}, index, index );
            this->_items.removeAt( index );
            this->endRemoveRows();
        }

        auto& list() const {
            return this->_items;
        }

      protected:
        QList<T*> _items;
    };

} // namespace Editor::Models