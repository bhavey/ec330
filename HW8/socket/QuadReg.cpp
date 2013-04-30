#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;
//Reimplemented from http://www.codeproject.com/Articles/63170/Least-Squares-Regression-for-Quadratic-Curve-Fitti
//Code was a C# class, implemented by Alex Etchells. Changed to C++.
//Uses s{jk} notation.
//Incorporated different containers and implemented clear and find zero functions.

class QuadReg {
public:
    //constructor
    QuadReg() {
        numOfEntries = 0;
        pair<long double,long double> pointpair;
    }

    void ClearContents() {
        numOfEntries = 0;
        pointArray.clear();
    }

    //add point pairs
    void AddPoints(long double x, long double y)  {
        pair<long double, long double> pointpair (x,y); 
        numOfEntries +=1; 
        pointArray.push_back(pointpair);
    }

    //returns the a term of the equation ax^2 + bx + c
    long double aTerm() {
        if (numOfEntries < 3) {
            printf("Insufficient pairs of co-ordinates\n");
            return 0;
        }
        //notation sjk to mean the sum of x_i^j*y_i^k. 
        long double s40 = getSx4(); //sum of x^4
        long double s30 = getSx3(); //sum of x^3
        long double s20 = getSx2(); //sum of x^2
        long double s10 = getSx();  //sum of x
        long double s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        long double s21 = getSx2y(); //sum of x^2*y
        long double s11 = getSxy();  //sum of x*y
        long double s01 = getSy();   //sum of y

        //a = Da/D
        return (s21*(s20 * s00 - s10 * s10) - 
                s11*(s30 * s00 - s10 * s20) + 
                s01*(s30 * s10 - s20 * s20))
                /
                (s40*(s20 * s00 - s10 * s10) -
                 s30*(s30 * s00 - s10 * s20) + 
                 s20*(s30 * s10 - s20 * s20));
    }

    //returns the b term of the equation ax^2 + bx + c
    long double bTerm() {
        if (numOfEntries < 3) {
            printf("Insufficient pairs of co-ordinates\n");
            return 0;
        }
        //notation sjk to mean the sum of x_i^j*y_i^k.
        long double s40 = getSx4(); //sum of x^4
        long double s30 = getSx3(); //sum of x^3
        long double s20 = getSx2(); //sum of x^2
        long double s10 = getSx();  //sum of x
        long double s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        long double s21 = getSx2y(); //sum of x^2*y
        long double s11 = getSxy();  //sum of x*y
        long double s01 = getSy();   //sum of y

        //b = Db/D
        return (s40*(s11 * s00 - s01 * s10) - 
                s30*(s21 * s00 - s01 * s20) + 
                s20*(s21 * s10 - s11 * s20))
                /
                (s40 * (s20 * s00 - s10 * s10) - 
                 s30 * (s30 * s00 - s10 * s20) + 
                 s20 * (s30 * s10 - s20 * s20));
    }

    //returns the c term of the equation ax^2 + bx + c
    long double cTerm() {
        if (numOfEntries < 3) {
            printf("Insufficient pairs of co-ordinates\n");
            return 0;
        }
        //notation sjk to mean the sum of x_i^j*y_i^k.
        long double s40 = getSx4(); //sum of x^4
        long double s30 = getSx3(); //sum of x^3
        long double s20 = getSx2(); //sum of x^2
        long double s10 = getSx();  //sum of x
        long double s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        long double s21 = getSx2y(); //sum of x^2*y
        long double s11 = getSxy();  //sum of x*y
        long double s01 = getSy();   //sum of y

        //c = Dc/D
        return (s40*(s20 * s01 - s10 * s11) - 
                s30*(s30 * s01 - s10 * s21) + 
                s20*(s30 * s11 - s20 * s21))
                /
                (s40 * (s20 * s00 - s10 * s10) - 
                 s30 * (s30 * s00 - s10 * s20) + 
                 s20 * (s30 * s10 - s20 * s20));
    }
    
    long double rSquare() { // get r-squared
        if (numOfEntries < 3) {
            printf("Insufficient Entries.\n");
            return 0;
        }
        // 1 - (residual sum of squares / total sum of squares)
        return 1 - getSSerr() / getSStot();
    }

    long double findPosZero() {
        long double inSqrt=bTerm()*bTerm()-4*aTerm()*cTerm();
        printf("inSqrt: %.3Le\n",inSqrt);
        long double outSqrt=pow(inSqrt,.5);
        printf("outSqrt: %.3Le\n",outSqrt);
        long double posterm=-bTerm()+outSqrt;
        posterm/=2;
        posterm/=aTerm();
        return posterm;
    }
    long double findNegZero() {
        long double inSqrt=bTerm()*bTerm()-4*aTerm()*cTerm();
        long double outSqrt=pow(inSqrt,.5);
        long double negterm=-bTerm()-outSqrt;
        negterm/=2;
        negterm/=aTerm();
        return negterm;
    }
   

private:
    int numOfEntries; 
    long double *pointpair; 
    vector<pair<long double,long double> > pointArray; 

    //helper methods
    long double getSx() { //get sum of x
        long double Sx = 0;
        //FIX THAT!!!!
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx += (*it).first;
        }
        return Sx;
    }

    long double getSy() { //get sum of y
        long double Sy = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sy += (*it).second;
        }
        return Sy;
    }

    long double getSx2() { //get sum of x^2
        long double Sx2 = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx2 += pow((*it).first, 2); //sum of x^2
        }
        return Sx2;
    }

    long double getSx3() { //get sum of x^3
        long double Sx3 = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx3 += pow((*it).first, 3); //sum of x^3
        }
        return Sx3;
    }

    long double getSx4() { //get sum of x^4
        long double Sx4 = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx4 += pow((*it).first, 4); //sum of x^4
        }
        return Sx4;
    }

    long double getSxy() { //get sum of x*y
        long double Sxy = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sxy += (*it).first * (*it).second; //sum of x*y
        }
        return Sxy;
    }

    long double getSx2y() { //get sum of x^2*y
        long double Sx2y = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx2y += pow((*it).first, 2) * (*it).second; //sum of x^2*y
        }
        return Sx2y;
    }

    long double getYMean() { //mean value of y
        long double y_tot = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            y_tot += (*it).second; 
        }
        return y_tot/numOfEntries;
    }

    long double getSStot() { //total sum of squares
        //the sum of the squares of the differences between 
        //the measured y values and the mean y value
        long double ss_tot = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            ss_tot += pow((*it).second - getYMean(), 2);
        }
        return ss_tot;
    }

    long double getSSerr() { //residual sum of squares
        //the sum of the squares of te difference between 
        //the measured y values and the values of y predicted by the equation
        long double ss_err = 0;
        for (vector<pair<long double, long double> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            ss_err += pow((*it).second - getPredictedY((*it).first), 2);
        }
        return ss_err;
    }

    long double getPredictedY(long double x) {
        //returns value of y predicted by the equation for a given value of x
        return aTerm() * pow(x, 2) + bTerm() * x + cTerm();
    }
};

//int main()