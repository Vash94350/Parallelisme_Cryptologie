#include "rc4.h"
#include "fileManager.h"

#include <queue>
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
	
	if(argc<5){
	
		cout << "Error ! Missing Argument !" << endl;
		
		cout << "Argument Pattern : main.exe {-e|-d} NB_THREADS INPUT_FILE OUTPUT_FILE KEY" << endl;
		
		return 0;
	}
	
	FileManager fileManager;
	
	string extension = argv[1];

	unsigned long int threadNumber = atoi(argv[2]);
	
	string inputFileName = argv[3];
	
	string outputFileName = argv[4];

	string key = argv[5];
	
	if(extension.compare("-e") == 0){
	
		outputFileName = outputFileName + ".rc4";
	}
	else if(extension.compare("-d") == 0){
		
		outputFileName = outputFileName + ".decrypt";
	}
	
	string * chunkedInputFile = fileManager.readAndChunkFile(inputFileName, threadNumber);
	
	unsigned long long int chunkedInputFileLength = fileManager.numberOfChunckedPart(inputFileName, threadNumber);
	
	string * encryptedString = new string[chunkedInputFileLength];
	
	//unsigned long long int indexesState = 0;
	
	deque<future<string>> threadFutureDeque;
	
	for(unsigned long long int i = 0; i < chunkedInputFileLength; i++) {
		
		//cout << chunkedInputFile[i] << endl;
		
		RC4 rc4;
		//RC4 * rc4 = new RC4();
		
		//std::thread t(&rc4::rc4Encryption, chunkedInputFile[i], key);
        //std::thread t = std::thread(rc4.rc4Encryption, chunkedInputFile[i], key);
		
		//auto f4 = std::bind(&Foo::bar4, &foo, _1, _2, _3, _4);
		
		/*if(i != 0){
            
			indexesState = indexesState + chunkedInputFile[i-1].length()-1;
            
			rc4.setIndexes(indexesState);
		}*/
		
		threadFutureDeque.emplace_back(async(&RC4::rc4Encryption, rc4, chunkedInputFile[i], key));
		
		//encryptedString[i] = future.get();		
		
		//encryptedString[i] = std::thread t(&RC4::rc4Encryption, &rc4, chunkedInputFile[i], key);
		
		//t.join();
	}
	
	for(unsigned long int j= 0; j < threadNumber; j++) {

        threadFutureDeque[j].wait();

        encryptedString[j] = threadFutureDeque[j].get();

    }
	
	for(unsigned long long int i = 0; i < chunkedInputFileLength; i++) {
		
		//cout << encryptedString[i] << endl;
		
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
