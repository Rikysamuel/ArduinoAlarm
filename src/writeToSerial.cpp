#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <cstring>
#include <unistd.h>
#include <windows.h>
#include <sstream>
using namespace std;

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

DWORD WINAPI MyThreadFunction( LPVOID lpParam );
void playSong();
HANDLE hThread;
DWORD dwThreadId;

// application reads from the specified serial port and reports the collected data
int main(int argc, char* argv[])
{
	printf("Welcome to the serial test app!\n\n");
	string str = "\\\\.\\COM13";

	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	Serial* SP = new Serial(cstr);    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected\n");

	//char incomingData[256] = "";
	int dataLength = 256;
	int readResult = 0;

	//kirim start
	cin >> str;
	cout << "user command = " << str << endl;
	str+="\n";

	char* sendData = new char[str.length()+1];
	strcpy(sendData, str.c_str());

	SP->WriteData(sendData, dataLength);

	if (str == "start\n") {
		playSong();
	}

	while(SP->IsConnected())
	{
		char incomingData[256] = "";
		readResult = SP->ReadData(incomingData,dataLength);
		printf("Bytes read: (-1 means no data available) %i\n",readResult);

		std::string test(incomingData);
		printf("%s\n",incomingData);
		if (test.find("off") != std::string::npos) {
		    std::cout << "CountDown Off!" << '\n';
		    //kill(PID, 15);  //Sends the SIGINT Signal to the process, telling it to stop.
		    int retval = ::_tsystem( _T("taskkill /F /T /IM wmplayer.exe") );
		    TerminateThread(hThread, dwThreadId);
			CloseHandle(hThread);
		    break;
		}

		test = "";

		Sleep(500);
	}
	return 0;
}

void playSong() {
	 hThread = CreateThread( 
        NULL,      // default security attributes
        0,                      // use default stack size  
        MyThreadFunction,       // thread function name
        NULL,          // argument to thread function 
        0,                      // use default creation flags 
        &dwThreadId);   // returns the thread identifier 
}

DWORD WINAPI MyThreadFunction( LPVOID lpParam ) {
    system("song.mp3");
    return 0; 
}