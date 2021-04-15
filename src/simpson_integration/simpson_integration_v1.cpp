#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>       // std::vector

using namespace std;

auto func = [](double x) {return pow(x,4) -2*x + 1;};

double integrate(double a, double b, int N){
    vector<double> funcArray (N-1);
    double h = (double) (b-a)/N;
    generate (funcArray.begin(), funcArray.end(), [a,h,i=1]() mutable {
        return i % 2 == 0 ? 2*func(a+h*i++) : 4*func(a+h*i++);    
    });
    
    return 1/3. * h * accumulate(funcArray.begin(), funcArray.end(), func(a) + func(b));
}


int main(){

    int Nmin = 2;
    int Nmax = pow(2,25);
    double a = 0.;
    double b = 2.;
    double exact_integral = 4.4;
    double error;
    ofstream file_errors("../build/output/simpson_integration/simpson_approximation_errors_v1.txt", ofstream::trunc);
    file_errors << "N" << "\t" << "Error"<<endl;


    while(Nmin < Nmax){
        error = integrate(a,b,Nmin) - exact_integral;
        file_errors<< Nmin << "\t" << error <<endl;
        cout << "Step " << log2(Nmin) << "  Error: " << error << endl;
        Nmin *= 2;
    }
    
    file_errors.close();
    cout << "Output saved in ../build/output/simpson_integration/simpson_approximation_errors_v1.txt" << endl;


    return 0;
}
