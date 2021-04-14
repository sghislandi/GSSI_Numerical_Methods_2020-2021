import numpy as np
import matplotlib.pyplot as plt

N, err = np.loadtxt('../output/simpson_integration/simpson_approximation_errors.txt', skiprows = 1, unpack = True)

plt.plot(N,np.abs(err),'o')
plt.title('Simpson rule integral approximation error')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Number of divisions')
plt.ylabel('Error')

plt.savefig('../output/simpson_integration/simpson_approximation_errors.pdf')