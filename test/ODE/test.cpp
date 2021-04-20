#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>  

//Test ODE: dy/dx = x
auto dydt(double x){
    return x;
}

//Exact solutions
auto fx(double t){
    return 0.5*(std::exp(t) + std::exp(-t));
}

auto fy(double t){
    return 0.5*(std::exp(t) - std::exp(-t));
}

//Runge-Kutta method
void RK2(double h, int step, std::vector<double> &x, std::vector<double> &y){
    double k1 = h*y[step-1];
    double k2 = h*dydt(x[step-1]);
    double k3 = h*dydt(x[step-1]+0.5*k1);
    y[step] = y[step-1] + k3;
    x[step] = x[step-1] + k1;

    return;
}

int main(){

    //Initial condition
    const double x0 = 1;
    const double y0 = 0;

    //Time interval
    const double t0 = 0;
    const double tf = 10;

    //Number of initial divisions
    const int nMin = 100;
    const int nMax = 1e9;
    int N = nMin;
    double maxErrorX;
    double maxErrorY;

    std::ofstream output("rk2Test.txt", std::ofstream::trunc);

    /////////////////////////////////////////////////
    while(N <= nMax){
    maxErrorX = 0;
    maxErrorY = 0;
    double h = (double)(tf - t0)/N;
    int step = 1;
    std::vector<double> x(N+1,0);
    std::vector<double> y(N+1,0);

    //Setting initial conditions
    x[0] = x0;
    y[0] = y0;

    //Runge-Kutta routine
    while(t0+step*h<=tf){
        RK2(h,step,x,y);
        maxErrorX = std::max(std::abs(x[step] / fx(t0+step*h)-1),maxErrorX);
        maxErrorY = std::max(std::abs(y[step] /fy(t0+step*h)-1),maxErrorY);
        step++;
    }

    output << N << "\t" << maxErrorX << "\t" << maxErrorY << std::endl; 
    N*=2;
    }

    output.close();

    std::cout << "Output saved in rk2Test.txt" << std::endl;

    return 0;
}