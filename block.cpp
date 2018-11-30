//
//  block.cpp
//  CIS269_Lecture_LinkedLIsts
//
//  Created by Adrian Bao on 10/16/18.
//  Copyright © 2018 Adrian Bao. All rights reserved.
//

#include "block.hpp"

// Getter Methods
long Block::getID() { return id; }
string Block::getHash() { return current_hash; }
string Block::getPreviousHash() { return previousHash; }
long Block::getNonce() { return nonce; }
long Block::getTimeID()  { return timeId; }

// Setter Methods
void Block::setID(long new_id) { id = new_id; }
void Block::setHash(string new_hash) { this->current_hash = new_hash; }
void Block::setPreviousHash(string new_previousHash) { previousHash = new_previousHash; }
void Block::setNonce(long new_nonce) { nonce = new_nonce; }
void Block::setTimeID(long new_timeId) { timeId = new_timeId; }


// Constructor with all parameters
Block::Block(long id, string hash, string previousHash, long nonce, long timeId) {
    this->id = id;
    this->current_hash = hash;
    this->previousHash = previousHash;
    this->nonce = nonce;
    this->timeId = timeId;
}

// Constructor with 4 parameters, excludes hash that will be generated inside
Block::Block(long id, string previousHash, long nonce, long timeId) {
    this->id = id;
    this->previousHash = previousHash;
    this->nonce = nonce;
    this->timeId = timeId;
    
    // Generate the hash using method above
    this->current_hash = generate_hash(previousHash, nonce);
}

/******************************************************************
 * generate_hash() - Function that generates a new hash using the *
 *      previous hash and nonce of the Block Object.              *
 ******************************************************************/
string Block::generate_hash(string previousHash, long nonce) {
    string string_value = previousHash + to_string(nonce);
    // cout << string_value << endl;
    hash<string> ptrHash;
    size_t hash_value = ptrHash(string_value);
    
    return to_string(hash_value);
}
