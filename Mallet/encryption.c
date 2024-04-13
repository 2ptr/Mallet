#include <stdio.h>
#include <Windows.h>
#include "aes.h"
#include "util.h"

// Quick Mode - Triple AES

void QuickModeEncrypt(OUT PVOID pPayload, IN SIZE_T sPayloadSize)
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

	// Generate IVs and Keys
	printf("Generating keys and IVs...\n");

	BYTE pKey1[32];
	BYTE pIV1[16];
	RandomBytes(pKey1, 32);
	RandomBytes(pIV1, 16);
	BYTE pKey2[32];
	BYTE pIV2[16];
	RandomBytes(pKey2, 32);
	RandomBytes(pIV2, 16);
	BYTE pKey3[32];
	BYTE pIV3[16];
	RandomBytes(pKey3, 32);
	RandomBytes(pIV3, 16);

	// Encrypt
	printf("Encrypting payload...\n");

	AES_init_ctx_iv(&tiny, pKey1, pIV1);
	AES_CBC_encrypt_buffer(&tiny, pPadded.pPayload, pPadded.sPayloadSize);
	AES_init_ctx_iv(&tiny, pKey2, pIV2);
	AES_CBC_encrypt_buffer(&tiny, pPadded.pPayload, pPadded.sPayloadSize);
	AES_init_ctx_iv(&tiny, pKey3, pIV3);
	AES_CBC_encrypt_buffer(&tiny, pPadded.pPayload, pPadded.sPayloadSize);

	// Write keychain to file
	FILE* fptr = fopen("keychain.txt","w");
	fprintf(fptr,"************KEYCHAIN************\n");
	fprintf(fptr, "KEY 1: ");
	for (int i = 0; i < 32; i++) {
		fprintf(fptr, "\\x%0.2X", pKey1[i]);
	}
	fprintf(fptr, "\n");
	fprintf(fptr, "IV 1: ");
	for (int i = 0; i < 16; i++) {
		fprintf(fptr, "\\x%0.2X", pIV1[i]);
	}
	fprintf(fptr, "\n");
	fprintf(fptr, "KEY 2: ");
	for (int i = 0; i < 32; i++) {
		fprintf(fptr, "\\x%0.2X", pKey2[i]);
	}
	fprintf(fptr, "\n");
	fprintf(fptr, "IV 2: ");
	for (int i = 0; i < 16; i++) {
		fprintf(fptr, "\\x%0.2X", pIV2[i]);
	}
	fprintf(fptr, "\n");
	fprintf(fptr, "KEY 3: ");
	for (int i = 0; i < 32; i++) {
		fprintf(fptr, "\\x%0.2X", pKey3[i]);
	}
	fprintf(fptr, "\n");
	fprintf(fptr, "IV 3: ");
	for (int i = 0; i < 16; i++) {
		fprintf(fptr, "\\x%0.2X", pIV3[i]);
	}
	fprintf(fptr, "\n");
	fclose(fptr);
	printf("Keychain written to keychain.txt.");

	return EXIT_SUCCESS;
}

