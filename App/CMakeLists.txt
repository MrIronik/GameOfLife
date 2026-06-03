set(DISPLAY_SOURCES
    Display/oled.c
)
set(DISPLAY_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Display
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${DISPLAY_SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${DISPLAY_HEADERS}
)