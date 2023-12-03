/*
	You can modify this file for your testing purpose 
	but note that we will use our own copies of this file for testing during grading 
	so changes in this file will be overwritten
*/



// function prototypes
void generateCRC(char *sendm, char *poly, char *crc);
int checkCRC(char *recvm, char *poly);
void generateHammingCode(char *sendm, int parity, char *output);
int checkMessage(char *recvm, int parity);
void runCRC(char *sendm, char *poly, char **recvm);//CRC
void runHammingCode(char *sendm, int parity, char **recvm);//Hamming Code
