#include <stdio.h>
#include <string.h>

// Function to perform binary XOR operation on two strings
void binaryXOR(char *a, char *b) {
    int len = strlen(a);
    for (int i = 0; i < len; i++) {
        if (a[i] == b[i]) {
            a[i] = '0';
        } else {
            a[i] = '1';
        }
    }
}

// Function to generate CRC
void generateCRC(char *sendm, char *poly, char *crc) {
    // Initialize the CRC result with the message
    strcpy(crc, sendm);

    int msgLen = strlen(sendm);
    int polyLen = strlen(poly);

    // Perform polynomial division (XOR operation)
    for (int i = 0; i <= msgLen - polyLen; i++) {
        if (crc[i] == '1') {
            binaryXOR(crc + i, poly);
        }
    }
}

// Function to check CRC
int checkCRC(char *recvm, char *poly) {
    int msgLen = strlen(recvm);
    int polyLen = strlen(poly);

    // Make a copy of the received message
    char copyMsg[msgLen + 1];
    strcpy(copyMsg, recvm);

    // Perform polynomial division (XOR operation)
    for (int i = 0; i <= msgLen - polyLen; i++) {
        if (copyMsg[i] == '1') {
            binaryXOR(copyMsg + i, poly);
        }
    }

    // If the result is all '0's, no error
    for (int i = 0; i < msgLen; i++) {
        if (copyMsg[i] == '1') {
            return 1; // Error detected
        }
    }

    return 0; // No error detected
}

int main() {
    char sendm[] = "110110101011"; // Binary message
    char recvm[] = "110110101011"; // Received message
    char poly[] = "1011";          // Binary polynomial
    char crc[20];                  // CRC result, adjust the size as needed

    generateCRC(sendm, poly, crc);

    printf("Message: %s\n", sendm);
    printf("CRC Polynomial: %s\n", poly);
    printf("CRC Result: %s\n", crc);

    int error = checkCRC(recvm, poly);

    if (error) {
        printf("Transmission Error Detected!\n");
    } else {
        printf("No Transmission Error Detected.\n");
    }

    return 0;
}
