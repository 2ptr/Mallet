#include <stdio.h>
#include "aes.h"
#include "Common.h"

int Generate(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions)
{

	// Padding and setting stuff up
	PVOID pPaddedPayload = NULL;
	SIZE_T sPaddedPayloadSize = NULL;
	if (sMenuOptions.cAlgorithm == 1 && sMenuOptions.nRounds != 0 && (sPayloadSize % 16) != 0)
	{
		AESPadding((PBYTE)pPayload, sPayloadSize, (PBYTE*)& pPaddedPayload, (SIZE_T*)&sPaddedPayloadSize);
	}
	else {
		pPaddedPayload = pPayload;
		sPaddedPayloadSize = sPayloadSize;
	}

	// Encrypt and log to keychain
	BYTE* pKey[32];
	BYTE* pIV[16];
	for (int j = 0; j < sMenuOptions.nRounds; j++) {
		switch (sMenuOptions.cAlgorithm) {
		case 1: //AES
			AESEncrypt((PBYTE)pPaddedPayload, sPaddedPayloadSize, (BYTE*)pKey, (BYTE*)pIV);
			LogAES((BYTE*)pKey, (BYTE*)pIV, j);
			break;
		case 2: //RC4
			printf("RC4!\n");
			break;
		case 3: //XOR
			printf("XOR!\n");
			break;
		}
	}

	// Write runner
	WriteRunner(pPaddedPayload, sPaddedPayloadSize, sMenuOptions);

	return EXIT_SUCCESS;
}