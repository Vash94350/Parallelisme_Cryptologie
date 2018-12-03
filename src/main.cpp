#include "rc4.h"
#include "fileManager.h"

#include <thread>
#include <future>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::string;

using namespace rc4::sequential;
using namespace fileManager::parallel;

using namespace std;

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
	
	string * encryptedString = new string[chunkedInputFileLength];
	
	for(unsigned long long int i = 0; i < chunkedInputFileLength; i++) {
		
		cout << chunkedInputFile[i] << endl;
		//RC4 * rc4 = new RC4();
		
		//std::thread t(&rc4::rc4Encryption, chunkedInputFile[i], key);
        //std::thread t = std::thread(rc4.rc4Encryption, chunkedInputFile[i], key);
		
		//auto f4 = std::bind(&Foo::bar4, &foo, _1, _2, _3, _4);
		
		auto future = std::async(RC4::rc4Encryption, &rc4, chunkedInputFile[i], key);
		
		encryptedString[i] = future.get();
		
		//encryptedString[i] = std::thread t(&RC4::rc4Encryption, &rc4, chunkedInputFile[i], key);
		
		//t.join();
	}
	
	for(unsigned long long int i = 0; i < chunkedInputFileLength; i++) {
		
		cout << encryptedString[i] << endl;
		
		if(i==0){
		
			fileManager.writeFile(outputFileName, encryptedString[i], false);
		}
		else {
		
			fileManager.writeFile(outputFileName, encryptedString[i], true);
		}
	}	
	
	/*
	string messageToEncrypt = fileManager.readFile(inputFileName);
	
	string encrypted = rc4.rc4Encryption(messageToEncrypt, key);

	fileManager.writeFile(outputFileName, encrypted);
	*/
	
	return 0;
}
