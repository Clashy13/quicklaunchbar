#pragma once

#include <QObject>
#include <QUuid>

namespace Editor::Models {

    class UuidModel : public QObject {
        Q_OBJECT

      public:
        explicit UuidModel( const QUuid& uuid, QObject* parent = nullptr )
            : QObject( parent ), _uuid( uuid ) {}

        auto uuid() const {
            return this->_uuid;
        }

        virtual bool isEdited() const = 0;

        virtual void saveEdited() = 0;

      signals:
        void editedChanged( const bool edited );

      private:
        QUuid _uuid;
    };

} // namespace Editor::Models