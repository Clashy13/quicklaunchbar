#pragma once

#include "ListModelBase.hpp"
#include "UuidModel.hpp"

// #include <QAbstractListModel>

namespace Editor::Models {

    template <typename T>
        requires std::derived_from<T, UuidModel>
    class ListModel : public ListModelBase {

      public:
        enum Roles { ItemRole = Qt::UserRole + 1 };

        explicit ListModel( const QList<T*>& items, QObject* parent = nullptr )
            : ListModelBase( parent ), _items( items ) {
            this->_uuidList.reserve( items.size() );
            for ( const auto& item : items ) {
                this->_uuidList.push_back( item->uuid() );
                QObject::connect( item,
                                  &T::editedChanged,
                                  this,
                                  &ListModelBase::emitEditedChanged );
            }
        }

        T* itemAt( const qsizetype index ) const {
            return this->_items.at( index );
        }

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
            emit this->editedChanged( true );
        }

        void removeItem( qsizetype index ) {
            if ( index < 0 || index >= this->_items.size() ) {
                return;
            }

            this->beginRemoveRows( {}, index, index );
            this->_items.removeAt( index );
            this->endRemoveRows();

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

        void moveItem( const qsizetype from, const qsizetype to ) {
            if ( from < 0 || from >= this->rowCount() || to < 0 || to >= this->rowCount() ||
                 from == to ) {
                return;
            }

            if ( to > from ) {
                this->beginMoveRows( {}, from, from, {}, to + 1 );
            } else {
                this->beginMoveRows( {}, from, from, {}, to );
            }

            this->_items.move( from, to );

            this->endMoveRows();

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

        void insertItem( const qsizetype index, T* item ) {
            if ( index < 0 || index > this->_items.size() ) {
                return;
            }

            this->beginInsertRows( {}, index, index );

            this->_items.insert( index, item );

            this->endInsertRows();

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

        auto& list() const {
            return this->_items;
        }

        virtual bool isEdited() const override {
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

        virtual void saveEdited() override {
            this->_uuidList.clear();
            this->_uuidList.reserve( this->_items.size() );
            for ( const auto& profile : this->_items ) {
                this->_uuidList.push_back( profile->uuid() );
            }
        }

      protected:
        QList<T*> _items;
        QList<QUuid> _uuidList;
    };

} // namespace Editor::Models