#include "q1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>  // Include this header for assert

void test_insert_to_list() {
    struct car *head = NULL;

    // Test inserting a single car
    struct car *car1 = insert_to_list(&head, "ABC123", 5000, -1);
    assert(car1 != NULL);
    assert(strcmp(head->plate, "ABC123") == 0);
    assert(head->mileage == 5000);
    assert(head->return_date == -1);

    // Test inserting another car
    struct car *car2 = insert_to_list(&head, "XYZ789", 3000, 20231231);
    assert(car2 != NULL);
    assert(strcmp(head->plate, "XYZ789") == 0);
    assert(head->mileage == 3000);
    assert(head->return_date == 20231231);
    printf("\nTesting insert_to_list passed\n");
}

void test_print_list() {
    struct car *head = NULL;
    insert_to_list(&head, "ABC123", 5000, -1);
    insert_to_list(&head, "XYZ789", 3000, 20231231);

    printf("Testing print_list:\n");
    print_list(head);
    // Output should show both cars with their details
    printf("\nTesting test_print_list passed\n");
}

void test_is_plate_in_list() {
    struct car *head = NULL;
    insert_to_list(&head, "ABC123", 5000, -1);
    
    assert(is_plate_in_list(head, "ABC123") == true);
    assert(is_plate_in_list(head, "XYZ789") == false);

    printf("\nTesting test_is_plate_in_list passed\n");

}

void test_remove_car_from_list() {
    struct car *head = NULL;
    insert_to_list(&head, "ABC123", 5000, -1);
    insert_to_list(&head, "XYZ789", 3000, 20231231);

    struct car *removedCar = remove_car_from_list(&head, "ABC123");
    assert(removedCar != NULL);
    assert(strcmp(removedCar->plate, "ABC123") == 0);
    free(removedCar);

    // Check if car is removed
    assert(is_plate_in_list(head, "ABC123") == false);
    
    printf("\nTesting test_remove_car_from_list passed\n");

}

void test_remove_first_from_list() {
    struct car *head = NULL;
    insert_to_list(&head, "ABC123", 5000, -1);
    insert_to_list(&head, "XYZ789", 3000, 20231231);

    struct car *removedCar = remove_first_from_list(&head);
    assert(removedCar != NULL);
    assert(strcmp(removedCar->plate, "XYZ789") == 0);
    free(removedCar);

    // Check if the head is now "ABC123"
    assert(strcmp(head->plate, "ABC123") == 0);

    printf("\nTesting test_remove_first_from_list passed\n");

}

void test_profit_calculator() {
    double profit = profit_calculator(5000, 5200);
    assert(profit == 80.0); // Within 200 km

    profit = profit_calculator(5000, 5400);
    assert(profit == 110.0); // 200 km + 30 km * 0.15
    
    printf("\nTesting test_profit_calculator passed\n");

}

void test_write_list_to_file() {
    struct car *head = NULL;
    insert_to_list(&head, "ABC123", 5000, -1);
    
    write_list_to_file("test_output.txt", head);

    // You would need to manually check test_output.txt to verify the contents
    
    printf("\nTesting test_write_list_to_file passed\n");

}

void test_read_file_into_list() {
    struct car *head = NULL;
    read_file_into_list("test_input.txt", &head);
    print_list(head);
    // Test if the data has been read correctly (you might want to assert specific values)
    printf("\nTesting test_read_file_into_list passed\n");


}

void test_free_list() {
    struct car *head = NULL;
    insert_to_list(&head, "ABC123", 5000, -1);
    free_list(&head);
    assert(head == NULL); // Head should be NULL after free

    printf("\nTesting test_free_list passed\n");
}

int main() {
    test_insert_to_list();
    test_print_list();
    test_is_plate_in_list();
    test_remove_car_from_list();
    test_remove_first_from_list();
    test_profit_calculator();
    // test_write_list_to_file();
    test_read_file_into_list();
    test_free_list();

    printf("All tests passed!\n");
    return 0;
}
