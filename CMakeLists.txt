cmake_minimum_required(VERSION 3.14)
project(Messenger)

set(CMAKE_CXX_STANDARD 17)

option(ENABLE_COVERAGE "Enable code coverage instrumentation" OFF)

# Enable Clang coverage flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND ENABLE_COVERAGE)
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif()

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

add_subdirectory(src/client)
add_subdirectory(src/server)
add_subdirectory(tests)

# Define paths for output files
set(PROFRAW_FILE "${CMAKE_BINARY_DIR}/coverage.profraw")
set(PROFDATA_FILE "${CMAKE_BINARY_DIR}/coverage.profdata")
set(COVERAGE_HTML_DIR "${CMAKE_BINARY_DIR}/coverage_html")

# Add custom target to automate all coverage steps.
# 1. Run: cmake -S . -B build -DENABLE_COVERAGE=ON.
# 2. cmake --build build --target coverage
add_custom_target(coverage
    COMMAND LLVM_PROFILE_FILE=${PROFRAW_FILE} $<TARGET_FILE:my_tests>
    COMMAND llvm-profdata merge -sparse ${PROFRAW_FILE} -o ${PROFDATA_FILE}
    COMMAND llvm-cov show $<TARGET_FILE:my_tests>
            -instr-profile=${PROFDATA_FILE}
            -format=html
            -output-dir=${COVERAGE_HTML_DIR}
            --sources ${CMAKE_SOURCE_DIR}/src
            --ignore-filename-regex=".*/_deps/.*"
    COMMAND ${CMAKE_COMMAND} -E echo "✅ Coverage report generated at: ${COVERAGE_HTML_DIR}/index.html"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS my_tests
)