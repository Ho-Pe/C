/* ==
* @brief UDP 채팅 프로그램(스레드 사용 X) - Client
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

	// 포트 입력 확인
	if (argc != 2) {
		printf("Please, Insert Port Number\n");
		exit(0);
	}

	// WinSock 2.2 DLL 확인
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		perror("Load WinSock 2.2 DLL Error");

	// 소켓 생성 (AF_INET = IPv4 주소체계 / SOCK_DGRAM = UDP/IP)
	clnt_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	// 소켓 생성 에러 확인
	if (clnt_sock == INVALID_SOCKET)
		perror("Socket Error");

	memset(&serv_addr, 0, sizeof(SOCKADDR_IN));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	// htons = 빅엔디안 32비트 long / atoi = 문자열을 정수타입으로
	serv_addr.sin_port = htons(atoi(argv[1]));

	// 채팅 부분
	while (1) {
		// server로 보낼 메세지 입력
		printf("메세지를 입력하세요 >> ");
		gets_s(message, sizeof(message));
		sendto(clnt_sock, message, sizeof(message) - 1, 0, (SOCKADDR*)&serv_addr, tolen);

		// exit = 종료
		if (check_exit(message) == 0)
			break;

		// server에서 메세지 받음
		recvfrom(clnt_sock, message, sizeof(message) - 1, 0, (SOCKADDR*)&serv_addr, &tolen);
		printf("[Server] : %s\n", message);

		// exit = 종료
		if (check_exit(message) == 0)
			break;
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
		printf("[Server] : Close Conneciton...\n");
		return 0;
	}
	else
		return 1;
}