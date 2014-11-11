import numpy as np 
import matplotlib.pyplot as plt
import sys 
import matplotlib 
from mpl_toolkits.mplot3d import Axes3D

name = sys.argv[1]
data = np.loadtxt(name) 

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

x = np.linspace(0,101,101)
y = np.linspace(0, 121, 121)

for i in range(len(data)):
    
    x = np.linspace(0,101, len(data[i]))
    y = data[i]
    z = [ i for j in range(len(data[i]))]
    
    ax.set_xlabel(" x ")
    ax.set_ylabel("Time")
    ax.set_zlabel("height")
    
    plt.plot(x,z,y)
    plt.title("Triangular wave evolution ")
    plt.savefig("grafica_3D_name.pdf")
    plt.show()
    plt.close()
