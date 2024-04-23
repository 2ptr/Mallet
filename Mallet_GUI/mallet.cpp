#include <stdio.h>
#include "Common.h"

void Mallet(struct UserOptions sMenuOptions)
{

	// Clear keychain
	FILE* fKeychain = fopen("..\\..\\..\\Output\\keychain.txt", "w");
	fprintf(fKeychain, "");
	fclose(fKeychain);

	// Determine payload mode and load it in

	PVOID pPayload = NULL;
	SIZE_T sPayloadSize = NULL;

	char* temp = (sMenuOptions.sPayloadName).data(); // stupid
	ReadShellcode(temp, &pPayload, &sPayloadSize);

	Generate(pPayload, sPayloadSize, sMenuOptions);
	Compile();

	MessageBox(NULL, L"Compilation successful. Check Output folder for results.", L"Success", MB_OK);

	exit(0);
}