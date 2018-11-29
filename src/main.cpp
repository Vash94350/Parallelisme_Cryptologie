#include "rc4.h"
#include "fileManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::string;

using namespace rc4::sequential;
using namespace fileManager::sequential;

int main(int argc, char *argv[]) {
	
	RC4 rc4;
	
	FileManager fileManager;
	
	string key = "yolo";
	
	string extension = argv[1];

	int threadNumber = atoi(argv[2]);
	
	string inputFileName = argv[3];
	
	string outputFileName = argv[4];
	
	if(extension.compare("-e") == 0){
	
		outputFileName = outputFileName + ".rc4";
	}
	else if(extension.compare("-d") == 0){
		
		outputFileName = outputFileName + ".decrypt";
	}
	
	string messageToEncrypt = fileManager.readFile(inputFileName);
	
	string encrypted = rc4.rc4Encryption(messageToEncrypt, key);

	fileManager.writeFile(outputFileName, encrypted);
	
	return 0;
}
