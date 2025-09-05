cmake_minimum_required(VERSION 3.14)
project(Messenger)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS program_options)

if(Boost_FOUND)
    include_directories(${BOOST_ROOT})
    include_directories(${Boost_INCLUDE_DIR})
    message("-- Boost found: ${Boost_VERSION_STRING}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

set(OPENSSL_USE_STATIC_LIBS TRUE)

find_package(OpenSSL REQUIRED)

if(OpenSSL_FOUND)
  include_directories(${OpenSSL_ROOT})
  include_directories(${OpenSSL_INCLUDE_DIRS})
  message("-- OpenSSL found.")
else()
  message(FATAL_ERROR "Error: OpenSSL not found!")
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src/client)
add_subdirectory(src/server)
add_subdirectory(tests)