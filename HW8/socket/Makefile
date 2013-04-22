# Makefile for the socket programming example
#

simple_server_objects = ServerSocket.o Socket.o simple_server_main.o
simple_client_objects = ClientSocket.o Socket.o simple_client_main.o

# the default compilation from .cpp to .o
.cpp.o:
	g++ -g -c $<

all : simple_client

simple_client: $(simple_client_objects)
	g++ -o simple_client $(simple_client_objects)


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
simple_client_main: simple_client_main.cpp


clean:
	rm -f *.o simple_server simple_client
