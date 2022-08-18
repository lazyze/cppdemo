cmake_minimum_required(VERSION 3.13)

project(demo)

option(BOOST_SUPPORT "Support Boost 1.7x library" ON)

if(BOOST_SUPPORT)
set(Boost_NO_SYSTEM_PATHS TRUE)
if(Boost_NO_SYSTEM_PATHS)
 
  set(BOOST_ROOT "/opt/boost/boost-1.71-x64")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
# set(BUILD_SHARED_LIBS ON)
  add_definitions(-DBOOST_ALL_DYN_LINK)
endif (Boost_NO_SYSTEM_PATHS)


endif (BOOST_SUPPORT)

find_package(Boost REQUIRED COMPONENTS log log_setup thread)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(demo main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${BOOST_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${BOOST_LIBRARY_DIRS}   
)
message(${BOOST_LIBRARY_DIRS})

target_link_libraries(${PROJECT_NAME}
    boost_log
    boost_log_setup
    boost_thread
)
