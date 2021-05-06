#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

#define GSL_SUCCESS 0

double uAnalytical(double x){
    return std::cos(M_PI*x/2.);
}

 /*
 *     diag  offdiag          0   .....
 *  offdiag     diag    offdiag   .....
 *        0  offdiag       diag   .....
 *        0        0    offdiag   .....
 */
int solve_tridiag_sym(const double diag, const double offdiag, std::vector<double>& rhs,
  std::vector<double>& x, size_t N)
{
    int status = 0;
    double gamma;
    std::vector<double> alpha(N);
    std::vector<double> z(N);

    size_t i, j;

    /* Cholesky decomposition
        A = L.D.L^t
        lower_diag(L) = gamma
        diag(D) = alpha
    */
    alpha[0] = diag;
    z[0] = rhs[0];

    if (alpha[0] == 0) {
    status = 1;
    }

    /* update RHS */
    for (i = 1; i < N; i++)
    {
        gamma = offdiag / alpha[i-1];
        alpha[i] = diag - offdiag*gamma;
        z[i] = rhs[i] - gamma * z[i - 1];
    }

    /* backsubstitution */
    x[N - 1] = z[N-1] / alpha[N-1];
    if (N >= 2){
        for (i = N - 2, j = 0; j <= N - 2; j++, i--){
            x[i] = (z[i] - gamma * x[i + 1]) / alpha[i];
        }
    }

  if (status == 1) {
    std::cout << "matrix must be positive definite" << std::endl;
  }

  return status;
}

std::vector<double> CrankNicolsonDiffusion(double alpha, std::vector<double>& Q, std::vector<double>& u){
    int N = u.size();
    std::vector<double> uNew(N);

    double diag = 1 + 2.*alpha;
    double offdiag = -alpha;

    std::vector<double> rhs = Q;
    rhs[0] += alpha*u[1] + (1-2.*alpha)*u[0];
    rhs[N-1] += alpha*u[N-2] + (1-2.*alpha)*u[N-1];

    for(int i=1; i<N-1; i++){
        rhs[i] += (1-2.*alpha)*u[i] + alpha*(u[i-1] + u[i+1]);
    }

    solve_tridiag_sym(diag, offdiag, rhs, uNew, N);
    uNew[0] = 0;
    uNew[N] = 0;

    return uNew;
}

double ComputeRMS(std::vector<double> u, const double xMin, const double dx){
    double RMS = 0;
    size_t N = u.size();
    for(int i=0; i<N; i++){
        RMS += std::pow(u[i] - uAnalytical(xMin + (double)i*dx),2);
    }
    return (double)std::sqrt(RMS / (double)N);
}


int main(){
    //std::ofstream output("output/PDE/PDE_2Norm.txt", std::ofstream::trunc);
    std::ofstream output("PDE_2Norm.txt", std::ofstream::trunc);
    const int xDivision = std::pow(2,8) -1;
    const double xMin = -1.;
    const double xMax = 1.;
    const double dx = (xMax-xMin) / xDivision;
    const double dt = std::pow(10,-3);
    const double tMax = 100;

    const double D = 0.1;
    const double alpha = D*dt/2./dx/dx;

    const int N = xDivision + 1;

    std::cout << N;
    std::vector<double> f(N,0);
    std::vector<double> Q(N,0);

    for(int i = 1; i < N ; i++){
        f[i] = uAnalytical(xMin + (double)i*dx);
        Q[i] = M_PI*M_PI/4.*D*dt*uAnalytical(xMin + (double)i*dx);
    }

    double tTemp = 0;
    while(tTemp < tMax){
        f = CrankNicolsonDiffusion(alpha, Q, f);
        output << tTemp << "\t" << ComputeRMS(f, xMin, dx) << std::endl;
        tTemp += dt;
    }

    output.close();
    std::cout << "Output saved in output/PDE/PDE_2Norm.txt" << std::endl;

    std::ofstream output_f("f.txt", std::ofstream::trunc);
    for(int i = 0; i < N; i++){
        output_f << xMin + i*dx << "\t" << f[i]/dx << "\t" << uAnalytical(xMin + i*dx) << std::endl;
    }

    output_f.close();

    
    return 0;
}