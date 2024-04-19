#pragma once
#ifndef UTIL_H
#define UTIL_H

struct PayloadInfo {
	PVOID pPayload;
	SIZE_T sPayloadSize;
}PayloadInfo;

// Struct for menu option management
struct UserOptions {
	char* sCipher;
	int nRounds;
	int cPlacement;
	int cExecute;
	int cFormat;
	int cObfuscate;
} UserOptions;

#endif