#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

double uAnalytical(double x){
    return std::cos(M_PI*x/2.);
}

double ComputeRMS(std::vector<double> u, const double xMin, const double dx){
    double RMS = 0;
    size_t N = u.size();
    for(int i=1; i<N-1; i++){
        RMS += std::pow(u[i] - uAnalytical(xMin + (double)i*dx),2);
    }
    return std::sqrt(RMS / (double) N);
}


std::vector<double> CNLoop(int N, const double dt, const double tMax){
    std::vector<double> errors;
    
    const int xDivision = N - 1;
    const double xMin = -1.;
    const double xMax = 1.;
    const double dx = (double)(xMax-xMin) / xDivision;

    const double D = 0.1;
    double alpha = D*dt/2./dx/dx;

    std::vector<double> f(N,0);
    std::vector<double> Q(N-2,0);

    for(int i = 1; i < N-1 ; i++){
        Q[i-1] = M_PI*M_PI/4.*D*dt*uAnalytical(xMin + (double)i*dx);
    }

    //Intermediate functions 
    std::vector<double> f0 = f;    
    std::vector<double> f1(N,0);
    std::vector<double> f2(N,0);
    std::vector<double> f4(N,0);
    std::vector<double> f8(N,0);
    std::vector<double> f16(N,0);

    double t = 0.;
    for(int tIndex = 0; tIndex<tMax/dt; tIndex ++){
        f = CrankNicolson(f, Q, alpha);
        errors.push_back(ComputeRMS(f, xMin, dx));
        if(N == 256){
            if(tIndex == 1000) f1 = f;
            if(tIndex == 2000) f2 = f;
            if(tIndex == 4000) f4 = f;
            if(tIndex == 8000) f8 = f;
            if(tIndex == 16000) f16 = f;
        }
    }
    if(N == 256){
        saveIntermediateFunctions(xMin,dx,N,f0,f1,f2,f4,f8,f16,f);
    }

    return errors;
}


int main(){
    std::ofstream output("output/PDE/PDE_2Norm.txt", std::ofstream::trunc);

    const double dt = std::pow(10,-3);
    const double tMax = 70;

    std::vector<int> N{(int)std::pow(2,8),
                       (int)std::pow(2,9),
                       (int)std::pow(2,10)};

    std::vector<double> errors256 = CNLoop(N[0], dt, tMax);
    std::vector<double> errors512 = CNLoop(N[1], dt, tMax);
    std::vector<double> errors1024 = CNLoop(N[2], dt, tMax);

    double time = 0;
    for(int i=0; i<tMax/dt; i++){
        output << time << "\t" << errors256[i] << "\t" << errors512[i] << "\t" << errors1024[i] << std::endl;
        time +=dt;
    }

    output.close();
    std::cout << "Output saved in output/PDE/PDE_2Norm.txt" << std::endl;

    
    return 0;
}