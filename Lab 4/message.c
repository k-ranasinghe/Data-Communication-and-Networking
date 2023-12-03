#include <stdio.h>
#include <string.h>

// Function to count the number of parity bits needed
int countParityBits(int totalBits) {
    int m = 0;
    while ((1 << m) < totalBits + m + 1) {
        m++;
    }
    return m;
}

// Function to check if a bit is set at the given position
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
    char recvm[] = "1010110"; // Received Hamming Coded message (change a bit for testing)
    int parity = 1;          // Odd parity (change to 0 for even parity)

    int errorBit = checkMessage(recvm, parity);

    if (errorBit != 0) {
        printf("Error detected at bit position %d\n", errorBit);
    } else {
        printf("No errors detected\n");
    }

    return 0;
}
