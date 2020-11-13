import subprocess

results = []
with open("results.csv",'w') as file:
    for k in range(1,100,2):
        print("Calculating " + str(k))
        p = subprocess.Popen('/usr/bin/time ./out '+ str(k),shell=True,stderr=subprocess.PIPE,stdout=subprocess.PIPE)
        file.write(p.stderr.readlines()[0].decode().split()[2][:-7])
        file.write(',')
