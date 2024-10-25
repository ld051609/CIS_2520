/*
Name:
Student ID: 
Assignment 2, Question 2
*/

#include "q2.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Pushes a new value onto the stack.
 * 
 * @param stack Pointer to the pointer of the stack's head.
 * @param value The value to be added to the stack.
 */
void push(Operand **stack, double value){
  Operand *newNode = (Operand *)malloc(sizeof(Operand));
  newNode->value = value; //give the new node the value
  newNode->next = *stack; //point the new node to the current head
  *stack = newNode; //make the new node the head


}


/**
 * Pops the top value from the stack and returns it.
 * 
 * @param stack Pointer to the pointer of the stack's head.
 * @return The value that was at the top of the stack.
 */
double pop(Operand **stack){
  if(*stack == NULL){
    return 0;
  }
  Operand *temp = *stack; //create a temporary pointer to the head
  double value = temp->value; //store the value of the head
  *stack = temp->next; //move the head to the next node
  free(temp); //free the memory of the old head
  return value; //return the value of the old head

}


/**
 * Prints all values in the stack.
 * 
 * @param stack Pointer to the stack's head.
 */
void print(Operand *stack){
  Operand *temp = stack; //create a temporary pointer to the head
  while(temp != NULL){ //while the pointer is not null
    printf("%lf\n", temp->value); //print the value of the node
    temp = temp->next; //move to the next node
  }

  
  
}