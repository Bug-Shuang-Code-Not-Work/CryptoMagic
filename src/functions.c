/*
File: functions.c
Project: cryptoMagic
Programmer: Shuang Liang 7492259
First Version: 2018-01-25
Description: This c file containing all functions for the encryption/decryption functions including 
checkArguments, encryptMode, decryptMode, getbaseFileName, addExtension, encryptAndWrite, decryptAndWrite,
*/


#include "../inc/crypto.h"


/*
Function: checkArguments
Parameter: int howManyArgument, char argument1[], char argument2[
Return Value: -1 if there is an error and 0 otherwise
Description: This function checks the format of command line argument and pass the value to other functions accordingly.
*/
int checkArguments(int howManyArgument, char argument1[], char argument2[]) {

	const char encryptSwitch[kSwitch] = "-encrypt";
	const char decryptSwitch[kSwitch] = "-decrypt";
	char argument[kMaxInput] = "";

	if (howManyArgument == 1) {

		printf("Need at least one argument!\n Format:<Program> <Switch> <File Name>\n");
		return ERROR;
	}

	else if (howManyArgument == 2) {

		strcpy(argument, argument1);

		encryptMode(argument);

		return 0;
	}


	else if (howManyArgument == 3) {

			if (strcmp(argument1, encryptSwitch) == 0) {

				strcpy(argument, argument2);
				encryptMode(argument);
				return 0;

		}

			else if (strcmp(argument1, decryptSwitch) == 0) {

				strcpy(argument, argument2);
				decryptMode(argument);
				return 0;
			}

			else { 
				printf("INVALID Input!\n Format:<Program> <Switch> <File Name>\n");
				return ERROR;

			}
		}

	else {
		printf("Too many arguments!\n Format:<Program> <Switch> <File Name>\n");
		return ERROR;
	}

}



/*
Function: encryptMode
Parameter: char* filePath
Return Value: -1 if there's an error and 0 otherwise
Description: This function is the entire encryption utility. It takes a file with any extension and creates the encrypted file with .crp extension.
*/
int encryptMode(char* filePath) {

	char Encrypt = 'e';
	char fileName[kMaxInput] = "";
	char buffer[kMaxInput] = "";

	//get base file name from the path and append the .crp suffix
	getbaseFileName(filePath, fileName);
	addExtension(fileName, Encrypt);

	//Open input and output file
	FILE* fpInput = fopen(filePath, "r");
	if (fpInput == NULL) {

		printf("File does not exist!\n");
		return ERROR;
	}

	FILE* fpOutput = fopen(fileName, "w");
	if (fpOutput == NULL) {

		printf("Cannot open the output file!\n");
		return ERROR;
	}
		

	//In the loop get one line and see whether reach the end of file
		while (fgets(buffer, kMaxInput, fpInput) != NULL ){

			//The algorithm takes a line of input and encrypt it and write to file 
			encryptAndWrite(buffer, fpOutput);	

			//empty the string
			memset(buffer, 0, sizeof(buffer));

			if (feof(fpInput) != 0) {
				break;
			}

	}

		// close file
		if (fclose(fpOutput) != 0) {

			printf("Failed to close the output file!\n");
			return ERROR;
		}

		if (fclose(fpInput) != 0) {

			printf("failed to close the input file!\n");
			return ERROR;
		}

		return 0;
}






/*
Function: decryptMode
Parameter: char* filePath
Return Value: -1 if there is an error and 0 otherwise
Description: This function is the decryption utility and takes the file with any extension and create the decrypted file with .txt extension
*/
int decryptMode(char* filePath) {
	char Decrypt = 'd';
	char fileName[kMaxInput] = "";



	//get base file name from the path and append the .txt suffix
	getbaseFileName(filePath, fileName);
	addExtension(fileName, Decrypt);

	//open input and output file
	FILE* fpInput = fopen(filePath, "r");
	if (fpInput == NULL) {

		printf("File does not exist!\n");
		return ERROR;
	}

	FILE* fpOutput = fopen(fileName, "w");
	if (fpOutput == NULL) {

		printf("Cannot open the output file!\n");
		return ERROR;
	}
	
	char buffer[kMaxInput] = "";
	//call decrypt algorithm to decrypt and write to file
	*buffer = '\0';
	while (fgets(buffer, kMaxInput, fpInput) != NULL) {

		decryptAndWrite(buffer, fpOutput);

		//empty the string
		memset(buffer, 0, sizeof(buffer));


		if (feof(fpInput) != 0) {
			break;
		}
		
	}


	//close file
	if (fclose(fpOutput) != 0) {

		printf("Failed to close the output file!\n");
		return ERROR;
	}

	if (fclose(fpInput) != 0) {

		printf("failed to close the input file!\n");
		return ERROR;
	}

	return 0;


}







/*
Function: char* filePath
Parameter: char* inputPath, char* baseFileName
Return Value: 0
Description: This function takes the user input from command argument and determine whether the input contains path and extension and parse the input to get the base filename
*/
int getbaseFileName(char* inputPath, char* baseFileName) {

	//need to change 
	char slash = '/';
	char dot = '.';
	char encryMode = 'e';
	char decryMode = 'd';

	//find the last slash and dot
	char* pSlash = strrchr(inputPath, slash);
	char* pDot = strrchr(inputPath, dot);
	
	//Only file base name
	if (pSlash == NULL && pDot == NULL) {

		strcpy(baseFileName, inputPath);

		return 0;

	}

	//File path with Extension
	else if (pSlash != NULL && pDot != NULL) {
		
		char* pCopy = pSlash + 1;
		char* pPaste = baseFileName;

			while (pCopy != pDot) {
				
			*pPaste = *pCopy;
			pPaste++;
			pCopy++;
			
			}
	
		return 0;
	}

	//File path without extension
	else if (pSlash != NULL && pDot == NULL) {

		char* pCopy = ++pSlash;
		strcpy(baseFileName, pCopy);
		
		return 0;
	}
	
	//File Name with extension
	else if (pSlash == NULL && pDot != NULL) {

		char* pPaste = baseFileName;
		char* pCopy = inputPath;

		while (*pCopy != dot) {

			*pPaste = *pCopy;
			pPaste++;
			pCopy++;

		}

		return 0;
	}

	return 0;
}






/*
Function: addExtension
Parameter: char* baseFileName, char mode
Return Value: None
Description: This function adds the .crp or .txt extension based on the encrypt/decrypt mode.
*/
void addExtension(char* baseFileName, char mode) {

	char Encrypt = 'e';
	char Decrypt = 'd';
	const char txtExtension[kSwitch] = ".txt";
	const char crpExtension[kSwitch] = ".crp";

	if (mode == Encrypt) {

		strcat(baseFileName, crpExtension);
	}

	else if (mode == Decrypt) {

		strcat(baseFileName, txtExtension);
	}

}




/*
Function: char* baseFileName, char mode
Parameter: char* inputline, FILE* fpOutput
Return Value: None
Description: This function takes the inputline from the file. It encrypts and writes to the ouput file.
*/
void encryptAndWrite(char* inputline, FILE* fpOutput) {

	char CR = '\n';
	char tab = '\t';
	char writeTab = 'T';
	char Source[kMaxInput] = "";
	strcpy(Source, inputline);
	char* pSource = Source;


	while (*pSource != '\0') {

		if (*pSource == CR) {

			fprintf(fpOutput, "\n");
		}

		else if (*pSource == tab) {

			fprintf(fpOutput, "%c", writeTab);
			fprintf(fpOutput, "%c", writeTab);
		}

		else {

			int outchar = *pSource - 16;

			if (outchar < 32) {

				outchar = (outchar - 32) + 144;
			}

			fprintf(fpOutput, "%02X", outchar);

		}

		pSource++;
	}

}



/*
Function: decryptAndWrite
Parameter: char* inputline, FILE* fpOutput
Return Value: None
Description: This functions takes the input line from the file. It decrypts and writes to the output file.
*/
void decryptAndWrite(char* inputline, FILE* fpOutput) {
	char tab = 'T';
	char CR = '\n';
	char writeTab = '\t';

	//2 pointers starting at the beginning and the second place of the input array
	
	
	char* pSource = inputline;
	while (*pSource !='\0') {

		if (*pSource == tab) {

			fprintf(fpOutput,"%c", writeTab);
			pSource += 2;

		}

		else if (*pSource == '\n') {
				
			fprintf(fpOutput, "\n");
			pSource++;

		}

		else {
			int faceValue1 = *pSource;
			int faceValue2 = *(++pSource);

			//get the actual value 
			if (faceValue1 >= 48 && faceValue1 <= 57) {

				faceValue1 -= 48;
			}
				if (faceValue2 >= 48 && faceValue2 <= 57) {

					faceValue2 -= 48;
				}


			//if the value is at A to F need to convert to face value
			if (faceValue1 >= 65 && faceValue1 <= 70) {

				faceValue1 -= 55;
			}
				if (faceValue2 >= 65 && faceValue2 <= 70) {

					faceValue2 -= 55;
				}
			
				int outChar = faceValue1 * 16 + faceValue2 + 16;

					if (outChar > 127) {

					outChar = (outChar - 144) + 32;
					}

			fprintf(fpOutput, "%c", outChar);
			pSource++;
				
		}
		
	}

}
