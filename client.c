#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>



#define PORT 37
#define BUFF_SIZE 16
#define TIME_DIFF_1900 2208988800

int errorMessage(char *errorType, int returnValue);


int main()
{
    int clientSocket = 0, len, n;

    char emptyBuffer[BUFF_SIZE];

    struct sockaddr_in serverAddress;
    time_t *recvBuffer = malloc(sizeof(time_t));
    time_t result = 0;


    clientSocket = errorMessage("Socket", socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)); //Creates UDP socket with DGRAM type

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    errorMessage("Send", sendto(clientSocket, (const char*)emptyBuffer, BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &serverAddress, sizeof(serverAddress)));

    errorMessage("Recieve", recvfrom(clientSocket, recvBuffer, sizeof(time_t), MSG_WAITALL, (struct sockaddr *) &serverAddress, &len));
    result = ntohl(*recvBuffer); //Sets byte order from network
    result -= TIME_DIFF_1900; //Removes 70 years to function with time()

    printf("Server says date and time is: %s", ctime(&result));

    free(recvBuffer);
    exit(EXIT_SUCCESS);
}


int errorMessage(char *errorType, int returnValue)
{
    if(returnValue < 0 )
    {
        perror(errorType);
        printf("Unable to get time. Exiting..\n");
        exit(EXIT_FAILURE);
    }
    return returnValue;
}