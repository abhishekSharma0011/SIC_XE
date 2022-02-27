/*
    This header file includes all the procedures required for the second assignment given to me by Raghunath Sharma Sir.

    company : iota (technology for service...)

    Author : Abhishek Kumar Sharma
    email : abhishekkrsharma1999@gmail.com
*/



/* ---------------------------------------------------------------------------
NOTE : It's not complete yet. Lot of things will be added. Afterall, I have 
to make the assemble , linker and loader.
   --------------------------------------------------------------------------- */

#ifndef SIC_XE
#define SIC_XE





// The structure of the sic/se instruction format

struct Instruction {

    unsigned int n : 1;
    unsigned int i : 1;
    unsigned int x : 1;
    unsigned int b : 1;
    unsigned int p : 1;
    unsigned int e : 1;
};

struct SicXe {
    unsigned int opCode : 6;
    struct Instruction addbits; // The n, i, x, b, p, e bits
    unsigned int addressField;  // The 20 bit address field
};


void hexToBin(char* hexadecimal, char* binaryValue);  // To convert the hexadecimal(string) into a binary value

void addressingMode(char* binary);  // Analyzes the binary value(string) and displays the addressing mode 


#endif