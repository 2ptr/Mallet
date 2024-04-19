#include <stdio.h>
#include <Windows.h>
#include "aes.h"
#include "util.h"
#include "encryption.h"

// Quick Mode - AES with Local Thread Execution.
void QuickMode(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions)
{
	
	struct PayloadInfo pPadded;
	pPadded.pPayload = NULL;
	pPadded.sPayloadSize = NULL;

	// Check for padding
	if ((sPayloadSize % 16) != 0)
	{
		printf("Padding payload...\n");
		AESPadding(pPayload, sPayloadSize, &pPadded.pPayload, &pPadded.sPayloadSize);
		printf("New payload size: %ld bytes\n", pPadded.sPayloadSize);

	}
	else {
		pPadded.pPayload = pPayload;
		pPadded.sPayloadSize = sPayloadSize;
	}

	// Generate Keys and Encrypt
	printf("Encrypting payload...\n");

	BYTE* pKey[32];
	BYTE* pIV[16];

	AESEncrypt(pPadded.pPayload, pPadded.sPayloadSize, pKey, pIV);
	LogAES(pKey, pIV, 0);

	// Write to runner with quickmode settings (.text, one round AES)
	WriteRunner(pPadded.pPayload, pPadded.sPayloadSize, sMenuOptions);

	return EXIT_SUCCESS;
}

// Custom Mode

void CustomMode(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions)
{

	// Padding and setting stuff up early
	struct PayloadInfo pPadded;
	pPadded.pPayload = NULL;
	pPadded.sPayloadSize = NULL;
	if ((sPayloadSize % 16) != 0)
	{
		printf("Padding payload...\n");
		AESPadding(pPayload, sPayloadSize, &pPadded.pPayload, &pPadded.sPayloadSize);
		printf("New payload size: %ld bytes\n", pPadded.sPayloadSize);

	}
	else {
		pPadded.pPayload = pPayload;
		pPadded.sPayloadSize = sPayloadSize;
	}
	BYTE* pKey[32];
	BYTE* pIV[16];

	// Loop over the user's encryption string.

	int enc;
	for (int j = 0; j < sMenuOptions.nRounds; j++) {
		enc = sMenuOptions.sCipher[j] - '0'; // Trick to convert from ascii val
		switch (enc) {
		case 1: //AES
			AESEncrypt(pPadded.pPayload, pPadded.sPayloadSize, pKey, pIV);
			LogAES(pKey, pIV, j);
			break;
		case 2: //RC3
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
	printf("Keychain written to keychain.txt.\n");

	WriteRunner(pPadded.pPayload, pPadded.sPayloadSize, sMenuOptions);

	return EXIT_SUCCESS;
}