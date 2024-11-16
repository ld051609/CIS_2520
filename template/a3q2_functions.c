#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the smallest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
*/
void downHeap(int key[20], int pos, int array[20][10]){
  // Key contains the node values and pos is the position of the node to be downheaped

  // largestNode is the position of the current node
  int largestNode = pos;

  // leftChild and rightChild are the positions of the left and right children of the current node
  int leftChild = 2*pos + 1;
  int rightChild = 2*pos + 2;

  // Check if the pos has children, if not then return cuz it's a leaf node
  if(!isParent(pos)){
    return;
  }

  // If the left child is greater than the current node, then the largest node is the left child
  if(leftChild < 20 && key[leftChild] > key[largestNode]){
    largestNode = leftChild;
  }

  // If the right child is greater than the current node, then the largest node is the right child
  if(rightChild < 20 && key[rightChild] > key[largestNode]){
    largestNode = rightChild;
  }

  // If the largest node is not the current node, then the current node and the largest node are swapped
  if(largestNode != pos){
    swap(pos, largestNode, key, array);
    downHeap(key, largestNode, array);
  }

}

// The isParent function returns true if the passed position has a child or false if there's no child
bool isParent(int keyPos){
  // Check whether the keyPos has left child or right child or both
  int leftChild = 2*keyPos + 1;
  int rightChild = 2*keyPos + 2;
  if(leftChild || rightChild){
    return true;
  }

  return false;

}

// The swap function swaps 2 rows in the 2D array and the key array. It receives the position of the 2 rows to be swapped, the key array, and the 2D array in its arguements.
void swap(int key1Pos, int key2Pos, int key[20], int array[20][10]){
  // Swapping the keys (node values)
  int tempKey = key[key1Pos];
  key[key1Pos] = key[key2Pos];
  key[key2Pos] = tempKey;

  // Swapping keys' rows in the 2D array
  for(int i = 0; i < 10; i++){
    int tempNum = array[key1Pos][i];
    array[key1Pos][i] = array[key2Pos][i];
    array[key2Pos][i] = tempNum;
  }

}
