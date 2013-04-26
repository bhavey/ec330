#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
using namespace std;

int main (int argc, char* argv[]) {
	string reply;
	string tmpreply;
	int recv;

 	if (argc!=3) {
 		printf("Incorrect format! Use ./PROG USER PASS\n");
 		return -1;
 	}
 	try {
		//Algorithmics.bu.edu is 128.197.185.27
		ClientSocket client_socket("128.197.185.27", 8001);
		string send;
		string old_reply="jjs";
		char tmp[1000];

		while (send!="done") {
			cout << "CLIENT: ";
			getline(cin,send); // i.e. get the whole line (this is important, cin >> send stops at a whitespace
			sprintf(tmp,"%s %s %s\n",argv[1],argv[2],send.c_str()); //Write the formatted string to tmp
			send=tmp;
			int allChars=-12;
			client_socket << send;
			recv=(int)reply.find("ERR");
			usleep(10000);
			client_socket >> reply;
			int old_length;

			while(recv==string::npos) {
				old_length=reply.size();
				client_socket << argv[1] << " " << argv[2] << " \n";
				usleep(10000);
				client_socket >> tmpreply;
				reply += tmpreply;
				recv=(int)reply.find("ERR");
				if (recv!=string::npos) {
					reply=reply.substr(0,recv);
					break;
				}
			}
			cout << "SERVER:  " << reply << endl;
		}
	}
	catch(SocketException& e) {
		cout << "Exception was caught:" << e.description() << "\n";
		cout << "Reply: " << reply << endl;
	}
	return 0;
}
	
