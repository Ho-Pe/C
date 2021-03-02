/* ==
* @brief UDP Chatting Program(No Thread) - Server
* @reporting date 19/12/12
* @last modified 21/02/28
* @dev by Windows 10
== */
#include "header.h"

int check_exit(char* message);

int main(int argc, char* argv[]) {
	WSADATA wsadata;
	SOCKET serv_sock;
	SOCKADDR_IN serv_addr, clnt_addr;

	char message[BUFSIZE];
	int fromlen = sizeof(clnt_addr);

	// Input Port Number Check
	if (argc != 2) {
		printf("Please, Insert Port Number\n");
		exit(1);
	}

	// WinSock 2.2 DLL Check
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		perror("Load WinSock 2.2 DLL Error");

	// Socket Create (AF_INET = IPv4 / SOCK_DGRAM = UDP/IP)
	serv_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// Socket Create Error Check
	if (serv_sock == INVALID_SOCKET)
		perror("Socket Error");

	memset(&serv_addr, 0, sizeof(SOCKADDR_IN));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	// htons = Big-endian 32bit long / atoi = string to integer
	serv_addr.sin_port = htons(atoi(argv[1]));

	// Socket Bind
	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		perror("Bind Error");

	printf("[Server] : Bind Ok...\n");
	printf("[Server] : Waiting Receive...\n");

	// Chat
	while (1) {
		// Receive Client Message
		recvfrom(serv_sock, message, sizeof(message) - 1, 0, (SOCKADDR*)&clnt_addr, &fromlen);
		
		// exit check
		if (check_exit(message) == 0)
			break;

		printf("[Client] >> %s\n", message);

		// Send to Client
		printf("메세지를 입력하세요 >> ");
		gets_s(message, sizeof(message));
		sendto(serv_sock, message, sizeof(message) - 1, 0, (SOCKADDR*)&clnt_addr, fromlen);

		// exit check
		if (check_exit(message) == 0)
			break;
	}

	WSACleanup();
	closesocket(serv_sock);
	_getch();

	return 0;
}

/* ==
* @brief Input "exit" Check
* @param (char*) Input Message
* @return exit to return 0 / other 1
== */
int check_exit(char* message) {
	if (strcmp(message, "exit") == 0) {
		printf("[Server] : Close Conneciton...\n");
		return 0;
	}
	else
		return 1;
}