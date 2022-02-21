#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100

struct messagebuffer{
	long msg_type;
	char msg_txt[100];
}message;

int main(){
	key_t key;
	int msgid;
	
	//ftok(char* path, int id);
	key = ftok("progfile", 65);
	
	// int msgget (key_t key, int msgtig)
	//creates a message queue and returns integer
	msgid = msgget(key, 0666 | IPC_CREAT);
	
	//type define kar 
	message.msg_type = 1;
	
	printf("Write Data:");
	//char * str, int n, FIle Stream
	fgets(message.msg_txt, MAX, stdin);
	
	//send the message
	msgsnd(msgid, &message, sizeof(message), 0);
	
	//print what you sent 
	printf("Data send is: %s \n", message.msg_txt);
	return 0;
}
