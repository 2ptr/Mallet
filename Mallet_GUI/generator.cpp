#include <stdio.h>
#include "aes.h"
#include "Common.h"

int Generate(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions)
{

	// Padding and setting stuff up early
	PVOID pPaddedPayload = NULL;
	SIZE_T sPaddedPayloadSize = NULL;
	if ((sPayloadSize % 16) != 0)
	{
		// printf("Padding payload...\n");
		AESPadding((PBYTE)pPayload, sPayloadSize, (PBYTE*)& pPaddedPayload, (SIZE_T*)&sPaddedPayloadSize);
		// printf("New payload size: %ld bytes\n", sPaddedPayloadSize);

	}
	else {
		pPaddedPayload = pPayload;
		sPaddedPayloadSize = sPayloadSize;
	}
	BYTE* pKey[32];
	BYTE* pIV[16];

	// Loop over the user's encryption string.

	int enc;
	for (int j = 0; j < sMenuOptions.nRounds; j++) {
		enc = sMenuOptions.sCipher[j] - '0'; // Trick to convert from ascii val
		switch (enc) {
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
		default:
			printf("Invalid method specified: %ld. Skipping encryption round...\n", enc);
			break;
		}
	}
	// printf("Keychain written to keychain.txt.\n");

	WriteRunner(pPaddedPayload, sPaddedPayloadSize, sMenuOptions);

	return EXIT_SUCCESS;
}