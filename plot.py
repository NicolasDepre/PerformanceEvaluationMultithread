from matplotlib import pyplot as plt
import numpy as np

Y = []
with open("c-presults.csv","r") as file:
    file.readline()
    for line in file.readlines():
        print(line)
        line=line.strip().split(',')
        temp = [float((k[2:].strip('0'))) for k in line if k != ""]
        Y.append(np.mean(temp))
print("y:")
print(Y)
X = np.arange(1,17)

plt.figure()
plt.plot(X,Y)
plt
plt.show()
