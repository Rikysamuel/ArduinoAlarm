#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <cstring>
using namespace std;

// application reads from the specified serial port and reports the collected data
int main(int argc, char* argv[])
{
	printf("Welcome to the serial test app!\n\n");
	string str = "\\\\.\\COM30";
	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	Serial* SP = new Serial(cstr);    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 256;
	int readResult = 0;

	while(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData,dataLength);
		printf("Bytes read: (-1 means no data available) %i\n",readResult);

		std::string test(incomingData);

		printf("%s",incomingData);
		test = "";

		Sleep(500);
	}
	return 0;
}