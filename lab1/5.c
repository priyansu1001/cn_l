#include <stdio.h>
#include <stdint.h>

// Function to check endianness
int isLittleEndian() {
    uint32_t test = 1;
    return (*(uint8_t *)&test == 1);
}

// Function to convert endianness
uint32_t convertEndianness(uint32_t num) {
    return ((num >> 24) & 0xFF) |
           ((num >> 8) & 0xFF00) |
           ((num << 8) & 0xFF0000) |
           ((num << 24) & 0xFF000000);
}

// Function to print the content of each byte
void printBytes(uint32_t num) {
    uint8_t *bytePtr = (uint8_t *)&num;
    for (int i = 0; i < 4; i++) {
        printf("Byte %d: %02X\n", i, bytePtr[i]);
    }
}

int main() {
    uint32_t number;

    // Check endianness of the machine
    if (isLittleEndian()) {
        printf("Host machine is Little Endian.\n");
    } else {
        printf("Host machine is Big Endian.\n");
    }

    // Prompt the user to enter a number
    printf("Enter a 32-bit unsigned integer: ");
    scanf("%u", &number);

    // Print the content of each byte location
    printf("Original number byte representation:\n");
    printBytes(number);

    // Convert the endianness of the number
    uint32_t convertedNumber = convertEndianness(number);

    // Print the content of each byte location after conversion
    printf("Converted number byte representation:\n");
    printBytes(convertedNumber);

    return 0;
}
