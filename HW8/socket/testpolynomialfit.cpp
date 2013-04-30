#include <stdio.h>
#include "LstSquQuadRegr.cpp"
  
int main() {
	float x[11] = {0,  1,  2,  3,  4,  5,  6,   7,   8,   9,   10};
	float y[11] = {1,  6,  22, 36, 57, 86, 110, 162, 209, 262, 321};
	QuadReg QR;
	for (int i = 0; i<11; i++) {
		QR.AddPoints(x[i],y[i]);
	}
	printf("EQTN: %.3f*x^2 + %.3f*x + %.3f, R=%.3f\n",QR.aTerm(),QR.bTerm(),QR.cTerm(),QR.rSquare());
	return 0;
}