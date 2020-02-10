#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>


#define PORT 37
#define BUFF_SIZE 1024


time_t getTime();
int errorMessage(char *errorType, int returnValue);


int main()
{
    int server_socket = 0, cli_addr_size;
    char readBuffer[BUFF_SIZE];

    struct sockaddr_in serv_addr, cli_addr;


    server_socket = errorMessage("Create socket", socket(AF_INET, SOCK_DGRAM, 0));
    time_t *returnTime = malloc(sizeof(time_t));

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    errorMessage("Bind", bind (server_socket, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)));

    cli_addr_size = sizeof(cli_addr);


    while(1)
    {
        printf("Pending requests..\n");
        memset(&cli_addr, 0, sizeof(cli_addr));
        memset(&readBuffer, 0, BUFF_SIZE);

        errorMessage("Recieve", recvfrom(server_socket, (char *)readBuffer, BUFF_SIZE, MSG_WAITALL, (struct sockaddr *) &cli_addr, &cli_addr_size)); //Recieves request and stores senders address in cliaddr/len
        printf("Received request\n");

        *returnTime = getTime();
        printf("Current time is: %s\n", ctime(returnTime));

        errorMessage("Sendback", sendto(server_socket, returnTime, sizeof(time_t), MSG_CONFIRM, (const struct sockaddr *) &cli_addr, cli_addr_size));
        printf("Answer sent\n");
    }

}


time_t getTime()
{
    time_t cTime;
    time(&cTime);
    return cTime;
}

int errorMessage(char *errorType, int returnValue)
{
    if(returnValue < 0 )
    {
        perror(errorType);
        exit(EXIT_FAILURE);
    }
    return returnValue;
}

