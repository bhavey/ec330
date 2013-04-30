#include <stdio.h>
#include "QuadReg.cpp"
  
int main() {
	float x[10] = {.2,  .4,  .6,  .8,  1,  1.2,  1.4,   1.6,   1.8,   2};
	float y[10] = {690.1947, 690.1938, 690.1369, 690.08, 690.0231, 690.0231, 689.966, 689.909, 689.8525, 689.7957};
	QuadReg QR;
	for (int i = 0; i<11; i++) {
		QR.AddPoints(x[i],y[i]);
	}
	printf("EQTN: %.3Le*x^2 + %.3Le*x + %.3Le, R=%.3Le\n",QR.aTerm(),QR.bTerm(),QR.cTerm(),QR.rSquare());
	printf("Pos: %.3Le, Neg: %.3Le\n",QR.findPosZero(),QR.findNegZero());
	return 0;
}