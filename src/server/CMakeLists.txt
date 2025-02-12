add_executable(server main.cpp)

if(Boost_FOUND)
  include_directories(${BOOST_ROOT})
  include_directories(${Boost_INCLUDE_DIRS})
  message("-- Boost link to: ${Boost_VERSION_STRING}")
else()
  message(FATAL_ERROR "Boost not found!")
endif()

add_library(LSERVER Server.cpp ChatUser.cpp ChatSpace.cpp ../common/Message.cpp)

target_link_libraries(server LSERVER ${Boost_LIBRARIES})

target_include_directories(LSERVER
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )