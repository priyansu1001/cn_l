#include <stdio.h>
#include <stdint.h> // for uint32_t

int main() {
    // Define a 32-bit unsigned integer (4 bytes)
    uint32_t number;

    // Prompt the user to enter a number
    printf("Enter a 32-bit unsigned integer: ");
    scanf("%u", &number);

    // Extract each byte
    unsigned char byte1 = (number >> 24) & 0xFF;
    unsigned char byte2 = (number >> 16) & 0xFF;
    unsigned char byte3 = (number >> 8) & 0xFF;
    unsigned char byte4 = number & 0xFF;

    // Print the bytes
    printf("Byte 1: %02X\n", byte1);
    printf("Byte 2: %02X\n", byte2);
    printf("Byte 3: %02X\n", byte3);
    printf("Byte 4: %02X\n", byte4);

    return 0;
}
