#include <stdio.h>
#include <string.h>

// Define the 'dob' structure
struct dob {
    int day;
    int month;
    int year;
};

// Define the 'student_info' structure
struct student_info {
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

// Function to print student information using call-by-value
void printStudentInfoByValue(struct student_info student) {
    printf("Using call-by-value:\n");
    printf("Roll No: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("DOB: %02d/%02d/%04d\n", student.age.day, student.age.month, student.age.year);
}

// Function to print student information using call-by-address
void printStudentInfoByAddress(struct student_info *student) {
    printf("Using call-by-address:\n");
    printf("Roll No: %d\n", student->roll_no);
    printf("Name: %s\n", student->name);
    printf("CGPA: %.2f\n", student->CGPA);
    printf("DOB: %02d/%02d/%04d\n", student->age.day, student->age.month, student->age.year);
}

int main() {
    // Create an instance of 'student_info' and populate its members
    struct student_info student;
    student.roll_no = 1;
    strcpy(student.name, "John Doe");
    student.CGPA = 3.75;
    student.age.day = 15;
    student.age.month = 8;
    student.age.year = 2000;

    // Call the function using call-by-value
    printStudentInfoByValue(student);

    // Call the function using call-by-address
    printStudentInfoByAddress(&student);

    return 0;
}
