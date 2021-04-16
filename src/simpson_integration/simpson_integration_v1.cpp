#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>  

#define a  0
#define b  2
#define exact_integral 4.4

// function to be integrated
auto func = [](double x) {return std::pow(x,4) -2*x + 1;};

// Simpson integration method
double integrate(int N){
    std::vector<double> funcArray (N-1);
    double h = (double) (b-a)/N;
    std::generate (funcArray.begin(), funcArray.end(), [h,i=1]() mutable {
        return i % 2 == 0 ? 2*func(a+h*i++) : 4*func(a+h*i++);    
    });
    return 1/3. * h * std::accumulate(funcArray.begin(), funcArray.end(), func(a) + func(b));
}


int main(){

    int Nmin = 2;
    int Nmax = pow(2,25);
    double error;
    std::ofstream file_errors("../build/output/simpson_integration/simpson_approximation_errors_v1.txt", std::ofstream::trunc);
    file_errors << "log2(N)" << "\t" << "Error"<<std::endl;

    while(Nmin < Nmax){
        error = integrate(Nmin) - exact_integral;
        file_errors<< std::log2(Nmin) << "\t" << error <<std::endl;
        std::cout << "Step " << std::log2(Nmin) << "  Error: " << error << std::endl;
        Nmin *= 2;
    }
    
    file_errors.close();
    std::cout << "Output saved in ../build/output/simpson_integration/simpson_approximation_errors_v1.txt" << std::endl;

    return 0;
}