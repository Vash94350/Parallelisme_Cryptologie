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
				
					int messageToEncryptLength = messageToEncrypt.length();
					
					unsigned char * encryptedMessage =  (unsigned char *) malloc(messageToEncrypt.size() + 1);
					
					encrypt((unsigned char *) messageToEncrypt.c_str(), encryptedMessage, messageToEncrypt.length(), (unsigned char *) key.c_str(), key.length());
					
					string encryptedString((char*) encryptedMessage);
					
					encryptedString = encryptedString.substr(0, messageToEncryptLength);
					
					return encryptedString;
				}				
			
			private:
			
				unsigned char swapBox[256];
				
				void encrypt(unsigned char * toEncrypt, unsigned char * cryptedOutput, int messageSize, unsigned char key[], int keySize){
					
					for(int i=0; i<256; i++){
				
						swapBox[i] = (unsigned char) i;				
					}		
				
					ksa(key, keySize);
				
					prga(toEncrypt, cryptedOutput, messageSize);				
				}
				
				void ksa(unsigned char * key, int keySize){
				
					int j=0;
				
					for(int i=0; i<256; i++){
				
						j=(j+swapBox[i]+key[i% keySize])%256;
				
						swap(swapBox,i,j);				
					}				
				}
			
				void prga(unsigned char * toEncrypt, unsigned char * cryptedOutput, int messageSize){

					int a(0), b(0);
				
					for(int c=0; c<messageSize; c++){

						a = (a+1) % 256;

						b = (b+swapBox[a]) % 256;

						swap(swapBox, a, b);

						cryptedOutput[c] = swapBox[ (swapBox[a] + swapBox[b]) %256 ] ^ toEncrypt[c];
					}
				}			
				
				void swap(unsigned char data[], int i , int j){
				
					unsigned char temp = data[i];
				
					data[i] = data[j];
				
					data[j] = temp;				
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
				
				string rc4Encryption(string messageToEncrypt, string key){
					
					unsigned long long int messageToEncryptLength = messageToEncrypt.length();
					
					unsigned char * encryptedMessage = encrypt((unsigned char *) messageToEncrypt.c_str(), messageToEncryptLength, (unsigned char *) key.c_str(), key.length());
					
					string encryptedString((char*) encryptedMessage);
					
					encryptedString = encryptedString.substr(0, messageToEncryptLength);
					
					return encryptedString;
				}

				void setAandB(unsigned long long int  lastPosition) {

					for(unsigned long long int z=0; z<lastPosition; z++) {

						a = (a  + 1) % 256;
					
						b = (b + swapBox[a]) % 256;
						
						swap(a, b);
					}
				}
			
			private:
			
				unsigned char swapBox[256];
				
				unsigned long long int a = 0, b = 0;
				
				unsigned char * encrypt(unsigned char * toEncrypt, unsigned long long int  messageSize, unsigned char * key, unsigned long long int  keySize){
				
					for(unsigned long long int  i=0; i<256; i++){
				
						swapBox[i] = (unsigned char) i;
					}
				
					ksa(key, keySize);
				
					return prga(toEncrypt, messageSize);				
				}
				
				void ksa(unsigned char * key, int keySize){
				
					unsigned long long int j=0;
				
					for(int i=0; i<256; i++){
				
						j = (j+swapBox[i]+key[i%keySize])%256;
				
						swap(i,j);
					}				
				}
			
				unsigned char * prga(unsigned char * toEncrypt, unsigned long long int  messageSize){
				
					unsigned char * encryptedMessage =  (unsigned char *) malloc(messageSize + 1);
				
					for(unsigned long long int c=0; c<messageSize; c++){

						a = (a+1) % 256;

						b = (b+swapBox[a]) % 256;

						swap(a, b);

						encryptedMessage[c] = swapBox[ (swapBox[a] + swapBox[b]) %256 ] ^ toEncrypt[c];
					}
					
					return encryptedMessage;
				}			
				
				void swap(unsigned long long int  i , unsigned long long int  j){
				
					unsigned char temp = swapBox[i];
				
					swapBox[i] = swapBox[j];
				
					swapBox[j] = temp;				
				}
		};
	}
}

#endif