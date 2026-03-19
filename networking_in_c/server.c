#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_LEN 2048

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_LEN] = {0};

    const char* html_body = "<html><head><meta charset='utf-8'><title>Sucesso!</title></head>"
                           "<body><h1>Servidor em C funcionando!</h1>"
                           "<p>Conexão estabelecida com sucesso.</p></body></html>";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erro no bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Erro no listen");
        exit(EXIT_FAILURE);
    }

    char html_response[BUFFER_LEN];
    snprintf(html_response, sizeof(html_response), 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s", (int)strlen(html_body), html_body);

    printf("Webserver iniciado em http://localhost:%d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        
        if (client_fd < 0) {
            continue;
        }

        memset(buffer, 0, BUFFER_LEN);
        read(client_fd, buffer, sizeof(buffer));

        send(client_fd, html_response, strlen(html_response), 0);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}