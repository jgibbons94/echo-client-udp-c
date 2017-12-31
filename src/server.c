#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define announce(msg) printf("server: %s", msg)
int main(int argc, const char** argv)
{
	announce("Hello World\n");
	//variables
	int sock = 0;
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;
	socklen_t addrsize;
	char buffer[16];
	//setup
	announce("setting up...\n");
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	memset(buffer, 0, sizeof(buffer));
	memset(&caddr, 0, sizeof(struct sockaddr_in));
	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(0x4B47);
	saddr.sin_addr.s_addr = INADDR_ANY;
	//bind
	announce("binding...\n");
	if(bind(sock, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in))==-1)
	{
		perror("bind failed");
		return 1;
	}
	//listen as a server
	announce("receiving...\n");
	if(recvfrom(sock, buffer, sizeof(buffer)-1,
		0, (struct sockaddr*)(&caddr), &addrsize)==-1)
	{
		perror("recvfrom failed");
		return 2;
	}	
	
	//respond
	announce("sending...\n");
	fprintf(stderr, "%s\n", buffer);

	#ifdef WATCHING
	fprintf(stderr, "sendto(%%i, \"%%s\", %i, %%i,\n {caddr.sin_family: %%i, caddr.sin_port:%x, caddr.sin_addr:%s}, %i);\n"
			//, sock
			//, buffer
			, strlen(buffer)
			//, 0
			//, caddr.sin_family
			, caddr.sin_port
			, inet_ntoa(caddr.sin_addr)
			, addrsize
		);
	#endif
	
	if(sendto(sock, buffer, strlen(buffer), 0,
			(struct sockaddr*)(&caddr), addrsize)==-1)
	{
		perror("sendto failed");
		return 3;
	}
	announce("successful.\n");
	//finish up
	announce("closing...\n");
	close(sock);
	sock = 0;
	return 0;
}
