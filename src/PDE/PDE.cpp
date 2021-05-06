#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

double uAnalytical(double x){
    return std::cos(M_PI*x/2.);
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