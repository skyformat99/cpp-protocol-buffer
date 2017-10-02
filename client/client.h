//
//  client.h
//  client
//
//  Created by Anthony Fiorito on 2017-10-01.
//  Copyright © 2017 Anthony Fiorito. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdexcept>

#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

class Client {
private:
    int socket_fd;
    
public:
    ~Client();
    
    void openSocket();
    void connectToServer(int);
    void sendRequest(void*, size_t);
    void readResponse(void*, size_t);
    void close();
    
    
};

#endif // CLIENT_CLIENT_H_
