rock_library(inclinometer_solar2
    SOURCES Solar2.cpp
    HEADERS Solar2.hpp
    DEPS_PKGCONFIG iodrivers_base)

rock_executable(sensor_tester sensor_tester.cpp
    DEPS inclinometer_solar2
    DEPS_PKGCONFIG iodrivers_base)

