idf_component_register(SRCS "smart-watch.cpp" 
                            "./gpio_inputs/button.cpp" 
                            "./gpio_inputs/rotary_encoder.cpp"
                            "./watch_gui/watch_gui.cpp"
                    INCLUDE_DIRS ".")
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++2a)
