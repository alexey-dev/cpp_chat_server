add_executable(server main.cpp)

if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found!")
endif()

if(NOT OpenSSL_FOUND)
  message(FATAL_ERROR "OpenSSL not found!")
endif()

add_library(LSERVER 
  IServer.cpp
  Server.cpp
  SslServer.cpp
  IChatUser.cpp
  ChatUser.cpp
  SslChatUser.cpp
  ChatSpace.cpp
  ../common/MessageBlock.cpp
  ../common/MessageBuilder.cpp
  ../common/Message.cpp)

target_link_libraries(server LSERVER ${Boost_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)

target_include_directories(LSERVER
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )