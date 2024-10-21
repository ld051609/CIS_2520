#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "q1.h" // Include your header file with function prototypes

// Function to create a sample file for testing
void create_test_file() {
    FILE *file = fopen("car_data.txt", "w");
    if (file != NULL) {
        fprintf(file, "ABC123,10000,230921\n");
        fprintf(file, "XYZ789,5000,230921\n");
        fprintf(file, "LMN456,7500,-1\n");
        fclose(file);
    } else {
        printf("Error creating test file\n");
    }
}

// Test function to perform all tests
void run_tests() {
    struct car *head = NULL;

    // Test insert_to_list
    printf("Test 1: Inserting cars into the list...\n");
    insert_to_list(&head, "ABC123", 10000, 230921);
    insert_to_list(&head, "XYZ789", 5000, 230921);
    insert_to_list(&head, "LMN456", 7500, -1);

    // Expected output: should print 3 cars
    printf("Expected: 3 cars in the list\n");
    print_list(head);

    // Test is_plate_in_list
    printf("\nTest 2: Checking if plates are in the list...\n");
    printf("ABC123: %s\n", is_plate_in_list(head, "ABC123") ? "Found" : "Not Found");
    printf("XYZ789: %s\n", is_plate_in_list(head, "XYZ789") ? "Found" : "Not Found");
    printf("ZZZ999: %s\n", is_plate_in_list(head, "ZZZ999") ? "Found" : "Not Found");

    // Test sort_list by mileage
    printf("\nTest 3: Sorting cars by mileage...\n");
    sort_list(&head, true, false);
    printf("Expected: Cars sorted by mileage (should be in ascending order)\n");
    print_list(head);

    // Test remove_car_from_list
    printf("\nTest 4: Removing car with plate 'XYZ789'...\n");
    struct car *removed = remove_car_from_list(&head, "XYZ789");
    if (removed) {
        printf("Removed car: Plate: %s, Mileage: %d\n", removed->plate, removed->mileage);
        free(removed);
    }
    printf("Expected: XYZ789 removed\n");
    print_list(head);

    // Test profit_calculator
    printf("\nTest 5: Calculating profit...\n");
    double profit = profit_calculator(10000, 20500);
    printf("Expected profit for mileage difference: $%.2f\n", profit);

    // Write the list to a file
    char *filename = "car_data.txt";
    write_list_to_file(filename, head);
    printf("Expected: List written to %s\n", filename);

    // Free the list
    free_list(&head);
}

// Main function
int main() {
    create_test_file(); // Create a sample test file for read operations
    run_tests(); // Run the tests
    return 0;
}
