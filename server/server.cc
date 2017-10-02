//
//  server.cpp
//  server
//
//  Created by Anthony Fiorito on 2017-10-01.
//  Copyright © 2017 Anthony Fiorito. All rights reserved.
//

#include "server.h"
using namespace std;

Server::Server(int queue_size) : queue_size(queue_size) {}

Server::~Server() {
    close();
}

void Server::openSocket() {
    listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_socket_fd < 0) {
        throw std::runtime_error("Error opening socket\n");
    };
}

void Server::listen(int port_num) {
    struct sockaddr_in server_address;
    int status;
    
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_num);
    
    status = bind(listen_socket_fd, (struct sockaddr*) &server_address, sizeof(server_address));
    
    if (status < 0) throw std::runtime_error("Error binding to socket\n");
    
    ::listen(listen_socket_fd, queue_size);
    printf("Server listening on port %d\n", port_num);
    
}

void Server::readRequest(void* buffer, size_t size) {
    struct sockaddr_in client_address;
    socklen_t client_length = sizeof(client_address);
    message_socket_fd = accept(listen_socket_fd, (struct sockaddr*) &client_address, &client_length);
    
    if(message_socket_fd < 0) throw std::runtime_error("Error receiving connection\n");
    printf("Server: got connection from %s port %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
    
    const ssize_t status = read(message_socket_fd, buffer, size);
    if (status < 0) throw std::runtime_error("Error reading socket");
}

void Server::sendResponse(const void* buffer, size_t size) const {
    const ssize_t status = send(message_socket_fd, buffer, size, 0);
    
    if (status < 0) throw std::runtime_error("Error sending message");
}

void Server::close() {
    ::close(message_socket_fd);
    ::close(listen_socket_fd);
}

