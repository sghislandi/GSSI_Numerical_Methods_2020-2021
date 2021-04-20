from tkinter import *
import math
import numpy as np
import os.path
 
########################################################
#Reading the output
if os.path.exists('../../build/output/ODE/ODE.txt'):
    t, x, y = np.loadtxt('../../build/output/ODE/ODE.txt', skiprows = 0, unpack = True)
else:
    print("No output file found")
    exit()
########################################################

deltaT = int((t[1]-t[0])*1000)

class Animation:
    def __init__(self, gw):
        self.window = gw
        self.xoff, self.yoff = 300, 300
        self.angle = 150*math.pi/180
        self.sina = math.sin(self.angle)
        self.cosa = math.cos(self.angle)
        self.rodLength = 150
        self.bobRadius = 15
        self.bobCenter = self.rodLength + self.bobRadius
        self.rodx0, self.rody0 = self.xoff, self.yoff
        self.rx1 = self.rodx0
        self.ry1 = self.rody0
        self.rx2 = self.xoff + self.rodLength*self.sina
        self.ry2 = self.yoff + self.rodLength*self.cosa
        self.bx1 = self.xoff - self.bobRadius + self.bobCenter*self.sina
        self.by1 = self.yoff - self.bobRadius + self.bobCenter*self.cosa
        self.bx2 = self.xoff + self.bobRadius + self.bobCenter*self.sina
        self.by2 = self.yoff + self.bobRadius + self.bobCenter*self.cosa
        self.step = 0
        self.actualTime = 0
        self.xText = 500
        self.yText = 20
 
        # create / fill canvas:
        self.cnv = Canvas(gw, bg='white')
        self.cnv.pack(fill=BOTH, expand=True)
 
        radius = 4
        self.cnv.create_oval(300-radius, 300-radius,
                             300+radius, 300+radius,
                             fill='black')    
 
        self.bob = self.cnv.create_oval(self.bx1,
                                        self.by1,
                                        self.bx2,
                                        self.by2,
                                        fill='red',
                                        width=2)
 
        self.rod = self.cnv.create_line(self.rx1,
                                        self.ry1,
                                        self.rx2,
                                        self.ry2,
                                        fill='black',
                                        width=4)
                                    
        self.time = self.cnv.create_text(self.xText,
                                         self.yText,
                                         font=("courier", 15, "bold"),
                                         text='Time = 0 s')
 
        self.animate()


 
    def animate(self):

        self.angle = x[self.step]
        self.sina = math.sin(self.angle)
        self.cosa = math.cos(self.angle)
        self.rx1 = self.rodx0
        self.ry1 = self.rody0
        self.rx2 = self.xoff + self.rodLength*self.sina
        self.ry2 = self.yoff + self.rodLength*self.cosa
        self.bx1 = self.xoff - self.bobRadius + self.bobCenter*self.sina
        self.by1 = self.yoff - self.bobRadius + self.bobCenter*self.cosa
        self.bx2 = self.xoff + self.bobRadius + self.bobCenter*self.sina
        self.by2 = self.yoff + self.bobRadius + self.bobCenter*self.cosa
        self.cnv.itemconfigure(self.time, text= 'Time = {:.1f} s'.format(t[self.step]))
        self.actualTime = t[self.step]
        self.step += 1
 
        self.cnv.coords(self.rod,
                        self.rx1,
                        self.ry1,
                        self.rx2,
                        self.ry2)
        self.cnv.coords(self.bob,
                        self.bx1,
                        self.by1,
                        self.bx2,
                        self.by2)
        self.window.update()
        if self.step < len(x):
            self.cnv.after(deltaT, self.animate)
        else:
            exit()

 
root = Tk()
root.title('Pendulum')
root.geometry('600x600+100+50')
root.resizable(False, False)
a = Animation(root)
root.mainloop() 
