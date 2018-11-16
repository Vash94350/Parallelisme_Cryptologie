#include "rc4.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::string;

using namespace rc4::sequential;


int main()
{
    RC4 rc4;
	
	string messageToEncypt = "bonjour";
	
	cout << "main msg : " << messageToEncypt << endl;
	
	string key = "yolo";
	
	cout << "main key : " << key << endl;
	
	unsigned char * encrypted = rc4.rc4Encryption(messageToEncypt, key);
	
	encrypted[strlen((char*) encrypted)] = '\0';
	
	cout << encrypted << endl;
	
	return 0;
}
