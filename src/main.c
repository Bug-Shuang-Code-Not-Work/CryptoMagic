/*
File: main.c
Project: cryptoMagic
Programmer: Shuang Liang 7492259
First Version: 2018-01-25
Description: This program is a linux utility for encyrpting and decrypting txt files using command line arguments.
*/

#include "../inc/crypto.h"


int main (int argc, char* argv[]){




// check Argument to see the format and initiate the modes
checkArguments(argc, argv[1], argv[2]);



return 0;

}
