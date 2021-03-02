/* ==
* @brief TCP 채팅 프로그램(스레드 사용 X) - Client
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

	// WinSock 2.2 DLL 확인
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		perror("Load WinSock 2.2 DLL Error");

	// 소켓 생성 (AF_INET = IPv4 주소체계 / SOCK_STREAM = TCP/IP)
	clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (clnt_sock == INVALID_SOCKET)
		perror("Socket Error");

	// 포트 넘버 입력
	printf("Input Port Number : ");
	gets_s(message, sizeof(message));
	port_num = atoi(message);

	// 소켓 설정 (AF_INET = IPv4 주소체계 / IP_ADDR = 127.0.0.1)
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	serv_addr.sin_port = htons(port_num);

	// 연결 요청
	if (connect(clnt_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		perror("Connection Error");
	else
		printf("Connection Complete!\n");

	// 채팅 부분
	while (1) {
		// server로 보낼 메세지 입력
		printf("메세지를 입력하세요 >> ");
		gets_s(message, sizeof(message));
		send(clnt_sock, message, sizeof(message) - 1, 0);

		if (check_exit(message) == 0)
			break;

		// server로부터 받음
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
* @brief "exit" 입력 확인 후 종료 체크
* @param char* 입력받은 메세지
* @return exit입력 확인 0 / 이외 1
== */
int check_exit(char* message) {
	if (strcmp(message, "exit") == 0) {
		printf("[Server] : Close Connection...\n");
		return 0;
	}
	else
		return 1;
}