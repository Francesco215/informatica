import numpy as np
import pylab

data = np.genfromtxt('dati.csv', delimiter=',')
Y=np.transpose(data[1:])[1:][0]
X=np.arange(len(Y))


def gradient_descent(Y,X,x,speed,iterations,tau):
	Xt=[np.ones(len(X)),X]
	X=np.transpose(Xt)
	parametri=np.zeros(len(X[0]))#deve avere la lunghezza uguale alla larghezza di X
	gradient=np.zeros(len(parametri))
	sigma=np.zeros(len(Y))
	loss=sigma
	for k in range(0,iterations):
		for j in range(0,len(parametri)):
			for i in range(1,len(Y)):
				sigma[i]=np.exp(np.linalg.norm(X[i][1:]-x)/tau)
				loss[i]=np.dot(X[i],parametri)
				gradient[j]=simga_i*np.dot(X,loss)
				parametri=parametri+speed*gradient
