add_executable(client main.cpp)

if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found!")
endif()

if(NOT OpenSSL_FOUND)
  message(FATAL_ERROR "OpenSSL not found!")
endif()

add_library(LCLIENT
  IClient.cpp
  IClientBuilder.cpp
  PlainClientBuilder.cpp
  SslClientBuilder.cpp
  PlainClient.cpp
  SslClient.cpp
  ClientArgumentsParser.cpp
  ../common/MessageBlock.cpp
../common/MessageBuilder.cpp
../common/Message.cpp)

target_link_libraries(client LCLIENT ${Boost_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)

target_include_directories(LCLIENT
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )