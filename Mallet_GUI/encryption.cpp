#include <stdio.h>
extern "C"
{
#include "aes.h"
}
#include "Common.h"

// Takes in a buffer for AES-256 and pads with null bytes if needed (taken from MA)
BOOL AESPadding(IN PBYTE pPayload, IN SIZE_T sPayloadSize, OUT PBYTE* pPaddedRet, OUT SIZE_T* sPaddedSizeRet) {

	// Init buffers
	PBYTE	pPadded = NULL;
	SIZE_T	sPaddedSize = NULL;

	// Find closest 16th multiple and allocate mem
	sPaddedSize = sPayloadSize + 16 - (sPayloadSize % 16);
	pPadded = (PBYTE)malloc(sPaddedSize);

	// Zero memory as we just want to add some null bytes
	ZeroMemory(pPadded, sPaddedSize);

	// Copy payload to expanded buffer and return expanded buffer
	memcpy(pPadded, pPayload, sPayloadSize);
	*pPaddedRet = pPadded;
	*sPaddedSizeRet = sPaddedSize;

	return TRUE;
}

// Will encrypt a payload with a random key. Returns payload and the keys used
BOOL AESEncrypt(OUT PBYTE pPayload, OUT SIZE_T sPayloadSize, OUT BYTE* pKey, OUT BYTE* pIV)
{
	// Init Tiny-AES struct
	struct AES_ctx tiny;

	// Update key buffers
	RandomBytes(pKey, 32);
	RandomBytes(pIV, 16);

	AES_init_ctx_iv(&tiny, pKey, pIV);
	AES_CBC_encrypt_buffer(&tiny, pPayload, sPayloadSize);

	return EXIT_SUCCESS;
}

BOOL XOREncrypt(OUT PBYTE pPayload, OUT SIZE_T sPayloadSize, OUT BYTE* pKey)
{
	// Update key
	RandomBytes(pKey, 32);

	for (size_t i = 0, j = 0; i < sPayloadSize; i++, j++) {
		// if end of the key, start again 
		if (j >= 32)
		{
			j = 0;
		}
		pPayload[i] = pPayload[i] ^ pKey[j];
	}

	return EXIT_SUCCESS;
}