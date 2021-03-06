#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


struct message
{
    float floatnum;
};

int main()
{ 
    //server socket creation
    int s_socket;
    s_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (s_socket == -1)
    {
        printf("Error in socket creation.");
    }

    struct sockaddr_in s_address;
    struct sockaddr_in c_address;
    socklen_t client_len;
    struct message s_data;
    
    int ping;
    int ping2;

    client_len = sizeof(c_address);


    s_address.sin_family = AF_INET;//address family
    s_address.sin_port = htons(8090);//port number
    s_address.sin_addr.s_addr = INADDR_ANY;//IP address
    
    //bind the socket with the Port
    bind(s_socket, (struct sockaddr *)&s_address, sizeof(s_address));

    //receive message 
    recvfrom(s_socket, &s_data, sizeof(s_data), 0, (struct sockaddr *)&c_address, &client_len);

    //receive ping
    recvfrom(s_socket, &ping, sizeof(ping), 0, (struct sockaddr *)&c_address, &client_len);


    s_data.floatnum = pow(s_data.floatnum, 1.5);

    sendto(s_socket, &s_data, sizeof(s_data), 0, (struct sockaddr *)&c_address, client_len);

    printf("Server process completed.\n");

    //close the socket
    close(s_socket);
}
