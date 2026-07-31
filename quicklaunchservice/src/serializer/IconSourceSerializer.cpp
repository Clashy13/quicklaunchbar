#include "IconSourceSerializer.hpp"

namespace Service::Serializer {

    QUrl IconSourceSerializer::iconSourceToUrl( const IconSource& iconSource ) {
        switch ( iconSource.type ) {
            case IconSource::Type::Theme:
                return QUrl( "image://themeicons/" + iconSource.value );
            case IconSource::Type::FromFile:
                return QUrl( "image://fileicons" + iconSource.value );
            case IconSource::Type::Image:
                return QUrl( "image:/" + iconSource.value );
            case IconSource::Type::Resource:
                return QUrl( "qrc:/icons/" + iconSource.value + ".svg" );
        }
    }
} // namespace Service::Serializer