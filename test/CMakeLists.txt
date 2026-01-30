set(FETCHCONTENT_QUIET OFF)
include(FetchContent)

FetchContent_Declare(Catch2
    URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.12.0.tar.gz
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(Catch2)

add_executable(test_pythonicpp
    test_string.cpp
)

target_link_libraries(test_pythonicpp
    PRIVATE
    pythonicpp
    Catch2::Catch2
    Catch2::Catch2WithMain
)