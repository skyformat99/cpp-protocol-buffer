
.PHONY: client server clean

all: client server

clean: 
	rm -f client.o server.o

client:
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -I ./ client/main.cc client/client.cc product.pb.cc  -o client.o `pkg-config --cflags --libs protobuf`

server:
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -I ./ server/main.cc server/server.cc product.pb.cc -o server.o --std=c++11  `pkg-config --cflags --libs protobuf`
