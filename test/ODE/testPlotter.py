import numpy as np
import matplotlib.pyplot as plt
import os.path
from matplotlib.pyplot import figure

#Reading the output
if os.path.exists('rk2Test.txt'):
    t, errX, errY = np.loadtxt('rk2Test.txt', skiprows = 0, unpack = True)
else:
    print("No output file found")
    exit()

#Plot functions
fig, (ax1, ax2) = plt.subplots(2, figsize=(10,10))
ax2.set_xlabel('Time')
ax1.set_ylabel('errX')
ax2.set_ylabel('errY')
ax1.plot(np.log10(t),np.log10(errX),'o',markersize=4)
ax2.plot(np.log10(t),np.log10(errY),'o',markersize=4)

plt.savefig('test.pdf')

 
