//
//  block.hpp
//  CIS269_Lecture_LinkedLIsts
//
//  Created by Adrian Bao on 10/16/18.
//  Copyright © 2018 Adrian Bao. All rights reserved.
//

#ifndef block_hpp
#define block_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class Block {
    
private:
    long id;
    string current_hash;
    string previousHash;
    long nonce;
    long timeId;
    
public:
    // Empty Constructor
    Block() {
        id = 0;
        current_hash = "";
        previousHash = "";
        nonce = 0;
        timeId = 0;
    }
    
    // Constructor with all the properties - See Template below
    Block(long, string, string, long, long);
    
    // Constructor with id, previousHash, nonce, and timeId - See Template below
    Block(long, string, long, long);
    
    ~Block(){}; // Deconstructor REQUIRED!
    
    // Getter Methods
    long getID();
    string getHash();
    string getPreviousHash();
    long getNonce();
    long getTimeID();
    
    // Setter Methods
    void setID(long new_id);
    void setHash(string new_hash);
    void setPreviousHash(string new_previousHash);
    void setNonce(long new_nonce);
    void setTimeID(long new_timeId);
    
    // Generate Hash Prototype
    string generate_hash(string previousHash, long nonce);
    
    // C++ version of 'toString' method of formatted output
    friend std::ostream& operator<<(std::ostream &strm, const Block &block) {
        return strm << "ID:         " << block.id << "\n"
        << "Hash:       " << block.current_hash << "\n"
        << "PrevHash:   " << block.previousHash << "\n"
        << "Nonce:      " << block.nonce << "\n"
        << "Time ID:    " << block.timeId << "\n";
    }
    
}; // Semicolon required after class declaration

#endif /* block_hpp */
