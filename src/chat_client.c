/*
 ============================================================================
 Name        : chat_server.c
 Author      :
 Version     :
 Copyright   :
 Description : Simple message client
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {

	struct sockaddr_in serv_addr;
	int sock = 0;
	char buffer[1024] = {0};
	char *hello = "hello from client";

	sock = socket(AF_INET, SOCK_STREAM, 0);

	//allocate memory
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		puts("\nInvalid address/ Address not supported \n");
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\n Connection failed \n");
		return EXIT_FAILURE;
	}

	send(sock, hello, strlen(hello), 0);
	puts("Hello message sent");
	int valread = read(sock, buffer, 1024);
	printf("Server response: %s\n", buffer);

	return EXIT_SUCCESS;
}
