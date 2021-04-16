// Integral evaluation with Simpson rule

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

#define a  0
#define b  2
#define exact_integral 4.4

using namespace std;


double func(double x){
    return pow(x,4) -2*x + 1;
}

double integrate(int N){
    double h = (double) (b-a)/N;
    double approx_integral = func(a)+func(b);
    for(int i=1; i < N; i++){ 
        if(i%2==0) approx_integral +=  2*func(a+i*h);
        else approx_integral +=  4*func(a+i*h);
    }

    return approx_integral *= h/3.;
}

int main(){

    int N_max = pow(2,25);
    double error;
    ofstream file_errors("../build/output/simpson_integration/simpson_approximation_errors.txt", ofstream::trunc);
    file_errors<< "N" << "\t" << "Error"<<endl;

    for(int N = 2; N< N_max; N*=2){
        error = integrate(N) - exact_integral;
        file_errors<< N << "\t" << error <<endl;
        cout << "Step " << log2(N) << "  Error: " << error << endl;
    }
    
    file_errors.close();
    cout << "Output saved in ../build/output/simpson_integration/simpson_approximation_errors.txt" << endl;

    return 0;
}



