import numpy as np
import matplotlib.pyplot as plt
import os.path
from matplotlib.pyplot import figure
from math import radians
from matplotlib  import cm

#Defining the energy
alpha0 = 179
g = 981     #in cm/s**2
L = 10      #in cm
correctE = g*L*(1-np.cos(radians(alpha0)))/1000       #in kerg/g

#Reading the output
if os.path.exists('../../build/output/ODE/ODE.txt'):
    t, x, y = np.loadtxt('../../build/output/ODE/ODE.txt', skiprows = 0, unpack = True)
    #Plots
    E = np.array(g*L*(1-np.cos(x)) + 0.5*y*y*L*L)/1000    #in kerg/g
    fig, (ax1, ax2, ax3) = plt.subplots(3, figsize=(10,10))
    ax1.set_title('Runge-Kutta with fixed time step', fontsize=17)
    plt.subplots_adjust(hspace=.2)
    ax3.set_xlabel('Time [s]', fontsize=15)
    ax1.set_ylabel(r'$\theta$ [rad]', fontsize=15)
    ax2.set_ylabel(r'$\omega$ [Hz]', fontsize=15)
    ax3.set_ylabel(r'Energy [$\frac{kerg}{g}$]', fontsize=15)
    ax1.plot(t,x,'o',markersize=2, color='tab:red')
    ax2.plot(t,y,'o',markersize=2, color='tab:green')
    ax3.plot(t,E,'o',markersize=2, color='tab:blue', label='RK energy')
    ax3.hlines(correctE, t[0], t[-1], linewidth=2, color='tab:orange', linestyle='dashed', label='Correct energy')
    ax3.legend(loc='lower right')

    plt.savefig('ODE.pdf')
else:
    print("../../build/output/ODE/ODE.txt not found")

#Reading the output with adaptive step size method
if os.path.exists('../../build/output/ODE/ODE_Adaptive.txt'):
    t, x, y = np.loadtxt('../../build/output/ODE/ODE_Adaptive.txt', skiprows = 0, unpack = True)
    #Plots
    E = np.array(g*L*(1-np.cos(x)) + 0.5*y*y*L*L)/1000    #in kerg/g
    figAdaptive, (ax1Adaptive, ax2Adaptive, ax3Adaptive) = plt.subplots(3, figsize=(10,10))
    ax1Adaptive.set_title('Runge-Kutta with adaptive step size method', fontsize=17)
    plt.subplots_adjust(hspace=.2)
    ax3Adaptive.set_xlabel('Time [s]', fontsize=15)
    ax1Adaptive.set_ylabel(r'$\theta$ [rad]', fontsize=15)
    ax2Adaptive.set_ylabel(r'$\omega$ [Hz]', fontsize=15)
    ax3Adaptive.set_ylabel(r'Energy [$\frac{kerg}{g}$]', fontsize=15)
    ax1Adaptive.plot(t,x,'o',markersize=2, color='tab:red')
    ax2Adaptive.plot(t,y,'o',markersize=2, color='tab:green')
    ax3Adaptive.plot(t,E,'o',markersize=2, color='tab:blue', label='RK energy')
    ax3Adaptive.hlines(correctE, t[0], t[-1], linewidth=2, color='tab:orange', linestyle='dashed', label='Correct energy')
    ax3Adaptive.legend(loc='lower right')

    plt.savefig('ODE_Adaptive.pdf')
else:
    print("../../build/output/ODE/ODE_Adaptive.txt not found")

