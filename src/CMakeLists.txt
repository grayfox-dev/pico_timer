add_executable(timer_blink
    timer_blink.c
)

target_link_libraries(timer_blink pico_stdlib)

pico_add_extra_outputs(timer_blink)
