#ifndef RC4_H
#define RC4_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::string;

using namespace std;

namespace rc4 {
	
    namespace sequential {
		
        class RC4 {
			
			public:

				RC4() {
				
				}
				
				~RC4() {
			   
				}
				
				string rc4Encryption(string messageToEncrypt, string key){
				
					unsigned long long int messageToEncryptLength = messageToEncrypt.length();
					
					unsigned char * swapBox = new unsigned char[256]();
					
					unsigned char * encryptedMessage = encrypt((unsigned char *) messageToEncrypt.c_str(), messageToEncryptLength, (unsigned char *) key.c_str(), key.length(), swapBox);
					
					string encryptedString((char*) encryptedMessage);
					
					encryptedString = encryptedString.substr(0, messageToEncryptLength);
					
					return encryptedString;
				}				
			
			private:
				
				unsigned char * encrypt(unsigned char * toEncrypt, unsigned long long int messageSize, unsigned char * key, unsigned long long int keySize, unsigned char * swapBox){
					
					for(int i=0; i<256; i++){
				
						swapBox[i] = (unsigned char) i;
					}		
				
					swapBox = ksa(key, keySize, swapBox);
				
					return prga(toEncrypt, messageSize, swapBox);
				}
				
				unsigned char * ksa(unsigned char * key, unsigned long long int keySize, unsigned char * swapBox){
				
					int j=0;
				
					for(int i=0; i<256; i++){
				
						j=(j+swapBox[i]+key[i% keySize])%256;
				
						swapBox = swap(i, j, swapBox);				
					}

					return swapBox;
				}
			
				unsigned char * prga(unsigned char * toEncrypt, unsigned long long int messageSize, unsigned char * swapBox){

					unsigned long long int a(0), b(0);
					
					unsigned char * encryptedMessage = (unsigned char *) malloc(messageSize + 1);
					
					for(unsigned long long int c=0; c<messageSize; c++){

						a = (a+1) % 256;

						b = (b+swapBox[a]) % 256;

						swapBox = swap(a, b, swapBox);

						encryptedMessage[c] = swapBox[ (swapBox[a] + swapBox[b]) %256 ] ^ toEncrypt[c];
					}
					
					return encryptedMessage;
				}			
				
				unsigned char * swap(int i , int j, unsigned char * swapBox){
				
					unsigned char temp = swapBox[i];
				
					swapBox[i] = swapBox[j];
				
					swapBox[j] = temp;

					return swapBox;
				}
		};
	}
	
	namespace parallel {
		
		class RC4 {
			
			public:

				RC4() {
				
				}
				
				~RC4() {
			   
				}
				
				/*string rc4Encryption(string messageToEncrypt, string key, unsigned long long int positionOfThePart){
				
					unsigned long long int messageToEncryptLength = messageToEncrypt.length();
					
					unsigned char * swapBox = new unsigned char[256]();
					
					swapBox = variableInitialization(swapBox);
					
					swapBox = ksa((unsigned char *) key.c_str(), key.length(), swapBox);
					
					if(positionOfThePart!=0){
					
						swapBox = setAandB(swapBox, positionOfThePart);
					}
					
					unsigned char * encryptedMessage = prga((unsigned char *) messageToEncrypt.c_str(), messageToEncryptLength, swapBox);
					
					string encryptedString = "";
					
					for(unsigned long long int r=0; r<messageToEncryptLength; r++){
					
						encryptedString += encryptedMessage[r];
					}
					
					return encryptedString;
				}*/			
				
				string rc4Encryption(unsigned char * messageToEncrypt, string key, unsigned long long int messageToEncryptLength, unsigned long long int positionOfThePart){
					
					unsigned char * swapBox = new unsigned char[256]();
					
					swapBox = variableInitialization(swapBox);
					
					swapBox = ksa((unsigned char *) key.c_str(), key.length(), swapBox);
					
					if(positionOfThePart!=0){
					
						swapBox = setAandB(swapBox, positionOfThePart);
					}
					
					return prga(messageToEncrypt, messageToEncryptLength, swapBox);
				}
			
			protected:
			
				unsigned long long int a, b;
				
				unsigned char * variableInitialization(unsigned char * swapBox){
				
					a = 0;
					b = 0;
					
					for(int i=0; i<256; i++){
				
						swapBox[i] = (unsigned char) i;
					}
					
					return swapBox;
				}
				
				unsigned char * ksa(unsigned char * key, unsigned long long int keySize, unsigned char * swapBox){
				
					int j=0;
				
					for(int i=0; i<256; i++){
				
						j = ( j + swapBox[i] + key[i% keySize]) % 256;
				
						swapBox = swap(i, j, swapBox);				
					}

					return swapBox;
				}			
				
				unsigned char * swap(int i , int j, unsigned char * swapBox){
				
					unsigned char temp = swapBox[i];
				
					swapBox[i] = swapBox[j];
				
					swapBox[j] = temp;

					return swapBox;
				}
				
				unsigned char * setAandB(unsigned char * swapBox, unsigned long long int lastPosition) {

					for(unsigned long long int z=0; z<lastPosition; z++) {

						a = (a + 1) % 256;
					
						b = (b + swapBox[a]) % 256;
						
						swap(a, b, swapBox);
					}
					
					return swapBox;
				}
			
				string prga(unsigned char * toEncrypt, unsigned long long int messageSize, unsigned char * swapBox){
					
					string encryptedString;
					
					for(unsigned long long int c=0; c<messageSize; c++){

						a = (a+1) % 256;

						b = (b+swapBox[a]) % 256;

						swapBox = swap(a, b, swapBox);

						toEncrypt[c] = swapBox[ (swapBox[a] + swapBox[b]) %256 ] ^ toEncrypt[c];

						encryptedString += toEncrypt[c];
					}
					
					delete(toEncrypt);
					
					return encryptedString;
				}
		};
	}
}

#endif