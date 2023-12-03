// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here

// user-defined header files
#include "transmissionerr.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
void generateCRC(char *sendm, char *poly, char *crc)
{
	//TODO
}
int checkCRC(char *recvm, char *poly)
{
	//TODO
}
void generateHammingCode(char *sendm, int parity, char *output)
{
	//TODO
}
int checkMessage(char *recvm, int parity)
{
	//TODO
}
