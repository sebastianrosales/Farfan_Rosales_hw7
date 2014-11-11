import matplotlib.pyplot as plt
import numpy as np
import sys

if len(sys.argv) != 2:
    print "Este programa necesita un (1) argumento para funcionar"
    sys.exit()


filename=sys.argv[1]
pimp=np.loadtxt(filename)

x=pimp[:,0]
v=pimp[:,1]
p=pimp[:,2]
r=pimp[:,3]

# Simple data to display in various forms
y = np.sin(x ** 2)

plt.close('all')

# Two subplots, the axes array is 1-d
f, axarr = plt.subplots(3, sharex=True)
axarr[0].plot(x, v)
axarr[0].set_title('Velocidad')
axarr[1].plot(x, p)
axarr[1].set_title('Presion')
axarr[2].plot(x, r)
axarr[2].set_title('Densidad')

filename = filename[:-4]
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()
plt.show()
