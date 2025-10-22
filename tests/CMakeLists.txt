add_executable(my_tests ServerArgumentsParserTests.cpp)
target_link_libraries(my_tests gtest_main LSERVER ${Boost_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()

# This command automatically discovers and adds all tests to CTest
gtest_discover_tests(my_tests)