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
                                                                       flowDirection ),
              _savedMode( mode ), _savedPosition( position ), _savedOffset( offset ),
              _savedWrapMode( wrapMode ), _savedFlowDirection( flowDirection ) {}

        auto getMode() const {
            return this->mode;
        }

        void setMode( const Mode mode );

        auto getPosition() const {
            return this->position;
        }

        void setPosition( const Position position );

        auto getOffset() const {
            return this->offset;
        }

        void setOffset( const qsizetype offset );

        auto getWrapMode() const {
            return this->wrapMode;
        }

        void setWrapMode( const WrapMode wrapMode );

        auto getFlowDirection() const {
            return this->flowDirection;
        }

        void setFlowDirection( const FlowDirection flowDirection );

        bool isEdited();

        void saveEdited();

      signals:
        void modeChanged();
        void positionChanged();
        void offsetChanged();
        void wrapModeChanged();
        void flowDirectionChanged();

        void editedChanged( const bool edited );

      private:
        Mode _savedMode;
        Position _savedPosition;
        qsizetype _savedOffset;
        WrapMode _savedWrapMode;
        FlowDirection _savedFlowDirection;
    };
} // namespace Editor::Models
