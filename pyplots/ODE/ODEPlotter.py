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
plt.plot(t,x,'o',markersize=5)


plt.savefig('ODE.pdf')

 
