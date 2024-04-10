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
int main(){
	
	int server = Socket(AF_INET, SOCK_STREAM,0);
	
	struct sockaddr_in adr = {0};
	adr.sin_family = AF_INET;
	adr.sin_port = htons(34543);
	Bind(server, (struct sockaddr *)&adr, sizeof adr);

	Listen(server, 5);
	
	socklen_t adrlen = sizeof adr;
	int fd = Accept(server, (struct sockaddr *)&adr, &adrlen);
	
	ssize_t nread;
	char buf[256];
	nread = read(fd, buf, 256);
	if(nread == -1){
		perror("Unable to read");
		exit(EXIT_FAILURE);
	}
	if(nread == -1){
		printf("END OF FILE occured");
		exit(EXIT_FAILURE);
	}

	write(STDOUT_FILENO, buf, nread);
	
	write(fd, buf, nread);

	sleep(1);

	close(fd);
	close(server);
	return 0;
}
