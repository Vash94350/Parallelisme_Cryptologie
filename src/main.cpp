#include "fileManager.h"
#include "executionManager.h"

#include <queue>
#include <thread>
#include <future>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::string;

using namespace fileManager::parallel;
using namespace executionManager::parallel;

using namespace std;

int main(int argc, char *argv[]) {
	
	if(argc<5){
	
		cout << "Error ! Missing Argument !" << endl;
		
		cout << "Argument Pattern : main.exe {-e|-d} NB_THREADS INPUT_FILE OUTPUT_FILE KEY" << endl;
		
		return 0;
	}
	
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
	
	FileManager fileManager;
	
	unsigned long long int fileLength = fileManager.getFileLength(inputFileName.c_str());	
	
	unsigned long long int chunkSize = (unsigned long long int) fileLength / threadNumber;
	
	unsigned long long int lastChunkSize = 0;
	
	if( (threadNumber * chunkSize) < fileLength ) {		
		
		lastChunkSize = chunkSize + ( fileLength - (threadNumber * chunkSize) );
	}	
	
	string * encryptedString = new string[threadNumber];
	
	unsigned long long int positionInTheFile = 0;
	
	deque<future<string>> threadFutureDeque;
	
	for(unsigned long long int i = 0; i < threadNumber; i++) {
	
		ExecutionManager executionManager;
	
		if(i != 0){
            
			positionInTheFile = positionInTheFile + chunkSize;
		}
		
		if( (i == threadNumber-1) && (lastChunkSize!=0) ){
		
			chunkSize = lastChunkSize;		
		}
		
		threadFutureDeque.emplace_back(async(launch::async, &ExecutionManager::executeRC4OnPartOfFile, executionManager, inputFileName, chunkSize, positionInTheFile, key));
	}
	
	for(unsigned long int j= 0; j < threadNumber; j++) {

        threadFutureDeque[j].wait();

        encryptedString[j] = threadFutureDeque[j].get();
    }
	
	threadFutureDeque.clear();
	
	for(unsigned long long int i = 0; i < threadNumber; i++) {
		
		if(i==0){
		
			fileManager.writeFile(outputFileName, encryptedString[i], false);
		}
		else {
		
			fileManager.writeFile(outputFileName, encryptedString[i], true);
		}
	}
	
	/*string * chunkedInputFile = fileManager.readAndChunkFile(inputFileName, threadNumber);
	
	unsigned long long int chunkedInputFileLength = fileManager.getNumberOfChunckedPart();
	
	string * encryptedString = new string[chunkedInputFileLength];
	
	unsigned long long int aAndBState = 0;
	
	deque<future<string>> threadFutureDeque;
	
	for(unsigned long long int i = 0; i < chunkedInputFileLength; i++) {
		
		RC4 rc4;
		
		if(i != 0){
            
			aAndBState = aAndBState + chunkedInputFile[i-1].length();
		}
		
		threadFutureDeque.emplace_back(async(&RC4::rc4Encryption, rc4, chunkedInputFile[i], key, aAndBState));
	}
	
	for(unsigned long int j= 0; j < threadNumber; j++) {

        //threadFutureDeque[j].wait();

        encryptedString[j] = threadFutureDeque[j].get();
    }
	
	threadFutureDeque.clear();
	
	for(unsigned long long int i = 0; i < chunkedInputFileLength; i++) {
		
		if(i==0){
		
			fileManager.writeFile(outputFileName, encryptedString[i], false);
		}
		else {
		
			fileManager.writeFile(outputFileName, encryptedString[i], true);
		}
	}*/
	
	return 0;
}
