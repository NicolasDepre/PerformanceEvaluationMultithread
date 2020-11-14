from matplotlib import pyplot as plt
import numpy as np

Y = []
with open("results.csv","r") as file:
    file.readline()
    for line in file.readlines():
        line=line.strip().split(',')
        temp = [float((k[2:].strip('0'))) for k in line if k != ""]
        Y.append(np.mean(temp))

print(Y)
X = np.arange(1,21)
plt.plot(X,Y)
plt.show()
