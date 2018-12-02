#include "rc4.h"
#include "fileManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::string;

using namespace rc4::sequential;
using namespace fileManager::parallel;

int main(int argc, char *argv[]) {
	
	RC4 rc4;
	
	FileManager fileManager;
	
	string key = "yolo";
	
	string extension = argv[1];

	unsigned long int threadNumber = atoi(argv[2]);
	
	string inputFileName = argv[3];
	
	string outputFileName = argv[4];
	
	if(extension.compare("-e") == 0){
	
		outputFileName = outputFileName + ".rc4";
	}
	else if(extension.compare("-d") == 0){
		
		outputFileName = outputFileName + ".decrypt";
	}
	
	string * chunkedInputFile = fileManager.readAndChunkFile(inputFileName, threadNumber);
	
	unsigned long long int chunkedInputFileLength = fileManager.numberOfChunckedPart(inputFileName, threadNumber);
	
	cout << chunkedInputFileLength << "\n"; 
	
	for(unsigned long long int i = 0; i < chunkedInputFileLength; i++) {
		
        cout << chunkedInputFile[i] << "\n"; 
	}
	
	/*
	string messageToEncrypt = fileManager.readFile(inputFileName);
	
	string encrypted = rc4.rc4Encryption(messageToEncrypt, key);

	fileManager.writeFile(outputFileName, encrypted);
	*/
	
	return 0;
}
