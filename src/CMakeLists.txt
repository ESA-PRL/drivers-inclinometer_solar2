rock_library(inclinometer_solar2
    SOURCES Solar2.cpp
    HEADERS Solar2.hpp
    DEPS_PKGCONFIG iodrivers_base)

rock_executable(inclinometer_solar2_bin main.cpp
    DEPS inclinometer_solar2
    DEPS_PKGCONFIG iodrivers_base)

