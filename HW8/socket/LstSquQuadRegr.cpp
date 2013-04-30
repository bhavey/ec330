#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;
//Reimplemented from http://www.codeproject.com/Articles/63170/Least-Squares-Regression-for-Quadratic-Curve-Fitti
//Code was a C# class, implemented by Alex Etchells. Changed to C++.
//Uses s{jk} notation.

class QuadReg {
public:
    //constructor
    QuadReg() {
        numOfEntries = 0;
        pair<float,float> pointpair;
    }

    //add point pairs
    void AddPoints(float x, float y)  {
        pair<float,float> pointpair (x,y); 
        numOfEntries +=1; 
        pointArray.push_back(pointpair);
    }

    //returns the a term of the equation ax^2 + bx + c
    float aTerm() {
        if (numOfEntries < 3) {
            printf("Insufficient pairs of co-ordinates\n");
            return 0;
        }
        //notation sjk to mean the sum of x_i^j*y_i^k. 
        double s40 = getSx4(); //sum of x^4
        double s30 = getSx3(); //sum of x^3
        double s20 = getSx2(); //sum of x^2
        double s10 = getSx();  //sum of x
        double s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        double s21 = getSx2y(); //sum of x^2*y
        double s11 = getSxy();  //sum of x*y
        double s01 = getSy();   //sum of y

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
    float bTerm() {
        if (numOfEntries < 3) {
            printf("Insufficient pairs of co-ordinates\n");
            return 0;
        }
        //notation sjk to mean the sum of x_i^j*y_i^k.
        float s40 = getSx4(); //sum of x^4
        float s30 = getSx3(); //sum of x^3
        float s20 = getSx2(); //sum of x^2
        float s10 = getSx();  //sum of x
        float s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        float s21 = getSx2y(); //sum of x^2*y
        float s11 = getSxy();  //sum of x*y
        float s01 = getSy();   //sum of y

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
    float cTerm() {
        if (numOfEntries < 3) {
            printf("Insufficient pairs of co-ordinates\n");
            return 0;
        }
        //notation sjk to mean the sum of x_i^j*y_i^k.
        float s40 = getSx4(); //sum of x^4
        float s30 = getSx3(); //sum of x^3
        float s20 = getSx2(); //sum of x^2
        float s10 = getSx();  //sum of x
        float s00 = numOfEntries;
        //sum of x^0 * y^0  ie 1 * number of entries

        float s21 = getSx2y(); //sum of x^2*y
        float s11 = getSxy();  //sum of x*y
        float s01 = getSy();   //sum of y

        //c = Dc/D
        return (s40*(s20 * s01 - s10 * s11) - 
                s30*(s30 * s01 - s10 * s21) + 
                s20*(s30 * s11 - s20 * s21))
                /
                (s40 * (s20 * s00 - s10 * s10) - 
                 s30 * (s30 * s00 - s10 * s20) + 
                 s20 * (s30 * s10 - s20 * s20));
    }
    
    float rSquare() { // get r-squared
        if (numOfEntries < 3) {
            printf("Insufficient Entries.\n");
            return 0;
        }
        // 1 - (residual sum of squares / total sum of squares)
        return 1 - getSSerr() / getSStot();
    }
   

private:
    int numOfEntries; 
    float *pointpair; 
    vector<pair<float,float> > pointArray; 

    //helper methods
    float getSx() { //get sum of x
        float Sx = 0;
        //FIX THAT!!!!
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx += (*it).first;
        }
        return Sx;
    }

    double getSy() { //get sum of y
        float Sy = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sy += (*it).second;
        }
        return Sy;
    }

    float getSx2() { //get sum of x^2
        float Sx2 = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx2 += pow((*it).first, 2); //sum of x^2
        }
        return Sx2;
    }

    float getSx3() { //get sum of x^3
        float Sx3 = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx3 += pow((*it).first, 3); //sum of x^3
        }
        return Sx3;
    }

    float getSx4() { //get sum of x^4
        float Sx4 = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx4 += pow((*it).first, 4); //sum of x^4
        }
        return Sx4;
    }

    float getSxy() { //get sum of x*y
        float Sxy = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sxy += (*it).first * (*it).second; //sum of x*y
        }
        return Sxy;
    }

    float getSx2y() { //get sum of x^2*y
        float Sx2y = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            Sx2y += pow((*it).first, 2) * (*it).second; //sum of x^2*y
        }
        return Sx2y;
    }

    float getYMean() //mean value of y
    {
        float y_tot = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            y_tot += (*it).second; 
        }
        return y_tot/numOfEntries;
    }

    float getSStot() { //total sum of squares
        //the sum of the squares of the differences between 
        //the measured y values and the mean y value
        float ss_tot = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            ss_tot += pow((*it).second - getYMean(), 2);
        }
        return ss_tot;
    }

    float getSSerr() { //residual sum of squares
        //the sum of the squares of te difference between 
        //the measured y values and the values of y predicted by the equation
        float ss_err = 0;
        for (vector<pair<float, float> >::iterator it = pointArray.begin(); it != pointArray.end(); it++) {
            ss_err += pow((*it).second - getPredictedY((*it).first), 2);
        }
        return ss_err;
    }

    float getPredictedY(float x) {
        //returns value of y predicted by the equation for a given value of x
        return aTerm() * pow(x, 2) + bTerm() * x + cTerm();
    }
};

//int main()