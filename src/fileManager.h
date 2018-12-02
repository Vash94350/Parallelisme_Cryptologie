#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <string>
#include <vector>

using std::string;

using namespace std;

namespace fileManager {
	
	namespace sequential {
		
        class FileManager {
			
			public:

				FileManager() {
				
				}
				
				~FileManager() {
			   
				}

				string readFile(string filename) {
					
					const char * formatedFilename = filename.c_str();
				
					ifstream fileStream(formatedFilename, ios::in | ios::binary);

					string fileContent;
					
					if(fileStream) {
						
						fileStream.seekg(0, ios::end);
						
						fileContent.resize(fileStream.tellg());
						
						fileStream.seekg(0, std::ios::beg);
						
						fileStream.read(&fileContent[0], fileContent.size());
						
						fileStream.close();	
					}
					
					return(fileContent);
				}
				
				void writeFile(string fileName, string data) {
					
					ofstream outputFile(fileName);  
					
					if (outputFile.is_open()){
				
						outputFile << data;
						
						outputFile.close();
					}
				}
		};
	}
	
	namespace parallel {
		
		class FileManager {
			
			public:

				FileManager() {
				
				}
				
				~FileManager() {
			   
				}
				
				string * readAndChunkFile(string fileName, unsigned long int threadNumber){
					
					const char * formatedFilename = fileName.c_str();
					
					unsigned long long int fileLength = getFileLength(formatedFilename);
					
					unsigned long long int chunkSize = (int) fileLength / threadNumber;
					
					unsigned long long int numberOfChunckedPart = threadNumber;
					
					if(chunkSize==1){
						
						numberOfChunckedPart = fileLength;
					}
					else if( (numberOfChunckedPart*chunkSize) < fileLength ) {
						
						numberOfChunckedPart ++;
					}
					
					return chunkFile(formatedFilename, numberOfChunckedPart, chunkSize);
				}
				
				unsigned long long int numberOfChunckedPart(string fileName, unsigned long int threadNumber) {
					
					const char * formatedFilename = fileName.c_str();
					
					unsigned long long int fileLength = getFileLength(formatedFilename);
					
					unsigned long long int chunkSize = (int) fileLength / threadNumber;
					
					unsigned long long int numberOfChunckedPart = threadNumber;
					
					if(chunkSize==1){
						
						numberOfChunckedPart = fileLength;
					}
					else if( (numberOfChunckedPart*chunkSize) < fileLength ) {
						
						numberOfChunckedPart ++;
					}
					
					return numberOfChunckedPart;
				}
			
			private:
				
				string * chunkFile(const char * fileName, unsigned long int nbChunckedPart, unsigned long long int chunkSize) {
					
					ifstream fileStream;
					
					fileStream.open(fileName, ios::in | ios::binary);
					
					string * chunkedFileTable = new string[nbChunckedPart];
					
					unsigned long int counter = 0;		
					
					while( counter < nbChunckedPart ) {
						
						char * buffer = new char[chunkSize];

						fileStream.read(buffer, chunkSize);
						
						string stringifiedBuffer((char*) buffer);
						
						stringifiedBuffer = stringifiedBuffer.substr(0, chunkSize);
						
						chunkedFileTable[counter] = stringifiedBuffer;
						
						delete(buffer);
						
						counter++;							
					}
						
					fileStream.close();

					return chunkedFileTable;
				}
				
				unsigned long long int getFileLength(const char * fileName) {
					
					ifstream fileStream;
					
					fileStream.open(fileName, ios::in | ios::binary);
				
					fileStream.seekg (0, fileStream.end);
					
					unsigned long long int length = fileStream.tellg();
					
					fileStream.seekg (0, fileStream.beg);
					
					fileStream.close();
					
					return length;
				}
				
				
		};		
	}
}

#endif