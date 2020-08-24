#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8080

int main ()
{
    std::cout << "Hello world!\n";

    char buffer[1024] {0};
    struct sockaddr_in address;
    int opt = 1;

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

    long int connection {connect(server_fd,
                                 (struct sockaddr*) &address,
                                 sizeof(address))};

    if (connection < 0)
    {
        perror("Error connecting");
        exit(EXIT_FAILURE);
    }


    while (true)
    {
        std::cout << "Please enter message now\n";
        bzero(buffer, 1024);
        fgets(buffer, 1024, stdin);

        // EXIT is typed to quit the socket
        // because fgets gives us a new line character at the end we
        // need to include that in the comparison
        if ( strcmp(buffer, "EXIT\n") == 0 )
        {
            write(server_fd, "EXIT", strlen("EXIT"));
            std::cout << "client exiting now \n";
            break;
        }

        long int n = write(server_fd, buffer, strlen(buffer));

        if ( n < 0 )
        {
            perror("Error writing to socket");
            exit(EXIT_FAILURE);
        }

        bzero(buffer, 1024);
        n = read(server_fd, buffer, 1024);

        if (n < 0)
        {
            perror("Error writing to socket");
            exit(EXIT_FAILURE);
        }

        std::cout << "Got back message: " << buffer << '\n';
    }

    close(server_fd);

    return 0;
}
