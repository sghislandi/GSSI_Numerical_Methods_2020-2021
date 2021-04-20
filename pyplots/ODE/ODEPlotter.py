import numpy as np
import matplotlib.pyplot as plt
import os.path
from matplotlib.pyplot import figure

#Reading the output
if os.path.exists('../../build/output/ODE/ODE.txt'):
    t, x, y = np.loadtxt('../../build/output/ODE/ODE.txt', skiprows = 0, unpack = True)
else:
    print("No output file found")
    exit()

#Defining the energy
g = 981     #in cm/s**2
L = 10      #in cm
E = np.array(g*L*(1-np.cos(x)) + 0.5*y*y*L*L)/1000    #in kerg/g
Emean = np.cumsum(E,axis=0)
#Emean = Emean / np.arange(1,len(E)+1)

#Plots
fig, (ax1, ax2, ax3) = plt.subplots(3, figsize=(10,10))
ax3.set_xlabel('Time [s]')
ax1.set_ylabel(r'$\theta$ [rad]')
ax2.set_ylabel(r'$\omega$ [Hz]')
ax3.set_ylabel(r'Energy [$\frac{kerg}{g}$]')
ax1.plot(t,x,'o',markersize=2)
ax2.plot(t,y,'o',markersize=2)
ax3.plot(t,E,'o',markersize=2)
#ax3.plot(t,Emean,'o',markersize=2, color='orange')

#Fit
energyFit = np.polyfit(t, E, 1)
ax3.plot(t,energyFit[0]*t+energyFit[1],'-',c='orange',linewidth=3)
results = '\n'.join((
    r'$E = mt+q$',
    'm = {:.3e}'.format(energyFit[0]),
    'q = {:.3f}'.format(energyFit[1])))


#Text box with fit results
props = dict(boxstyle='round', alpha=0.5, color='orange')
ax3.text(0.78, 0.35, results, transform=ax3.transAxes, fontsize=14,
        verticalalignment='top', bbox=props)



plt.savefig('ODE.pdf')

 
