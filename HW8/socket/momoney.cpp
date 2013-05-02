#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <sys/time.h>
using namespace std;

#define N 2

int main (int argc, char* argv[]) {
	string reply;
	string tmpreply;
	int recv;
	int startCur=0;
	int destCur=12;
	float tradeAmount=5; //US $ to trade per transaction.
	float run_time;
	timeval start, end;
	gettimeofday(&start, NULL);
 	if (argc<3) {
 		printf("Incorrect format! Use ./PROG USER PASS\n");
 		return -1;
 	}
 	if (argc==5) {
 		startCur=atoi(argv[3]);
 		destCur=atoi(argv[4]);
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
			float tradeRate;
			long double avgArrag[10];
			float prevRate = -1;
			float curRate= 0;
			float minRate=0;
			bool buy=0;

			int iter;
			iter=0;
			recv=(int)send.find("getOneRate");
			if (recv!=string::npos) {
				//printf("HERE DAMNIT.\n");
				//printf("ASKED FOR ONE RATE...\n");
				float MaxRate, under1, CurRate, MinRate, over1, avg;
				MaxRate=0;
				under1=-10;
				CurRate=-1;
				while (CurRate > under1) { //Find the max peak in a currency exchange.
					if (iter==100) //break on average!
						break;
					//Request the rate!
					sprintf(tmp,"%s %s getOneRate %d %d\n",argv[1],argv[2],startCur,destCur);

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
					//cout << "Found this oneRate: " << reply << endl;
					usleep(1000000);
					recv=(int)reply.find(":");
					reply=reply.substr(recv+3);
					//avgArrag[iter]=atol(reply.c_str());
//					cout << /*"Specificially:" << */ avgArrag[iter] << endl;
					curRate=atof(reply.c_str());

					if (prevRate==-1) {
						prevRate=atof(reply.c_str()); //Initialize prevRate
					} else {
						if (!buy) { //We're looking to buy!
							if (prevRate<(curRate*.995)) { //Made the threshold! BUY.
								cout << "Found a max!\n";
								sprintf(tmp,"%s %s exchange %d %f %d\n",argv[1],argv[2],startCur,tradeAmount,destCur);
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
								cout << reply << endl;
								//break; //Get out of here!!!
								recv=reply.find_last_of(":");
								reply=reply.substr(recv+3);
								cout << reply << endl;
								tradeRate=atof(reply.c_str());
								if (tradeRate>1000)
									tradeRate=999.99;
								minRate=prevRate;
								buy=1;	//Set the bool flag
							} else {
								prevRate=CurRate; //Not jumping yet! Reset the buy flag
							}
						} else {
							if (curRate<(minRate*1.005)) { //Made the threshold. SELL!
								sprintf(tmp,"%s %s exchange %d %f %d\n",argv[1],argv[2],destCur,tradeRate,startCur);
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
								recv=reply.find_last_of(":");
								reply=reply.substr(recv+3);
							}
						}
					}
					cout << atof(reply.c_str()) << endl;
					iter++;
					gettimeofday(&end, NULL);
					run_time=0;
					//run_time=(float)(end.tv_sec-start.tv_sec);
					if (run_time>50) {
						printf("been running for over %f seconds.\n",run_time);
						ClientSocket client_socket("128.197.185.27", 8001);
						gettimeofday(&start,NULL);
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
					}
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