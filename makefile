
all: server client

# Put here all the common files which are being used both in client and server
COMMON_SOURCES = Trip.cpp Trip.h Driver.cpp Driver.h Cab.cpp Cab.h LuxuryCab.cpp LuxuryCab.h Passenger.cpp Passenger.h StationInfo.cpp StationInfo.h TaxiStation.cpp TaxiStation.h Map.cpp Map.h CreateLayout.cpp CreateLayout.h MapCreator.cpp MapCreator.h CabFactory.cpp CabFactory.h Bfs.cpp Bfs.h Grid.cpp Node.cpp ParseFromString.cpp PointBase.cpp PointHistory.cpp SearchAlgo.cpp SearchAlgo.h Udp.cpp Udp.h Socket.cpp Socket.h CabsSender.cpp CabsSender.h Server.cpp Server.h Clock.cpp Clock.h
server:
	g++ -std=c++0x server.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o server.out
# (for example)
client:
	g++ -std=c++0x client.cpp ClientOps.cpp ClientOps.h $(COMMON_SOURCES) -lboost_serialization -I. -o client.out
