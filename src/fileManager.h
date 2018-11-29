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
}

#endif