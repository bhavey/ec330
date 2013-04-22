#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main (int argc, char* argv[]) {
 	if (argc!=3) {
 		printf("Incorrect format! Use ./PROG USER PASS\n")
 		return -1;
 	}
 	try {
		//Algorithmics.bu.edu is 128.197.185.27
		ClientSocket client_socket("128.197.185.27", 8001);
		string send;
		string reply;
		char tmp[1000];

		while (send!="done") {
			cout << "CLIENT: ";
			getline(cin,send); // i.e. get the whole line (this is important, cin >> send stops at a whitespace
			sprintf(tmp,"%s %s %s\n",argv[1],argv[2],send.c_str()); //Write the formatted string to tmp
			send=tmp;

			client_socket << send;
			usleep(500000);   // give a little time between send and receive.
			client_socket >> reply;
			cout << "SERVER:  " << reply << endl;
		}
	}
	catch(SocketException& e) {
		cout << "Exception was caught:" << e.description() << "\n";
	}
	return 0;
}
	
