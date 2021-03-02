/* ==
* @brief TCP 채팅 프로그램(스레드 사용 X) - Server
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

	// 포트 입력 확인
	if (argc != 2) {
		printf("Please, Insert Port Number\n");
		exit(1);
	}

	// WinSock 2.2 DLL 확인
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		perror("Load WinSock 2.2 DLL Error");

	// 소켓 생성 (AF_INET = IPv4 주소체계 / SOCK_STREAM = TCP/IP)
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 소켓 생성 에러 확인
	if (serv_sock == INVALID_SOCKET)
		perror("Socket Error");

	// 소켓 설정 (AF_INET = IPv4 주소체계 / IP_ADDR = 127.0.0.1)
	memset(&serv_addr, 0, sizeof(SOCKADDR_IN));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	serv_addr.sin_port = htons(atoi(argv[1]));

	// 소켓에 주소를 설정해줌
	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		perror("Bind Error");

	// 소켓 대기
	if (listen(serv_sock, 5) == SOCKET_ERROR)
		perror("Listen Error");

	printf("[Server] : Waiting Connection Request...\n");

	// 소켓 정보 받음
	clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &fromlen);

	// 소켓 정보 에러
	if (clnt_sock == INVALID_SOCKET)
		printf("Accept Error %d\n", WSAGetLastError());
	else {
		printf("[Server] : %s Connection Complete!\n", inet_ntoa(clnt_addr.sin_addr));
		printf("[Server] : Start...\n");
	}

	closesocket(serv_sock);

	// 채팅 부분
	while (1) {
		// client에서 메세지 받음
		rcv = recv(clnt_sock, message, sizeof(message) - 1, 0);
		message[rcv] = '\0';
		if (check_exit(message) == 0)
			break;

		printf("[Client] : %s\n", message);

		// client로 보낼 메세지
		printf("메세지 입력 >> ");
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