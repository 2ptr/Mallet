#include "Common.h"
using namespace std;

// Generate random bytes buffer (used for keygen)
void RandomBytes(PBYTE pByte, SIZE_T sSize)
{
	srand(time(NULL) ^ pByte[0]);
	for (int i = 0; i < sSize; i++) {
		pByte[i] = (BYTE)rand() % 0xFF;
	}
}

// Dumps hex of a memory buffer
void DumpHexBuffer(PBYTE Data, SIZE_T Size) {
	//printf("\n======= DUMP ADDRESS 0x%p | SIZE %ld =======\n", Data, Size);
	for (int i = 0; i < Size; i++) {
		printf("\\x%0.2X", Data[i]);
	}
	printf("\n");
}

void Copyfile(IN string sFromFile, OUT FILE* fDump)
{
	ifstream file(sFromFile);
	string line;
	while (getline(file, line))
	{
		fprintf(fDump, line.c_str());
		fprintf(fDump, "\n");
	}
}