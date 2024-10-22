#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./q1.h"
// This function is used to get the index of the node
struct car * helper(struct car * head, int nodeIndex){
    struct car * temp = head;
    int i = 0;
    // Transverse the list to find the noden index
    while(temp != NULL && i < nodeIndex){
        temp = temp->next;
        i++;
    }
  // return a pointer to the node at the index
  return temp;
}
// Check if the format of the plate is only letters and numbers with 2-8 characters
bool check_plate_format(char plate[]){
    // Check if the length of the plate is between 2 and 8
    if(strlen(plate) < 2 || strlen(plate) > 8){
        return false;
    }
    // Check if the plate contains only letters and numbers
    for(int i = 0; i < strlen(plate); i++){
        if(!((plate[i] >= '0' && plate[i] <= '9') || (plate[i] >= 'A' && plate[i] <= 'Z') || (plate[i] >= 'a' && plate[i] <= 'z'))){
            return false;
        }
    }
    return true;
}
// check valid date
bool check_date_valid(int date){
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;

    if(month < 1 || month > 12){
        return false;
    }
    int days_in_month;
    switch (month)
    {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        days_in_month = 31;
        break;
    case 4: case 6: case 9: case 11:
        days_in_month = 30;
        break;
    case 2:
        if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0){
            days_in_month = 29;
        }else{
            days_in_month = 28;
        }
        break;
    default:
        return false;
    }
    if(day < 1 || day > days_in_month){
        return false;
    }
    if(year > 2024){
        return false;
    }
    return true;
}