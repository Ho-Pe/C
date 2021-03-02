/* ==
* @brief TCP ä�� ���α׷�(������ ��� X) - Server
* @reporting date 19/12/23
* @last modified 21/03/01
* @dev by Windows 10
== */

#include "header.h"

int check_exit(char* message);

int main(int argc, char* argv[]) {
	WSADATA wsadata;
	SOCKET serv_sock, clnt_sock;
	SOCKADDR_IN serv_addr, clnt_addr;

	// BUFSIZE = 4096
	char message[BUFSIZE];
	int fromlen = sizeof(clnt_addr);
	int rcv;

	// ��Ʈ �Է� Ȯ��
	if (argc != 2) {
		printf("Please, Insert Port Number\n");
		exit(1);
	}

	// WinSock 2.2 DLL Ȯ��
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		perror("Load WinSock 2.2 DLL Error");

	// ���� ���� (AF_INET = IPv4 �ּ�ü�� / SOCK_STREAM = TCP/IP)
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// ���� ���� ���� Ȯ��
	if (serv_sock == INVALID_SOCKET)
		perror("Socket Error");

	// ���� ���� (AF_INET = IPv4 �ּ�ü�� / IP_ADDR = 127.0.0.1)
	memset(&serv_addr, 0, sizeof(SOCKADDR_IN));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	serv_addr.sin_port = htons(atoi(argv[1]));

	// ���Ͽ� �ּҸ� ��������
	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		perror("Bind Error");

	// ���� ���
	if (listen(serv_sock, 5) == SOCKET_ERROR)
		perror("Listen Error");

	printf("[Server] : Waiting Connection Request...\n");

	// ���� ���� ����
	clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &fromlen);

	// ���� ���� ����
	if (clnt_sock == INVALID_SOCKET)
		printf("Accept Error %d\n", WSAGetLastError());
	else {
		printf("[Server] : %s Connection Complete!\n", inet_ntoa(clnt_addr.sin_addr));
		printf("[Server] : Start...\n");
	}

	closesocket(serv_sock);

	// ä�� �κ�
	while (1) {
		// client���� �޼��� ����
		rcv = recv(clnt_sock, message, sizeof(message) - 1, 0);
		message[rcv] = '\0';
		if (check_exit(message) == 0)
			break;

		printf("[Client] : %s\n", message);

		// client�� ���� �޼���
		printf("�޼��� �Է� >> ");
		gets_s(message, sizeof(message));
		send(clnt_sock, message, sizeof(message), 0);

		if (check_exit(message) == 0)
			break;
	}

	closesocket(clnt_sock);
	WSACleanup();
	_getch();

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