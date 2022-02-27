#include <stdio.h>
#include "sic_xe.h"


int main(int argc, char* argv[]) {

    char hex[10];   // hexadecimal number


    printf("Enter the hexadecimal number : ");
    fflush(stdin);

    fgets(hex, 10, stdin);

    char binary[30];

    hexToBin(hex, binary);


    addressingMode(binary);     // gets the addressing mode


    return 0;
}