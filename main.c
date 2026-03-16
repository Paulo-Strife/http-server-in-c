struct addrinfo
{
    int ai_flags; //AI_PASSIVE, AI_CANONNAME
    int ai_family; //AF_NET, AF_INET6 - Uma ipv4 e outra ipv6
    int ai_socktype; //Escolher entre sock_stream ou sock_dgram
    int ai_protocol; //Protocolo, 0 é o protocolo padrão
    size_t ai_addrlen; //tamanho de ai_addr em bytes

    struct sockaddr *ai_addr; // struct sockaddr_in ou _in6, depende do ai_family
    char *ai_canonname; // nome do host canônico

    struct addrinfo *ai_next; //lista ligada, e vai para o próximo nó
};

struct sockaddr
{
    // para identificar a familia de endereços, IPV4 ou IPV6
    unsigned short sa_family;
    // 14 bytes de endereço do protocolo, mas IPV6 precisa de mais
    char sa_data[14];
};
