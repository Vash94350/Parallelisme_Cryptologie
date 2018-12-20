#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#include <fcntl.h>

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
				
				unsigned long long int getFileLength(const char * fileName) {
				
					ifstream fileStream;
				
					fileStream.open(fileName, ios::in | ios::binary);
				
					fileStream.seekg(0, fileStream.end);
				
					unsigned long long int length = fileStream.tellg();
				
					fileStream.close();
				
					return length;
				}

				int createOutputFile(const char * fileName, unsigned long long int fileSize){
				
					int fileDescriptor = open(fileName, O_RDWR|O_CREAT, 0666);
				
					return posix_fallocate(fileDescriptor, 0, fileSize);
				}
				
				unsigned char * getPartOfFile(const char * fileName, unsigned long long int chunkSize, unsigned long long int positionOfThePart) {
					
					ifstream fileStream;
					
					fileStream.open(fileName, ios::in | ios::binary);
				
					fileStream.seekg(positionOfThePart, ios::beg);
				
					unsigned char * partOfFile = new unsigned char[chunkSize+1];

					for(unsigned long long int c=0; c<chunkSize; c++) {
						
						partOfFile[c] = fileStream.get();
					}
					
					partOfFile[chunkSize] = 0; 
					
					fileStream.close();

					return partOfFile;
				}
				
				void writeFile(const char * fileName, string data, unsigned long long int positionOfThePart) {
					
					ofstream outputFile;
	
					outputFile.open(fileName, ios_base::in | ios_base::out | ios_base::ate);	
					
					outputFile.seekp(positionOfThePart, ios::beg);
					
					outputFile << data;
					
					outputFile.close();
				}
			
		};		
	}
}

#endif
