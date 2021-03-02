/* ==
* @brief TCP ä�� ���α׷�(������ ��� X) - Client
* @reporting date 19/12/23
* @last modified 21/03/01
* @dev by Windows 10
== */

#include "header.h"

int check_exit(char* message);

int main(int argc, char* argv[]) {
	WSADATA wsadata;
	SOCKET clnt_sock;
	SOCKADDR_IN serv_addr;

	// BUFSIZE = 4096
	char message[BUFSIZE];
	int tolen = sizeof(serv_addr);
	int port_num;
	int rcv;

	// WinSock 2.2 DLL Ȯ��
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		perror("Load WinSock 2.2 DLL Error");

	// ���� ���� (AF_INET = IPv4 �ּ�ü�� / SOCK_STREAM = TCP/IP)
	clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (clnt_sock == INVALID_SOCKET)
		perror("Socket Error");

	// ��Ʈ �ѹ� �Է�
	printf("Input Port Number : ");
	gets_s(message, sizeof(message));
	port_num = atoi(message);

	// ���� ���� (AF_INET = IPv4 �ּ�ü�� / IP_ADDR = 127.0.0.1)
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	serv_addr.sin_port = htons(port_num);

	// ���� ��û
	if (connect(clnt_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		perror("Connection Error");
	else
		printf("Connection Complete!\n");

	// ä�� �κ�
	while (1) {
		// server�� ���� �޼��� �Է�
		printf("�޼����� �Է��ϼ��� >> ");
		gets_s(message, sizeof(message));
		send(clnt_sock, message, sizeof(message) - 1, 0);

		if (check_exit(message) == 0)
			break;

		// server�κ��� ����
		rcv = recv(clnt_sock, message, sizeof(message), 0);

		if (check_exit(message) == 0)
			break;

		printf("[Server] : %s\n", message);
	}

	closesocket(clnt_sock);
	WSACleanup();

	return 0;
}

/* ==
* @brief "exit" �Է� Ȯ�� �� ���� üũ
* @param char* �Է¹��� �޼���
* @return exit�Է� Ȯ�� 0 / �̿� 1
== */
int check_exit(char* message) {
	if (strcmp(message, "exit") == 0) {
		printf("[Server] : Close Connection...\n");
		return 0;
	}
	else
		return 1;
}