add_executable(my_tests ServerArgumentsParserTests.cpp)
target_link_libraries(my_tests gtest_main LSERVER ${Boost_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)

include(GoogleTest)

enable_testing()

# This command automatically discovers and adds all tests to CTest
gtest_discover_tests(my_tests)