#include "ClientSocket.h"
#include "SocketException.h"
#include "baseclass.cpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

#define N 2
float sumVector(vector<float> inVec) { //Sum the negative log contents of the array.
	float sum=0;
	//printf("Numbers to sum: ");
	for(vector<float>::iterator it = inVec.begin(); it != inVec.end(); it++) {
	//	printf("%.3f ",*it);
		sum-=log(*it);
	}
	//printf("\nsum: %f\n",sum);
	return sum;
}

int main (int argc, char* argv[]) {
	string reply;
	int start = 0; //Starting currency!
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

		while (send!="done") {
			cout << "CLIENT: ";
			getline(cin,send); // i.e. get the whole line (this is important, cin >> send stops at a whitespace
			sprintf(tmp,"%s %s %s\n",argv[1],argv[2],send.c_str()); //Write the formatted string to tmp
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
				printf("exchange[0][50]: %f\n",exchange[0][98]);
				vector<pair<vector<float>,float> > weights;
				int inBase[N];
				Base b(inBase,99,N); //I got 99 bases but a bitch aint one.
				for (int i=0; i<101; i++)
					b++;
				for (int i=0; i<9800; i++) { //99*99=9800. Don't you forget it.
					float weight;
					if ((b.at(0)==start) || (b.at(1)==start) || (b.at(0)==b.at(1))) {
						b++;
						continue; //We don't want any overlaps.
					}
					vector<float> paths;
					paths.push_back(exchange[0][b.at(0)]);
					paths.push_back(exchange[b.at(0)][b.at(1)]);
					paths.push_back(exchange[b.at(1)][0]);
					//printf("Path for 0->%d->%d->0: ",b.at(0),b.at(1));
					for (vector<float>::iterator it = paths.begin(); it != paths.end(); it++) {
					//	printf("%.3f ", *it);
					}
					weight=sumVector(paths);
					//	exchange[b.at(0)][b.at(1)], exchange[b.at(1)][0]);
					if (weight<0) {
						printf("Negative path for 0->%d->%d->0: ",b.at(0),b.at(1));
						for (vector<float>::iterator it = paths.begin(); it != paths.end(); it++) {
							printf("%.5f ", *it);
						}
						printf("\nOf weight: %.5f\n\n",weight);
						weights.push_back(make_pair(paths,weight));
					}
					paths.clear();
					b++;
				}
				b++;
			} else {
				cout << "Not asking for all rates!\n";
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