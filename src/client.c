#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define announce(msg) printf("client: %s", msg)
int main(int argc, const char** argv)
{
	announce("Hello World\n");
	//variables
	int sock = 0;
	struct sockaddr_in saddr;
	const char* message = "Hello World";
	char buffer[16];
	//setup
	announce("setting up...\n");
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	memset(buffer, 0, sizeof(buffer));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(0x4B47);
	if(inet_aton("127.0.0.1", &(saddr.sin_addr)) == 0)
	{
		perror("invalid address");
		return 1;
	}
	if((sock=socket(AF_INET, SOCK_DGRAM, 0))==-1)
	{
		perror("failed to make a socket");
		return 2;
	}

	//connect
	announce("connecting...\n");
	if(connect(sock, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in))==-1)
	{
		perror("failed to connect");
		return 3;
	}

	//send
	announce("sending...\n");
	if(send(sock, message, strlen(message), 0)==-1)
	{
		perror("failed to send");
		return 4;
	}

	//receive
	announce("receiving...\n");
	if(recv(sock, buffer, sizeof(buffer)-1, 0)==-1)
	{
		perror("failed to receive");
		return 5;
	}
	printf("client%s\n",buffer);
	//cleanup
	announce("cleaning up...\n");
	close(sock);
	return 0;
}