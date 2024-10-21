#include "q1.h"
#include "./helper.c"
#include <stdio.h>
#include <stdlib.h>

/* function will display the primary user interface
    This is already done for you*/
void prompt(){

  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
  printf("Enter your choice: ");
}

/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
struct car * insert_to_list(struct car ** head, char plate[], int mileage, int return_date){
    // Create a new node
    struct car * newCar = (struct car *)malloc(sizeof(struct car));
    if(newCar == NULL){
        printf("Memory allocation for a new car failed\n");   
        return NULL;
    }
    // Initialize a new car's details
    strcpy(newCar->plate, plate);
    newCar->mileage = mileage;
    newCar->return_date = return_date;
    newCar->next = NULL;

    // Insert the car to the front of the list
    if(*head == NULL){
        *head = newCar;
    }else{
        newCar->next = *head;
        *head = newCar;
    }  
    return newCar;
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head){
    if(head == NULL){
        printf("List is empty\n");  
        return -1;
    }
    struct car * temp = head;
    while(temp != NULL){
        printf("Plate: %s\n, Mileage: %d\n", temp->plate, temp->mileage);
        if(temp->return_date != -1){
            printf("Return Date: ");
            date(temp->return_date);
        }
        printf("\n");
        temp = temp->next;
    }
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car * head, char plate[]){
    if(head == NULL){
        printf("List is empty\n");
        return false;
    }
    struct car * tempHead = head;
    while(tempHead != NULL){
        // check if the 2 plates are the same
        if(strcmp(tempHead->plate, plate) == 0){
            return true;
        }
        // move to the next car
        tempHead = tempHead->next;
    }

    return false;
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b){
    // swap the plates
    char tempPlate[7];
    strcpy(tempPlate, a->plate);
    strcpy(a->plate, b->plate);
    strcpy(b->plate, tempPlate);

    // swap the mileage
    int tempMileage = a->mileage;
    a->mileage = b->mileage;
    b->mileage = tempMileage;

    // swap the return date
    char tempReturnDate[20];
    strcpy(tempReturnDate, a->return_date);
    strcpy(a->return_date, b->return_date);
    strcpy(b->return_date, tempReturnDate);

}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car ** head, bool sort_by_mileage, bool sort_by_return_date){
    if(*head == NULL){
        printf("List is empty\n");
        return -1;
    }
    // sort by mileage with the car having the least miles at the front of the list
    if(sort_by_mileage){
        int counter = 0;
        struct  car * temp = *head;
        while(temp != NULL){
            counter++;
            temp = temp->next;
        }
        free(temp);

        // bubble sort 
        for (int i = 0; i < counter; i++){
            // Get the car at the index 1
            struct car *ptr1 = helper(*head, i);
            for(int j = i+1; j < counter; j++){
                // Get the car at the index 2
                struct car *ptr2 = helper(*head, j);
                if(ptr1->mileage > ptr2->mileage){
                    swap(ptr1, ptr2);
                }
            }
        }
    }
    // with the first car on this list having the earliest expected return date
    if(sort_by_return_date){
        int counter = 0;
        struct  car * temp = *head;
        while(temp != NULL){
            counter++;
            temp = temp->next;
        }
        free(temp);

        // bubble sort 
        for (int i = 0; i < counter; i++){
            // Get the car at the index 1
            struct car *ptr1 = helper(*head, i);
            for(int j = i+1; j < counter; j++){
                // Get the car at the index 2
                struct car *ptr2 = helper(*head, j);
                if(ptr1->return_date > ptr2->return_date){
                    swap(ptr1, ptr2);
                }
            }
        }
    }
    return;
}

/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car * remove_car_from_list(struct car **head, char plate[]){
    if(*head == NULL){
        printf("List is empty\n");
        return NULL;
    }
    struct car * tempHead = *head;
    struct car * prev = NULL;
    while(tempHead != NULL){
        // check if the 2 plates are the same
        if(strcmp(tempHead->plate, plate) == 0){
            // remove the car from the list
            if(prev == NULL){
                *head = tempHead->next;
            }else{
                prev->next = tempHead->next;
            }
            return tempHead;
        }
        // move to the next car
        prev = tempHead;
        tempHead = tempHead->next;
    }
    return NULL;
}

/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car * remove_first_from_list(struct car **head){
    if(*head == NULL){
        printf("List is empty\n");
        return NULL;
    }
    struct car * temp = *head;
    *head = temp->next;
    return temp;

}

/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage){
    int mileageDifference = final_mileage - initial_mileage;
    double charge = 0.0;  
    // a flat rate of $80.00 for up to 200 km  
    if(mileageDifference <= 200){
        charge = 80.0;
    } 
    // 15 cents per km for the additional (i.e. beyond 200) kilometres.
    else {
        charge = 80.0 + (mileageDifference - 200) * 0.15;
    }

}

/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
void write_list_to_file(char *filename, struct car *head){
    // open the file 
    FILE * file = fopen(filename, "w");
    // check if the file was opened successfully
    if(file == NULL){
        printf("Error opening file\n");
        return -1;
    }
    // Define variables
    char plate[7];
    int mileage;
    int return_date;

    struct car * temp = head;
    while(temp != NULL){
        strcpy(plate, temp->plate);
        mileage = temp->mileage;
        return_date = temp->return_date;
        fprintf(file, "%s,%d,%d\n", plate, mileage, return_date);
        temp = temp->next;
    }
    // close the file
    fclose(file);
}

/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Reads data from the file and inserts each car into the list.
 */
void read_file_into_list(char *filename, struct car **head){
    // open the file
    FILE * file = fopen(filename, "r");
    // check if the file was opened successfully
    if(file == NULL){
        printf("Error opening file\n");
        return -1;
    }
    while(!feof(file)){
        // Define variables
        char plate[7];
        int mileage;
        int return_date;
        // Read the data from the file
        fscanf(file, "%s,%d,%d\n", plate, &mileage, &return_date);
        // Insert the car into the list
        insert_to_list(head, plate, mileage, return_date);
    }

    // Close the file
    fclose(file);
}

/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date){
    int year = date / 10000; // get the 1st two digits - YY
    int month = (date % 10000) / 100; // get the next two digits - MM
    int day = date % 100; // get the last two digits - DD
    printf("%d/%d/%d\n", year, month, day);

}

/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car ** head){
    if(*head == NULL){
        printf("List is empty\n");
        return -1;
    }
    struct car * temp = *head;
    struct car * next = NULL;
    while (temp != NULL){
        next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
    printf("List has been freed\n");
}