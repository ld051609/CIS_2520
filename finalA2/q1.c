#include "q1.h"

/*
 * A basic menu based structure has been provided
*/

int main(){

    //Our three Linked Lists
    struct car *available_head = NULL;
	struct car *rented_head = NULL;
	struct car *repair_head = NULL;

    int choice;

    // starting the program with reading the data from the three files
    // TODO: uncomment later on
    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    do
    {
        prompt();
        scanf("%d", &choice);
        
        /*
         * You will need to add all the cases
         * Call the appropriate functions
         * You would also need to save data to disc upon exit
         * File Format: plate,mileage,return_date
         * Error Handling needs to happen too
        */

        switch (choice)
        {
        /* add a new car to the available-for-rent list */
        case 1:
            printf("Adding a new car to the available-for-rent list\n");
            // 1. Prompting the user for the car's plate, mileage, and return date
            char plate[7];
            int mileage;
            printf("Enter Plate: ");
            scanf("%s", plate);
            // length of 2-8 characters with only numbers and letters (capitalization does not matter).
            if(!check_plate_format(plate)){
                printf("Invalid plate format\n");
                break;
            } 
            // Check if the plate is duplicated or not
            if(is_plate_in_list(available_head, plate) == true){
                printf("Plate number is already in the list\n");
                break;
            }
            printf("Enter Mileage: ");
            scanf("%d", &mileage);
            // Check if mileage is valid
            if (mileage < 0){
                printf("Invalid mileage input\n");
                break;
            }
            // 2. Inserting the car into the available-for-rent list
            insert_to_list(&available_head, plate, mileage, -1);
            printf("Car %s added to the available-for-rent list\n", plate);
            // 3. Sorting the available-for-rent list
            sort_list(&available_head, true, false);
            break;

        /* add a returned car to the available-for-rent list (the rented list needs to be updated as well, and you may view it as transferring the car from the rented to the available-for-rent)*/
        case 2:
            printf("Adding a returned car from the rented list to the available-for-rent list\n");
            // 1. Prompting the user for the car's plate and mileage
            char plate2[7];
            int mileage2;
            
            printf("Enter Plate: ");
            scanf("%s", plate2);
                // Check plate is valid with only numbers and letters (capitalization does not matter).
            if (!check_plate_format(plate2)){
                printf("Invalid plate format\n");
                break;
            }
            printf("Enter Mileage: ");
            scanf("%d", &mileage2);
            // Check if mileage is valid
            if (mileage2 < 0){
                printf("Invalid mileage input\n");
                break;
            }
    
            // 2. Removing the car from the rented list with the given plate number
            struct car *car = remove_car_from_list(&rented_head, plate2);
            if(car == NULL)
            {
                printf("Failed to remove the car.\n");
                break;
            }
            // Check that when returning the car, the current total mileage should be larger than the previous stored mileage of this car.
            if (mileage2 < car->mileage)
            {
                printf("Error: New mileage must be greater than previous mileage (%d).\n", car->mileage);
                insert_to_list(&rented_head, car->plate, car->mileage, car->return_date); // Re-insert the car back to the rented list
                break;
            }
            // 3. Inserting the car into the available-for-rent list
            insert_to_list(&available_head, car->plate, mileage2, -1);
            printf("Car %s added to the available-for-rent list from the rented list\n", car->plate);
            // 4. Compute the charge and print
            double charge = profit_calculator(car->mileage, mileage2);
            printf("The charge for the car is: $%.2f\n", charge);
            
            // Sorting the available-for-rent list and rented list
            sort_list(&available_head, true, false);
            sort_list(&rented_head, false, true);
            break;
        /* add a returned car to the in-repair list (may view as transferring the car from the rented to the in-repair) */
        case 3:
            printf("Adding a returned car from the rented list to the in-repair list\n");
            // 1. Prompting the user for the car's plate and mileage
            char plate3[7];
            int mileage3;
            printf("Enter Plate: ");
            scanf("%s", plate3);
            // length of 2-8 characters with only numbers and letters (capitalization does not matter).
            if(!check_plate_format(plate3)){
                printf("Invalid plate format\n");
                break;
            } 
            printf("Enter Mileage: ");
            scanf("%d", &mileage3);
            if(mileage3 < 0)
            {
                printf("Invalid mileage input\n");
                break;
            }
            // 2. Removing the car from the rented list
            struct car *car2 = remove_car_from_list(&rented_head, plate3);
            if(car2 == NULL)
            {
                printf("Failed to remove the car.\n");
                break;
            }
            // Check that when returning the car, the current total mileage should be larger than the previous stored mileage of this car.
            if(mileage3 < car2->mileage)
            {
                printf("Error: New mileage must be greater than previous mileage (%d).\n", car2->mileage);
                insert_to_list(&rented_head, car2->plate, car2->mileage, car2->return_date); // Re-insert the car back to the rented list
                break;
            }
            // 3. Inserting the car into the in-repair list
            insert_to_list(&repair_head, car2->plate, mileage3, -1);
            printf("Car %s added to the in-repair list from the rented list\n", car2->plate);
            // 4. Compute the charge and print
            double charge2 = profit_calculator(car2->mileage, mileage3);
            printf("The charge for the car is: $%.2f\n", charge2);

            // Sorting the rented list and available-for-rent list
            sort_list(&available_head, true, false);
            sort_list(&rented_head, false, true);
            break;
        /* transfer a car from the in-repair list to the available-for-rent list */
        case 4:
            printf("Transferring a car from the in-repair list to the available-for-rent list\n");
            // 1. Prompting the user for the car's plate 
            char plate4[7];
            printf("Enter Plate: ");
            scanf("%s", plate4);
            // length of 2-8 characters with only numbers and letters (capitalization does not matter).
            if(!check_plate_format(plate4)){
                printf("Invalid plate format\n");
                break;
            } 
            // 2. Removing the car from the rented list 
            struct car *car3 = remove_car_from_list(&repair_head, plate4);
            if(car3 == NULL)
            {
                printf("Failed to remove the car.\n");
                break;
            }
            // 3. Inserting the car into the available-for-rent list
            insert_to_list(&available_head, car3->plate, car3->mileage, -1);
            printf("Car %s added to the available-for-rent list from the in-repair list\n", car3->plate);
            // Sorting the rented list and available-for-rent list
            sort_list(&available_head, true, false);
            sort_list(&rented_head, false, true);
            break;
        /* rent the first available car (may view as transferring the car from the available-for-rent to the rented) */
        case 5:
            printf("Renting the first available car in the available-for-rent list\n");
            // 1. Sorting the available-for-rent list
            sort_list(&available_head, true, false);
            // 2. Prompting the expected return date
            int return_date;
            printf("Enter Return Date: ");
            scanf("%d", &return_date);
            // Check that return date is valid
            if (return_date < 0)
            {
                printf("Error: Return date must be a positive integer.\n");
                break;
            }  
            if(!check_date_valid(return_date))
            {
                printf("Error: Invalid return date.\n");
                break;
            }
            // 3. Removing the first car from the available-for-rent list
            struct car *car4 = remove_first_from_list(&available_head);
            if(car4 == NULL)
            {
                printf("Failed to remove the car.\n");
                break;
            }
            // 4. Inserting the car into the rented list
            insert_to_list(&rented_head, car4->plate, car4->mileage, return_date);
            printf("Car %s rented from the available-for-rent list\n", car4->plate);
            // Sorting the rented list and available-for-rent list
            sort_list(&available_head, true, false);
            sort_list(&rented_head, false, true);
            break;
        /* print all the lists */
        case 6:
            printf("Available-for-Rent List:\n\n");
            sort_list(&available_head, true, false);
            print_list(available_head);
            printf("Rented List:\n");
            sort_list(&rented_head, false, true);
            print_list(rented_head);
            printf("In-Repair List:\n");
            print_list(repair_head);
            break;
        /* exit the program */
        case 7:
            // store the data in the three lists into the three relevant text files (available.txt, rented.txt, repair.txt)
            // TODO: uncomment later on
            write_list_to_file("available.txt", available_head); 
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);
            // Freeing the memory allocated for the lists
            free_list(&available_head);
            free_list(&rented_head);
            free_list(&repair_head);
            printf("Exiting Program\n");
            break;

        default:
            printf("Invalid Choice\n");
            break;
        }
        
    } while (choice != 7);
    

    return 0;
}