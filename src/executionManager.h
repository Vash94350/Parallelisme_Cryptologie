#ifndef EXECUTIONMANAGER_H
#define EXECUTIONMANAGER_H

#include "fileManager.h"
#include "rc4.h"

#include <string.h>

using std::string;

using namespace fileManager::parallel;
using namespace rc4::parallel;

using namespace std;

namespace executionManager {
	
	namespace parallel {
	
		class ExecutionManager {
			
			public:
			
				ExecutionManager(string inputFileNameData, string keyData, string outputFileNameData, unsigned long long int chunkSizeData, unsigned long long int positionOfThePartData) {
				
					inputFileName = inputFileNameData;

					key = keyData;

					outputFileName = outputFileNameData;

					chunkSize = chunkSizeData;

					positionOfThePart = positionOfThePartData;
				}
					
				~ExecutionManager() {
		
				}
				
				void executeRC4OnPartOfFile() {
				
					FileManager fileManager;
				
					unsigned char * partOfTheToEncrypt =  fileManager.getPartOfFile(inputFileName.c_str(), chunkSize, positionOfThePart);
				
					RC4 rc4;
				
					fileManager.writeFile(outputFileName.c_str(), rc4.rc4Encryption(partOfTheToEncrypt, key, chunkSize, positionOfThePart), positionOfThePart);
				}	
				
			private:

				string inputFileName;

				string key;

				string outputFileName;	
				
				unsigned long long int chunkSize;

				unsigned long long int positionOfThePart;	
		};
	}
}

#endif
