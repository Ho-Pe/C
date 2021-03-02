/* ==
* @brief server.c 헤더파일
* @reporting date 19/12/23
== */

#define _WINSOCK_DEPRECATED_NO_WARNINGS  // 에러 방지
#pragma comment(lib, "ws2_32.lib")  // 라이브러리 위치 특정
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <conio.h>

#define BUFSIZE 4096  // 버퍼사이즈
#define IP_ADDR "127.0.0.1"  // 아이피