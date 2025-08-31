# NTC Termistor library CMake
add_library(ntc_termistor STATIC
    src/ntc_termistor.c
)
target_include_directories(ntc_termistor PUBLIC inc)
