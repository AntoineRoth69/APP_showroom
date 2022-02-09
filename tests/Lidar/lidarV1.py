import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
from rplidar import RPLidar

lidar = RPLidar('/dev/ttyUSB0')

distance=[]
angle=[]

fig = plt.figure()
ax = fig.add_subplot(111, projection='polar')
line, = ax.plot(angle, distance)

def Mesures(k,Q):
    for i, scan in enumerate(lidar.iter_scans()):
        print('%d: Got %d measurments' % (i+1, len(scan)))
        for j in range(len(scan)):
            if scan[j][0] > Q:
                distance.append(scan[j][2])
                angle.append(scan[j][1])
        if i > k-2:
            break
    return distance, angle



def func_animate():
    D, A = Mesures(1,10)
    line.set_data(A, D)
    
    return line,



L=func_animate()
D, A = Mesures(1,10)

ax.scatter(A, D ,1)
#ax.set_xticks(np.arange(0,2.0*np.pi,np.pi/6.0))

ani = FuncAnimation(fig,
                    L,
                    frames=10,
                    interval=50)







#ani.save(r'animation.gif', fps=10)

plt.show()

    
    
