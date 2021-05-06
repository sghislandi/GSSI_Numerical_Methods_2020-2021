import numpy as np
import matplotlib.pyplot as plt
import os.path

#Reading the output
flag = 0
if os.path.exists('../../build/output/simpson_integration/simpson_approximation_errors_v1.txt'):
    flag = 1
    N, deviation = np.loadtxt('../../build/output/simpson_integration/simpson_approximation_errors_v1.txt', skiprows = 1, unpack = True)
elif os.path.exists('output/simpson_integration/simpson_approximation_errors_v1.txt'):
    flag = 2
    N, deviation = np.loadtxt('output/simpson_integration/simpson_approximation_errors_v1.txt', skiprows = 1, unpack = True)
elif os.path.exists('../../build/output/simpson_integration/simpson_approximation_errors.txt'):
    flag = 3
    N, deviation = np.loadtxt('../../build/output/simpson_integration/simpson_approximation_errors.txt', skiprows = 1, unpack = True)
elif os.path.exists('output/simpson_integration/simpson_approximation_errors.txt'):
    flag = 4
    N, deviation = np.loadtxt('output/simpson_integration/simpson_approximation_errors.txt', skiprows = 1, unpack = True)
else:
    print("No output file found")
    exit()

#Fixed quantities
a = 0
b = 2
third_derivative_a = 0
third_derivative_b = 48

#Error computed as I_simpson - I_exact
log_deviation = np.log10(abs(deviation))

#Error from theory
log_theoretical_error = np.log10(1/90*(third_derivative_b-third_derivative_a)*((b-a)/(2**N))**4)

#Error computed trhough the difference between I(N) and I(2N)
log_approximated_error= [None] * (deviation.size-1)
for i in range(0,deviation.size-1):
    log_approximated_error[i] = np.log10(1/15*(abs(deviation[i+1]-deviation[i])))

#Definition of useful quantities
N = 2**N
logN = np.log10(N)

#Plots
plt.plot(logN,log_deviation,'o',markersize=5, label = r'$\left| \widetilde{I} - I \right|$')
plt.plot(logN,log_theoretical_error,'o', markersize=5, color = 'red', label = 'Error from theory')
plt.plot(logN[1:],log_approximated_error,'o', markersize=5, label = 'Numerical error' )
plt.xlabel('Log(N)')
plt.ylabel('Log(value)')
plt.legend()

fit_deviation = np.polyfit(logN[0:10], log_deviation[0:10], 1)
fit_theoretical_error = np.polyfit(logN[0:10], log_theoretical_error[0:10], 1)
fit_approximated_error = np.polyfit(logN[0:10], log_approximated_error[0:10], 1)

print('**********************')
print('PYTHON SCRIPT RESULTS:')
print(f'Deviation slope = {fit_deviation[0]}')
print(f'Theoretical slope = {fit_theoretical_error[0]}')
print(f'Approximated slope = {fit_approximated_error[0]}')
print('**********************')

if(flag == 1 or flag == 3):
    plt.savefig('simpson_approximation_errors.pdf')
else:
    plt.savefig('../pyplots/simpson_integration/simpson_approximation_errors.pdf')

<<<<<<< HEAD
print("\nOutput saved in pyplots/simpson_approximation_errors.pdf")
=======
print("\nCreated plot at pyplots/simpson_integration/simpson_approximation_errors.pdf")
>>>>>>> 0f29f68ab4eca07e61e77ae6e3c3984178e08723
