#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>  

//Pulsation ODE: dy/dx = g/l*sin(x) where g = 981 (in cm/s**2) and l = 10 (in cm)
auto dydt(double x){
    return -981/10*std::sin(x);  
}

//Runge-Kutta 2nd order method applied to dy/dx = f(x)
void RK2(double h, int step, std::vector<double> &x, std::vector<double> &y){
    double k1 = h*y[step-1];
    double k2 = h*dydt(x[step-1]);
    double k3 = h*dydt(x[step-1]+0.5*k1);
    y.push_back(y[step-1] + k3);
    x.push_back(x[step-1] + k1);
    return;
}

//Adaptive step size method
void AdaptiveRK(double *h, std::vector<double> &t, std::vector<double> &x, std::vector<double> &y, const double accuracy){
    double hval = *h;
    std::vector<double> xtemp1(1,x.back());
    std::vector<double> ytemp1(1,y.back());
    std::vector<double> xtemp2(1,x.back());
    std::vector<double> ytemp2(1,y.back());
    RK2(hval, 1, xtemp1, ytemp1);       //Compute x_n-->x_n+1-->x_n+2
    RK2(hval, 2, xtemp1, ytemp1);
    RK2(2.*(hval), 1, xtemp2, ytemp2);  //Compute x_n---->x_n+2

    double rho = (double) 6.*hval*accuracy/std::abs(xtemp1[2]-xtemp2[1]);

    //if rho>1 I keep x and y but I make the step larger (avoiding to enlarge it too much)
    if(rho>=0.99){
        t.push_back(t.back()+hval);
        t.push_back(t.back()+hval);
        x.push_back(xtemp1[1]);
        x.push_back(xtemp1[2]);
        y.push_back(ytemp1[1]);
        y.push_back(ytemp1[2]);
        *h = hval*(std::min(2.,std::pow(rho,0.5)));
    }
    //if rho<1 I make the step smaller and I repeat the RK
    else{
        *h = (double)hval*(std::max(0.5,std::pow(rho,0.5)));
        AdaptiveRK(h,t,x,y,accuracy);
    }
    return;
}


int main(){

    //Fixed quantities
    const double pi = std::atan(1)*4;
    const double accuracy = 1e-5;
    const int N = 10000000;

    //Time
    const double t0 = 0;        //in s
    const double tf = 20;       //in s

    //Initial conditions
    const double x0 = 179.*pi/180.;   //in rad
    const double y0 = 0;              //in 1/s
    
    /////////////////////////////////////////////////
    double hValue = (double)(tf - t0)/N;
    int step = 1;

    //Runge-Kutta routine
    std::ofstream output("output/ODE/ODE.txt", std::ofstream::trunc);
    std::vector<double> x(1,x0);
    std::vector<double> y(1,y0);
    output << t0 << "\t" << x[0] << "\t" << y[0] << std::endl;  

    while(true){
        RK2(hValue,step,x,y);
        if(step % 10000 == 0){
        output << t0 + step*hValue << "\t" << x.back() << "\t" << y.back() << std::endl;  
        }
        
        if((t0 + step*hValue)>=tf){break;}
        step++;
    }
    output.close();
    std::cout << "Output saved in output/ODE/ODE.txt" << std::endl;


    //Runge-Kutta routine with adaptive step method
    std::ofstream outputAdaptive("output/ODE/ODE_Adaptive.txt", std::ofstream::trunc);
    std::vector<double> tAdaptive(1,t0);
    std::vector<double> xAdaptive(1,x0);
    std::vector<double> yAdaptive(1,y0);

    double *h;
    h = &hValue;

    step = 1;
    output << tAdaptive[0] << "\t" << xAdaptive[0] << "\t" << yAdaptive[0] << std::endl;  
    while(true){
        AdaptiveRK(h, tAdaptive, xAdaptive, yAdaptive, accuracy);
        if(step % 10000 == 0){
        outputAdaptive << tAdaptive.back() << "\t" << xAdaptive.back() << "\t" << yAdaptive.back() << std::endl;  
        }
        
        if(tAdaptive.back()>=tf){break;}
        step++;
    }

    outputAdaptive.close();
    std::cout << "Output saved in output/ODE/ODE_Adaptive.txt" << std::endl;


    return 0;
}