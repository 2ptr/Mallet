#undef UNICODE // This is required for proper name parsing
#include <ctype.h>
#include <Tlhelp32.h>

BOOL GetProcessHandle(LPWSTR sProcessName, DWORD* iProcessID, HANDLE* hProcess)
{
	// Get snapshot
	HANDLE hSnapshot = NULL;
	PROCESSENTRY32 pProcess = { .dwSize = sizeof(PROCESSENTRY32) };
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	do {
		// Lower image name for compare
		for (int i = 0; pProcess.szExeFile[i]; i++) {
			pProcess.szExeFile[i] = tolower(pProcess.szExeFile[i]);
		}
		// Find target process and return
		if (strcmp(pProcess.szExeFile, sProcessName) == 0) {
			*iProcessID = pProcess.th32ProcessID;
			*hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pProcess.th32ProcessID);
		}
	} while (Process32Next(hSnapshot, &pProcess));

	return EXIT_SUCCESS;

}

