import numpy as np
import pylab
import pandas as pd
data = np.transpose(np.genfromtxt('test.csv', delimiter=',')[1:])

print(type(data))
def linear(x,par):
	x=[np.ones(len(x)),x]
	return np.dot(par,x)

def gradient_descent(Y,X,speed,iterations):
	X=np.array([np.ones(len(X)),X])
	Xt=X
	X=np.transpose(X)
	parameters=np.zeros(len(X[0]))
	for i in range (0,iterations):
		loss=np.dot(X,parameters)-Y
		gradient=np.dot(Xt,loss)
		parameters=parameters-speed*gradient
	return parameters

def analitic_fit(Y,X):
	X=np.array([np.ones(len(X)),X])
	X=np.transpose(X)
	temp=np.linalg.inv(np.dot(np.transpose(X),X))
	return np.dot(np.dot(temp,np.transpose(X)),Y)

popt1=gradient_descent(Y,X,1e-8,1000)
popt2=analitic_fit(Y,X)

print(popt1,popt2)
"""
pylab.plot(X,Y,'.')
x=np.linspace(np.amin(X),np.amax(X),100)
pylab.plot(x,linear(x,popt1))
pylab.plot(x,linear(x,popt2))
pylab.show()"""