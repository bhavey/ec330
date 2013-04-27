#include <iostream>
#include <map>
#include <vector>
#include <utility>
using namespace std;

bool vecsort(pair <int,int> a, pair <int,int> b) {
	return a.second < b.second;
}

vector<pair<int,int> > mapsort(map<int,int> in) {
	//Put the map in a vector.
	vector<pair<int,int> > returnVec(in.begin(), in.end());
	//Use sort to sort by value instead of key.
	sort(returnVec.begin(),returnVec.end(),&vecsort);
	return returnVec;
}

int main () {
	map<int,int> test;
	test['a']=20;
	test['b']=10;
	test['c']=-1;
	test['d']=40;

	vector<pair<int,int> > sort_test;
	sort_test = mapsort(test);
	vector<pair<int,int> >::iterator it = sort_test.begin();
	for (it = sort_test.begin(); it != sort_test.end(); it++)
		cout << "test[" << (char)(*it).first << "]=" << (*it).second << "\n";
	return 0;
}