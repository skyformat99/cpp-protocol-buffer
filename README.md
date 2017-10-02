# C++ Protocol Buffer Example
### Client/server application testing Google's Protocol Buffer

The application allows a user to create a request for quote (RFQ). The communication between client & server is achieved using TCP sockets. Request and Response data are serialized/deserialized using Google's Protocol Buffer.

> Protocol buffers are the flexible, efficient, automated solution to solve exactly this problem. With protocol buffers, you write a .proto description of the data structure you wish to store. From that, the protocol buffer compiler creates a class that implements automatic encoding and parsing of the protocol buffer data with an efficient binary format.

## Prerequisites

It is necessary to have google's protocol buffer source code compiled. You can download it the source code [here](https://github.com/google/protobuf/releases).

Once you've downloaded the source files, follow the instructions in the ```README.md``` to install protoc along with the C++ runtime.

## Install Instructions

### 1. Clone the project
```
git clone https://github.com/a-fiorito/cpp-protocol-buffer.git 
```

### 2. Build the source code using make
```
make
```

## Usage

### 1. Start the server
```
./server.o    # in the root directory of the project
```

### 2. Start the client
```
./client.o    # in the root directory of the project
```

## Acknowledgements

The project was an assignment for COEN 424 - Programming on the Cloud.
