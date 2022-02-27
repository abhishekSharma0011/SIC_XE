/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Here we write the functions required for the addressing mode finding program 

Author : Abhishek Kumar Sharma

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */



#include "sic_xe.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>     



typedef struct SicXe inst;    // The sic/xe instruction type is now inst

/* -----------------------------------------------------------------------------------------------
The funciton to convert the hexadecimal number(which is in string) to the equivalent binary value
(again the binary value will be in string format)

Hexadecimal                 Binary
------------               --------
0                           0000
1                           0001
2                           0010
3                           0011
4                           0100
5                           0101
6                           0110
7                           0111
8                           1000
9                           1001
10                             A
11                             B
12                             C
13                             D
14                             E
15                             F


Since the sicxe instructions are of 24bits = 4bytes , we will require an array of at least size 24

NOTE : each digit of the hexadecimal corresponds to 4bits = 1 nibble

*/
// MODIFIED STRING COPY CUM STRING CONCATENATE FUNCTION
void strCat(char* string1, char* string2) {
    if(string1[0] == '\0') {
        strcpy(string1, string2);
    }
    else {
        strcat(string1, string2);
    }
}

// This function converts the hexadecimal number into binary number
void hexToBin(char* hexadecimal, char* binaryValue) {



    int register i = 0;

    while(hexadecimal[i]) {

        switch(hexadecimal[i]) {

            case '0' :
                strCat(binaryValue, "0000");
                break;
            case '1' :
                strCat(binaryValue, "0001");
                break;
            case '2' :
                strCat(binaryValue, "0010");
                break;
            case '3' :
                strCat(binaryValue, "0011");
                break;
            case '4' :
                strCat(binaryValue, "0100");
                break;
            case '5' :
                strCat(binaryValue, "0101");
                break;
            case '6' :
                strCat(binaryValue, "0100");
                break;
            case '7' :
                strCat(binaryValue, "0111");
                break;
            case '8' :
                strCat(binaryValue, "1000");
                break;
            case '9' :
                strCat(binaryValue, "1001");
                break;
            case 'A' :
            case 'a' :
                strCat(binaryValue, "1010");
                break;
            case 'B' :
            case 'b' :
                strCat(binaryValue, "1011");
                break;
            case 'C' :
            case 'c' :
                strCat(binaryValue, "1100");
                break;
            case 'D' :
            case 'd' :
                strCat(binaryValue, "1101");
                break;
            case 'E' :
            case 'e' :
                strCat(binaryValue, "1110");
                break;
            case 'F' :
            case 'f' :
                strCat(binaryValue, "1111");
                break;
            default :
                break;
        }

        i++;    
    }
}


// To find the addressing mode base on the nixbpe value
void addMode(int n, int i, int x, int b, int p, int e) {

    printf("~~~~~~~~ ADDRESSING MODES OF GIVEN INSTRUCTION ~~~~~~~~~\n\n");

    // only index
    if(e == 0) {
        printf("It's a format 3 instruction...\n");
    }
    else {
        printf("It's a format 4 instruction...\n");
    }

    // indexed with base or pc 
    if(x == 1) {
        printf(">>> INDEXED + \n");

        if(b == 1 && p == 0) {
            printf("BASE RELATIVE");
        }
        else if(b == 0 && p == 1) {
            printf("PC RELATIVE");
        }
        else if((b == 0 && p == 0) || (b == 1 && p == 1)) {
            printf("DIRECT");
        }
    }
    else {
        if(b == 1 && p == 0) {
            printf("BASE RELATIVE");
        }
        else if(b == 0 && p == 1) {
            printf("PC RELATIVE");
        }
        else if((b == 0 && p == 0) || (b == 1 && p == 1)) {
            printf("DIRECT");
        }
    }

    // simple addressing 
    if((n == 0 && i == 0) || (n == 1 && i == 1)) {
        printf("\n>>> SIMPLE");
    }


    // Immediate addressing
    if(n == 0 && i == 1) {
        printf("\n>>> IMMEDIATE");
    }


    // Indirect addressing
    if(n == 1 && i == 0) {
        printf("\n>>> INDIRECT");
    }
}


// This fuction sets the different fields of the sic/se intruction 
void addressingMode(char* binary) {

    inst instruction;

    const int lengthOfString = strlen(binary);


    if(lengthOfString > 24 || binary[0] == '\0') {
        printf("The instruction is invalid\n");
        exit(0);
    }
    else {
        printf("The machine instruction is : %s\n", binary);
    }

    char* tempString = (char*)malloc(lengthOfString * sizeof(char));

    if(tempString == NULL) {
        printf("An error occured... exiting... 3...2...1\n");
        exit(0);
    }
    else {
        // Operation Code 6 bits
        strncpy(tempString, binary, 6);
        instruction.opCode = atoi(tempString);


        // n, i, x, b, p, e
        instruction.addbits.n = binary[6];      // n field
        instruction.addbits.i = binary[7];      // i field
        instruction.addbits.x = binary[8];      // x field
        instruction.addbits.b = binary[9];      // b field
        instruction.addbits.p = binary[10];     // p field
        instruction.addbits.e = binary[11];     // e field


        // address field
        int register i = 12;

        while(binary[i]) {
            tempString[i - 12] = binary[i];
            i++;
        }

        instruction.addressField = atoi(tempString);
    }


    // To display the addressing modes based on the nixbpe values
    addMode(instruction.addbits.n, instruction.addbits.i, instruction.addbits.x, 
                    instruction.addbits.b, instruction.addbits.p, instruction.addbits.e);

    /* 
        FOR DEBUGGING
    */
    // printf("The instruction is : %d%d%d%d%d%d%d%d\n", instruction.opCode,
    //                                                 instruction.addbits.n, 
    //                                                 instruction.addbits.n, 
    //                                                 instruction.addbits.n, 
    //                                                 instruction.addbits.n,
    //                                                 instruction.addbits.n,
    //                                                 instruction.addbits.n,
    //                                                 instruction.addressField);

}   
