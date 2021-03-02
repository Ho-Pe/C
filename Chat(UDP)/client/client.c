/* ==
* @brief UDP ä�� ���α׷�(������ ��� X) - Client
* @reporting date 19/12/12
* @last modified 21/02/28
* @dev by Windows 10
== */
#include "header.h"

int check_exit(char* message);

int main(int argc, char* argv[]) {
	WSADATA wsadata;
	SOCKET clnt_sock;
	SOCKADDR_IN serv_addr;

	char message[BUFSIZE];
	int tolen = sizeof(serv_addr);

	// ��Ʈ �Է� Ȯ��
	if (argc != 2) {
		printf("Please, Insert Port Number\n");
		exit(0);
	}

	// WinSock 2.2 DLL Ȯ��
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		perror("Load WinSock 2.2 DLL Error");

	// ���� ���� (AF_INET = IPv4 �ּ�ü�� / SOCK_DGRAM = UDP/IP)
	clnt_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	// ���� ���� ���� Ȯ��
	if (clnt_sock == INVALID_SOCKET)
		perror("Socket Error");

	memset(&serv_addr, 0, sizeof(SOCKADDR_IN));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	// htons = �򿣵�� 32��Ʈ long / atoi = ���ڿ��� ����Ÿ������
	serv_addr.sin_port = htons(atoi(argv[1]));

	// ä�� �κ�
	while (1) {
		// server�� ���� �޼��� �Է�
		printf("�޼����� �Է��ϼ��� >> ");
		gets_s(message, sizeof(message));
		sendto(clnt_sock, message, sizeof(message) - 1, 0, (SOCKADDR*)&serv_addr, tolen);

		// exit = ����
		if (check_exit(message) == 0)
			break;

		// server���� �޼��� ����
		recvfrom(clnt_sock, message, sizeof(message) - 1, 0, (SOCKADDR*)&serv_addr, &tolen);
		printf("[Server] : %s\n", message);

		// exit = ����
		if (check_exit(message) == 0)
			break;
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
		printf("[Server] : Close Conneciton...\n");
		return 0;
	}
	else
		return 1;
}