#pragma once

#include <QAbstractListModel>
#include <QObject>

namespace Editor::Models {

    class ListModelBase : public QAbstractListModel {
        Q_OBJECT

      public:
        explicit ListModelBase( QObject* parent = nullptr ) : QAbstractListModel( parent ) {}

        virtual bool isEdited() const = 0;

        virtual void saveEdited() = 0;

        void emitEditedChanged( const bool edited ) {
            emit this->editedChanged( edited );
        }

      signals:
        void editedChanged( const bool edited );
    };

} // namespace Editor::Models