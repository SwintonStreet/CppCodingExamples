#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 8080

int main ()
{
    std::cout << "Hello world!\n";

    char buffer[1024] {0};
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // create socket and handle set up failure
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up socket options
    if (setsockopt(server_fd,
                   SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT,
                   &opt,
                   sizeof(opt)) )
    {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    // binding the socket to 8080
    if (bind(server_fd,
             (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failure");
        exit(EXIT_FAILURE);
    }

    // listen for incoming message
    if ( listen(server_fd, 3) < 0)
    {
        perror("listen failure");
        exit(EXIT_FAILURE);
    }
    std::cout << "listened\n";

    int new_socket = accept(server_fd,
                            (struct sockaddr *) &address,
                            (socklen_t*) &addrlen);

    if (new_socket < 0)
    {
        perror("accept failure");
        exit(EXIT_FAILURE);
    }
    std::cout << "accpeted\n";

    while (true)
    {
        bzero(buffer, 1024);
        read(new_socket, buffer, 1024);

        if ( strcmp(buffer, "EXIT") == 0 )
        {
            std::cout << "server exiting now\n";
            break;
        }

        std::cout << "got: " << buffer << '\n' ;

        send(new_socket, buffer, strlen(buffer), 0);
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
