#include "ShortcutEditor.hpp"

#include <QKeySequence>

namespace Editor::QmlElements {

    ShortcutEditor::ShortcutEditor( QObject* parent ) : QObject( parent ) {}

    QString ShortcutEditor::sequence() const {
        return this->_sequence.toString();
    }

    void ShortcutEditor::setSequence( const QString& sequence ) {
        const auto newSequence = QKeySequence::fromString( sequence );
        if ( this->_sequence == newSequence ) {
            return;
        }
        this->_sequence = newSequence;
        emit this->sequenceChanged();
    }

    bool ShortcutEditor::capturing() const {
        return this->_capturing;
    }

    void ShortcutEditor::setCapturing( bool capturing ) {
        if ( this->_capturing == capturing ) {
            return;
        }
        this->_capturing = capturing;
        emit capturingChanged();
    }

    void ShortcutEditor::keyPressed( int key, int modifiers ) {
        if ( key == Qt::Key_Control || key == Qt::Key_Shift || key == Qt::Key_Alt ||
             key == Qt::Key_Meta ) {
            return;
        }
        QKeySequence sequence( key | modifiers );
        this->setSequence( sequence.toString() );
        emit this->editingFinished();
    }

} // namespace Editor::QmlElements