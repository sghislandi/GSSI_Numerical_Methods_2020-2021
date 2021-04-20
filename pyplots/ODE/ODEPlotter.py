import numpy as np
import matplotlib.pyplot as plt
import os.path

#Reading the output
if os.path.exists('../../build/output/ODE/ODE.txt'):
    t, x, y = np.loadtxt('../../build/output/ODE/ODE.txt', skiprows = 0, unpack = True)
else:
    print("No output file found")
    exit()



#Plots
fig, (ax1, ax2) = plt.subplots(2)
ax2.set_xlabel('Time [s]')
ax1.set_ylabel(r'$\theta$ [rad]')
ax2.set_ylabel(r'$\omega$ [Hz]')
ax1.plot(t,x,'o',markersize=2)
ax2.plot(t,y,'o',markersize=2)


plt.savefig('ODE.pdf')

 
