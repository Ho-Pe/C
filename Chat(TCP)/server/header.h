/* ==
* @brief server.c �������
* @reporting date 19/12/23
== */

#define _WINSOCK_DEPRECATED_NO_WARNINGS  // ���� ����
#pragma comment(lib, "ws2_32.lib")  // ���̺귯�� ��ġ Ư��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <conio.h>

#define BUFSIZE 4096  // ���ۻ�����
#define IP_ADDR "127.0.0.1"  // ������