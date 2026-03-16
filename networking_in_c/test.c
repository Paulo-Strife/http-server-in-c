#include <stdio.h>
#include "server.h"
#include <string.h>

void launch(struct Server *server) {
    char buffer[3000];
    printf("WAITING FOR CONNECTIONS... \n");
    int address_lenght = sizeof(server->address);
    int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_lenght);
    read(new_socket, buffer, 3000);
    printf("%s\n", buffer);
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    write(new_socket, hello, strlen(hello));
    close(new_socket);
}

int main () {
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
    launch(&server);
}