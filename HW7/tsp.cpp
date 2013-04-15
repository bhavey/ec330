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
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <time.h>

using namespace std;

int main() {
	srand (time(NULL));
	int ran=rand()%12;
	printf("Random number: %d\n",ran);
	return 0;
}