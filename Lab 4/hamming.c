#include <stdio.h>
#include <string.h>

// Function to count the number of parity bits needed
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

int main() {
    char sendm[] = "1101"; // Message to be encoded
    int parity = 1;       // Odd parity (change to 0 for even parity)
    int totalBits = strlen(sendm) + countParityBits(strlen(sendm));
    char output[totalBits + 1]; // +1 for the null-terminator

    generateHammingCode(sendm, parity, output);

    printf("Original Message: %s\n", sendm);
    printf("Hamming Code: %s\n", output);

    return 0;
}
