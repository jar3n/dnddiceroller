# doing the special thing with google test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(range_test range_test.cc)

target_link_libraries(range_test
    GTest::gtest_main
    range
)

add_executable(character_test character_test.cc)

target_link_libraries(character_test
    GTest::gtest_main
    range
    character
)


include(GoogleTest)
gtest_discover_tests(range_test)
gtest_discover_tests(character_test)
