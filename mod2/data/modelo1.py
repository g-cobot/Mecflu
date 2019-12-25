    # -*- coding: utf-8 -*-
"""
Created on Mon Sep 23 15:29:49 2019

@author: laura
"""
import numpy as np
import matplotlib.pyplot as plt
r=0.15 			#[m] 		Raio do disco
A=np.pi*r**2 	#[m^2] 		Area do disco
Po=101325
rho=[1.2928]
t=[0]
i=0
Vol=[1*A]
k=Po*Vol[i]	#[Pa.m^3] 	Constante do modelo do gás ideal supondo T cte (nRT)
m_g=rho[i]*Vol[i]
F=[Po*A]
Zi=.9;
Z=[.9];
v=0.21;
tf=0.2;#(.9/v)/50
dt=0.0001
t=[0]
i=0
f= open("data.txt","w+")
print("Calculando :\n")
while (tf-t[i]>0.1):
    i+=1
    t.append(t[i-1]+dt)
    rho.append(1.2928/(1-0.01*t[i]))
    Vol.append( m_g/rho[i])
    F.append( A*k/Vol[i] )
    Z.append( Zi-v*t[i])
    print("t= %f z= %f  \n" % (t[i],Z[i]))
    f.write("%f %f \n"  % (Z[i], t[i]) )

f.close() 


#plt.plot(t,F)
#plt.grid()
#plt.xlabel("Tempo [s]")
#plt.ylabel("Força [N]")
#plt.title("1º Modelo")
#plt.show()

#plt.plot(t,rho)
#plt.grid()
#plt.xlabel("Tempo [s]")
#plt.ylabel("Massa Específica [$kg/m^3$]")
#plt.title("1º Modelo")
#plt.show()
