
import matplotlib as mpl
import matplotlib.pyplot as plt
import random 
import timeit
import sys
sys.setrecursionlimit(10**8)
def desenhaGrafico(x,y,y2,xl = "Entradas", yl = "Saídas"):
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111)
    ax.plot(x,y, label = "Lista Aleatória")
    ax.plot(x,y2, label = "Lista Invertida")
    ax.legend(bbox_to_anchor=(1, 1),bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)
    fig.savefig('Grafico_shell.png')

def geraAleatorio(tam):
    x = list(range(tam))
    #random.shuffle(x)
    return x

def shell(alist):
    sublistcount = len(alist)//2
    while sublistcount > 0:
      for start_position in range(sublistcount):
        gap_InsertionSort(alist, start_position, sublistcount)

      

      sublistcount = sublistcount // 2

def gap_InsertionSort(nlist,start,gap):
    for i in range(start+gap,len(nlist),gap):

        current_value = nlist[i]
        position = i

        while position>=gap and nlist[position-gap]>current_value:
            nlist[position]=nlist[position-gap]
            position = position-gap

        nlist[position]=current_value




x = [30000,40000,50000,60000,70000]
#x = [100, 200, 300, 600]
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
    tempo_aleatorio.append(timeit.timeit("shell({})".format(y_aleatorio[i]), setup="from __main__ import shell", number=1))
    tempo_reverso.append(timeit.timeit("shell({})".format(y_reverso[i]), setup="from __main__ import shell", number=1))
print(sys.getrecursionlimit())


desenhaGrafico(x,tempo_aleatorio,tempo_reverso)

