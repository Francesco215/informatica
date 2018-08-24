import csv
import numpy as np

with open('speed_gender_height.csv') as csvfile:
	readCVS=csv.reader(csvfile,delimiter=',')
	i=0
	dati=[]
	for row in readCVS:
		speed=row[1]
		height=row[3]
		sex=row[2]
		if sex=='female': sex='1'
		if sex=='male':sex='0'
		dati.append([speed,height,sex])
		i=i+1

dati=dati[1:]
dati=np.asarray(dati)
dati=dati.astype('float')


