#pragma once

#include <Windows.h>
#include <iostream>
using namespace std;
#ifndef COMMON_H
#define COMMON_H

// Util
typedef struct UserOptions {
	int cPayloadMode;
	int cTemplate;
	string sListenerIP;
	string sListenerPort;
	string sPayloadName;
	int cPlacement;
	string sCipher;
	int nRounds;
	int cFormat;
	string sExport;
	int cExecute;
	string sProcess;
}UserOptions;
void RandomBytes(PBYTE pByte, SIZE_T sSize);
BOOL RevshellPayload(OUT PVOID* pPayload, OUT SIZE_T* sPayloadSize, IN struct UserOptions sMenuOptions);
BOOL MeterpreterPayload(OUT PVOID* pPayload, OUT SIZE_T* sPayloadSize, IN struct UserOptions sMenuOptions);

// Main
void Mallet(struct UserOptions sMenuOptions);

// IO functions
BOOL ReadShellcode(IN char* sFileName, OUT PVOID* pPayload, OUT SIZE_T* sPayloadSize);
BOOL LogAES(IN BYTE* pKey, IN BYTE* pIV, IN int nRound);
BOOL WriteRunner(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions);
BOOL WriteHeader(IN PBYTE pPayload, IN SIZE_T sPayloadSize, IN FILE* fRunner, IN struct UserOptions sMenuOptions);
BOOL WriteExecution(IN FILE* fRunner, IN struct UserOptions sMenuOptions);

// Generator
int Generate(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions);

// Compiler
void Compile();

// Encryption
BOOL AESPadding(IN PBYTE pPayload, IN SIZE_T sPayloadSize, OUT PBYTE* pPaddedRet, OUT SIZE_T* sPaddedSizeRet);
BOOL AESEncrypt(OUT PBYTE pPayload, OUT SIZE_T sPayloadSize, OUT BYTE* pKey, OUT BYTE* pIV);

#endif // !1
