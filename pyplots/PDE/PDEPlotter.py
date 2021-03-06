import numpy as np
import matplotlib.pyplot as plt
import os.path
from matplotlib.pyplot import figure
from math import radians
from matplotlib  import cm

flag = 0
if os.path.exists('../../build/output/PDE/f.txt'):
    flag = 1
    x, f0, f1, f2, f4, f8, f16, flast, ftrue = np.loadtxt('../../build/output/PDE/f.txt', skiprows = 0, unpack = True)
    t, err256, err512, err1024 = np.loadtxt('../../build/output/PDE/PDE_2Norm.txt', skiprows = 0, unpack = True)

elif os.path.exists('output/PDE/f.txt'):
    flag = 2
    x, f0, f1, f2, f4, f8, f16, flast, ftrue = np.loadtxt('output/PDE/f.txt', skiprows = 0, unpack = True)
    t, err256, err512, err1024 = np.loadtxt('output/PDE/PDE_2Norm.txt', skiprows = 0, unpack = True)

if(flag):
    fig, (ax1,ax2) = plt.subplots(2, figsize=(6*np.sqrt(2),6))
    ax1.set_title('Crank-Nicolson method results',fontsize=13)
    ax1.plot(x,f0, '-', color='LightBlue', label='u(x,t=0)')
    ax1.plot(x,f1, '-', color='SkyBlue', label='u(x,t=1s) ')
    ax1.plot(x,f2, '-', color='LightSkyBlue', label='u(x,t=2s)')
    ax1.plot(x,f4, '-', color='CornflowerBlue', label='u(x,t=4s)')
    ax1.plot(x,f8, '-', color='RoyalBlue', label='u(x,t=8s)')
    ax1.plot(x,f16, '-', color='MediumBlue', label='u(x,t=16s)')
    ax1.plot(x,flast, '-', color='DarkBlue', label='u(x,t=70s) ')
    ax1.plot(x,ftrue, '-', color='red', label='u analytical')
    ax1.set_xlabel(r'$x$', fontsize = 13)
    ax1.set_ylabel(r'$u(x)$', fontsize = 13)
    ax1.legend()
    plt.subplots_adjust(hspace=.3)


    limitError256 = np.mean(err256[-5:])
    limitError512 = np.mean(err512[-5:])
    limitError1024 = np.mean(err1024[-5:])
    textstr = '\n'.join((
    r'Error ratios in the limit $t\rightarrow\infty$ are 1:%.2f:%.2f' % (limitError512/limitError256,limitError1024/limitError256),
    r'A doubled grid improves the error by a factor 4'
    ))

    plt.yscale('log')
    ax2.plot(t[np.arange(0,len(t),1000)],err256[np.arange(0,len(t),1000)], 'o',markersize=3, color='tab:red', label=r'N = $2^{8}$')
    ax2.plot(t[np.arange(0,len(t),1000)],err512[np.arange(0,len(t),1000)], 'o',markersize=3, color='tab:green', label=r'N = $2^{9}$')
    ax2.plot(t[np.arange(0,len(t),1000)],err1024[np.arange(0,len(t),1000)], 'o',markersize=3, color='tab:blue', label=r'N = $2^{10}$')
    ax2.set_xlabel('Time [s]', fontsize = 13)
    ax2.set_ylabel(r'$\left|\right|{u(x)-u_{a}(x)}\left|\right|_{2}$', fontsize = 13)
    ax2.legend(title='Space divisions')
    ax2.text(0.03, 0.12, textstr, transform=ax2.transAxes, fontsize=12,
        verticalalignment='center') 

    if(flag==1):
        plt.savefig('PDE.pdf')
    else:
        plt.savefig('../pyplots/PDE/PDE.pdf')
    print('Output saved in pyplots/PDE/PDE.pdf')
else:
    print('build/output/PDE/PDE_2Norm.txt NOT FOUND!')
