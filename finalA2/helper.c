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