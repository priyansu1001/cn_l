#include <stdio.h>
#include <stdlib.h>

// Function to swap the contents of two variables
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[]) {
    // Ensure the program is called with two arguments
    if (argc != 3) {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    // Convert command line arguments to integers
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    // Print the original values
    printf("Original values:\n");
    printf("num1 = %d, num2 = %d\n", num1, num2);

    // Swap the values
    swap(&num1, &num2);

    // Print the swapped values
    printf("Swapped values:\n");
    printf("num1 = %d, num2 = %d\n", num1, num2);

    return 0;
}
