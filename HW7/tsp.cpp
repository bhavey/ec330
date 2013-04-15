/*
First a quick explanation of simulated annealing in general:
************************************************************************
Simulated annealing is a heuristic method for solving the 'Hill
climbing' problem. An algorithm that finds the max of a large set of
data that when plotted graphically looks like a mountain range.
A simple hill climbing algorithm will get stuck at a local maxima,
as there are lower points to the right/left of a given peak.
Simulated annealing models the matallurgical practice of cooling
materials. It goes through the entire set, probablistically
choosing whether to go to a neighbor of the current point. If this
neighbor is a better fit it will always go there. Otherwise it will
potentially jump to a new 'lesser' fit. depending on a weighted
probability. As time goes on the weight of the probability decreases,
meaning it stays at the better fit no matter what. This is the analog
to the temperature dropping in metallurgic annealing.

Implementation of simulated annealing:
************************************************************************
First, start at a given beginning state (position). Now the algo
considers neightboring states and probablistically decides whether
to move to a given neighbor state or to stay at the current state. This
probability is weighted with a weighting that decreases over time,
eventually placing the final state as a good bet as the best state.

Now an overview of how it will work with the traveling sales man:
************************************************************************
(Note: This idea was borrowed from the wikipedia page on simulated annealing)
Each state is defined as a particular permutation of the cities to be visited.
The neighbors of a permutation are the permutations that are produced by
interchanging a pair of adjacent cities. The action taken to alter the solution
in order to find the neighbouring solutions is called a "move" and different moves
give different neighbours.

Psuedocode that will be ultimately implemented:
(Note, taken from: http://en.wikipedia.org/wiki/Simulated_annealing)
************************************************************************
s ← s0; e ← E(s)                    // Initial state, energy.
sbest ← s; ebest ← e                // Initial "best" solution
k ← 0                               // Energy evaluation count.
while k < kmax and e > emax         // While time left & not good enough:
  T ← temperature(k/kmax)           // Temperature calculation.
  snew ← neighbour(s)               // Pick some neighbour.
  enew ← E(snew)                    // Compute its energy.
  if P(e, enew, T) > random() then  // Should we move to it?
    s ← snew; e ← enew              // Yes, change state.
  if enew < ebest then              // Is this a new best?
    sbest ← snew; ebest ← enew      // Save 'new neighbour' to 'best found'.
  k ← k + 1                         // One more evaluation done
return sbest        

Information acquired about the structure of the map:
************************************************************************
There are a total of 1502 cities. This was found by running:
$ awk '{print $1}' map.txt | uniq | wc -l
   1502
Not every city points to every other city. Found by running:
$ awk '{print $1}' map.txt | grep ETCW | wc -l
   893
(Since there isn't 1501 places ETCW goes to, it doesn't go to any other city)
Not every path is bidirectional. If so, total lines of ETCW would be 2*893=1786
$ cat map.txt | grep ETCW | wc -l
   1749
4 Cities have paths to themselves (MDGZ, NVPR, NXEO, KGZX):
$ awk 'substr($1,1,4)==substr($3,1,4){print $1}' map.txt
   MDGZ
   NVPR
   NXEO
   KGZX

Restrictions put on us to complete the assignment
************************************************************************
 * Find the graph the goes through each vertex at least once and has the min weight
 * Must start/end at ETCW.

Implementation plans:
************************************************************************
1) First load the data:
 * Load an array of 4chars the possible cities into a name array of 4 char arrays.
 * Create a map<char*,bool> Visited denoting if a city has been visited.
 * Create a map<char*,struct city_Data > Paths listing off the travel path.
 * city_Data struct has the # of cities that lead to the current city. It also has a vector
 * of Cities the given city points to. After all the cities have their vectors populated,
 * this vector will be sorted with sort(). They will be sorted by how many cities point to them.
 * Also, it has a map<char*,int> that lists the price to go to a given place. = 0 if not
 * a possible destination. Finally, it has a bool GoesToETCW variable. =1 if the city
 * goes to ETCW in specific

2) Then create a valid random path:
 * Add ETCW to Paths. Go through the vector, checking if a city has been picked yet. If not,
 * go there 67% of the time. If not keep going. If you run out of possible cities, pick a
 * random one. Once you go to your next city add it to the path and repeat. Do this until
 * you've been to every city. At that point see if you can go to ETCW, if not, pick the last
 * one in the vector.

3) Try to find a better path. Do this n times. The larger n, the better the final path:
 * See if you can swap the 2nd/3rd. If not the 2nd/4th. etc until 2nd/last. If you come
 * up with a possible switch, check to see if it's cheaper. If so, do it! Repeat for 3rd,
 * 4th, etc until your at the last city. At this point you can repeat for an even better
 * graph.

*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <map>
#include <utility>

using namespace std;
#define CITY_NUM 1502

/*
1) First load the data:
 * Load an array of 4chars the possible cities into a name array of 4 char arrays.
 * Create a map<char*,bool> Visited denoting if a city has been visited.
 * Create a map<char*,struct city_Data > Paths listing off the travel path.
 * city_Data struct has the # of cities that lead to the current city. It also has a vector
 * of Cities the given city points to. After all the cities have their vectors populated,
 * this vector will be sorted with sort(). They will be sorted by how many cities point to them.
 * Also, it has a map<char*,int> that lists the price to go to a given place. = 0 if not
 * a possible destination. Finally, it has a bool GoesToETCW variable. =1 if the city
 * goes to ETCW in specific
 */

struct moves {
    int num; //# of cities that point to this city.
    vector<string> poss; //All the possible cities. Will get sorted at the end.
    map<string,int> prices; //The prices of going to the cities.
    bool GoesToETCW;
};

int main() {
    map<string,moves> Paths;
	string city_names[CITY_NUM];	
    fstream in;
    int i=0,j=0;
    in.open("map.txt", fstream::in);
    string entry;
    string cur_dest;
    long dick;
    while (in >> entry) {
        if ((i+4)%4==0) { //Source
            if ((city_names[j]!=entry)&&(j<CITY_NUM)) {
                if (j==0) {
                    city_names[j]=entry;
                } else {
                    j++;
                    city_names[j]=entry;
                }
            }
        } else if ((i+6)%4==0) { //Destination
            Paths[city_names[j]].poss.push_back(entry);
            cur_dest=entry;
        } else if ((i+7)%4==0) { //Price.
            Paths[city_names[j]].prices[cur_dest]=atoi(entry.c_str());
//            dick = atoi(entry.c_str());
        }
        i++;
    }
    //printf("City names:\n");
    //for (i=0; i<CITY_NUM; i++)
    //	printf("%s\n",city_names[i].c_str());
	srand (time(NULL));
	int ran=rand()%12;
	printf("Random number: %d\n",ran);
	in.close();	
	return 0;
}