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

void saveIntermediateFunctions(const double xMin, const double dx, const int N,
                               std::vector<double> f0, std::vector<double> f1,
                               std::vector<double> f2, std::vector<double> f4,
                               std::vector<double> f8, std::vector<double> f16,
                               std::vector<double> f){
    std::ofstream outputIntermediate("output/PDE/f.txt", std::ofstream::trunc);
    for(int i=1; i < N-1; i++){
        outputIntermediate << xMin + i*dx << "\t" << f0[i] << "\t" << f1[i] << "\t" 
                           << f2[i] << "\t" << f4[i] << "\t" << f8[i] << "\t" 
                           << f16[i] << "\t" << f[i] << "\t" << uAnalytical(xMin + i*dx) << std::endl;
    }
    outputIntermediate.close();
    std::cout << "Output saved in output/PDE/f.txt" << std::endl;

    return;
}

int solve_tridiag_sym(const std::vector<double>& diag, const std::vector<double>& offdiag, 
                      const std::vector<double>& rhs, std::vector<double>& x, size_t N) {
    int status = 0;
    std::vector<double> alpha(N);
    std::vector<double> z(N);
    size_t i, j;

    //Initialize and check alpha
    alpha[0] = diag[0];
    z[0] = rhs[0];
    if (alpha[0] == 0) {
        status = 1;
    }

    for (i = 1; i < N; i++){
        const double t = offdiag[i-1] / alpha[i-1];
        alpha[i] = diag[i] - t * offdiag[i-1];
        z[i] = rhs[i] - t * z[i-1];
        if(alpha[i] == 0){
            status = 1;
        }
    }

    x[N - 1] = z[N - 1] / alpha[N - 1];
    if(N >= 2){
        for (i=N-2, j=0; j<=N-2; j++, i--) {
            x[i] = (z[i] - offdiag[i] * x[i+1]) / alpha[i];
        }
    }

    if (status == 1){
        std::cout << "Error : matrix must be positive definite!" << "\n";
    }

    return status;
}

std::vector<double> CrankNicolson(std::vector<double> u, std::vector<double> Q, double alpha) {
    auto N = u.size();
    std::vector<double> uNew(N);
    std::vector<double> diagonal(N-2, 1. + 2*alpha);
    std::vector<double> offdiag(N-3, -alpha);
    std::vector<double> rhs(N-2);

    rhs = Q;
    for (int i=1; i<N-1; ++i) {
    rhs[i-1] += (1-2.*alpha)*u[i] + alpha*(u[i-1] + u[i+1]);
    }

    std::vector<double> solution(N - 2);
    solve_tridiag_sym(diagonal, offdiag, rhs, solution, solution.size());

    for (int i=1; i<N-1; ++i){
        uNew[i] = solution[i-1];
    }
    uNew[0] = 0.;
    uNew[N-1] = 0.;

return uNew;
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