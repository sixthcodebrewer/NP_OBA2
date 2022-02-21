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
	
	//msgrcv(int messageid, const void* messsageq, size_t msg, message _type, int msgid);
	msgrcv(msgid, &message, sizeof(message), 1,0);
	printf("Data Recieved: %s\n", message.msg_txt);

	//to destroy message 
	msgctl(msgid, IPC_RMID, NULL);
	
	return 0;
}
