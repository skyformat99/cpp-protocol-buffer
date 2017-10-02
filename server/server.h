//
//  server.hpp
//  server
//
//  Created by Anthony Fiorito on 2017-10-01.
//  Copyright © 2017 Anthony Fiorito. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

class Server {
private:
    int listen_socket_fd, message_socket_fd;
    // maximum number of requests the server can handle
    const int queue_size;
    
public:
    Server(int = 5);
    ~Server();
    
    
    void openSocket();
    void listen(int);
    void readRequest(void*, size_t);
    void sendResponse(const void* , size_t) const;
    void close();
    
};

#endif // SERVER_SERVER_H_
