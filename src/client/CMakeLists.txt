add_executable(client main.cpp)

if(Boost_FOUND)
  include_directories(${BOOST_ROOT})
  include_directories(${Boost_INCLUDE_DIRS})
  message("-- Boost link to: ${Boost_VERSION_STRING}")
else()
  message(FATAL_ERROR "Boost not found!")
endif()

add_library(LCLIENT Client.cpp ../common/Message.cpp)

target_link_libraries(client LCLIENT ${Boost_LIBRARIES})

target_include_directories(LCLIENT
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )