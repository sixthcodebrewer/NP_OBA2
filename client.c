#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netdb.h>

#define port 4696

int main(){
struct sockaddr_in serv_addr, cli_addr;
char buff[4096];
char buffer[4096];

// create a socket
int sockfd = socket(AF_INET, SOCK_STREAM,0);

//bzero(&cli_addr, sizeof(cli_addr));
cli_addr.sin_family = AF_INET;
cli_addr.sin_port = htons(port);
cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

// bind(socket filed, (struck sockaddr*)&client adrr, sizeof(client addr));
bind(sockfd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
printf("Read ...\n");

// connect 
connect(sockfd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
printf("connect..\n");

printf("Enter data:");
fgets(buffer, 4096, stdin);

//write first and read later
write(sockfd, buffer, 4096);
printf("data sent");


//print the data recived in different variable
read(sockfd, buff, 4096);
printf("data recv: %s\n",buff);

close(sockfd);

return 0;
}
