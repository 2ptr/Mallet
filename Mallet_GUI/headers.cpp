#include "Common.h"

BOOL WriteHeader(IN PBYTE pPayload, IN SIZE_T sPayloadSize, IN FILE* fRunner, IN struct UserOptions sMenuOptions)
{
	switch (sMenuOptions.cPlacement)
	{
		// .text
	case 1:
	{
		// Import header file
		Copyfile("..\\..\\..\\Assets\\Headers\\staticText.c", fRunner);

		// Write payload and size
		for (int j = 0; j < sPayloadSize; j++) {
			if (j == (sPayloadSize - 1))
			{
				fprintf(fRunner, "0x%0.2X };\n", pPayload[j]);
			}
			else {
				fprintf(fRunner, "0x%0.2X, ", pPayload[j]);
			}
		}
		fprintf(fRunner, "SIZE_T sPayloadSize = %ld;\n\n", sPayloadSize);

		break;
	}
	// .data
	case 2:
	{
		// Import header file
		Copyfile("..\\..\\..\\Assets\\Headers\\staticData_pre.c", fRunner);

		// Write payload and size (const)
		for (int j = 0; j < sPayloadSize; j++) {
			if (j == (sPayloadSize - 1))
			{
				fprintf(fRunner, "0x%0.2X };\n", pPayload[j]);
			}
			else {
				fprintf(fRunner, "0x%0.2X, ", pPayload[j]);
			}
		}
		fprintf(fRunner, "SIZE_T sPayloadSize = %ld;\n\n", sPayloadSize);

		// Finish header
		Copyfile("..\\..\\..\\Assets\\Headers\\staticData_post.c", fRunner);

		break;
	}

	// .rsrc - bit more involved. Need to write payload to .ico and add helper function.
	case 3:
	{
		WriteRsrc(pPayload, sPayloadSize);
		Copyfile("..\\..\\..\\Assets\\Headers\\staticRsrc.c", fRunner);

		break;
	}

	// HTTP stager
	case 4:



		break;
	}

	return EXIT_SUCCESS;
}