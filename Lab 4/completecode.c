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

int countParityBits(int messageLength) {
    int m = 0;
    while ((1 << m) < messageLength + m + 1) {
        m++;
    }
    return m;
}

// Function to set a specific bit in a binary sequence
void setBit(char *sequence, int bitPosition, char bitValue) {
    sequence[bitPosition] = bitValue;
}

// Function to generate Hamming code
void generateHammingCode(char *sendm, int parity, char *output) {
    int m = strlen(sendm);               // Length of the original message
    int parityBits = countParityBits(m); // Number of parity bits needed

    int totalBits = m + parityBits; // Total number of bits in the output
    int j = 0;                      // Index for the original message
    int k = 0;                      // Index for the output

    // Initialize the output message with '0's
    memset(output, '0', totalBits);

    // Calculate and set parity bits
    for (int i = 0; i < totalBits; i++) {
        if ((i + 1) == (1 << j)) {
            j++;
        } else {
            // Copy the original message bits
            setBit(output, i, sendm[k]);
            k++;
        }
    }

    // Calculate and set parity bits based on the parity type
    for (int p = 0; p < parityBits; p++) {
        int parityPosition = (1 << p) - 1;
        char computedParity = '0'; // Initialize with '0' for even parity

        // Calculate parity bit
        for (int i = parityPosition; i < totalBits; i += (1 << (p + 1))) {
            for (int j = 0; j < (1 << p); j++) {
                if (i + j < totalBits) {
                    if (output[i + j] == '1') {
                        computedParity = (computedParity == '1') ? '0' : '1';
                    }
                }
            }
        }

        // Set the calculated parity bit
        if (parity == 1) {
            // Odd parity
            setBit(output, parityPosition, (computedParity == '1') ? '0' : '1');
        } else {
            // Even parity
            setBit(output, parityPosition, computedParity);
        }
    }
}

int isBitSet(char *sequence, int bitPosition) {
    return sequence[bitPosition - 1] == '1';
}

// Function to check for errors in the received Hamming Coded message
int checkMessage(char *recvm, int parity) {
    int totalBits = strlen(recvm);     // Total number of bits in the received message
    int parityBits = countParityBits(totalBits); // Number of parity bits needed

    int errorBit = 0; // Bit position of the erroneous bit (if any)

    // Calculate and check parity bits
    for (int p = 0; p < parityBits; p++) {
        int parityPosition = (1 << p) - 1;
        char computedParity = '0'; // Initialize with '0' for even parity

        // Calculate parity bit
        for (int i = parityPosition; i < totalBits; i += (1 << (p + 1))) {
            for (int j = 0; j < (1 << p); j++) {
                if (i + j < totalBits) {
                    if (recvm[i + j] == '1') {
                        computedParity = (computedParity == '1') ? '0' : '1';
                    }
                }
            }
        }

        // Check the calculated parity bit against the received parity bit
        int receivedParityBit = isBitSet(recvm, parityPosition + 1); // Adjust for 1-based index
        if (parity == 1) {
            // Odd parity
            if (computedParity != receivedParityBit + '0') {
                errorBit += (1 << p);
            }
        } else {
            // Even parity
            if (computedParity == receivedParityBit + '0') {
                errorBit += (1 << p);
            }
        }
    }

    return errorBit;
}

int main() {
    int invokingMode;
    char sendm[100];
    char poly[100];
    char inputLine[100];
    
    scanf("%d", &invokingMode);
    scanf("%s", sendm);
    scanf("%s", poly);

    if (invokingMode == 0) {
        // CRC related functions
        while (scanf("%s", inputLine) != EOF) {
            int result = checkCRC(inputLine, poly);
            printf("%d ", result);
        }
    } else if (invokingMode == 1) {
        // Hamming Code related functions
        int parity;
        scanf("%d", &parity);
        
        while (scanf("%s", inputLine) != EOF) {
            int result = checkMessage(inputLine, parity);
            printf("%d ", result);
        }
    }

    return 0;
}