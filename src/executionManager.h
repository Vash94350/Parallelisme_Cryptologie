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
			
				ExecutionManager() {
				
				}
					
				~ExecutionManager() {
				
				}
				
				bool executeRC4OnPartOfFile(string inputFileName, unsigned long long int chunkSize, unsigned long long int positionOfThePart, string key, string outputFileName) {
				
					FileManager fileManager;
				
					unsigned char * partOfTheToEncrypt =  fileManager.getPartOfFile(inputFileName.c_str(), chunkSize, positionOfThePart);
				
					RC4 rc4;
				
					fileManager.writeFile(outputFileName.c_str(), rc4.rc4Encryption(partOfTheToEncrypt, key, chunkSize, positionOfThePart), positionOfThePart);
				
					return true;
				}
				
			private:
			
		};
	}
}

#endif