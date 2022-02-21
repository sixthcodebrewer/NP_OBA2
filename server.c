#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>

#include <arpa/inet.h>


#define port 4696

int main(){
struct sockaddr_in serv_addr, cli_addr;
char buffer[4096];

// create a socket
int sockfd = socket(AF_INET, SOCK_STREAM,0);

//bzero(&cli_addr, sizeof(cli_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(port);
serv_addr.sin_addr.s_addr = INADDR_ANY;

// bind(socket filed, (struck sockaddr*)&client adrr, sizeof(client addr));
bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
printf("Read ...\n");


//listen
listen(sockfd, 5);

//similar to bind
int clilen = sizeof(cli_addr);
int new_sockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
 
//read data 
read(new_sockfd, &buffer, 4096);
printf("data read: %s\n",buffer);


//write first and read later
write(new_sockfd, buffer, 4096);
printf("data echoed: %s\n", buffer);

close(sockfd);

return 0;
}
