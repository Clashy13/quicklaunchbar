add_subdirectory(models)
add_subdirectory(serializer)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/QmlRegistration.hpp
    PARENT_SCOPE
)
