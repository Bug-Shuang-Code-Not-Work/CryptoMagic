/*
File: crypto.h
Project: cryptoMagic
Programmer: Shuang Liang 7492259
First Version: 2018-01-25
Description: This header file contains the libraries, constants, and function prototypes for the program
*/

//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constants
#define ERROR -1
#define kMaxInput 121
#define kMaxOutput 256
#define kSwitch 11



// prototypes
int checkArguments(int howManyArgument, char argument1[], char argument2[]);
int encryptMode(char* inputFile);
int decryptMode(char* inputFile);
int getbaseFileName(char* inputPath, char* outputFileName);
void addExtension(char* baseFileName, char mode);
void encryptAndWrite(char* inputline, FILE* fpOutput);
void decryptAndWrite(char* inputline, FILE* fpOutput);

