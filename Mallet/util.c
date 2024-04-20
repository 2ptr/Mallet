#include <Windows.h>
#include <stdio.h>

// Useful struct for managing payloads.
struct PayloadInfo {
	PVOID pPayload;
	SIZE_T sPayloadSize;
}PayloadInfo;

// Struct for menu option management
struct UserOptions {
	char sCipher[1024];
	int cPlacement;
	int cExecute;
	int cFormat;
	int cObfuscate;
} UserOptions;

// Generate random bytes buffer (used for keygen)
void RandomBytes(PBYTE pByte, SIZE_T sSize)
{
	srand(time(NULL) ^ pByte[0]);
	for (int i = 0; i < sSize; i++) {
		pByte[i] = (BYTE)rand() % 0xFF;
	}
}

// Dumps hex of a memory buffer
void DumpHexBuffer(PBYTE Data, SIZE_T Size) {
	//printf("\n======= DUMP ADDRESS 0x%p | SIZE %ld =======\n", Data, Size);
	for (int i = 0; i < Size; i++) {
			printf("\\x%0.2X", Data[i]);
	}
	printf("\n");
}

BOOL MeterpreterPayload(PVOID pPayload, SIZE_T sPayloadSize)
{
	char sListenerIP[1024];
	int sListenerPort = 0;

	printf("\nListener IP: ");
	scanf("%s", sListenerIP);
	printf("\nListener Port: ");
	scanf("%i", sListenerPort);

	return EXIT_SUCCESS;
}

BOOL RevshellPayload(PVOID pPayload, SIZE_T sPayloadSize)
{
	char sListenerIP[1024];
	int sListenerPort = 0;

	printf("\nListener IP: ");
	scanf("%s", sListenerIP);
	printf("\nListener Port: ");
	scanf("%i", sListenerPort);

	return EXIT_SUCCESS;
}

BOOL HavocPayload(PVOID pPayload, SIZE_T sPayloadSize)
{
	char sListenerIP[1024];
	int sListenerPort = 0;

	printf("\nListener IP: ");
	scanf("%s", sListenerIP);
	printf("\nListener Port: ");
	scanf("%i", sListenerPort);

	return EXIT_SUCCESS;
}