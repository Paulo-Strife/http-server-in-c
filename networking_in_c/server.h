#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>


struct Server
{
    // socket information
    int domain;
    int service;
    int protocol;
    unsigned long interface;
    int port;
    int backlog;

    struct sockaddr address;
    // function to lounch the server

    int socket;

    void (*launch)(void);
};

struct Server server_constructor(int domain, int service, int protocol, unsigned long interface, int port, int backlog, void(*launch(struct Server *server)));

#endif /* Server_h */;