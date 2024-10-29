cmake_minimum_required(VERSION 3.10)

project(BMICalculator VERSION 1.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

set(SOURCES
        bmi_calculator.c
)

add_executable(bmi_calculator ${SOURCES})

target_include_directories(bmi_calculator PRIVATE ${GTK_INCLUDE_DIRS})
target_link_libraries(bmi_calculator ${GTK_LIBRARIES})

set_target_properties(bmi_calculator PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
