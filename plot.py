from matplotlib import pyplot as plt
import numpy as np

fig = plt.figure()
results = []
with open("results.txt",'r') as file:
    for line in file.readlines():
        if line == " ":
            continue
        results.append(line[2:].strip())
Y = [k for k in range(1,101,2)]
X = results

plt.plot(Y,X)
plt.yticks(np.linspace(0.0,6.0,12))
plt.show()
print("END")