// Shubham Gupta
//Assignment 2 

#include <vector>

#include <sstream>

#include<iostream>

#include <cmath>

#include<algorithm>

#include <stdio.h>

#include<string.h>

#include<stdlib.h>

using namespace std;

// An AVL tree node 
class Node {
  public:
    int key;
  Node * left;
  Node * right;
  int height;
};

//calculating height of the tree 
int height(Node * N) {
  if (N == NULL)
    return 0;
  return N -> height;
}

//finding maximum of two integers given 
int max(int a, int b) {
  return (a > b) ? a : b;
}

//Allocating new node initially with height 1 
Node * newNode(int key) {
  Node * node = new Node();
  node -> key = key;
  node -> left = NULL;
  node -> right = NULL;
  node -> height = 1;
  return (node);
}

//REBALANCING
//RIGHT ROTATE
Node * rightRotate(Node * y) {
  Node * x = y -> left;
  Node * T2 = x -> right;

  // Perform rotation 
  x -> right = y;
  y -> left = T2;

  // Updating heights 
  y -> height = max(height(y -> left),
    height(y -> right)) + 1;
  x -> height = max(height(x -> left),
    height(x -> right)) + 1;

  // Return new root 
  return x;
}

//REBALANCING
//LEFT ROTATE 
Node * leftRotate(Node * x) {
  Node * y = x -> right;
  Node * T2 = y -> left;

  // Perform rotation 
  y -> left = x;
  x -> right = T2;

  // Updating heights 
  x -> height = max(height(x -> left),
    height(x -> right)) + 1;
  y -> height = max(height(y -> left),
    height(y -> right)) + 1;

  // Return new root 
  return y;
}

// Get Balance factor of node N 
int getBalance(Node * N) {
  if (N == NULL)
    return 0;
  return height(N -> left) - height(N -> right);
}

//Inserting new node in our subtree
// returns the new root of the subtree. 
Node * insert(Node * node, int key) {
  //insertion
  if (node == NULL)
    return (newNode(key));

  if (key < node -> key)
    node -> left = insert(node -> left, key);
  else if (key > node -> key)
    node -> right = insert(node -> right, key);
  else //if  equal 
    return node;

  // Update height 
  node -> height = 1 + max(height(node -> left),
    height(node -> right));

  //checking if  unbalanced
  int balance = getBalance(node);

  //if unbalanced 
  //4 cases

  // Left Left Case 
  if (balance > 1 && key < node -> left -> key)
    return rightRotate(node);

  // Right Right Case 
  if (balance < -1 && key > node -> right -> key)
    return leftRotate(node);

  // Left Right Case 
  if (balance > 1 && key > node -> left -> key) {
    node -> left = leftRotate(node -> left);
    return rightRotate(node);
  }

  // Right Left Case 
  if (balance < -1 && key < node -> right -> key) {
    node -> right = rightRotate(node -> right);
    return leftRotate(node);
  }

  return node;
}

// A function to print preorder 
// traversal of the tree. 
void preOrder(Node * root) {
  if (root != NULL) {
    cout << root -> key << " ";
    preOrder(root -> left);
    preOrder(root -> right);
  }
}

// A function to print postorder 
// traversal of the tree.
void postOrder(Node * root) {
  if (root != NULL) {
    postOrder(root -> left);
    postOrder(root -> right);
    cout << root -> key << " ";

  }
}

// A function to print Inorder 
// traversal of the tree.
void inOrder(Node * root) {
  if (root != NULL) {
    inOrder(root -> left);
    cout << root -> key << " ";
    inOrder(root -> right);

  }
}

// a maximum value node will give the largest value node in the left subtree
//following class notes
Node * maxValueNode(Node * node) {
  Node * current = node;

  //finding the right most leaf i.e maximum 
  while (current -> right != NULL)
    current = current -> right;

  return current;
}

Node * deleteNode(Node * root, int key) {

  //standard delete
  if (root == NULL)
    return root;

  //if key less 
  if (key < root -> key)
    root -> left = deleteNode(root -> left, key);

  //if key greater  
  else if (key > root -> key)
    root -> right = deleteNode(root -> right, key);

  //if same  
  else {
    //following  class notes
    // node with only one child or no child  
    if ((root -> left == NULL) ||
      (root -> right == NULL)) {
      Node * temp = root -> left ?
        root -> left :
        root -> right;

      // No child case  
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else // One child case  
        *root = * temp; // Copy the contents of  
      // the non-empty child  
      free(temp);
    } else {
      // if two  children , getting the maximum  value node from left 
      Node * temp = maxValueNode(root -> left);

      //copying that in root  
      root -> key = temp -> key;

      // Delete  
      root -> left = deleteNode(root -> left,
        temp -> key);
    }
  }

  // If the tree had only one node 
  // then return  
  if (root == NULL)
    return root;

  //after deletion
  //updating  and chekcing the height of out tree
  root -> height = 1 + max(height(root -> left),
    height(root -> right));

  //checking balance  
  int balance = getBalance(root);

  //if unbalanced 
  //again 4 cases
  if (balance > 1 &&
    getBalance(root -> left) >= 0)
    return rightRotate(root);

  // Left Right Case  
  if (balance > 1 &&
    getBalance(root -> left) < 0) {
    root -> left = leftRotate(root -> left);
    return rightRotate(root);
  }

  // Right Right Case  
  if (balance < -1 &&
    getBalance(root -> right) <= 0)
    return leftRotate(root);

  // Right Left Case  
  if (balance < -1 &&
    getBalance(root -> right) > 0) {
    root -> right = rightRotate(root -> right);
    return leftRotate(root);
  }

  return root;
}

//main function 
int main() {
  Node * root = NULL;
  int n = 1;
  // n is just a placeholder for our main while loop 

  //input data like A2 , D3 
  string element;

  //this will store the key part of data like store 2 from A2
  string element_with_just_integer;

  //defining the last part of input data , i.e IN || PRE || Post
  string operation_1 = "IN";
  string operation_2 = "PRE";
  string operation_3 = "POST";

  int length_of_element = 0;
  int integer_element = 0;

  while (n != 0) {
    integer_element = 0;
    cin >> element;

    //cheking the conditions for  IN,PRE,POST and  the printing the result  
    if (operation_1 == element) {
      inOrder(root);
      if (root == NULL)
        cout << "EMPTY";
      cout << endl;
      //once printing we will break out of the while loop
      break;
    } else if (operation_2 == element) {
      preOrder(root);
      if (root == NULL)
        cout << "EMPTY";
      cout << endl;
      break;
    } else if (operation_3 == element) {
      postOrder(root);
      if (root == NULL)
        cout << "EMPTY";
      cout << endl;
      break;
    }

    // actual operations start 
    //store the lenght of entire input 
    //i.e  if A2 
    // len = 2
    //if A100
    //len =4 
    length_of_element = element.length();

    // at index 0 will be A or D i.e. Addition or Deletion
    //followed by  integer  which can  be from 1 to 100

    element_with_just_integer = element.substr(1, length_of_element);
    //for storing just the number from input data 

    //converting the string number to integer number 
    integer_element = atoi(element_with_just_integer.c_str());

    //checking  the initial condition 
    //Addition or Deletion
    //A for addition 
    //D for deletion 
    // and calling respective insert or delete functions 
    //and the entire while loop goes on until it break by POST,PRE, IN
    if (element[0] == 'A') {
      root = insert(root, integer_element);

    }

    if (element[0] == 'D') {
      root = deleteNode(root, integer_element);

    }
  }

  return 0;
}