#include <stdio.h>
#include "QuadReg.cpp"
  
#define N 10
int main() {
	long double x[10] = {.2,  .4,  .6,  .8,  1,  1.2,  1.4,   1.6,   1.8,   2};
	long double y[10] = {690.1947, 690.1938, 690.1369, 690.08, 690.0231, 690.0231, 689.966, 689.909, 689.8525, 689.7957};
//	double x[11] = {0,  1,  2,  3,  4,  5,  6,   7,   8,   9,   10};
//	double y[11] = {1,  6,  17, 34, 57, 86, 121, 162, 209, 262, 321};
	QuadReg QR;
	for (int i = 0; i<N; i++) {
		QR.AddPoints(x[i],y[i]/10000);
	}
	printf("EQTN: %.3Le*x^2 + %.3Le*x + %.3Le, R=%.3Le\n",QR.aTerm(),QR.bTerm(),QR.cTerm(),QR.rSquare());
	printf("Pos: %.3Le, Neg: %.3Le\n",QR.findPosZero(),QR.findNegZero());
	return 0;
}