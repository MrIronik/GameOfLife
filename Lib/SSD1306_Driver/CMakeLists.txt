set(SSD1306_DRIVER_SOURCES
    ssd1306_driver.c
)

set(SSD1306_DRIVER_HEADERS
    ssd1306_driver.h
    ssd1306_commands.h
)

add_library(SSD1306_DRIVER 
    STATIC
        ${SSD1306_DRIVER_SOURCES}
)

target_include_directories(SSD1306_DRIVER
    PUBLIC
        $(CMAKE_CURRENT_SOURCE_DIR)
)