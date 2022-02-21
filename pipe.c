#include <sys/wait.h> //wait
#include <stdio.h>
#include <stdlib.h> // exit functions
#include <unistd.h> //_exit, read, write, pipe
#include <string.h>


#define ReadEnd 0
#define WriteEnd 1

void report(const char * message){
	perror(message);
	exit (-1);
}


int main(){
	int pipeFds[2];
	char buf;
	const char * msg = "I love India\n";
	
	if (pipe(pipeFds) <0) report("pipe bro");
	pid_t cpid = fork(); 
	if (cpid<0) report("fork");
	
	if (0==cpid)
		{ //child
		close(pipeFds[WriteEnd]); //child write end band kartoh bruh
		
			while(read(pipeFds[ReadEnd],&buf,1)>0)
				write(STDOUT_FILENO, &buf, sizeof(buf)); //we pass the buffer address to console 
		close(pipeFds[ReadEnd]);
		_exit(0);
	}
	else //parent
	{
		close(pipeFds[ReadEnd]);
		
		write(pipeFds[WriteEnd],msg,sizeof(msg));
		close(pipeFds[WriteEnd]);
		
		wait(NULL);
		exit(0);
	}
	
	return 0;



}
