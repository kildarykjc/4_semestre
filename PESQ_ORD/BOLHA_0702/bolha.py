import matplotlib as mpl
import matplotlib.pyplot as plt
import random 
import timeit

def desenhaGrafico(x,y,y2,xl = "Entradas", yl = "Saídas"):
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111)
    ax.plot(x,y, label = "Lista Aleatória")
    ax.plot(x,y2, label = "Lista Invertida")
    ax.legend(bbox_to_anchor=(1, 1),bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)
    fig.savefig('Grafico_bubble.png')

def geraAleatorio(tam):
    x = list(range(tam))
    random.shuffle(x)
    return x

def bubble(lista):
    for passnum in range(len(lista)-1,0,-1):
        for i in range(passnum):
            if lista[i]>lista[i+1]:
                temp = lista[i]
                lista[i] = lista[i+1]
                lista[i+1] = temp   
    #print(lista)       
    return lista

x = [1000, 20000, 30000, 60000]
#x = [100, 2000, 3000, 6000]
y_aleatorio = []
y_reverso = []
tempo_aleatorio = []
tempo_reverso = []

for i in range(len(x)):
    y_aleatorio.append(geraAleatorio(x[i]))
    lista_reversa = list(range(1, x[i]))
    lista_reversa = lista_reversa[::-1]
    y_reverso.append(lista_reversa)

for i in range(len(x)):
    tempo_aleatorio.append(timeit.timeit("bubble({})".format(y_aleatorio[i]), setup="from __main__ import bubble", number=1))
    tempo_reverso.append(timeit.timeit("bubble({})".format(y_reverso[i]), setup="from __main__ import bubble", number=1))
#print(lista_reversa)

desenhaGrafico(x,tempo_aleatorio,tempo_reverso)