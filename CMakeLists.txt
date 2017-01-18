cmake_minimum_required(VERSION 3.5)
project(ex5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(core_sockets Socket.cpp Udp.cpp)
add_library(sockets ${core_sockets})
set(SOURCE_FILES Trip.cpp Trip.h Driver.cpp Driver.h Cab.cpp Cab.h LuxuryCab.cpp
        LuxuryCab.h Passenger.cpp Passenger.h StationInfo.cpp StationInfo.h  Map.cpp Map.h CreateLayout.cpp CreateLayout.h MapCreator.cpp
        MapCreator.h CabFactory.cpp CabFactory.h Bfs.cpp Bfs.h
        Grid.cpp Node.cpp ParseFromString.cpp PointBase.cpp PointHistory.cpp
         SearchAlgo.cpp SearchAlgo.h Udp.cpp Udp.h Socket.cpp Socket.h Server.cpp Server.h
        Clock.cpp Clock.h Tcp.cpp Trip.h)
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
find_package(Threads)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

#add_executable(server server.cpp)
add_executable(client client.cpp  ${SOURCE_FILES} ClientOps.cpp ClientOps.h)
add_executable(server ServerFlow.cpp TaxiStation.cpp
        TaxiStation.h ${SOURCE_FILES})
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})


