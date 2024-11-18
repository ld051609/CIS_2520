#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"


Variable variables[10];
int varCount = 0; 


// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data){
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	if(newNode == NULL){
		printf("Memory allocation for a node failed\n");
		return NULL;
	}
	// Null terminate the data
	data[strlen(data)] = '\0';
	strcpy(newNode->data, data);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr){
		// Logic:
		// 1. If the current character is '(', recursively call parseExpression to build the left subtree.
		// 2. If the current character is a variable, call parseVariable to build the node of subtree.
		// 3. If the current character is a number, call parseNumber to build the node of subtree.
		// 4. If the current character is an operator, create an operator node with the current character as data, and recursively call parseExpression to build the right subtrees.
		// 5. If the current character is ')', return the current subtree
		
    // printf("\n========== ENTER parseExpression ==========\n");
    // printf("Current position (varCount): %d\n", varCount);
    // printf("Processing: %s\n", expr + varCount);
    
    Node* currentSubtree = NULL;  // Tracks the current subtree being built

    while(expr[varCount] != '\0'){
        // Parentheses handling 
        if(expr[varCount] == '('){
            // printf("\n----- Found '(' -----\n");
            // printf("Position: %d\n", varCount);
            varCount++; // Move to the next character
            
						// Recursively call parseExpression to build the left subtree
            currentSubtree = parseExpression(expr);
            
						// TODO: print the left subtree
            // printf("\n----- Parentheses Subtree Result -----\n");
            // if (currentSubtree == NULL) {
            //     printf("Result: NULL subtree\n");
            // } else {
            //     printf("Root: '%s'\n", currentSubtree->data);
            //     printf("Left: '%s'\n", currentSubtree->left ? currentSubtree->left->data : "NULL");
            //     printf("Right: '%s'\n", currentSubtree->right ? currentSubtree->right->data : "NULL");
            // }
            
        }
				// If the current character is ')', return the current subtree
				if(expr[varCount] == ')') {
						// printf("\n----- Found ')' at position %d -----\n", varCount);
						varCount++; // Move to the next character
						return currentSubtree;  
				}

        // Variable handling
        if(isalpha(expr[varCount])){
            // printf("\n----- Processing Variable -----\n");
            // printf("Starting at position: %d\n", varCount);
            currentSubtree = parseVariable(expr); // Build the node of the subtree
            // printf("Created variable node: '%s'\n", currentSubtree->data);
            continue;
        }

        // Number handling
        if(isdigit(expr[varCount])){
            // printf("\n----- Processing Number -----\n");
            // printf("Starting at position: %d\n", varCount);
            currentSubtree = parseNumber(expr); // Build the node of the subtree
            // printf("Created number node: '%s'\n", currentSubtree->data);
            continue;
        }

        // Operator handling: making sure that there exists a current subtree
        if(currentSubtree != NULL && (expr[varCount] == '+' || expr[varCount] == '-' || 
           expr[varCount] == '*' || expr[varCount] == '/')){
            // printf("\n----- Processing Operator -----\n");
            // printf("Found operator: '%c' at position %d\n", expr[varCount], varCount);
						// Create an operator node with the current character as data
            char sign[2] = {expr[varCount], '\0'};
            varCount++; // Move to the next character

						// Build the operator node
            Node *opNode = createNode(sign);
            opNode->left = currentSubtree;  // Use the entire current subtree as left child
            opNode->right = parseExpression(expr); // Recursively call parseExpression to build the right subtree
            
						// TODO: print the operator node
            // printf("\n----- Operator Node Complete -----\n");
            // printf("Operator: '%s'\n", opNode->data);
            // printf("Left subtree root: '%s'\n", opNode->left->data);
            // printf("Right subtree root: '%s'\n", opNode->right->data);
            
            return opNode;
        }

        varCount++; // Move to the next character
    }

    // printf("\n========== EXIT parseExpression ==========\n");
    // if (currentSubtree) {
    //     printf("Returning subtree with root: '%s'\n", currentSubtree->data);
    // } else {
    //     printf("Returning NULL\n");
    // }
    
    return currentSubtree;
}


// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){
  if (root == NULL) {
    return;
  }
  printf("%s ", root->data);
  preorder(root->left);
  preorder(root->right);
}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
// Add paranthese around variable or number 
void inorder(Node *root){
  if(root == NULL){
    return;
  }
  // Add parentheses around the left subtree
  printf("(");
  
  inorder(root->left);
  printf("%s", root->data);
  inorder(root->right);
  // Add closing parentheses around the right subtree
  printf(")");
  
}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root){
  if(root == NULL){
    return;
  }
  postorder(root->left);
  postorder(root->right);
  printf("%s ", root->data);
}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root){
  int varExists = 0;
  if(root == NULL){
    return;
  }
  // Going over a tree, if the current node is a variable, prompt the user to assign a value to it
  if(isalpha(root->data[0]) && varCount < 10){
    // Check if the variable name with value already exists in the variables array
    for(int i = 0; i < varCount; i++){
      if(strcmp(variables[i].varName, root->data) == 0){
        printf("Variable %s already exists\n", root->data);
        varExists = 1;
        return;
      }
    }
    if(varExists == 0){
      printf("Enter a float value for %s: ", root->data);
      scanf("%f", &variables[varCount].value);
      // store the variable name in the struct
      strcpy(variables[varCount].varName, root->data);
      varCount++;
    }
  }
  promptVariables(root->left);
  promptVariables(root->right);
}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root){
  // Add a static flag to track division by zero error
  int divisionByZeroErrorVar = 0;
  
  if(root == NULL){
    return 0.00;
  }

  // If the current node is a number
  if(isdigit(root->data[0])){
    return atof(root->data);
  }

  // If the current node is a variable
  if(isalpha(root->data[0])){
    for(int i = 0; i < varCount; i++){
      if(strcmp(variables[i].varName, root->data) == 0){
        return variables[i].value;
      }
    }
  }

  float left = calculate(root->left);
  float right = calculate(root->right);

  // Check for division by zero before performing operations
  if(strcmp(root->data, "/") == 0 && right == 0){
    printf("ERROR - Division by zero!\n");
    divisionByZeroErrorVar = 1;
    return 0.00;
  }

  // If division by zero was detected in a sub-calculation, propagate the error
  if(divisionByZeroErrorVar){
    return 0.00;
  }

  // Perform the operations
  if(strcmp(root->data, "+") == 0) return left + right;
  if(strcmp(root->data, "-") == 0) return left - right;
  if(strcmp(root->data, "*") == 0) return left * right;
  if(strcmp(root->data, "/") == 0) return left / right;

  return 0.00;
}

/*
	Helper functions
*/
Node* parseVariable(char *expr){
	int var_pos = varCount;
	while(isalnum(expr[varCount]) || expr[varCount] == '_'){
		varCount++;
	}
	int length = varCount - var_pos;
	char *var = (char*)malloc(length+1);
	if(var == NULL){
		printf("Memory allocation for a variable failed\n");
		return NULL;
	}
	strncpy(var, expr+var_pos, length);
  Node *varNode = createNode(var);
  free(var);
	return varNode;
}

Node* parseNumber(char *expr){
	int num_pos = varCount;
	while(isdigit(expr[varCount]) || expr[varCount] == '.'){
		varCount++;
	}
	int length = varCount - num_pos;
	char *num = (char*)malloc(length+1);
	if(num == NULL){
		printf("Memory allocation for a number failed\n");
		return NULL;
	}
	strncpy(num, expr+num_pos, length);
  Node *numNode = createNode(num);
  free(num);
	return numNode;
}
int checkDivisionByZero(Node *root){
  if(strcmp(root->data, "/") == 0 && root->right->data[0] == '0') return 1;
  return 1;

  if (root->left != NULL) checkDivisionByZero(root->left);
  if (root->right != NULL) checkDivisionByZero(root->right);
  return 0;
}
// Free the memory allocated for the tree
void freeTree(Node *root){
  if(root == NULL) return;
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}
// End of a3q1_functions.c
