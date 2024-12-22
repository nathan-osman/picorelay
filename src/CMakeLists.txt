configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h")

set(SRC
    init.cpp
    main.cpp
)

add_executable(picorelay ${SRC})

pico_set_program_name(picorelay "picorelay")
pico_set_program_version(picorelay "0.1")

# Enable serial over USB
pico_enable_stdio_uart(picorelay 0)
pico_enable_stdio_usb(picorelay 1)

# Add the standard library to the build
target_link_libraries(picorelay
    pico_stdlib
)

# Add the standard include files to the build
target_include_directories(picorelay PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_LIST_DIR}
)

# Add required libraries
target_link_libraries(picorelay
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_add_extra_outputs(picorelay)
