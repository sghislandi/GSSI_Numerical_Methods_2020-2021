#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>  

//Pulsation ODE: dy/dx = g/l*sin(x) where g = 981 (in cm/s**2) and l = 10 (in cm)
auto dydt(double x){
    return -981/10*std::sin(x);  
}

void RK2(double h, int step, std::vector<double> &x, std::vector<double> &y){
    double k1 = h*y[step-1];
    double k2 = h*dydt(x[step-1]);
    double k3 = h*dydt(x[step-1]+0.5*k1);
    y[step] = y[step-1] + k3;
    x[step] = x[step-1] + k1;

    return;
}


int main(){

    //fixed quantities
    const double pi = std::atan(1)*4;

    //initial conditions
    const double x0 = 179.*pi/180.;   //in rad
    const double y0 = 0;              //in 1/s

    //Time
    const double t0 = 0;        //in s
    const double tf = 50;       //in s

    //Number of initial divisions
    const int N = 100000000;
    
    /////////////////////////////////////////////////
    double h = (double)(tf - t0)/N;
    int step = 1;
    std::vector<double> x(N+1,0);
    std::vector<double> y(N+1,0);

    //Setting initial conditions
    x[0] = x0;
    y[0] = y0;
    std::ofstream output("../build/output/ODE/ODE.txt", std::ofstream::trunc);

    while(t0+step*h<=tf){
        RK2(h,step,x,y);
        if(step % 10000 == 0){
        output << t0+step*h << "\t" << x[step] << "\t" << y[step] << std::endl; 
        }
        step++;
    }

    output.close();

    std::cout << "Output saved in ../build/output/ODE/ODE.txt" << std::endl;




    return 0;
}