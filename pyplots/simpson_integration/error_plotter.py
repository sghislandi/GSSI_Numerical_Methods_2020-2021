import numpy as np
import matplotlib.pyplot as plt

#Reading the output
try:
    try: 
        N, deviation = np.loadtxt('../../build/output/simpson_integration/simpson_approximation_errors_v1.txt', skiprows = 1, unpack = True)
    except:
        N, deviation = np.loadtxt('../../build/output/simpson_integration/simpson_approximation_errors.txt', skiprows = 1, unpack = True)
except: 
    print("No output file found")
    exit()

#Fixed quantities
a = 0
b = 2
third_derivative_a = 0
third_derivative_b = 48

#Error from theory
theoretical_error = 1/90*(third_derivative_b-third_derivative_a)*((b-a)/(2**N))**4

#Error computed trhough the difference between I(N) and I(2N)
approximated_error= [None] * (deviation.size-1)
for i in range(0,deviation.size-1):
    approximated_error[i] = 1/15*(deviation[i+1]-deviation[i])

#Plots
plt.plot(2**N,np.abs(deviation),'o', label = r'$\left| \widetilde{I} - I \right|$')
plt.plot(2**N,theoretical_error,'o', color = 'red', label = 'Error from theory')
plt.plot(2**N[:-1],approximated_error,'o',label = 'Numerical error' )
plt.xscale('log',base=2)
plt.xlabel('Number of divisions')
plt.ylabel('Value')
plt.yscale('log')
plt.legend()

plt.savefig('simpson_approximation_errors.pdf')
print("Output saved as simpson_approximation_errors.pdf")
