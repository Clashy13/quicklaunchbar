add_subdirectory(models)
add_subdirectory(serializer)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Backend.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Backend.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ProfileManager.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/ProfileManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QmlRegistration.hpp
    PARENT_SCOPE
)
