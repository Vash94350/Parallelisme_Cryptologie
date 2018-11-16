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
				
				unsigned char * rc4Encryption(string messageToEncypt, string key){
					
					unsigned char * encryptedMessage =  (unsigned char *) malloc(messageToEncypt.size() + 1);
					
					encrypt((unsigned char *) messageToEncypt.c_str(), encryptedMessage, messageToEncypt.length(), (unsigned char *) key.c_str(), key.length());
					
					return encryptedMessage;
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
}

#endif