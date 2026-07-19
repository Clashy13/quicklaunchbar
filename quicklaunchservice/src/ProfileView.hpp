#pragma once

#include <QObject>
#include <QString>

class ProfileView : public QObject {
    Q_OBJECT

  public:
    explicit ProfileView( const QString& mode,
                          const QString& horizontalAnchor,
                          const QString& verticalAnchor,
                          qsizetype margin,
                          const QString& wrapMode,
                          const QString& flowDirection,
                          QObject* parent = nullptr )
        : QObject( parent ), _mode( mode ), _horizontalAnchor( horizontalAnchor ),
          _verticalAnchor( verticalAnchor ), _margin( margin ), _wrapMode( wrapMode ),
          _flowDirection( flowDirection ) {}

    auto mode() const {
        return this->_mode;
    }

    auto horizontalAnchor() const {
        return this->_horizontalAnchor;
    }

    auto verticalAnchor() const {
        return this->_verticalAnchor;
    }

    auto margin() const {
        return this->_margin;
    }

    auto wrapMode() const {
        return this->_wrapMode;
    }

    auto flowDirection() const {
        return this->_flowDirection;
    }

  private:
    const QString _mode;
    const QString _horizontalAnchor;
    const QString _verticalAnchor;
    const qsizetype _margin;
    const QString _wrapMode;
    const QString _flowDirection;
};
