from matplotlib import pyplot as plt
import numpy as np
X = np.arange(1,9)
FILES =[] #Mettre les path des fichiers csv à plot
for file in FILES;
    Y = []
    with open("file","r") as file:
        file.readline()
        for line in file.readlines():
            line=line.strip().split(',')
            temp = [float((k[2:].strip('0'))) for k in line if k != ""]
            Y.append(np.mean(temp))
    plt.plot(X,Y)

plt.title("TITLE")
plt.ylabel("Temps d'exécution (s)")
plt.xlabel("Threads")
plt.grid()
plt.legend([],loc='upper right') 
plt.show()
