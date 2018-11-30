//
//  main.cpp
//  BlockChain_Tree
//
//  Created by Adrian Bao on 11/25/18.
//  Copyright © 2018 Adrian Bao. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <string>
#include <queue> // Used for Breadth First Traversal
#include "block.hpp"

// Constant size for array
const int ARRAY_SIZE = 100; // NOTE: Change these values if you would like to shorten the amount of output of program
const int DIFFICULTY = 3;   // - Difficulty level of 3 proved to be quick when running on my machine

using namespace std;

//// Struct Declaration for Binary Tree
struct node {

    Block block;
    node *left;
    node *right;

};

// Function Prototype Declarations
long mine_nonce(Block blockArr[], int difficulty, int idx, long target_length);
void inorder(node *n); // Inorder traversal
void breadth_first(node *root);




int main(void) {
    
    
    
    cout << endl << "================== START OF PART 1 ==================" << endl << endl;
    
    // Create Block array to hold 100 elements
    Block blockArr[ARRAY_SIZE];
    
    time_t t = time(0);
    int rand_nonce;
    
    // Create the Genesis Block
    blockArr[0] = Block(0, "0", 0, t);
    
    // Now loop to populate the rest of the array
    for (int i = 1; i < ARRAY_SIZE; i++) {
        rand_nonce = (rand() % 900) + 100; // Generates random number between 100-999
        blockArr[i] = Block(i, blockArr[i-1].getHash(), rand_nonce, t);
    }
    
    // Printing Block Chain
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << endl << blockArr[i] << endl;
    }
    
    cout << endl << "=================== END OF PART 1 ===================" << endl << endl;
    
    
    
    
    
    
    
    
    cout << endl << "================== START OF PART 2 ==================" << endl << endl;
    
    
    Block mined_blockArr[ARRAY_SIZE];
    long nonce = 0; // start at 0 for genesis block
    
    // Create Genesis Block
    mined_blockArr[0] = Block(0, "0", nonce, t);
    long target_length = mined_blockArr[0].getHash().length();
    
    // Create rest of block chain
    for (int i = 1; i < ARRAY_SIZE; i++) {
        // Generate new blocks by mining the nonce and generating a new hash with it
        nonce = mine_nonce(mined_blockArr, DIFFICULTY, i, target_length);
        mined_blockArr[i] = Block(i, mined_blockArr[i-1].getHash(), nonce, t);
    }
    
    // Print Block Chain
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << endl << mined_blockArr[i] << endl;
    }
    
    
    cout << endl << "=================== END OF PART 2 ===================" << endl << endl;
    
    
    
    
    
    
    
    
    cout << endl << "================== START OF PART 3 ==================" << endl << endl;
    
    /* Here we will place the previously generated BlockChain into a Binary Tree */
    
    // Insert first block AFTER genisis block as root and build from there
    node root;
    root.block = mined_blockArr[1];
    root.left = NULL;
    root.right = NULL;
    
    node *temp = (node*)malloc(sizeof(node));
    node *prev = (node*)malloc(sizeof(node));
    
    // Generate tree
    for (int i = 2; i < ARRAY_SIZE; i++) {
        
        node *new_node = new node;
        new_node->block = mined_blockArr[i];
        new_node->left = NULL;
        new_node->right = NULL;
        
        temp = &root;
        while (temp != NULL) {
            prev = temp;
            if (new_node->block.getNonce() < temp->block.getNonce()) {
                // Go left
                temp = temp->left;
            } else {
                // Go right
                temp = temp->right;
            }
            
        }
        
        if (new_node->block.getNonce() < prev->block.getNonce()) {
            cout << "" << new_node->block.getNonce() << " Inserted to left subtree of " << prev->block.getNonce() << endl;
            // Add node to left subtree
            prev->left = new_node;
        } else {
            cout << "" << new_node->block.getNonce() << " Inserted to right subtree of " << prev->block.getNonce() << endl;
            // Add node to right subtree
            prev->right = new_node;
        }
        
    }
    
    cout << endl << "Tree has been constructed!" << endl << endl;
    
    
    cout << endl << "=================== END OF PART 3 ===================" << endl << endl;
    
    
    
    
    
    
    
    
    
    
    
    
    cout << endl << "================== START OF PART 4 ==================" << endl << endl;
    

    cout << "INORDER TRAVERSAL: " << endl << endl;
    cout << "id:nonce:hash" << endl;
    inorder(&root);
    
    cout << endl << endl;
    
    cout << "BREADTH-FIRST TRAVERSAL: Top-Down, Left-to-Right" << endl << endl;
    cout << "id:nonce:hash" << endl;
    breadth_first(&root);
    
    
    cout << endl << "=================== END OF PART 4 ===================" << endl << endl;
    
    
    
    
    return 0;
}


/********************************************************************
 * inorder(): Function that follows the inorder traversal algorithm *
 *      to print out the values following the LVR sequence.         *
 ********************************************************************/
void inorder(node *n) {

    if (n != NULL) {
        inorder(n->left);
        cout << "" << n->block.getID() << ":" << n->block.getNonce() << ":" << n->block.getHash() << endl;
        inorder(n->right);
    }

}


/********************************************************************
 * breadth_first(): Function that follows the bread-first traversal *
 *      algorithm, specifically the Top-Down, Left-to-Right version *
 *      used in the PowerPoint from Lecture. Imported the STL queue *
 *      library to make use of the queue when traversing the tree.  *
 ********************************************************************/
void breadth_first(node *root) {

    queue<node> q;
    node *temp;
    
    temp = root;
    
    if( temp != NULL ) {
        q.push(*temp);
        while(q.size() != 0) {
            temp = &q.front();
            q.pop();
            cout << "" << temp->block.getID() << ":" << temp->block.getNonce() << ":" << temp->block.getHash() << endl;
            if (temp->left != NULL) {
                q.push(*temp->left);
            }
            if (temp->right != NULL) {
                q.push(*temp->right);
            }
        }
    }
}


/********************************************************************
 * mine_nonce(): Function that accepts a difficulty level, i.e. the *
 *      number of preceding zeros of the generated hash. The        *
 *      continuosly generates new hashes using incrementing nonces  *
 *      until a hash is generated with the matching difficulty level*
 *      When found, returns the nonce to be used to generate the    *
 *      new hash.                                                   *
 ********************************************************************/
long mine_nonce(Block blockArr[], int difficulty, int idx, long target_length) {
    
    long nonce = 0; // starting point
    string hash = blockArr[idx].generate_hash(blockArr[idx-1].getHash(), nonce);
    
    // Continue searching for a hash that matches the requirements set by DIFFICULTY
    while (hash.length() != (target_length - difficulty)) {
        hash = blockArr[idx].generate_hash(blockArr[idx-1].getHash(), nonce);
        nonce++;
    }
    
    // Display the nonce found from mining
    // cout << "Found nonce for block ID " << idx << ": " << nonce << endl;
    
    return nonce;
}
