#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <sstream>
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
		char tmp[1000];
		//sstream in ("dictionary");
		//string entry;

		//while (in >> entry) { //Find relevant entries and put them in the vetors
		//	if (entry.length() == 1)
		//}

		while (send!="done") {
			cout << "CLIENT: ";
			getline(cin,send); // i.e. get the whole line (this is important, cin >> send stops at a whitespace
			sprintf(tmp,"%s %s %s\n",argv[1],argv[2],send.c_str()); //Write the formatted string to tmp
//			send=tmp;
			int allChars=-12;
			client_socket << tmp;
			recv=(int)reply.find("ERR");
			usleep(10000);
			client_socket >> reply;
			int old_length;

			while(recv==string::npos) {
				old_length=reply.size();
				client_socket << 1[argv] << " " << 2[argv] << " \n";
				usleep(10000);
				client_socket >> tmpreply;
				reply += tmpreply;
				recv=(int)reply.find("ERR");
				if (recv!=string::npos) {
					reply=reply.substr(0,recv);
					break;
				}
			}
			string entry;
			stringstream ss(reply);

			float exchange[100][100];
			if (!strcmp(send.c_str(),"getAllRates")) {
				while(ss >> entry) {
					if (atof(entry.c_str()) != 0) { //Got a number!
						for (int i = 0; i < 100; i++) {
							for (int j=0; j<100; j++) {
								exchange[i][j]=atof(entry.c_str());
								ss >> entry;
							}
						}
						break;
					}
				}
			} else {
				cout << "Not asking for all rates!\n";
				cout << "SERVER: " << reply << endl;
			}

			if (!strcmp(send.c_str(),"getAllRates")) {
				for (int i = 0; i < 100; i++) {
					for (int j = 0; j < 100; j++) {
						cout << exchange[i][j] << " ";
					}
					cout << endl;
				}
			}
		}
	}
	catch(SocketException& e) {
		cout << "Exception was caught:" << e.description() << "\n";
		cout << "Reply: " << reply << endl;
	}
	return 0;
}