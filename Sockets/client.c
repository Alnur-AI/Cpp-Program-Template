#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol)
{
	// 1 - семейство протоколов которые хотим использовать в нашем случае ipv4
	// 2 - в случае TCP используем SOCK_STREAM, в случае UDP - SOCK_DGRAM
	// 3 - 0 - протокол нижележащего уровня
	// если нужно использовать значение по умолчанию, то 0
	int res = socket(domain, type, protocol);
	if(res == -1){
		perror("Unable to define socket in function Socket");
		exit(EXIT_FAILURE);
	}
	return res;
}
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
	int res = bind(sockfd, addr, addrlen);
	if(res == -1){
		perror("Unable to bind socket in function Bind");
		exit(EXIT_FAILURE);
	}
}
int Listen(int sockfd, int backlog){
	int res = listen(sockfd, backlog);
	if(res == -1){
		perror("Unable to listen in socket in function Listen");
		exit(EXIT_FAILURE);
	}
	return res;
}
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	int res = accept(sockfd, addr, addrlen);
	if(res == -1){
		perror("Unable to accept in function Accept");
		exit(EXIT_FAILURE);
	}
	return res;
}
void Connect(int sockfd, struct sockaddr *addr, socklen_t addrlen)
{
	int res = connect( sockfd, addr, addrlen);
	if(res == -1){
		perror("Unable to connect in function Connect");
		exit(EXIT_FAILURE);
	}
}
void Inet_pton(int af, const char *src, void *dst){
	int res = inet_pton(af, src, dst);
	if(res == 0){
		printf("inet_pton failed 0\n");
		exit(EXIT_FAILURE);
	}
	if(res == -1){
		printf("inet_pton failed 1\n");
		exit(EXIT_FAILURE);
	}
}
int main(){
	
	int fd = Socket(AF_INET, SOCK_STREAM,0);

	struct sockaddr_in adr = {0};
	adr.sin_family = AF_INET;
	adr.sin_port = htons(34543);
	Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);

	Connect(fd, (struct sockaddr*) &adr, sizeof adr);

	write(fd,"Hello from client\n", 19);
	
	char buf [256];
	ssize_t nread; 
	nread = read(fd, buf,256);
	if(nread == -1){
		perror("Unable to read");
		exit(EXIT_FAILURE);
	}
	if(nread == 0){
		printf("END OF FILE occured");
	}

	write(STDOUT_FILENO, buf, nread);


	close(fd);
	//close(listen);
	return 0;
}
