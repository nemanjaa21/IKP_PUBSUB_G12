#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>
#include "Queue.h"

#define SAFE_DELETE_HANDLE(h) {if(h)CloseHandle(h);}

bool InitializeWindowsSockets()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed with error: %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

MessageStruct* GenerateMessageStruct(char* poruka, int duzina) {

	MessageStruct* messageStruct = (MessageStruct *)(malloc(sizeof(MessageStruct)));

	messageStruct->header = duzina;
	memcpy(messageStruct->poruka, poruka, duzina);

	return messageStruct;

}
