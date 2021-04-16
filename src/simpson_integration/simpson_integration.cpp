// Integral evaluation with Simpson rule

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

#define a  0
#define b  2
#define exact_integral 4.4

using namespace std;

// function to be integrated
double func(double x){
    return std::pow(x,4) -2*x + 1;
}

// Simpson integration method
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
    std::ofstream file_errors("../build/output/simpson_integration/simpson_approximation_errors.txt", std::ofstream::trunc);
    file_errors<< "log2(N)" << "\t" << "Error"<<std::endl;

    for(int N = 2; N< N_max; N*=2){
        error = integrate(N) - exact_integral;
        file_errors<< std::log2(N) << "\t" << error <<std::endl;
        std::cout << "Step " << std::log2(N) << "  Error: " << error << std::endl;
    }
    
    file_errors.close();
    std::cout << "Output saved in ../build/output/simpson_integration/simpson_approximation_errors.txt" << std::endl;

    return 0;
}



