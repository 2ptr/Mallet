#pragma once

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;
#ifndef COMMON_H
#define COMMON_H

// Util
typedef struct UserOptions {
	string sPayloadName;
	int cPlacement;
	int cAlgorithm;
	int nRounds;
	int cFormat;
	string sExport;
	int cExecute;
	int cCalls;
	string sProcess;
}UserOptions;
void RandomBytes(PBYTE pByte, SIZE_T sSize);
void Copyfile(IN string sFromFile, OUT FILE* fDump);

// Main
void Mallet(struct UserOptions sMenuOptions);

// IO functions
BOOL ReadShellcode(IN char* sFileName, OUT PVOID* pPayload, OUT SIZE_T* sPayloadSize);
BOOL LogEncryption(IN BYTE* pKey, IN BYTE* pIV, IN int nRound);
BOOL WriteRunner(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions);
BOOL WriteRsrc(IN PVOID pPayload, IN SIZE_T sPayloadSize);
BOOL WriteWin32Execution(IN FILE* fRunner, IN struct UserOptions sMenuOptions);
BOOL WriteDecryption(IN FILE* fRunner, IN FILE* fKeychain, IN struct UserOptions sMenuOptions);

// Headers
BOOL WriteHeader(IN PBYTE pPayload, IN SIZE_T sPayloadSize, IN FILE* fRunner, IN struct UserOptions sMenuOptions);

// Generator
int Generate(IN PVOID pPayload, IN SIZE_T sPayloadSize, IN struct UserOptions sMenuOptions);

// Compiler
void Compile();

// Encryption
BOOL AESPadding(IN PBYTE pPayload, IN SIZE_T sPayloadSize, OUT PBYTE* pPaddedRet, OUT SIZE_T* sPaddedSizeRet);
BOOL AESEncrypt(OUT PBYTE pPayload, OUT SIZE_T sPayloadSize, OUT BYTE* pKey, OUT BYTE* pIV);
BOOL XOREncrypt(OUT PBYTE pPayload, OUT SIZE_T sPayloadSize, OUT BYTE* pKey);

#endif // !1
