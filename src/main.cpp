#include "fileManager.h"
#include "executionManager.h"

#include <vector>
#include <future>
#include <stdlib.h>
#include <string.h>

using std::string;

using namespace fileManager::parallel;
using namespace executionManager::parallel;

using namespace std;

int main(int argc, char *argv[]) {

	if(argc<4){
		
		cout << "main {-e|-d} NB_THREADS KEY INPUT_FILE" << endl;
		
		return 0;
	}
	
	string extension = argv[1];

	unsigned long int threadNumber = atoi(argv[2]);
	
	string key = argv[3];
	
	string inputFileName = argv[4];
	
	string outputFileName = inputFileName;
	
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

	fileManager.createOutputFile(outputFileName.c_str(), fileLength);
	
	unsigned long long int positionInTheFile = 0;
	
	vector<future<void>> threadFutureQeue;

	threadFutureQeue.reserve(threadNumber);

	for(unsigned long long int i = 0; i < threadNumber; i++) {

		if(i != 0){
            
			positionInTheFile = positionInTheFile + chunkSize;
		}
		
		if( (i == threadNumber-1) && (lastChunkSize!=0) ){
		
			chunkSize = lastChunkSize;		
		}
	
		ExecutionManager executionManager = ExecutionManager(inputFileName, key, outputFileName, chunkSize, positionInTheFile);

		threadFutureQeue.push_back(async(launch::async, &ExecutionManager::executeRC4OnPartOfFile, executionManager));
	}

	return 0;
}
