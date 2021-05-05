#include <math.h>
#include <vector>
#include <iostream>

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
    double alpha, gamma;
    std::vector<double> z(N);
    size_t i, j;

    /* Cholesky decomposition
        A = L.D.L^t
        lower_diag(L) = gamma
        diag(D) = alpha
    */
    alpha = diag;

    if (alpha == 0) {
    status = 1;
    }

    /* update RHS */
    z[0] = rhs[0];
    for (i = 1; i < N; i++)
    {
        gamma = offdiag / alpha;
        alpha = diag - offdiag*gamma;
        z[i] = rhs[i] - gamma * z[i - 1];
    }

    /* backsubstitution */
    x[N - 1] = z[i] / alpha;
    if (N >= 2){
        for (i = N - 2, j = 0; j <= N - 2; j++, i--){
            x[i] = (z[i] - gamma * x[i + 1]) / alpha;
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


int main(){

    return 0;
}