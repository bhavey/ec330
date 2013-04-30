#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

#define N 2

int main (int argc, char* argv[]) {
	string reply;
	int start = 0; //Starting currency!
	string tmpreply;
	int recv;
	int startCur=0;
	int destCur=50;

 	if (argc!=3) {
 		printf("Incorrect format! Use ./PROG USER PASS\n");
 		return -1;
 	}
 	try {
		//Algorithmics.bu.edu is 128.197.185.27
		ClientSocket client_socket("128.197.185.27", 8001);
		string send;
		char tmp[1000];

		while (send!="done") {
			cout << "CLIENT: ";
			getline(cin,send); // i.e. get the whole line (this is important, cin >> send stops at a whitespace
			sprintf(tmp,"%s %s %s\n",argv[1],argv[2],send.c_str()); //Write the formatted string to tmp
			int allChars=-12;
			client_socket << tmp;
			recv=(int)reply.find("ERR");
			usleep(10000);
			client_socket >> reply;

			while(recv==string::npos) {
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
			recv=(int)send.find("getOneRate");
			if (recv!=string::npos) {
				printf("ASKED FOR ONE RATE...\n");
				float MaxRate, under1, CurRate, MinRate, over1;
				MaxRate=0;
				under1=-10;
				CurRate=-1;
				while (CurRate > under1) { //Find the max peak in a currency exchange.
					//Request the rate!
					sprintf(tmp,"%s %s %d %d\n",argv[1],argv[2],startCur,destCur);
					client_socket << tmp;
					usleep(10000);
					client_socket >> reply;
					recv=(int)reply.find("ERR");
					while(recv==string::npos) {
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
					cout << "Found this oneRate: " << reply << endl;
					break;
				}

			} else {
				cout << "SERVER: " << reply << endl;
			}

//			if (!strcmp(send.c_str(),"getAllRates")) {
//				for (int i = 0; i < 100; i++) {
//					for (int j = 0; j < 100; j++) {
//						cout << exchange[i][j] << " ";
//					}
//					cout << endl;
//				}
//			}
		}
	}
	catch(SocketException& e) {
		cout << "Exception was caught:" << e.description() << "\n";
		cout << "Reply: " << reply << endl;
	}
	return 0;
}