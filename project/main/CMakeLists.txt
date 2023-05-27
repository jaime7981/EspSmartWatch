idf_component_register(SRCS "smart-watch.cpp" "buttons.cpp"
                    INCLUDE_DIRS ".")
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++2a)
