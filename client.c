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

int errorMessage(char *errorType, int returnValue);


int main()
{
    int sockfp = 0, len, n;

    char emptyBuffer[BUFF_SIZE];

    struct sockaddr_in serverAddress;
    time_t *recvBuffer = malloc(sizeof(time_t));


    sockfp = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    errorMessage("Send", sendto(sockfp, (const char*)emptyBuffer, BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &serverAddress, sizeof(serverAddress)));
    printf("Sent message to server\n");

    errorMessage("Recieve", recvfrom(sockfp, recvBuffer, sizeof(time_t), MSG_WAITALL, (struct sockaddr *) &serverAddress, &len));
    printf("Server says date and time is: %s", ctime(recvBuffer));

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