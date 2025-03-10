cmake_minimum_required(VERSION 3.14)
project(Messenger)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS locale)

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

add_subdirectory(src/client)
add_subdirectory(src/server)