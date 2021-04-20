import numpy as np
import matplotlib.pyplot as plt
import os.path
from matplotlib.pyplot import figure

#Reading the output
if os.path.exists('rk2Test.txt'):
    N, errX, errY = np.loadtxt('rk2Test.txt', skiprows = 0, unpack = True)
else:
    print("No output file found")
    exit()

#Plot functions
fig, (ax1, ax2) = plt.subplots(2)
ax2.set_xlabel('Log(N)')
ax1.set_ylabel(r'Log($\left| x(t) \,\, deviation \right|$)')
ax2.set_ylabel(r'Log($\left| y(t) \,\, deviation \right|$)')
ax1.plot(np.log10(N),np.log10(errX),'o',markersize=4)
ax2.plot(np.log10(N),np.log10(errY),'o',markersize=4)

plt.savefig('test.pdf')
