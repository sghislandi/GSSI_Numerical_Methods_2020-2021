// Integral evaluation with Simpson rule

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

#define a  0
#define b  2
#define exact_integral 4.4

using namespace std;


double function(double x){
    return pow(x,4) -2*x + 1;
}

double integrate(int N){
    
    double h = (double) (b-a)/N;
    double approx_integral = function(a)+function(b);

    for(int i=1; i < N; i++){ 
        if(i%2==0) approx_integral +=  2*function(a+i*h);
        else approx_integral +=  4*function(a+i*h);
    }

    return approx_integral *= h/3.;
}

int main(){

    int N_max = pow(2,25);
    ofstream file_errors("../../output/simpson_integration/simpson_approximation_errors.txt", ofstream::trunc);
    file_errors<< "N" << "\t" << "Error"<<endl;

    for(int N = 2; N< N_max; N*=2){
        file_errors<< N << "\t" << integrate(N)-exact_integral<<endl;
    }
    
    file_errors.close();

    return 0;
}



