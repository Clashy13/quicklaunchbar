add_subdirectory(models)
add_subdirectory(serializer)
add_subdirectory(manager)
add_subdirectory(qmlelements)
add_subdirectory(provider)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/QmlRegistration.hpp
    PARENT_SCOPE
)
