import numpy as np
import matplotlib.pyplot as plt

try:
    try: 
        N, err = np.loadtxt('../../build/output/simpson_integration/simpson_approximation_errors_v1.txt', skiprows = 1, unpack = True)
    except:
        N, err = np.loadtxt('../../build/output/simpson_integration/simpson_approximation_errors.txt', skiprows = 1, unpack = True)
except: 
    print("No output file found")
    exit()

<<<<<<< HEAD
plt.plot(2**N,np.abs(err),'o')
plt.title('Simpson rule integral approximation error')
plt.xscale('log',base=2)
=======
plt.plot(N,np.abs(err),'o')
plt.title('Simpson method approximation error')
plt.xscale('log')
>>>>>>> 4ddecfb5dea0b20fc262630c2acec7ebe1a61f07
plt.yscale('log')
plt.xlabel('Number of divisions')
plt.ylabel(r'$\left|I_{Simpson} - I\right|$')

plt.savefig('simpson_approximation_errors.pdf')
print("Output saved as simpson_approximation_errors.pdf")
