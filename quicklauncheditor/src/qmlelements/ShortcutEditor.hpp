#pragma once

#include <QKeySequence>
#include <QObject>

namespace Editor::QmlElements {

    class ShortcutEditor : public QObject {

        Q_OBJECT

        Q_PROPERTY( QString sequence READ sequence WRITE setSequence NOTIFY sequenceChanged )
        Q_PROPERTY( bool capturing READ capturing WRITE setCapturing NOTIFY capturingChanged )

      public:
        explicit ShortcutEditor( QObject* parent = nullptr );

        QString sequence() const;

        void setSequence( const QString& sequence );

        bool capturing() const;

        void setCapturing( bool capturing );

        Q_INVOKABLE void keyPressed( int key, int modifiers );

      signals:
        void sequenceChanged();

        void capturingChanged();

        void editingFinished();

      private:
        QKeySequence _sequence;
        bool _capturing = false;
    };
} // namespace Editor::QmlElements