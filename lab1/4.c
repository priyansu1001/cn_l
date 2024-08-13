#include <stdio.h>
#include <stdint.h> // for uint32_t

// Define the 'pkt' structure
struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    // Define a 32-bit unsigned integer (4 bytes)
    uint32_t number;

    // Prompt the user to enter a number
    printf("Enter a 32-bit unsigned integer: ");
    scanf("%u", &number);

    // Create an instance of 'pkt' and populate its members
    struct pkt packet;
    packet.ch1 = (number >> 24) & 0xFF;
    packet.ch2[0] = (number >> 16) & 0xFF;
    packet.ch2[1] = (number >> 8) & 0xFF;
    packet.ch3 = number & 0xFF;

    // Print the content of each member of the structure
    printf("Content of each member:\n");
    printf("ch1: %02X\n", (unsigned char)packet.ch1);
    printf("ch2[0]: %02X\n", (unsigned char)packet.ch2[0]);
    printf("ch2[1]: %02X\n", (unsigned char)packet.ch2[1]);
    printf("ch3: %02X\n", (unsigned char)packet.ch3);

    // Aggregate the members to form the original number
    uint32_t aggregated_number = ((uint32_t)packet.ch1 << 24) |
                                 ((uint32_t)packet.ch2[0] << 16) |
                                 ((uint32_t)packet.ch2[1] << 8) |
                                 (uint32_t)packet.ch3;

    // Print the aggregated number
    printf("Aggregated number: %u\n", aggregated_number);

    return 0;
}
