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
    int sockfp = 0, len;
    char buffer[BUFF_SIZE];

    struct sockaddr_in servaddr, cliaddr;


    sockfp = errorMessage("Create socket", socket(AF_INET, SOCK_DGRAM, 0));
    time_t *returnTime = malloc(sizeof(time_t));

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    errorMessage("Bind", bind (sockfp, (const struct sockaddr *) &servaddr, sizeof(servaddr)));

    len = sizeof(cliaddr);


    while(1)
    {
        printf("Pending requests..\n");
        memset(&cliaddr, 0, sizeof(cliaddr));
        memset(&buffer, 0, BUFF_SIZE);

        errorMessage("Recieve", recvfrom(sockfp, (char *)buffer, BUFF_SIZE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len)); //Recieves request and stores senders address in cliaddr/len
        printf("Received request\n");

        *returnTime = getTime();
        printf("Current time is: %s\n", ctime(returnTime));

        errorMessage("Sendback", sendto(sockfp, returnTime, sizeof(time_t), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len));
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

