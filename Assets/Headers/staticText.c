#include <Windows.h>
#include "aes.h"

int main(int argc, char* argv[])
{
	struct AES_ctx ctx;
	BYTE pPayload[] = { 
