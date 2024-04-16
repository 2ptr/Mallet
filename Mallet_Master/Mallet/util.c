#include <Windows.h>
#include <stdio.h>

struct PayloadInfo {
	PVOID pPayload;
	SIZE_T sPayloadSize;
}PayloadInfo;

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

// Takes in a buffer for AES-256 and pads with null bytes if needed (taken from MA)
BOOL PaddingAES(IN PBYTE pPayload, IN SIZE_T sPayloadSize, OUT PBYTE* pPaddedRet, OUT SIZE_T* sPaddedSizeRet) {

	// Init buffers
	PBYTE	pPadded = NULL;
	SIZE_T	sPaddedSize = NULL;

	// Find closest 16th multiple and allocate mem
	sPaddedSize = sPayloadSize + 16 - (sPayloadSize % 16);
	pPadded = malloc(sPaddedSize);

	// Zero memory as we just want to add some null bytes
	ZeroMemory(pPadded, sPaddedSize);

	// Copy payload to expanded buffer and return expanded buffer
	memcpy(pPadded, pPayload, sPayloadSize);
	*pPaddedRet = pPadded;
	*sPaddedSizeRet = sPaddedSize;

	return TRUE;
}