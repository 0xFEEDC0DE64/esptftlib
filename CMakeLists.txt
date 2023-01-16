set(headers
    src/icon.h
    src/tftinterface.h
)

set(sources
)

set(dependencies
    cpputils
    cxx-ring-buffer
    espchrono
    espcpputils
    expected
    espwifistack
    fmt
)

idf_component_register(
    INCLUDE_DIRS
        src
    SRCS
        ${headers}
        ${sources}
    REQUIRES
        ${dependencies}
)

target_compile_options(${COMPONENT_TARGET}
    PRIVATE
        -fstack-reuse=all
        -fstack-protector-all
        -Wno-unused-function
        -Wno-deprecated-declarations
        -Wno-missing-field-initializers
        -Wno-parentheses
)
