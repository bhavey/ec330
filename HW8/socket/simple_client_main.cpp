#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main (int argc, int argv[]) {
	try {
		//Algorithmics.bu.edu is 128.197.185.27
		ClientSocket client_socket ("128.197.185.27", 8001);
		string send;
		string reply;
      
		while (send!="done") {
			cout << "CLIENT: ";
			getline(cin,send); // i.e. get the whole line (this is important, cin >> send stops at a whitespace
			client_socket << send+"\n";
			sleep(1);   // give a little time between send and receive (1 second is usually overkill,
						//but it's safe)
			client_socket >> reply;
			cout << "SERVER:  " << reply << endl;
		}
	}
	catch(SocketException& e) {
		cout << "Exception was caught:" << e.description() << "\n";
	}
	return 0;
}
	
