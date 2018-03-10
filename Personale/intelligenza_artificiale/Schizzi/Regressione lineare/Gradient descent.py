import numpy as np
import pylab
data = np.genfromtxt('test.csv', delimiter=',')

data=np.transpose(data[1:])

X=data[0]
Y=data[1]


def linear(x,par):
	x=[np.ones(len(x)),x]
	return np.dot(par,x)

def gradient_descent(Y,X,speed,iterations):
	X=np.array([np.ones(len(X)),X])
	X=np.transpose(X)
	parameters=np.zeros(len(X[0]))
	for i in range (0,iterations):
		loss=np.dot(X,parameters)-Y
		gradient=np.dot(np.transpose(X),loss)
		parameters=parameters-speed*gradient
	return parameters

def fit_analitico(Y,X):
	X=np.array([np.ones(len(X)),X])
	X=np.transpose(X)
	cos=np.linalg.inv(np.dot(np.transpose(X),X))
	return np.dot(np.dot(cos,np.transpose(X)),Y)

popt1=gradient_descent(Y,X,1e-8,1000)
popt2=fit_analitico(Y,X)

print(popt1,popt2)

pylab.plot(X,Y,'.')
x=np.linspace(np.amin(X),np.amax(X),100)
pylab.plot(x,linear(x,popt1))
pylab.plot(x,linear(x,popt2))
pylab.show()