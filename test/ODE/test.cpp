#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>  

//Code to test the implemented Runge-Kutta method @ 2nd order. The test 
//ODE is d2x/dt2 = 6*x^(1/3) which has analytical solution x(t) = t^(3)

//Test ODE: dy/dx = x
auto dydt(double x){
    return 6*std::pow(x,1./3.);
}

//Analytical solutions
auto fx(double t){
    return t*t*t;
}

auto fy(double t){
    return 3*t*t;
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

    //Time interval
    const double t0 = 1;
    const double tf = 10;

    //Initial condition
    const double x0 = 1;
    const double y0 = 3;

    //Number of initial divisions
    const int nMin = 1000;
    const int nMax = 10e8;
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
            maxErrorX = std::max((double)std::abs(x[step] - fx(t0+step*h))/fx(t0+step*h),maxErrorX);
            maxErrorY = std::max((double)std::abs(y[step] - fy(t0+step*h))/fy(t0+step*h),maxErrorY);
            step++;
        }
        output << N << "\t" << maxErrorX << "\t" << maxErrorY << std::endl; 
        N*=2;
    }

    output.close();
    std::cout << "Output saved in rk2Test.txt" << std::endl;

    return 0;
}
