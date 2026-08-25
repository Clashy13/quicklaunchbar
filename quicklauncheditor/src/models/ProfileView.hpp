#pragma once

#include "shared/models/ProfileView.hpp"

#include <QObject>
#include <qobject.h>
#include <qtypes.h>

namespace Editor::Models {
    class ProfileView : public QObject, public Shared::Models::Profile::ProfileView {

        Q_OBJECT

        Q_PROPERTY( Mode mode READ getMode WRITE setMode NOTIFY modeChanged );
        Q_PROPERTY( Position position READ getPosition WRITE setPosition NOTIFY positionChanged );
        Q_PROPERTY( qsizetype offset READ getOffset WRITE setOffset NOTIFY offsetChanged );
        Q_PROPERTY( WrapMode wrapMode READ getWrapMode WRITE setWrapMode NOTIFY wrapModeChanged );
        Q_PROPERTY( FlowDirection flowDirection READ getFlowDirection WRITE setFlowDirection NOTIFY
                        flowDirectionChanged );

        Q_ENUM( Mode );
        Q_ENUM( Position );
        Q_ENUM( WrapMode );
        Q_ENUM( FlowDirection );

      public:
        explicit ProfileView( const Mode mode,
                              const Position position,
                              const qsizetype offset,
                              const WrapMode wrapMode,
                              const FlowDirection flowDirection,
                              QObject* parent = nullptr )
            : QObject( parent ), Shared::Models::Profile::ProfileView( mode,
                                                                       position,
                                                                       offset,
                                                                       wrapMode,
                                                                       flowDirection ) {}

        auto getMode() const {
            return this->mode;
        }

        void setMode( const Mode mode ) {
            if ( this->mode != mode ) {
                this->mode = mode;
                emit this->modeChanged();
            }
        }

        auto getPosition() const {
            return this->position;
        }

        void setPosition( const Position position ) {
            if ( this->position != position ) {
                this->position = position;
                emit this->positionChanged();
            }
        }

        auto getOffset() const {
            return this->offset;
        }

        void setOffset( const qsizetype offset ) {
            if ( this->offset != offset ) {
                this->offset = offset;
                emit this->offsetChanged();
            }
        }

        auto getWrapMode() const {
            return this->wrapMode;
        }

        void setWrapMode( const WrapMode wrapMode ) {
            if ( this->wrapMode != wrapMode ) {
                this->wrapMode = wrapMode;
                emit this->wrapModeChanged();
            }
        }

        auto getFlowDirection() const {
            return this->flowDirection;
        }

        void setFlowDirection( const FlowDirection flowDirection ) {
            if ( this->flowDirection != flowDirection ) {
                this->flowDirection = flowDirection;
                emit this->flowDirectionChanged();
            }
        }

      signals:
        void modeChanged();
        void positionChanged();
        void offsetChanged();
        void wrapModeChanged();
        void flowDirectionChanged();
    };
} // namespace Editor::Models
