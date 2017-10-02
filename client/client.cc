//
//  client.c
//  client
//
//  Created by Anthony Fiorito on 2017-10-01.
//  Copyright © 2017 Anthony Fiorito. All rights reserved.
//

#include "client.h"
using namespace std;

Client::~Client() {
    close();
}

void Client::openSocket() {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (socket_fd < 0) throw std::runtime_error("Error opening socket");
}

void Client::connectToServer(int port_num) {
    struct hostent* server;
    struct sockaddr_in server_address;
    
    server = gethostbyname("localhost");
    if (server == NULL) throw new std::runtime_error("Error could not find host");
    
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *) &server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(port_num);
    
    const int status = connect(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address));
    
    if (status < 0) throw std::runtime_error("Error could not connect to server.");
    
}

void Client::sendRequest(void* buffer, size_t size) {
    const ssize_t status = write(socket_fd, buffer, size);
    
    if (status < 0) throw std::runtime_error("Error sending message.");
}

void Client::readResponse(void* buffer, size_t size) {
    const ssize_t status = read(socket_fd, buffer, size);
    
    if (status < 0) throw std::runtime_error("Error reading response.");
}

void Client::close() {
    ::close(socket_fd);
}




